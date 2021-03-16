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
import javax.swing.JOptionPane;
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
 * 线路信息的窗口
 **/
public class LineMsgWindow extends JFrame {
	
	private BusSystem bussys;
	private JPanel contentPane;
	private JTable table;
	private JButton changeRouteButton;
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
	public LineMsgWindow() {
		addWindowFocusListener(new WindowFocusListener() {
			public void windowGainedFocus(WindowEvent arg0) {
				refleshTable();
			}
			public void windowLostFocus(WindowEvent arg0) {
			}
		});
		
		setResizable(false);
		setIconImage(Toolkit.getDefaultToolkit().getImage(StationWindow.class.getResource("/icon/bus01.png")));
		setTitle("\u7EBF\u8DEF\u4FE1\u606F");
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 492, 428);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(176, 25, 285, 352);
		contentPane.add(scrollPane);
		
		table = new JTable();
		table.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent arg0) {
				changeRouteButton.setEnabled(true);
				int selected = table.getSelectedRow();
				msgLabel.setText(bussys.searchTarLine(selected));
			}
		});
		table.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		table.setModel(new DefaultTableModel(
			new Object[][] {
			},
			new String[] {
				"id", "\u8DEF\u7EBF\u540D\u79F0", "\u6807\u8BB0\u989C\u8272"
			}
		) {
			Class[] columnTypes = new Class[] {
				Integer.class, String.class, String.class
			};
			public Class getColumnClass(int columnIndex) {
				return columnTypes[columnIndex];
			}
		});
		table.getColumnModel().getColumn(0).setPreferredWidth(35);
		table.getColumnModel().getColumn(1).setPreferredWidth(90);
		table.getColumnModel().getColumn(2).setPreferredWidth(130);
		scrollPane.setViewportView(table);
		
		JLabel lblNewLabel = new JLabel("\u7EBF\u8DEF\u4FE1\u606F\u8868");
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 18));
		lblNewLabel.setBounds(25, 25, 141, 28);
		contentPane.add(lblNewLabel);
		
		JButton addButton = new JButton("\u6DFB\u52A0\u65B0\u7EBF\u8DEF\u4FE1\u606F");
		addButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		addButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				addStation();
			}
		});
		addButton.setBounds(25, 343, 135, 34);
		contentPane.add(addButton);
		
		JButton refleshButton = new JButton("");
		refleshButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				refleshTable();
			}
		});
		refleshButton.setIcon(new ImageIcon(StationWindow.class.getResource("/icon/redo.png")));
		refleshButton.setBounds(122, 28, 23, 23);
		contentPane.add(refleshButton);
		
		JButton routeButton = new JButton("\u6DFB\u52A0\u65B0\u8DEF\u7EBF");
		routeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				addRoute();
			}
		});
		routeButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		routeButton.setBounds(25, 299, 135, 34);
		contentPane.add(routeButton);
		
		changeRouteButton = new JButton("\u4FEE\u6539\u9009\u4E2D\u8DEF\u7EBF\u4FE1\u606F");
		changeRouteButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				changeMsg();
			}
		});
		changeRouteButton.setEnabled(false);
		changeRouteButton.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		changeRouteButton.setBounds(25, 255, 135, 34);
		contentPane.add(changeRouteButton);
		
		msgLabel = new JLabel("");
		msgLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 12));
		msgLabel.setVerticalAlignment(SwingConstants.TOP);
		msgLabel.setBounds(25, 60, 141, 185);
		contentPane.add(msgLabel);
		
		//创客弹出在中间
		setLocationRelativeTo(null);
	}
	
	
	private void refleshTable() {
		DefaultTableModel model = (DefaultTableModel) table.getModel();
		model.setRowCount(0);
		//System.out.println(bussys);
		int len = bussys.lineMsgList.size();
		for (int i = 0; i < len; i++) {
			Vector<Object> v = new Vector<>();
			v.add(bussys.lineMsgList.get(i).getId());
			v.add(bussys.lineMsgList.get(i).getName());
			v.add(bussys.lineMsgList.get(i).getDetail().split(" ")[2]);
			model.addRow(v);
		}
		
		changeRouteButton.setEnabled(false);
		msgLabel.setText("");
	}
	
	private void addRoute() {
		if (bussys.lineMsgList.isEmpty() || bussys.stationList.isEmpty()) {
			JOptionPane.showMessageDialog(this, "车站或线路信息过少，无法添加新路线。", "提示", JOptionPane.PLAIN_MESSAGE);
			return;
		}
		
		new RouteDialog().setSuperWindow(this).setBusSystem(bussys).setVisible(true);
	}
	
	private void addStation() {
		new AddLineMsgDialog().setSuperWindow(this).setBusSystem(bussys).setVisible(true);
	}
	
	private void changeMsg() {
		int selected = table.getSelectedRow();
		new ChangeLineMsgDialog().setBeforeMsg(bussys.lineMsgList.get(selected)).setSuperWindow(this).setBusSystem(bussys).setVisible(true);
	}
	
	public LineMsgWindow setBusSystem(BusSystem bussys) {
		this.bussys = bussys;
		return this;
	}
}
