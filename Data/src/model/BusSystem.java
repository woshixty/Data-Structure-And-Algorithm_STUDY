package model;

import java.io.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class BusSystem {
	//站点列表
	public List<Station> stationList;
	//线路列表
	public List<LineMsg> lineMsgList;

	//创建公交系统对象，并从文件中读取数据
	public BusSystem() throws IOException {
		//存路线的各项信息
		File lineMsgFile = new File("line_msg.csv");
		//存站点
		File stationFile = new File("station.csv");
		//存路线
		File routeFile = new File("route.csv");
		//不存在就创建一个
		if (!lineMsgFile.exists()) {
			lineMsgList = new ArrayList<>();
		} else {
			//建立整条线路信息
			List<LineMsg> lineMsgs = new ArrayList<>();
			//文件流
			BufferedReader reader = null;
			try {
				reader = new BufferedReader(new InputStreamReader(new FileInputStream(lineMsgFile), "gbk"));
				String line;
				reader.readLine();
				while ((line = reader.readLine()) != null) {
					lineMsgs.add(new LineMsg(line));
				}
			} catch (IOException e) {
				e.printStackTrace();
			} finally {
				reader.close();
			}
			//赋值
			lineMsgList = lineMsgs;
		}
		//读站点信息
		if (!stationFile.exists()) stationList = new ArrayList<>();
		else {
			List<Station> stations = new ArrayList<>();
			List<Route> routes = null;
			try {
				if (routeFile.exists()) {
					routes = new ArrayList<>();
					Route lastRoute = new Route();

					BufferedReader routeReader = new BufferedReader(new InputStreamReader(new FileInputStream(routeFile), "gbk"));
					String line;

					routeReader.readLine();
					while ((line = routeReader.readLine()) != null) {
						Route route = new Route(line);
						lastRoute.setNextRoute(route);
						if (route.nextRouteId() < 0) {
							route.setNextRoute(null);
							lastRoute = new Route();
						}
						else lastRoute = route;
						routes.add(route);
					}

					routeReader.close();
				}
				BufferedReader stationReader = new BufferedReader(new InputStreamReader(new FileInputStream(stationFile), "gbk"));
				String line;

				stationReader.readLine();
				while ((line = stationReader.readLine()) != null) {
					Station station = new Station(line);

					if (routes != null && station.firstRouteId() >= 0) {
						station.setFirstRoute(routes.get(station.firstRouteId()));
					}
					else station.setFirstRoute(null);

					stations.add(station);
				}

				stationReader.close();
			} catch (IOException e) {
				e.printStackTrace();
			}

			stationList = stations;
		}
	}

	//保存入csv文件
	public void save() {
		File lineMsgFile = new File("line_msg.csv");
		File stationFile = new File("station.csv");
		File routeFile = new File("route.csv");

		try {
			BufferedWriter lineMsgWriter = new BufferedWriter (new OutputStreamWriter(new FileOutputStream(lineMsgFile),"gbk"));

			lineMsgWriter.write("id,name,detail");
			lineMsgWriter.newLine();
			for (LineMsg lineMsg : lineMsgList) {
				lineMsgWriter.write(lineMsg.toOutString());
				lineMsgWriter.newLine();
			}

			lineMsgWriter.close();

			BufferedWriter stationWriter = new BufferedWriter (new OutputStreamWriter(new FileOutputStream(stationFile),"gbk"));
			BufferedWriter routeWriter = new BufferedWriter (new OutputStreamWriter(new FileOutputStream(routeFile),"gbk"));

			stationWriter.write("id,pos_x,pos_y,name,first_route_id");
			stationWriter.newLine();
			routeWriter.write("id,msg_id,target_id,next_route_id");
			routeWriter.newLine();

			int routeId = 0;

			for (Station station : stationList) {
				Route curr = station.getFirstRoute();
				if (curr != null) {
					routeWriter.write(routeId + curr.toOutString() + ((curr.getNextRoute() == null) ? -1 : (routeId + 1)));
					routeWriter.newLine();
					stationWriter.write(station.toOutString() + routeId);
					stationWriter.newLine();
					routeId++;
					curr = curr.getNextRoute();
				} else {
					stationWriter.write(station.toOutString() + "-1");
					stationWriter.newLine();
					continue;
				}
				while(curr != null) {
					routeWriter.write(routeId + curr.toOutString() + ((curr.getNextRoute() == null) ? -1 : (routeId + 1)));
					routeWriter.newLine();
					routeId++;
					curr = curr.getNextRoute();
				}
			}

			stationWriter.close();
			routeWriter.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * 添加一个站点
	 * @param pos
	 * @param name
	 * @return
	 */
	public BusSystem addStation(Position pos, String name) {
		stationList.add(new Station(stationList.size(), pos, name, null));
		return this;
	}
	
	/**
	 * 添加一个线路
	 * @param startId
	 * @param tarId
	 * @param msgId
	 * @return
	 */
	public BusSystem addRoute(int startId, int tarId, int msgId) {
		Route newRoute = new Route(msgId, tarId, null);
		Station start = stationList.get(startId);
		
		if (start.getFirstRoute() == null) {
			start.setFirstRoute(newRoute);
		}
		else {
			Route curr = start.getFirstRoute();
			while(curr.getNextRoute() != null) {
				curr = curr.getNextRoute();
			}
			curr.setNextRoute(newRoute);
		}
		
		Route newRouteR = new Route(msgId, startId, null);
		Station startR = stationList.get(tarId);
		
		if (startR.getFirstRoute() == null) {
			startR.setFirstRoute(newRouteR);
		}
		else {
			Route curr = startR.getFirstRoute();
			while(curr.getNextRoute() != null) {
				curr = curr.getNextRoute();
			}
			curr.setNextRoute(newRouteR);
		}
		return this;
	}
	
	/**
	 * 添加一个线路信息
	 * @param name
	 * @param detail
	 * @return
	 */
	public BusSystem addLineMsg(String name, String detail) {
		lineMsgList.add(new LineMsg(lineMsgList.size(), name, detail));
		return this;
	}
	
	/**
	 * 查找两站之间的可通路线，返回字符串
	 * @param startId
	 * @param tarId
	 * @return
	 */
	public String searchLine(int startId, int tarId) {
		List<Route> res = searchLineList(startId, tarId);
		//System.out.println(res);
		
		if (res.isEmpty()) return stationList.get(startId).getName() + " 与 " + stationList.get(tarId).getName() + " 之间没有直达（不换乘）的路线";
		
		int time = 1;
		String out = "";
		String start = stationList.get(startId).getName();
		
		for (Route ans : res) {
			String aout = "";
			
			while(ans != null) {
				String lineName = lineMsgList.get(ans.getMsgId()).getName();
				String stationName = stationList.get(ans.getTargetId()).getName();
				aout = " --(" + lineName + ")--> " + stationName + aout;
				ans = ans.getNextRoute();
			}
			
			aout = start + aout;
			
			out = out + "路线" + time + ":\n" + aout + "\n\n";
			time++;
		}
		
		return out;
	}
	
	/**
	 * 查找两站之间的直达路线，返回字符串
	 * @param startId
	 * @param tarId
	 * @return
	 */
	public String searchStraight(int startId, int tarId) {
		List<Route> res = searchStraightList(startId, tarId);
		//System.out.println(res);
		
		if (res.isEmpty()) return stationList.get(startId).getName() + " 与 " + stationList.get(tarId).getName() + " 之间没有直达（不换乘）的路线";
		
		int time = 1;
		String out = "";
		
		for (Route ans : res) {
			String aout = stationList.get(startId).getName();
			
			String lineName = lineMsgList.get(ans.getMsgId()).getName();
			
			while (ans != null) {
				aout = aout + " --> " + stationList.get(ans.getTargetId()).getName();
				ans = ans.getNextRoute();
			}
			
			out = out + "路线" + time + " (乘坐 " + lineName + "):\n" + aout + "\n\n";
			time++;
		}
		return out;
	}
	
	public String searchTarLine(int msgId) {
		LineMsg msg = lineMsgList.get(msgId);
		String[] args = msg.getDetail().split(" ");
		List<Route> res = searchStraightList(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
		Route tar = null;
		for (Route route : res) {
			if (route.getMsgId() == msgId) tar = route;
		}
		
		if (tar == null) return "查询失败";
		
		String aout = "<html><body>" + "路经站点：<br>" + stationList.get(Integer.parseInt(args[0])).getName();
		
		while(tar != null) {
			aout = aout + "<br>" + stationList.get(tar.getTargetId()).getName();
			tar = tar.getNextRoute();
		}
		
		return aout + "<body></html>";
	}
	
	public String searchStationLine(int stationId) {
		Route curr = stationList.get(stationId).getFirstRoute();
		
		if (curr == null) return "无公交线";
		
		Set<LineMsg> set = new HashSet<>();
		
		
		while (curr != null) {
			set.add(lineMsgList.get(curr.getMsgId()));
			curr = curr.getNextRoute();
		}
		
		String aout = "<html><body>" + "公交线：";
		
		for (LineMsg msg : set) {
			aout = aout + "<br>" + msg.getName();
		}
		
		return aout + "<body></html>";
	}
	
	/**
	 * 查找两站之间的直达路线，返回列表
	 * @param startId
	 * @param tarId
	 * @return
	 */
	private List<Route> searchStraightList(int startId, int tarId) {
		List<Route> res = new ArrayList<>();
		
		Route curr = stationList.get(startId).getFirstRoute();
		while (curr != null) {
			Route ans = new Route(curr.getMsgId(), curr.getTargetId(), null);
			
			if (ans.getTargetId() == tarId) {
				res.add(ans);
				curr = curr.getNextRoute();
				continue;
			}
			
			Route cu = ans;
			int currId = startId;
			
			Route next = stationList.get(ans.getTargetId()).getFirstRoute();
			while (next != null) {
				if (next.getMsgId() == ans.getMsgId()) {
					if (next.getTargetId() == currId) {
						next = next.getNextRoute();
						continue;
					}
					
					currId = cu.getTargetId();
					cu.setNextRoute(new Route(next.getMsgId(), next.getTargetId(), null));
					cu = cu.getNextRoute();
					
					if (next.getTargetId() == tarId) {
						res.add(ans);
						break;
					}
					
					next = stationList.get(next.getTargetId()).getFirstRoute();
				}
				else next = next.getNextRoute();
			}
			
			curr = curr.getNextRoute();
		}
		
		return res;
	}
	
	/**
	 * 查找两站之间的可通路线，返回列表
	 * @param startId
	 * @param tarId
	 * @return
	 */
	private List<Route> searchLineList(int startId, int tarId) {
		List<Route> res = new ArrayList<>();
		//dfs(startId, tarId, startId, -1, false, res);
		dfsNoReturn(startId, tarId, startId, -1, false, null, res);
		
		return res;
	}
	
	private void dfsNoReturn(int startId, int tarId, int lastId, int lastMsgId, boolean changed, Route lastRoute, List<Route> res) {
		if (stationList.get(startId).getFirstRoute() == null) return;
		
		Route curr = stationList.get(startId).getFirstRoute();
		while (curr != null) {
			int nextId = curr.getTargetId();
			int currMsgId = curr.getMsgId();
			Route nextRoute = new Route(currMsgId, nextId, lastRoute);
			
			if (lastMsgId == -1) {
				if (nextRoute.getTargetId() == tarId) res.add(nextRoute);
				else dfsNoReturn(nextRoute.getTargetId(), tarId, startId, nextRoute.getMsgId(), changed, nextRoute, res);
			}
			else if (!changed && currMsgId != lastMsgId) {
				if (nextRoute.getTargetId() == tarId) res.add(nextRoute);
				else dfsNoReturn(nextRoute.getTargetId(), tarId, startId, nextRoute.getMsgId(), !changed, nextRoute, res);
			}
			else if (currMsgId == lastMsgId && nextId != lastId) {
				if (nextRoute.getTargetId() == tarId) res.add(nextRoute);
				else dfsNoReturn(nextRoute.getTargetId(), tarId, startId, nextRoute.getMsgId(), changed, nextRoute, res);
			}
			
			curr = curr.getNextRoute();
		}	
	}
	
	/**
	 * 通过站名查找id
	 * @param name
	 * @return
	 */
	public int searchStationId(String name) {
		for (Station station : stationList) {
			if (station.getName().equals(name)) return station.getId();
		}
		return -1;
	}
}
