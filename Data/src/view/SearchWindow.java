package view;

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import model.BusSystem;
import java.awt.Toolkit;
import javax.swing.JTextField;
import javax.swing.JLabel;
import java.awt.Font;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JRadioButton;
/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 * 查询线路窗口
 **/
public class SearchWindow extends JFrame {
	
	private BusSystem bussys;
	private JPanel contentPane;
	private JTextField startText;
	private JTextField endText;
	private JTextArea textArea;
	private JRadioButton oneRdbt;
	private JRadioButton moreRdbt;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SearchWindow frame = new SearchWindow();
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
	public SearchWindow() {
		setResizable(false);
		setIconImage(Toolkit.getDefaultToolkit().getImage(SearchWindow.class.getResource("/icon/bus01.png")));
		setTitle("\u67E5\u8BE2\u4E24\u7AD9\u4E4B\u95F4\u7EBF\u8DEF");
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 552, 247);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		startText = new JTextField();
		startText.setBounds(87, 10, 110, 21);
		contentPane.add(startText);
		startText.setColumns(10);
		
		endText = new JTextField();
		endText.setBounds(87, 37, 110, 21);
		contentPane.add(endText);
		endText.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("\u8D77\u70B9\u7AD9\uFF1A");
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel.setBounds(21, 13, 54, 15);
		contentPane.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("\u5230\u8FBE\u7AD9\uFF1A");
		lblNewLabel_1.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_1.setBounds(21, 40, 54, 15);
		contentPane.add(lblNewLabel_1);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(20, 65, 501, 132);
		contentPane.add(scrollPane);
		
		textArea = new JTextArea();
		textArea.setEditable(false);
		scrollPane.setViewportView(textArea);
		
		JButton searchButton = new JButton("\u67E5\u8BE2");
		searchButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		searchButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				search();
			}
		});
		searchButton.setBounds(230, 10, 93, 21);
		contentPane.add(searchButton);
		
		oneRdbt = new JRadioButton("\u4E0D\u6362\u4E58");
		oneRdbt.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		oneRdbt.setBounds(359, 9, 121, 23);
		
		moreRdbt = new JRadioButton("\u81F3\u591A\u6362\u4E58\u4E00\u6B21");
		moreRdbt.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		moreRdbt.setBounds(359, 36, 121, 23);
		
		ButtonGroup btnGroup = new ButtonGroup();
		btnGroup.add(oneRdbt);
		btnGroup.add(moreRdbt);
		
		oneRdbt.setSelected(true);
		
		contentPane.add(oneRdbt);
		contentPane.add(moreRdbt);
		
		//创客弹出在中间
		setLocationRelativeTo(null);
	}
	
	private void search() {
		String startTxt = startText.getText();
		String endTxt = endText.getText();
		
		if (startTxt.equals("") || endTxt.equals("")) {
			textArea.setText("站名不能为空。");
			return;
		}
		
		int startId = bussys.searchStationId(startTxt);
		int endId = bussys.searchStationId(endTxt);
		
		if (startId < 0 || endId < 0) {
			textArea.setText("站名找不到。");
			return;
		}
		
		String out = "";
		if (oneRdbt.isSelected()) out = bussys.searchStraight(startId, endId);
		else {
			out = bussys.searchLine(startId, endId);
		}
		
		textArea.setText(out);
	}
	
	
	public SearchWindow setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
}
