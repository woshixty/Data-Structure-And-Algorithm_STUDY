package model;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class Station {
	
	private int id;
	
	private Position pos;
	
	private String name;
	
	private Route firstRoute;

	@Override
	public String toString() {
		return "Station [id=" + id + ", pos=" + pos + ", name=" + name + ", firstRoute=" + firstRoute + "]";
	}
	
	public String toOutString() {
		return id + "," + pos.getX() + "," + pos.getY() + "," + name + ",";
	}

	public Station(int id, Position pos, String name, Route firstRoute) {
		this.id = id;
		this.pos = pos;
		this.name = name;
		this.firstRoute = firstRoute;
	}
	public Station(String inStr) {
		String[] strs = inStr.split(",");
		this.id = Integer.parseInt(strs[0]);
		int pos_x = Integer.parseInt(strs[1]);
		int pos_y = Integer.parseInt(strs[2]);
		this.pos = new Position(pos_x, pos_y);
		this.name = strs[3];
		this.firstRoute = new Route(Integer.parseInt(strs[4]), id, null);
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public Position getPos() {
		return pos;
	}

	public void setPos(Position pos) {
		this.pos = pos;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Route getFirstRoute() {
		return firstRoute;
	}

	public void setFirstRoute(Route firstRoute) {
		this.firstRoute = firstRoute;
	}
	
	public int firstRouteId() {
		if (firstRoute.getTargetId() == id) return firstRoute.getMsgId();
		return -1;
	}
}
