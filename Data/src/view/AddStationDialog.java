package view;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import model.BusSystem;
import model.Position;

import java.awt.Toolkit;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 * 添加站点信息
 **/
public class AddStationDialog extends JDialog {
	
	private BusSystem bussys;
	private final JPanel contentPanel = new JPanel();
	private JTextField nameText;
	private JTextField xText;
	private JTextField yText;
	private JLabel lblNewLabel_2;
	private JLabel lblNewLabel_3;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			AddStationDialog dialog = new AddStationDialog();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 */
	public AddStationDialog() {
		setModalityType(ModalityType.APPLICATION_MODAL);
		setIconImage(Toolkit.getDefaultToolkit().getImage(AddStationDialog.class.getResource("/icon/bus01.png")));
		setTitle("\u6DFB\u52A0\u4E00\u4E2A\u7AD9\u70B9");
		setResizable(false);
		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 304, 178);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("\u7AD9\u70B9\u540D");
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel.setBounds(31, 30, 54, 15);
		contentPanel.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("\u7AD9\u70B9\u4F4D\u7F6E");
		lblNewLabel_1.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_1.setBounds(31, 55, 54, 15);
		contentPanel.add(lblNewLabel_1);
		
		nameText = new JTextField();
		nameText.setBounds(95, 27, 163, 21);
		contentPanel.add(nameText);
		nameText.setColumns(10);
		
		xText = new JTextField();
		xText.setColumns(10);
		xText.setBounds(116, 52, 54, 21);
		contentPanel.add(xText);
		
		yText = new JTextField();
		yText.setColumns(10);
		yText.setBounds(204, 52, 54, 21);
		contentPanel.add(yText);
		
		lblNewLabel_2 = new JLabel("x:");
		lblNewLabel_2.setBounds(95, 55, 23, 15);
		contentPanel.add(lblNewLabel_2);
		
		lblNewLabel_3 = new JLabel("y:");
		lblNewLabel_3.setBounds(180, 55, 23, 15);
		contentPanel.add(lblNewLabel_3);
		
		JButton confirmButton = new JButton("\u786E\u5B9A");
		confirmButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		confirmButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				confirm();
			}
		});
		confirmButton.setBounds(84, 98, 119, 29);
		contentPanel.add(confirmButton);
		
	}
	
	private void confirm() {
		String name = nameText.getText();
		String xTxt = xText.getText();
		String yTxt = yText.getText();
		//错误输入处理
		if (name.isEmpty() || xTxt.isEmpty() || yTxt.isEmpty()) {
			JOptionPane.showMessageDialog(this, "请填写完整信息。", "提示", JOptionPane.PLAIN_MESSAGE);
			return;
		}
		//横纵坐标
		int pos_x;
		int pos_y;
		//设置
		try {
			pos_x = Integer.parseInt(xTxt);
			pos_y = Integer.parseInt(yTxt);
		} catch (Exception e) {
			JOptionPane.showMessageDialog(this, "请正确填写信息。", "提示", JOptionPane.PLAIN_MESSAGE);
			return;
		}
		//位置
		Position pos = new Position(pos_x, pos_y);
		bussys.addStation(pos, name);
		bussys.save();
		dispose();
	}
	
	public AddStationDialog setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
	
	public AddStationDialog setSuperWindow(StationWindow sw) {
		//创客弹出在中间
		setLocationRelativeTo(sw);
		return this;
	}
}
