package main;

import model.BusSystem;
import view.MainWindow;
import java.io.IOException;

/**
 * @mail qyyzxty@icloud.com
 * @author xty
 * @data 2021/3/6
 **/
public class Application {
	public static void main(String[] args) throws IOException {
		BusSystem bsys = new BusSystem();
		new MainWindow().setBusSystem(bsys).setVisible(true);
	}
}