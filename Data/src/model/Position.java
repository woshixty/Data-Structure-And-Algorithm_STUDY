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
	
	public Position() {}
	public Position(int x, int y) {
		this.x = x;
		this.y = y;
	}
	
	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	
}
