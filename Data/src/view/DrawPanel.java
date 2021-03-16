package view;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.lang.reflect.Field;
import javax.swing.JPanel;
import enums.ColorPos;
import model.BusSystem;
import model.Route;
import model.Station;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 * 显示线路图
 **/
public class DrawPanel extends JPanel {
	private BusSystem bussys = MainWindow.bussys;

	private int x = 450;
	private int y = 300;

	//画图
	public void display()
	{
		//重绘JPanel
		this.repaint();
	}
	
	/**
	 * repaint方法会调用paint方法，并自动获得Graphics对像
	 * 然后可以用该对像进行2D画图
	 * 注：该方法是重写了JPanel的paint方法
	 */
	public void paint(Graphics g)
	{
		//调用的super.paint(g),让父类做一些事前的工作，如刷新屏幕
		super.paint(g);	
		Graphics2D g2d = (Graphics2D)g;
		drawLine(g2d);
		drawPoint(g2d);
	}
	
	private void drawLine(Graphics2D g2d) {
		for (Station station : bussys.stationList) {
			Route curr = station.getFirstRoute();
			Color color = null;
			while (curr != null) {
				try {
					Field field = Color.class.getField(bussys.lineMsgList.get(curr.getMsgId()).getDetail().split(" ")[2]);
					color = (Color)field.get(null);
				} catch (NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException e) {
					e.printStackTrace();
				}
				g2d.setColor(color);
				g2d.drawLine(station.getPos().getX() + 10 + ColorPos.getPosByColor(color), 
						station.getPos().getY() + 10, 
						bussys.stationList.get(curr.getTargetId()).getPos().getX() + 10 + ColorPos.getPosByColor(color),
						bussys.stationList.get(curr.getTargetId()).getPos().getY() + 10);
				curr = curr.getNextRoute();
			}
		}
	}
	
	private void drawPoint(Graphics2D g2d) {
		for (Station station : bussys.stationList) {
			int posX = station.getPos().getX();
			int posY = station.getPos().getY();
			g2d.setColor(Color.white);//设置画图的颜色
			g2d.fillOval(posX, posY, 20, 20);
			g2d.setColor(Color.black);//设置画图的颜色
			g2d.drawString("" + station.getId(), posX + 4, posY + 15);
			g2d.setColor(Color.white);
			g2d.drawString(station.getName(), posX + 25, posY);
		}
	}
}
