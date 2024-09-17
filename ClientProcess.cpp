#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>

int main()
{
    HANDLE pipe = CreateFile(L"\\\\.\\pipe\\ScreenCapturePipe",
        GENERIC_READ,
        0,  // No sharing
        NULL,  // Default security attributes
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);  // No template file

    if (pipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to connect to pipe: " << GetLastError() << std::endl;
        return 1;
    }

    std::vector<unsigned char> buffer(1024 * 1024);  // 1 MB buffer
    DWORD bytesRead;

    //std::ofstream outputFile("captured_image.png", std::ios::binary);

    //if (!outputFile.is_open()) {
    //    std::cerr << "Failed to open output file." << std::endl;
    //    CloseHandle(pipe);
    //    return 1;
    //}

    // 基本文件名和扩展名
    std::string baseFilename = "captured_image";
    std::string extension = ".png";

    // 文件编号
    int fileNumber = 1;
    std::string filename;

    while (true) {
        bool readSuccess = ReadFile(pipe, buffer.data(), buffer.size(), &bytesRead, NULL);
        if (!readSuccess) {
            DWORD error = GetLastError();
            if (error == ERROR_BROKEN_PIPE) {
                std::cerr << "Pipe broken. No more data from server." << std::endl;
                break;
            }
            else {
                std::cerr << "Failed to read from pipe: " << error << std::endl;
                break;
            }
        }

        if (bytesRead > 0) {
            filename = baseFilename + std::to_string(fileNumber++) + extension;
            std::ofstream outputFile(filename, std::ios::binary);

            if (!outputFile.is_open()) {
                std::cerr << "Failed to open output file." << std::endl;
                CloseHandle(pipe);
                return 1;
            }
            outputFile.write(reinterpret_cast<const char*>(buffer.data()), bytesRead);
            outputFile.close();

            std::cerr << "captured_image: " << filename << std::endl;
        }
        else {
            std::cerr << "No data read from pipe." << std::endl;
            break;
        }
    }

    //outputFile.close();
    CloseHandle(pipe);

    return 0;
}
