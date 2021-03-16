package model;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class LineMsg {
	//线路id
	private int id;
	//线路名称-几路车
	private String name;
	//线路描述
	private String detail;

	@Override
	public String toString() {
		return "LineMsg [id=" + id + ", name=" + name + ", detail=" + detail + "]";
	}

	//输出到文件-逗号分隔符
	public String toOutString() {
		return id + "," + name + "," + detail;
	}

	//全构造
	public LineMsg(int id, String name, String detail) {
		this.id = id;
		this.name = name;
		this.detail = detail;
	}

	//一个字符串创建一个站点-处理
	public LineMsg(String inStr) {
		String[] strs = inStr.split(",");
		id = Integer.parseInt(strs[0]);
		name = strs[1];
		detail = strs[2];
	}

	public int getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDetail() {
		return detail;
	}

	public void setDetail(String detail) {
		this.detail = detail;
	}
	
}
