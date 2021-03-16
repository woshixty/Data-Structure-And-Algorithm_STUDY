package model;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class Route {

	private int msgId;
	
	private int targetId;
	
	private Route nextRoute;

	@Override
	public String toString() {
		return "Route [msgId=" + msgId + ", targetId=" + targetId + ", nextRoute=" + nextRoute + "]";
	}
	
	public String toOutString() {
		return "," + msgId + "," + targetId + ",";
	}

	public Route() {}
	public Route(int msgId, int targetId, Route nextRoute) {
		this.msgId = msgId;
		this.targetId = targetId;
		this.nextRoute = nextRoute;
	}
	public Route(String inStr) {
		String[] strs = inStr.split(",");
		
		this.msgId = Integer.parseInt(strs[1]);
		this.targetId = Integer.parseInt(strs[2]);
		this.nextRoute = new Route(Integer.parseInt(strs[3]), -1, null);
	}

	public int getMsgId() {
		return msgId;
	}

	public void setMsgId(int msgId) {
		this.msgId = msgId;
	}

	public int getTargetId() {
		return targetId;
	}

	public void setTargetId(int targetId) {
		this.targetId = targetId;
	}

	public Route getNextRoute() {
		return nextRoute;
	}

	public void setNextRoute(Route nextRoute) {
		this.nextRoute = nextRoute;
	}

	public int nextRouteId() {
		if (nextRoute.targetId < 0) return nextRoute.msgId;
		return -1;
	}
}
