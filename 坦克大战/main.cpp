//===============================
//程序名称：坦克大战
//版本号：1.0
//制作人：杨新瑞
//
//创建时间：2017.3.27
//完工时间：2017.5.18
//代码量：10065行
//制作周期：21 天
//
//===============================

#include"functions.h"
athena::ADBConnector DB;

int main()
{
	ege::setinitmode(ege::INIT_ANIMATION + ege::INIT_WITHLOGO);
	// 图形初始化
	ege::initgraph(Win_W, Win_H);//初始化绘图环境
	setcaption("坦克大战 Demo"); //修改窗口名称
	setbkmode(TRANSPARENT);//设置输出文字时的背景模式为透明

	DB.connectTo("localhost", "siri", "root", "", 3306);
	if (!DB.isConnected())
	{
		setcolor(WHITE);
		setfont(50, 0, "楷体");
		setbkmode(TRANSPARENT);
		outtextxy((Win_W - 400) / 2, 250, "数据库连接失败!");
		ege::getch();
		return 0;
	}
	DB.query("update battle_city set count=count+1");
	// 随机数初始化
	ege::randomize();
	// 程序主循环
	mainloop();
	// 关闭绘图设备
	ege::closegraph();

	return 0;
}