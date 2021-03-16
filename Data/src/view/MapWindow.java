package view;

import java.awt.EventQueue;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Color;
import java.awt.Toolkit;
import javax.swing.JButton;
import javax.swing.ImageIcon;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JLabel;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseEvent;
/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 * 线路图窗口
 **/
public class MapWindow extends JFrame {

	private JPanel contentPane;
	private JLabel dataLabel;
	private DrawPanel dp;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					MapWindow frame = new MapWindow();
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
	public MapWindow() {
		setIconImage(Toolkit.getDefaultToolkit().getImage(MapWindow.class.getResource("/icon/bus01.png")));
		setTitle("\u8DEF\u7EBF\u56FE");
		setResizable(false);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 500, 400);
		contentPane = new JPanel();
		contentPane.addMouseMotionListener(new MouseMotionAdapter() {
			@Override
			public void mouseMoved(MouseEvent e) {
				int x = e.getX() - 15;
				int y = e.getY() - 10;
				
				if (x > 450 || x < 0 || y < 0 || y > 300) dataLabel.setText(""); 
				else dataLabel.setText("(" + x + ", " + y + ")");
			}
		});
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		JButton refleshButton = new JButton("");
		refleshButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				dp.display();
			}
		});
		refleshButton.setIcon(new ImageIcon(MapWindow.class.getResource("/icon/redo.png")));
		refleshButton.setBounds(231, 321, 23, 23);
		contentPane.add(refleshButton);
		dataLabel = new JLabel("");
		dataLabel.setBounds(352, 329, 79, 15);
		contentPane.add(dataLabel);
		dp = new DrawPanel();
		dp.setBounds(15, 10, 450, 300);
		dp.setBackground(Color.lightGray);
		contentPane.add(dp);
		//创客弹出在中间
		setLocationRelativeTo(null);
	}
}
