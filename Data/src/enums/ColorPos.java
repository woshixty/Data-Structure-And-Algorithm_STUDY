package enums;

import java.awt.Color;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public enum ColorPos {

	GREEN(1, Color.green),
	YELLOW(-1, Color.yellow),
	RED(4, Color.red),
	BLUE(-4, Color.blue),
	CYAN(7, Color.cyan),
	BLACK(-7, Color.BLACK);
	
	private int pos;
	private Color color;
	
	ColorPos(int pos, Color color) {
		this.pos = pos;
		this.color = color;
	}
	
	public int getPos() {
		return pos;
	}
	
	public static int getPosByColor(Color color) {
		if (color.equals(Color.green)) {
			return GREEN.getPos();
		}
		else if (color.equals(Color.yellow)) {
			return YELLOW.getPos();
		}
		else if (color.equals(Color.red)) {
			return RED.getPos();
		}
		else if (color.equals(Color.blue)) {
			return BLUE.getPos();
		}
		else if (color.equals(Color.cyan)) {
			return CYAN.getPos();
		}
		return BLACK.getPos();
	}
}
