package view;

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Toolkit;
import java.util.Vector;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import model.BusSystem;
import javax.swing.ListSelectionModel;
import javax.swing.JLabel;
import java.awt.Font;
import javax.swing.JButton;
import java.awt.event.WindowFocusListener;
import java.awt.event.WindowEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.ImageIcon;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.SwingConstants;
/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 * 站点信息
 **/
public class StationWindow extends JFrame {
	
	private BusSystem bussys;
	private JPanel contentPane;
	private JTable table;
	private JButton changeButton;
	private JLabel msgLabel;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					StationWindow frame = new StationWindow();
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
	public StationWindow() {
		addWindowFocusListener(new WindowFocusListener() {
			public void windowGainedFocus(WindowEvent arg0) {
				refreshTable();
			}
			public void windowLostFocus(WindowEvent arg0) {
			}
		});
		setResizable(false);
		setIconImage(Toolkit.getDefaultToolkit().getImage(StationWindow.class.getResource("/icon/bus01.png")));
		setTitle("\u8F66\u7AD9\u4FE1\u606F");
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 492, 372);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(176, 25, 285, 295);
		contentPane.add(scrollPane);
		table = new JTable();
		table.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				changeButton.setEnabled(true);
				int selected = table.getSelectedRow();
				msgLabel.setText(bussys.searchStationLine(selected));
			}
		});
		table.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.setModel(new DefaultTableModel(
			new Object[][] {
			},
			new String[] {
				"id", "\u8F66\u7AD9\u540D", "\u4F4D\u7F6E"
			}
		) {
			Class[] columnTypes = new Class[] {
				Integer.class, String.class, String.class
			};
			public Class getColumnClass(int columnIndex) {
				return columnTypes[columnIndex];
			}
			boolean[] columnEditables = new boolean[] {
				false, false, false
			};
			public boolean isCellEditable(int row, int column) {
				return columnEditables[column];
			}
		});
		table.getColumnModel().getColumn(0).setPreferredWidth(35);
		table.getColumnModel().getColumn(1).setPreferredWidth(120);
		table.getColumnModel().getColumn(2).setPreferredWidth(70);
		scrollPane.setViewportView(table);
		JLabel lblNewLabel = new JLabel("\u8F66\u7AD9\u4FE1\u606F\u8868");
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 18));
		lblNewLabel.setBounds(25, 25, 141, 28);
		contentPane.add(lblNewLabel);
		JButton addButton = new JButton("\u6DFB\u52A0\u65B0\u7AD9\u70B9");
		addButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		addButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				addStation();
			}
		});
		addButton.setBounds(25, 278, 126, 34);
		contentPane.add(addButton);
		JButton refreshButton = new JButton("");
		refreshButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				refreshTable();
			}
		});
		refreshButton.setIcon(new ImageIcon(StationWindow.class.getResource("/icon/redo.png")));
		refreshButton.setBounds(122, 28, 23, 23);
		contentPane.add(refreshButton);
		changeButton = new JButton("\u4FEE\u6539\u9009\u4E2D\u8F66\u7AD9");
		changeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				changeStation();
			}
		});
		changeButton.setEnabled(false);
		changeButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		changeButton.setBounds(25, 239, 126, 34);
		contentPane.add(changeButton);
		msgLabel = new JLabel("");
		msgLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		msgLabel.setVerticalAlignment(SwingConstants.TOP);
		msgLabel.setBounds(25, 63, 141, 166);
		contentPane.add(msgLabel);
		//创客弹出在中间
		setLocationRelativeTo(null);
	}
	
	
	private void refreshTable() {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);
		int len = bussys.stationList.size();
		for (int i = 0; i < len; i++) {
			Vector<Object> v = new Vector<>();
			v.add(bussys.stationList.get(i).getId());
			v.add(bussys.stationList.get(i).getName());
			v.add(bussys.stationList.get(i).getPos().toString());
			model.addRow(v);
		}
		changeButton.setEnabled(false);
		msgLabel.setText("");
	}
	
	private void changeStation() {
		int selected = table.getSelectedRow();
		new ChangeStationDialog().setBeforeStation(bussys.stationList.get(selected)).setSuperWindow(this).setBusSystem(bussys).setVisible(true);
	}
	
	private void addStation() {
		new AddStationDialog().setSuperWindow(this).setBusSystem(bussys).setVisible(true);
	}
	
	public StationWindow setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
}
