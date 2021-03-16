package view;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import model.BusSystem;
import model.LineMsg;

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
 * 改变路线信息
 **/
public class ChangeLineMsgDialog extends JDialog {
	
	private BusSystem bussys;
	private LineMsg beforeMsg;
	private final JPanel contentPanel = new JPanel();
	private JTextField nameText;
	private JTextField detailText;

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
	public ChangeLineMsgDialog() {
		setModalityType(ModalityType.APPLICATION_MODAL);
		setIconImage(Toolkit.getDefaultToolkit().getImage(AddStationDialog.class.getResource("/icon/bus01.png")));
		setTitle("\u4FEE\u6539\u7EBF\u8DEF\u4FE1\u606F");
		setResizable(false);
		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 304, 178);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("\u7EBF\u8DEF\u540D\u79F0");
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel.setBounds(31, 30, 54, 15);
		contentPanel.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("\u7EBF\u8DEF\u8BE6\u60C5");
		lblNewLabel_1.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_1.setBounds(31, 55, 54, 15);
		contentPanel.add(lblNewLabel_1);
		
		nameText = new JTextField();
		nameText.setBounds(95, 27, 163, 21);
		contentPanel.add(nameText);
		nameText.setColumns(10);
		
		detailText = new JTextField();
		detailText.setColumns(10);
		detailText.setBounds(95, 52, 163, 21);
		contentPanel.add(detailText);
		
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
		String detail = detailText.getText();
		
		if (name.isEmpty() || detail.isEmpty()) {
			JOptionPane.showMessageDialog(this, "请填写完整信息。", "提示", JOptionPane.PLAIN_MESSAGE);
			return;
		}
		
		bussys.lineMsgList.get(beforeMsg.getId()).setName(name);
		bussys.lineMsgList.get(beforeMsg.getId()).setDetail(detail);
		bussys.save();
		dispose();
	}
	
	public ChangeLineMsgDialog setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
	
	public ChangeLineMsgDialog setSuperWindow(LineMsgWindow sw) {
		//创客弹出在中间
		setLocationRelativeTo(sw);
		return this;
	}
	
	public ChangeLineMsgDialog setBeforeMsg(LineMsg lineMsg) {
		this.beforeMsg = lineMsg;
		nameText.setText(beforeMsg.getName());
		detailText.setText(beforeMsg.getDetail());
		return this;
	}
}
