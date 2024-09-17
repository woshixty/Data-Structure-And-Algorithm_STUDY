#include "ScreenCapture.h"
#include "ScreenCapture_C_API.h"
#include "internal/SCCommon.h" //DONT USE THIS HEADER IN PRODUCTION CODE!!!! ITS INTERNAL FOR A REASON IT WILL CHANGE!!! ITS HERE FOR TESTS ONLY!!!
#include <algorithm>
#include <atomic>
#include <chrono>
#include <climits>
#include <iostream>
#include <locale>
#include <string>
#include <thread>
#include <vector>

// THESE LIBRARIES ARE HERE FOR CONVINIENCE!! They are SLOW and ONLY USED FOR
// HOW THE LIBRARY WORKS!
#define TJE_IMPLEMENTATION
#include "tiny_jpeg.h"
#define LODEPNG_COMPILE_PNG
#define LODEPNG_COMPILE_DISK
#include "lodepng.h"
/////////////////////////////////////////////////////////////////////////

// 测试将图像数据从非连续格式复制到连续格
// - 创建一个256x256像素的图像，每个像素的颜色值为VALID。
// - 将图像数据复制到一个连续的字节数组中。
// - 验证复制是否正确。
void TestCopyContiguous()
{

    constexpr auto VALID(static_cast<unsigned char>(0xFF));
    constexpr auto INVALID(static_cast<unsigned char>(0xFE));
    constexpr auto PIXEL_DEPTH(sizeof(SL::Screen_Capture::ImageBGRA));
    constexpr unsigned WIDTH(256), HEIGHT(256);

    std::vector<SL::Screen_Capture::ImageBGRA> strided;

    for (unsigned row(0); row < HEIGHT; ++row) {
        for (unsigned col(0); col < WIDTH; ++col) {
            strided.push_back(SL::Screen_Capture::ImageBGRA{VALID, VALID, VALID, VALID});
        }
    }

    auto bytes = strided.size() * PIXEL_DEPTH;
    std::vector<unsigned char> contiguous(bytes, static_cast<unsigned char>(0));
    auto image = SL::Screen_Capture::Image{{0, 0, WIDTH, HEIGHT}, 0, true, strided.data()};

    auto result = SCL_Utility_CopyToContiguous(contiguous.data(), &image);
    auto distance = std::distance(contiguous.data(), static_cast<unsigned char *>(result));

    if (distance != (WIDTH * HEIGHT * PIXEL_DEPTH))
        std::abort();

    auto const begin(contiguous.begin()), end(contiguous.end());

    for (auto current(begin); current != end; ++current) {
        if (*current != VALID)
            std::abort();
    }
}

// 测试处理非连续内存布局的图像数据
// - 在每行图像数据后添加填充。
// - 验证复制是否正确，只复制有效数据，不包括填充。
void TestCopyNonContiguous()
{

    constexpr auto VALID(static_cast<unsigned char>(0xFF));
    constexpr auto INVALID(static_cast<unsigned char>(0xFE));
    constexpr auto PIXEL_DEPTH(sizeof(SL::Screen_Capture::ImageBGRA));
    constexpr unsigned WIDTH(256), HEIGHT(256), PADDING(64), STRIDE_IN_BYTES((WIDTH + PADDING) * PIXEL_DEPTH);

    std::vector<SL::Screen_Capture::ImageBGRA> strided;

    for (unsigned row(0); row < HEIGHT; ++row) {

        for (unsigned col(0); col < WIDTH; ++col) {
            strided.push_back(SL::Screen_Capture::ImageBGRA{VALID, VALID, VALID, VALID});
        }

        for (unsigned pad(0); pad < PADDING; ++pad) {
            strided.push_back(SL::Screen_Capture::ImageBGRA{INVALID, INVALID, INVALID, INVALID});
        }
    }

    auto bytes = strided.size() * PIXEL_DEPTH;
    std::vector<unsigned char> contiguous(bytes, static_cast<unsigned char>(0));
    auto image = SL::Screen_Capture::Image{{0, 0, WIDTH, HEIGHT}, STRIDE_IN_BYTES, false, strided.data()};

    auto result = SCL_Utility_CopyToContiguous(contiguous.data(), &image);
    auto distance = std::distance(contiguous.data(), static_cast<unsigned char *>(result));

    // Ensures that the pointer incremented by only the amount written.
    if (distance != (WIDTH * HEIGHT * PIXEL_DEPTH))
        std::abort();

    auto const begin(contiguous.begin());
    auto contiguousEnd(begin), absoluteEnd(contiguous.end());

    std::advance(contiguousEnd, WIDTH * HEIGHT * PIXEL_DEPTH);

    for (auto current(begin); current != contiguousEnd; ++current) {
        if (*current != VALID)
            std::abort();
    }

    for (auto current(contiguousEnd); current != absoluteEnd; ++current) {
        if (*current != 0)
            std::abort();
    }
}

// 将图像数据转换为RGBA格式
// - 遍历图像，将BGRA格式转换为RGBA格式。
// - 将alpha通道设置为0。
void ExtractAndConvertToRGBA(const SL::Screen_Capture::Image &img, unsigned char *dst, size_t dst_size)
{
    assert(dst_size >= static_cast<size_t>(SL::Screen_Capture::Width(img) * SL::Screen_Capture::Height(img) * sizeof(SL::Screen_Capture::ImageBGRA)));
    auto imgsrc = StartSrc(img);
    auto imgdist = dst;
    for (auto h = 0; h < Height(img); h++) {
        auto startimgsrc = imgsrc;
        for (auto w = 0; w < Width(img); w++) {
            *imgdist++ = imgsrc->R;
            *imgdist++ = imgsrc->G;
            *imgdist++ = imgsrc->B;
            *imgdist++ = 0; // alpha should be zero
            imgsrc++;
        }
        imgsrc = SL::Screen_Capture::GotoNextRow(img, startimgsrc);
    }
}

using namespace std::chrono_literals;
std::shared_ptr<SL::Screen_Capture::IScreenCaptureManager> framgrabber;
std::atomic<int> realcounter;
std::atomic<int> onNewFramecounter;

inline std::ostream &operator<<(std::ostream &os, const SL::Screen_Capture::ImageRect &p)
{
    return os << "left=" << p.left << " top=" << p.top << " right=" << p.right << " bottom=" << p.bottom;
}
inline std::ostream &operator<<(std::ostream &os, const SL::Screen_Capture::Monitor &p)
{
    return os << "Id=" << p.Id << " Index=" << p.Index << " Height=" << p.Height << " Width=" << p.Width << " OffsetX=" << p.OffsetX
              << " OffsetY=" << p.OffsetY << " Name=" << p.Name;
}

// 创建一个捕获所有监视器的抓取器。
// - 获取所有监视器。
// - 设置帧和鼠标变化的处理逻辑。
// - 每秒输出一次帧率。
auto onNewFramestart = std::chrono::high_resolution_clock::now();
void createframegrabber()
{
    realcounter = 0;
    onNewFramecounter = 0;
    framgrabber = nullptr;
    // 获取所有可用的监视器
    framgrabber =
        SL::Screen_Capture::CreateCaptureConfiguration([]() {
            auto mons = SL::Screen_Capture::GetMonitors();
            std::cout << "Library is requesting the list of monitors to capture!" << std::endl;
            for (auto &m : mons) {
                std::cout << m << std::endl;
            }
            return mons;
        })
            ->onFrameChanged([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) {
                // std::cout << "Difference detected!  " << img.Bounds << std::endl;
                // Uncomment the below code to write the image to disk for debugging
                /*
                        auto r = realcounter.fetch_add(1);
                        auto s = std::to_string(r) + std::string("MONITORDIF_") + std::string(".jpg");
                        auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);
                         auto imgbuffer(std::make_unique<unsigned char[]>(size));
                         ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
                         tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char*)imgbuffer.get());
                */
            })
            ->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) {
                // Uncomment the below code to write the image to disk for debugging

                //auto r = realcounter.fetch_add(1);
                //auto s = std::to_string(r) + std::string("MONITORNEW_") + std::string(".jpg");
                //auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);
                //auto imgbuffer(std::make_unique<unsigned char[]>(size));
                //ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
                //tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char *)imgbuffer.get());

                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - onNewFramestart).count() >= 1000) {
                    std::cout << "onNewFrame fps" << onNewFramecounter << std::endl;
                    onNewFramecounter = 0;
                    onNewFramestart = std::chrono::high_resolution_clock::now();
                }
                onNewFramecounter += 1;
            })
            ->onMouseChanged([&](const SL::Screen_Capture::Image *img, const SL::Screen_Capture::MousePoint &mousepoint) {
                // Uncomment the below code to write the image to disk for debugging
                /*
                        auto r = realcounter.fetch_add(1);
                        auto s = std::to_string(r) + std::string(" M") + std::string(".png");
                        if (img) {
                            std::cout << "New mouse coordinates  AND NEW Image received."
                                      << " x= " << mousepoint.Position.x << " y= " << mousepoint.Position.y << std::endl;
                            lodepng::encode(s, (unsigned char *)StartSrc(*img), Width(*img), Height(*img));
                        }
                        else {
                            std::cout << "New mouse coordinates received."
                                      << " x= " << mousepoint.Position.x << " y= " << mousepoint.Position.y
                                      << " The mouse image is still the same as the last " << std::endl;
                        }

                */
                std::cout << "New mouse coordinates received.\n";
            })
            ->start_capturing();

    framgrabber->setFrameChangeInterval(std::chrono::milliseconds(100));
    framgrabber->setMouseChangeInterval(std::chrono::milliseconds(100));
}

// 创建一个只捕获部分监视器的抓取器。
void createpartialframegrabber()
{
    realcounter = 0;
    onNewFramecounter = 0;
    framgrabber = nullptr;
    framgrabber =
        SL::Screen_Capture::CreateCaptureConfiguration([]() {
            auto mons = SL::Screen_Capture::GetMonitors();
            auto newmons = std::vector<SL::Screen_Capture::Monitor>();
            std::cout << "Library is requesting the list of monitors to capture!" << std::endl;
            for (auto &m : mons) {
                if (SL::Screen_Capture::Height(m) >= 512 * 2 && SL::Screen_Capture::Width(m) >= 512 * 2) {
                    SL::Screen_Capture::Height(m, 512);
                    SL::Screen_Capture::Width(m, 512);
                    std::cout << m << std::endl;
                    newmons.push_back(m);
                }
            }
            return newmons;
        })
            ->onFrameChanged([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) {
                // Uncomment the below code to write the image to disk for debugging
                // std::cout << "Difference detected!  " << img.Bounds << std::endl;
                /*
                  auto r = realcounter.fetch_add(1);
                  auto s = std::to_string(r) + std::string("MONITORDIF_") + std::string(".jpg");
                  auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);
                   auto imgbuffer(std::make_unique<unsigned char[]>(size));
                   ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
                   tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char*)imgbuffer.get());
              */
            })
            ->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) {
                // Uncomment the below code to write the image to disk for debugging

                /*
                auto r = realcounter.fetch_add(1);
                 auto s = std::to_string(r) + std::string("MONITORNEW_") + std::string(".jpg");
                 auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);
                 assert(Height(img) == 512);
                 assert(Width(img) == 512);
                  auto imgbuffer(std::make_unique<unsigned char[]>(size));
                  ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
                  tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char*)imgbuffer.get());
                  */

                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - onNewFramestart).count() >=
                    1000) {
                    std::cout << "onNewFrame fps" << onNewFramecounter << std::endl;
                    onNewFramecounter = 0;
                    onNewFramestart = std::chrono::high_resolution_clock::now();
                }
                onNewFramecounter += 1;
            })
            ->onMouseChanged([&](const SL::Screen_Capture::Image *img, const SL::Screen_Capture::MousePoint &mousepoint) {
                // Uncomment the below code to write the image to disk for debugging
                /*
                auto r = realcounter.fetch_add(1);
                auto s = std::to_string(r) + std::string(" M") + std::string(".png");
                if (img) {
                    std::cout << "New mouse coordinates AND NEW Image received."
                              << " x= " << mousepoint.Position.x << " y= " << mousepoint.Position.y << std::endl;
                    lodepng::encode(s, (unsigned char *)StartSrc(*img), Width(*img), Height(*img));
                }
                else {
                    std::cout << "New mouse coordinates received."
                              << " x= " << mousepoint.Position.x << " y= " << mousepoint.Position.y
                              << " The mouse image is still the same as the last" << std::endl;
                }
                */
            })
            ->start_capturing();

    framgrabber->setFrameChangeInterval(std::chrono::milliseconds(100));
    framgrabber->setMouseChangeInterval(std::chrono::milliseconds(100));
}


auto getWindowToCapture(std::string window_to_search_for = "blizzard")
{
    auto windows = SL::Screen_Capture::GetWindows(); 
    // convert to lower case for easier comparisons
    std::transform(window_to_search_for.begin(), window_to_search_for.end(), window_to_search_for.begin(),
                   [](char c) { return std::tolower(c, std::locale()); });
    decltype(windows) filtereditems;
    for (auto &a : windows) {
        std::string name = a.Name;
        std::transform(name.begin(), name.end(), name.begin(), [](char c) { return std::tolower(c, std::locale()); });
        if (name.find(window_to_search_for) != std::string::npos) {
            filtereditems.push_back(a);
            std::cout << "ADDING WINDOW  Height " << a.Size.y << "  Width  " << a.Size.x << "   " << a.Name << std::endl;
        }
    }

    return filtereditems;
}

// 创建一个捕获特定窗口的抓取器。
void createwindowgrabber()
{
    auto w = getWindowToCapture();
    if (w.empty()) {
        std::cout << "In order to test window capturing, you must modify the getWindowToCapture() function to search for a window that actually exists!" << std::endl;
        return;
    }
    realcounter = 0;
    onNewFramecounter = 0;
    framgrabber = nullptr;
    framgrabber =
        SL::Screen_Capture::CreateCaptureConfiguration([]() {
            auto filtereditems = getWindowToCapture(); 
            return filtereditems;
        })

            ->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Window &window) {
                // Uncomment the below code to write the image to disk for debugging

                /*
                auto r = realcounter.fetch_add(1);
                 auto s = std::to_string(r) + std::string("WINNEW_") + std::string(".jpg");
                 auto size = Width(img) * Height(img) * sizeof(SL::Screen_Capture::ImageBGRA);
                  auto imgbuffer(std::make_unique<unsigned char[]>(size));
                  ExtractAndConvertToRGBA(img, imgbuffer.get(), size);
                  tje_encode_to_file(s.c_str(), Width(img), Height(img), 4, (const unsigned char*)imgbuffer.get());
                  */

                if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - onNewFramestart).count() >=
                    1000) {
                    std::cout << "onNewFrame fps" << onNewFramecounter << std::endl;
                    onNewFramecounter = 0;
                    onNewFramestart = std::chrono::high_resolution_clock::now();
                }
                onNewFramecounter += 1;
            })
            ->onMouseChanged([&](const SL::Screen_Capture::Image *img, const SL::Screen_Capture::MousePoint &mousepoint) {
                // Uncomment the below code to write the image to disk for debugging
                /*
                auto r = realcounter.fetch_add(1);
                auto s = std::to_string(r) + std::string(" M") + std::string(".png");
                if (img) {
                    std::cout << "New mouse coordinates  AND NEW Image received."
                              << " x= " << mousepoint.Position.x << " y= " << mousepoint.Position.y << std::endl;
                    lodepng::encode(s, (unsigned char *)StartSrc(*img), Width(*img), Height(*img));
                }
                else {
                    std::cout << "New mouse coordinates received."
                              << " x= " << mousepoint.Position.x << " y= " << mousepoint.Position.y << " The mouse image is still the same as the last
                "
                              << std::endl;
                }
                */
            })
            ->start_capturing();

    framgrabber->setFrameChangeInterval(std::chrono::milliseconds(100));
    framgrabber->setMouseChangeInterval(std::chrono::milliseconds(100));
}

int main2()
{
    std::srand(std::time(nullptr));
    std::cout << "Starting Capture Demo/Test" << std::endl;
    std::cout << "Testing captured monitor bounds check" << std::endl;

    TestCopyContiguous();
    TestCopyNonContiguous();

    std::cout << "Checking for Permission to capture the screen" << std::endl;
    if (SL::Screen_Capture::IsScreenCaptureEnabled()) {
        std::cout << "Application Allowed to Capture the screen!" << std::endl;
    }
    else if (SL::Screen_Capture::CanRequestScreenCapture()) {
        std::cout << "Application Not Allowed to Capture the screen. Waiting for permission " << std::endl;
        while (!SL::Screen_Capture::IsScreenCaptureEnabled()) {
            SL::Screen_Capture::RequestScreenCapture();
            std::cout << " . ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else {
        std::cout << "Cannot Capture the screen due to permission issues. Exiting" << std::endl;
        return 0;
    }

    auto goodmonitors = SL::Screen_Capture::GetMonitors();
    for (auto &m : goodmonitors) {
        std::cout << m << std::endl;
        assert(SL::Screen_Capture::isMonitorInsideBounds(goodmonitors, m));
    }
    auto badmonitors = SL::Screen_Capture::GetMonitors();

    for (auto m : badmonitors) {
        m.Height += 1;
        std::cout << m << std::endl;
        assert(!SL::Screen_Capture::isMonitorInsideBounds(goodmonitors, m));
    }
    for (auto m : badmonitors) {
        m.Width += 1;
        std::cout << m << std::endl;
        assert(!SL::Screen_Capture::isMonitorInsideBounds(goodmonitors, m));
    }
    std::cout << "Running display capturing for 10 seconds" << std::endl;
    createframegrabber();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Running window capturing for 10 seconds" << std::endl;
    createwindowgrabber();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Running Partial display capturing for 10 seconds" << std::endl;
    createpartialframegrabber();
    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Pausing for 10 seconds. " << std::endl;
    framgrabber->pause();
    auto counti = 0;
    while (counti++ < 10) {
        assert(framgrabber->isPaused());
        std::cout << " . ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << std::endl << "Resuming  . . . for 5 seconds" << std::endl;
    framgrabber->resume();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Testing changing the interval during runtime for race conditions " << std::endl;

    // HAMMER THE SET FRAME INTERVAL FOR RACE CONDITIONS!!
    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() < 10) {
        for (auto t = 0; t < 100; t++) {
            framgrabber->setFrameChangeInterval(std::chrono::microseconds(100));
            framgrabber->setMouseChangeInterval(std::chrono::microseconds(100));
        }
    }

    std::cout << "Changing the cpature rate to 1 second" << std::endl;
    framgrabber->setFrameChangeInterval(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Setting timer using chrono literals" << std::endl;
    // You can use chron's literals as well!
    framgrabber->setFrameChangeInterval(10ms);
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Testing recreating" << std::endl;
    createframegrabber();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Testing destroy" << std::endl;
    framgrabber = nullptr;

    std::cout << "Testing recreating" << std::endl;
    createframegrabber();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 4k image
    int height = 2160;
    int width = 3840;
    std::vector<SL::Screen_Capture::ImageBGRA> image1, image2;
    image1.resize(height * width);
    for (auto &a : image1) {
        a.B = static_cast<unsigned short>(std::rand() % 255);
        a.A = static_cast<unsigned short>(std::rand() % 255);
        a.G = static_cast<unsigned short>(std::rand() % 255);
        a.R = static_cast<unsigned short>(std::rand() % 255);
    }
    image2.resize(height * width);
    for (auto &a : image2) {
        a.B = static_cast<unsigned short>(std::rand() % 255);
        a.A = static_cast<unsigned short>(std::rand() % 255);
        a.G = static_cast<unsigned short>(std::rand() % 255);
        a.R = static_cast<unsigned short>(std::rand() % 255);
    }
    long long durationaverage = 0;
    long long smallestduration = INT_MAX;
    for (auto i = 0; i < 100; i++) { // run a few times to get an average
        auto starttime = std::chrono::high_resolution_clock::now();
        auto difs =
            SL::Screen_Capture::GetDifs(SL::Screen_Capture::CreateImage(SL::Screen_Capture::ImageRect(0, 0, width, height), 0, image1.data()),
                                        SL::Screen_Capture::CreateImage(SL::Screen_Capture::ImageRect(0, 0, width, height), 0, image2.data()));
        long long d = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - starttime).count();
        smallestduration = std::min(d, smallestduration);
        durationaverage += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - starttime).count();
    }
    durationaverage /= 100;
    std::cout << "Best Case -- Time to get diffs " << durationaverage << " microseconds" << std::endl;
    std::cout << "Best Case -- Lowest Time " << smallestduration << " microseconds" << std::endl;
    memset(image1.data(), 5, image1.size() * sizeof(SL::Screen_Capture::ImageBGRA));
    memset(image2.data(), 5, image2.size() * sizeof(SL::Screen_Capture::ImageBGRA));

    durationaverage = 0;
    smallestduration = INT_MAX;
    for (auto i = 0; i < 100; i++) { // run a few times to get an average
        auto starttime = std::chrono::high_resolution_clock::now();
        auto difs =
            SL::Screen_Capture::GetDifs(SL::Screen_Capture::CreateImage(SL::Screen_Capture::ImageRect(0, 0, width, height), 0, image1.data()),
                                        SL::Screen_Capture::CreateImage(SL::Screen_Capture::ImageRect(0, 0, width, height), 0, image2.data()));
        long long d = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - starttime).count();
        smallestduration = std::min(d, smallestduration);
        durationaverage += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - starttime).count();
    }
    durationaverage /= 100;
    std::cout << "Worst Case -- Time to get diffs " << durationaverage << " microseconds" << std::endl;
    std::cout << "Worst Case -- Lowest Time " << smallestduration << " microseconds" << std::endl;

    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
#include "ScreenCapture.h" // 假设这是库的头文件
#include "lodepng.h"       // 用于PNG编码
#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

// 检查进程是否在运行
bool IsProcessRunning(const std::string &processName)
{
    // 实现进程检查逻辑
    return false; // 示例返回值
}

// 启动客户端进程
void StartClientProcess(const std::string &processPath)
{
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    if (!CreateProcess(processPath.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to start process: " << GetLastError() << std::endl;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// 监控进程线程
void MonitorProcessThread(const std::string &processName, const std::string &processPath)
{
    while (true) {
        if (!IsProcessRunning(processName)) {
            StartClientProcess(processPath);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5)); // 每5秒检查一次
    }
}

// 捕获和响应线程
void CaptureAndRespondThread()
{
    HANDLE pipe = CreateNamedPipe("\\\\.\\pipe\\ScreenCapturePipe", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, 0, NULL);
    if (pipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe: " << GetLastError() << std::endl;
        return;
    }

    while (true) {
        if (ConnectNamedPipe(pipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED) {
            auto framgrabber = 
                SL::Screen_Capture::CreateCaptureConfiguration([]() { return SL::Screen_Capture::GetMonitors(); })
                                   ->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) 
                                       {
                                       std::vector<unsigned char> png;
                                       unsigned error = lodepng::encode(png, (unsigned char *)SL::Screen_Capture::StartSrc(img),
                                                                        SL::Screen_Capture::Width(img), SL::Screen_Capture::Height(img));
                                       if (!error) {
                                           DWORD bytesWritten;
                                           WriteFile(pipe, png.data(), png.size(), &bytesWritten, NULL);
                                       }
                                   })
                                   ->start_capturing();

            framgrabber->setFrameChangeInterval(std::chrono::milliseconds(1000));
        }
        DisconnectNamedPipe(pipe);
    }

    CloseHandle(pipe);
}

int main()
{
    std::string clientProcessName = "ClientProcess.exe";
    std::string clientProcessPath = "C:\\Path\\To\\ClientProcess.exe";

    std::thread monitorThread(MonitorProcessThread, clientProcessName, clientProcessPath);
    std::thread captureThread(CaptureAndRespondThread);

    monitorThread.join();
    captureThread.join();

    return 0;
}
**/

#include "ScreenCapture.h" // 假设这是库的头文件
#include "lodepng.h"       // 用于PNG编码
#include <atomic>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

std::thread monitorThread;
std::thread captureThread;
std::atomic<bool> stopService{false};

// 检查进程是否在运行
bool IsProcessRunning(const std::string &processName)
{
    // 实现进程检查逻辑
    return false; // 示例返回值
}

// 启动客户端进程
void StartClientProcess(const std::wstring &processPath)
{
    STARTUPINFO si = {sizeof(si)};
    PROCESS_INFORMATION pi;
    if (!CreateProcess(processPath.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Failed to start process: " << GetLastError() << std::endl;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

// 监控进程线程
void MonitorProcessThread(const std::string &processName, const std::wstring &processPath)
{
    while (!stopService) {
        if (!IsProcessRunning(processName)) {
            StartClientProcess(processPath);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5)); // 每5秒检查一次
    }
}

// 捕获和响应线程
void CaptureAndRespondThread()
{
    HANDLE pipe = CreateNamedPipe(L"\\\\.\\pipe\\ScreenCapturePipe", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE | PIPE_WAIT, 1, 0, 0, 0, NULL);
    if (pipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create named pipe: " << GetLastError() << std::endl;
        return;
    }

    while (!stopService) {
        // 等待客户端连接
        if (ConnectNamedPipe(pipe, NULL) || GetLastError() == ERROR_PIPE_CONNECTED) {
            auto framgrabber = SL::Screen_Capture::CreateCaptureConfiguration([]() { return SL::Screen_Capture::GetMonitors(); })
                                   ->onNewFrame([&](const SL::Screen_Capture::Image &img, const SL::Screen_Capture::Monitor &monitor) {
                                       std::vector<unsigned char> png;
                                       unsigned error = lodepng::encode(png, (unsigned char *)SL::Screen_Capture::StartSrc(img),
                                                                        SL::Screen_Capture::Width(img), SL::Screen_Capture::Height(img));
                                       if (!error) {
                                           DWORD bytesWritten;
                                           // 将数据写入管道
                                           BOOL writeSuccess = WriteFile(pipe, png.data(), png.size(), &bytesWritten, NULL);
                                           if (!writeSuccess) {
                                               std::cerr << "Failed to write to pipe: " << GetLastError() << std::endl;
                                           }
                                       }
                                   })
                                   ->start_capturing();

            framgrabber->setFrameChangeInterval(std::chrono::milliseconds(1000));

            // 断开管道连接之前，确保所有数据已经发送
            // 这里使用了一个简单的循环来检查是否完成了数据写入
            while (true) {
                DWORD pipeState;
                if (GetNamedPipeInfo(pipe, NULL, NULL, NULL, &pipeState) && pipeState == PIPE_SERVER_END) {
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        // 断开管道连接
        DisconnectNamedPipe(pipe);
    }

    CloseHandle(pipe);
}

// 服务控制处理函数
void WINAPI ServiceCtrlHandler(DWORD request)
{
    switch (request) {
    case SERVICE_CONTROL_STOP:
        ServiceStatus.dwWin32ExitCode = 0;
        ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        SetServiceStatus(hStatus, &ServiceStatus);

        // 停止服务的逻辑
        stopService = true;
        monitorThread.join();
        captureThread.join();

        ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(hStatus, &ServiceStatus);
        return;
    default:
        break;
    }
    SetServiceStatus(hStatus, &ServiceStatus);
}

// 服务主函数
void WINAPI ServiceMain(DWORD argc, LPTSTR *argv)
{
    hStatus = RegisterServiceCtrlHandler(L"MyService", ServiceCtrlHandler); // 使用宽字符版本
    if (hStatus == NULL) {
        return;
    }

    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;
    SetServiceStatus(hStatus, &ServiceStatus);

    // 启动监控和捕获线程
    std::string clientProcessName = "ClientProcess.exe";
    std::wstring clientProcessPath = L"C:\\Path\\To\\ClientProcess.exe";

    monitorThread = std::thread(MonitorProcessThread, clientProcessName, clientProcessPath);
    captureThread = std::thread(CaptureAndRespondThread);

    ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(hStatus, &ServiceStatus);

    // 等待线程结束
    monitorThread.join();
    captureThread.join();
}

// 主函数入口
int main()
{
    //SERVICE_TABLE_ENTRY ServiceTable[] = {{L"MyService", (LPSERVICE_MAIN_FUNCTION)ServiceMain}, {NULL, NULL}};

    //if (!StartServiceCtrlDispatcher(ServiceTable)) {
    //    std::cerr << "Failed to start service: " << GetLastError() << std::endl;
    //}
    //return 0;

    captureThread = std::thread(CaptureAndRespondThread);

    // 等待线程结束
    captureThread.join();
    return 0;
}

// sc.exe create MyService binPath= "D:\\code\\screen_capture_lite\\out\\build\\x64-Debug\\screen_capture_example_cpp_shared.exe" start=auto
// sc start MyService
// sc stop MyService

