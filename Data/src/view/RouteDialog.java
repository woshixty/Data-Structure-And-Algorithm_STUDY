package view;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFormattedTextField;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.text.DefaultFormatterFactory;
import javax.swing.text.NumberFormatter;

import model.BusSystem;

import java.awt.Toolkit;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.SpinnerNumberModel;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;
import javax.swing.JSpinner;
import java.awt.event.WindowFocusListener;
import java.awt.event.WindowEvent;

public class RouteDialog extends JDialog {
	
	private BusSystem bussys;

	private final JPanel contentPanel = new JPanel();
	private JSpinner startSpinner;
	private JSpinner endSpinner;
	private JSpinner msgSpinner;
	private JLabel startNumLabel;
	private JLabel endNumLabel;
	private JLabel msgNumLabel;

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
	public RouteDialog() {
		addWindowFocusListener(new WindowFocusListener() {
			public void windowGainedFocus(WindowEvent arg0) {
				reSetMax();
			}
			public void windowLostFocus(WindowEvent arg0) {
			}
		});
		setModalityType(ModalityType.APPLICATION_MODAL);
		setIconImage(Toolkit.getDefaultToolkit().getImage(AddStationDialog.class.getResource("/icon/bus01.png")));
		setTitle("\u6DFB\u52A0\u7EBF\u8DEF\u4FE1\u606F");
		setResizable(false);
		setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 304, 201);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("\u8D77\u70B9\u8F66\u7AD9id");
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel.setBounds(31, 30, 64, 15);
		contentPanel.add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("\u7EC8\u70B9\u8F66\u7AD9id");
		lblNewLabel_1.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_1.setBounds(31, 55, 64, 15);
		contentPanel.add(lblNewLabel_1);
		
		JButton confirmButton = new JButton("\u786E\u5B9A");
		confirmButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		confirmButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				confirm();
			}
		});
		confirmButton.setBounds(84, 121, 119, 29);
		contentPanel.add(confirmButton);
		
		JLabel lblNewLabel_1_1 = new JLabel("\u7EBF\u8DEF\u4FE1\u606Fid");
		lblNewLabel_1_1.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_1_1.setBounds(31, 81, 64, 15);
		contentPanel.add(lblNewLabel_1_1);
		
		startSpinner = new JSpinner(new SpinnerNumberModel(0, 0, Integer.MAX_VALUE, 1));
		startSpinner.setBounds(105, 27, 98, 22);
		JSpinner.NumberEditor editor = new JSpinner.NumberEditor(startSpinner, "0");
		startSpinner.setEditor(editor);
		JFormattedTextField textField = ((JSpinner.NumberEditor) startSpinner.getEditor()).getTextField();
		textField.setEditable(true);
		DefaultFormatterFactory factory = (DefaultFormatterFactory) textField.getFormatterFactory();
		NumberFormatter formatter = (NumberFormatter) factory.getDefaultFormatter();
		formatter.setAllowsInvalid(false);
		contentPanel.add(startSpinner);
		
		endSpinner = new JSpinner(new SpinnerNumberModel(0, 0, Integer.MAX_VALUE, 1));
		endSpinner.setBounds(105, 52, 98, 22);
		JSpinner.NumberEditor editor1 = new JSpinner.NumberEditor(endSpinner, "0");
		endSpinner.setEditor(editor1);
		JFormattedTextField textField1 = ((JSpinner.NumberEditor) endSpinner.getEditor()).getTextField();
		textField1.setEditable(true);
		DefaultFormatterFactory factory1 = (DefaultFormatterFactory) textField1.getFormatterFactory();
		NumberFormatter formatter1 = (NumberFormatter) factory1.getDefaultFormatter();
		formatter1.setAllowsInvalid(false);
		contentPanel.add(endSpinner);
		
		msgSpinner = new JSpinner(new SpinnerNumberModel(0, 0, Integer.MAX_VALUE, 1));
		msgSpinner.setBounds(105, 78, 98, 22);
		JSpinner.NumberEditor editor2 = new JSpinner.NumberEditor(msgSpinner, "0");
		msgSpinner.setEditor(editor2);
		JFormattedTextField textField2 = ((JSpinner.NumberEditor) msgSpinner.getEditor()).getTextField();
		textField2.setEditable(true);
		DefaultFormatterFactory factory2 = (DefaultFormatterFactory) textField2.getFormatterFactory();
		NumberFormatter formatter2 = (NumberFormatter) factory2.getDefaultFormatter();
		formatter2.setAllowsInvalid(false);
		contentPanel.add(msgSpinner);
		
		JLabel lblNewLabel_2 = new JLabel("\u6700\u5927");
		lblNewLabel_2.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_2.setBounds(212, 30, 30, 15);
		contentPanel.add(lblNewLabel_2);
		
		JLabel lblNewLabel_2_1 = new JLabel("\u6700\u5927");
		lblNewLabel_2_1.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_2_1.setBounds(213, 55, 30, 15);
		contentPanel.add(lblNewLabel_2_1);
		
		JLabel lblNewLabel_2_2 = new JLabel("\u6700\u5927");
		lblNewLabel_2_2.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		lblNewLabel_2_2.setBounds(213, 81, 30, 15);
		contentPanel.add(lblNewLabel_2_2);
		
		startNumLabel = new JLabel("0");
		startNumLabel.setBounds(244, 30, 30, 15);
		contentPanel.add(startNumLabel);
		
		endNumLabel = new JLabel("0");
		endNumLabel.setBounds(244, 55, 30, 15);
		contentPanel.add(endNumLabel);
		
		msgNumLabel = new JLabel("0");
		msgNumLabel.setBounds(244, 81, 30, 15);
		contentPanel.add(msgNumLabel);
		
	}
	
	private void confirm() {
		int startId = (int) startSpinner.getValue();
		int endId = (int) endSpinner.getValue();
		int msgId = (int) msgSpinner.getValue();
		
		if (startId == endId) {
			JOptionPane.showMessageDialog(this, "起点和终点不能相同。", "提示", JOptionPane.PLAIN_MESSAGE);
			return;
		}
		
		if (startId >= bussys.stationList.size() ||
			endId >= bussys.stationList.size() ||
			msgId >= bussys.lineMsgList.size()) {
			JOptionPane.showMessageDialog(this, "请填写正确的id值。", "提示", JOptionPane.PLAIN_MESSAGE);
			return;
		}
		
		bussys.addRoute(startId, endId, msgId);
		bussys.save();
		dispose();
	}
	
	private void reSetMax() {
		startNumLabel.setText("" + (bussys.stationList.size() - 1));
		endNumLabel.setText("" + (bussys.stationList.size() - 1));
		msgNumLabel.setText("" + (bussys.lineMsgList.size() - 1));
	}
	
	public RouteDialog setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
	
	public RouteDialog setSuperWindow(LineMsgWindow sw) {
		//创客弹出在中间
		setLocationRelativeTo(sw);
		return this;
	}
}
