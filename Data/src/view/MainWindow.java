package view;

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Toolkit;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import model.BusSystem;
import java.awt.Font;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 * 主窗口
 **/
public class MainWindow extends JFrame {
	public static BusSystem bussys;
	private JPanel contentPane;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MainWindow frame = new MainWindow();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public MainWindow() {
		setIconImage(Toolkit.getDefaultToolkit().getImage(MainWindow.class.getResource("/icon/bus01.png")));
		setResizable(false);
		setTitle("\u516C\u4EA4\u7CFB\u7EDF");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 295, 306);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		JButton staionButton = new JButton("\u67E5\u8BE2\u8F66\u7AD9\u4FE1\u606F");
		staionButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		staionButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new StationWindow().setBusSystem(bussys).setVisible(true);
			}
		});
		staionButton.setBounds(46, 38, 191, 33);
		contentPane.add(staionButton);
		JButton lineMsgButton = new JButton("\u67E5\u8BE2\u7EBF\u8DEF\u4FE1\u606F");
		lineMsgButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lineMsgButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				new LineMsgWindow().setBusSystem(bussys).setVisible(true);
			}
		});
		lineMsgButton.setBounds(46, 81, 191, 33);
		contentPane.add(lineMsgButton);
		JButton routeButton = new JButton("\u67E5\u8BE2\u4E24\u7AD9\u4E4B\u95F4\u7684\u7EBF\u8DEF");
		routeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				new SearchWindow().setBusSystem(bussys).setVisible(true);
			}
		});
		routeButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		routeButton.setBounds(46, 124, 191, 33);
		contentPane.add(routeButton);
		JButton exitButton = new JButton("\u9000\u51FA");
		exitButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		exitButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				System.exit(0);
			}
		});
		exitButton.setBounds(46, 210, 191, 33);
		contentPane.add(exitButton);
		JButton otherButton = new JButton("\u7EBF\u8DEF\u56FE");
		otherButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				new MapWindow().setVisible(true);
			}
		});
		otherButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		otherButton.setBounds(46, 167, 191, 33);
		contentPane.add(otherButton);
		//创客弹出在中间
		setLocationRelativeTo(null);
	}
	
	public MainWindow setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
}
