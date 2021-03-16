package model;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class LineMsg {
	//��·id
	private int id;
	//��·����-��·��
	private String name;
	//��·����
	private String detail;

	@Override
	public String toString() {
		return "LineMsg [id=" + id + ", name=" + name + ", detail=" + detail + "]";
	}

	//������ļ�-���ŷָ���
	public String toOutString() {
		return id + "," + name + "," + detail;
	}

	//ȫ����
	public LineMsg(int id, String name, String detail) {
		this.id = id;
		this.name = name;
		this.detail = detail;
	}

	//һ���ַ�������һ��վ��-����
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
