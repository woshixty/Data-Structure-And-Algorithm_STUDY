package model;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class Position {

	private int x;
	
	private int y;
	
	@Override
	public String toString() {
		return "("+ x + ", " + y + ")";
	}

	public Position(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}
	
}

