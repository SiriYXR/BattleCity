#include "designer_PVP.h"
#include"functions.h"
#include"Picture.h"
#include"map.h"
#include"Music.h"

designer_PVP::designer_PVP()
{

	isover = false;
	issave = true;
	saveOK = false;
	bigsize = true;

	cursor1_x = map_x;
	cursor1_y = map_y;
	cursor2_x = Win_W - 136 + 4;
	cursor2_y = map_y + 4;

	enemynum = 0;

	tempmap.init(PVP);


	tempmap.load_design();
}

void designer_PVP::init()
{
	tempmap.init(PVP);
	enemynum = 0;

}

designer_PVP::~designer_PVP()
{
}

void designer_PVP::update()
{

	update_size();

}

void designer_PVP::update_size()
{
	if (cursor2_y >= map_y + 12 + 80 && cursor2_y < map_y + 20 + 160)
	{
		if (cursor1_y >= map_y + 24 * 20 + 4)
			cursor1_y = map_y + 24 * 20;
		if (cursor1_x >= map_x + 24 * 20 + 4)
			cursor1_x = map_x + 24 * 20;
		bigsize = true;
	}
}

void designer_PVP::update_saveOK()
{
	saveOK = false;
}

bool designer_PVP::isOver()
{
	return isover;
}

void designer_PVP::onKey(key_msg key)
{
	if (key.msg == key_msg_down)
		saveOK = false;

	key_WASD(key);
	key_direction(key);
	key_Space(key);
	key_Shift(key);
	key_ESC(key);

}

void designer_PVP::key_direction(key_msg key)
{
	if (key.key == key_down&&key.msg == key_msg_down&&cursor2_y < map_y + 28 + 240)
	{
		cursor2_y += 44;
		music.mu_Switch();
	}
	if (key.key == key_up&&key.msg == key_msg_down&&cursor2_y > map_y + 4)
	{
		cursor2_y -= 44;
		music.mu_Switch();
	}
	if (key.key == key_right&&key.msg == key_msg_down&&cursor2_x < Win_W - 136 + 8 + 40)
	{
		cursor2_x += 44;
		music.mu_Switch();
	}
	if (key.key == key_left&&key.msg == key_msg_down&&cursor2_x > Win_W - 136 + 4)
	{
		cursor2_x -= 44;
		music.mu_Switch();
	}
}

void designer_PVP::key_WASD(key_msg key)
{
	if (key.key == key_S&&key.msg == key_msg_down)
	{
		if (!bigsize && cursor1_y < map_y + 24 * 20 + 4)
		{
			cursor1_y += 20;
			music.mu_Switch();
		}
		else if (bigsize && cursor1_y < map_y + 23 * 20 + 4)
		{
			cursor1_y += 20;
			music.mu_Switch();
		}
	}
	if (key.key == key_W&&key.msg == key_msg_down&&cursor1_y > map_y + 4)
	{
		cursor1_y -= 20;
		music.mu_Switch();
	}
	if (key.key == key_D&&key.msg == key_msg_down)
	{
		if (!bigsize && cursor1_x < 26 * 20 + 4)
		{
			cursor1_x += 20;
			music.mu_Switch();
		}
		else if (bigsize && cursor1_x < 25 * 20 + 4)
		{
			cursor1_x += 20;
			music.mu_Switch();
		}
	}
	if (key.key == key_A&&key.msg == key_msg_down&&cursor1_x > map_x + 4)
	{
		cursor1_x -= 20;
		music.mu_Switch();
	}
}

void designer_PVP::key_Space(key_msg key)
{
	if (key.key == key_space&&key.msg == key_msg_down)
	{
		music.mu_Switch();

		if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 4)
		{
			if (bigsize)
			{
				if (isOK_4())
				{
					tempmap.setmapmember_4(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, stone);
					issave = false;
				}
			}
			else
			{
				if (isOK())
				{
					tempmap.setmember(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, stone);
					issave = false;
				}
			}
		}
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 4)
		{
			if (bigsize)
			{
				if (isOK_4())
				{
					tempmap.setmapmember_4(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, steel);
					issave = false;
				}
			}
			else
			{
				if (isOK())
				{
					tempmap.setmember(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, steel);
					issave = false;
				}
			}
		}
		else if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 8 + 40)
		{
			if (bigsize)
			{
				if (isOK_4())
				{
					tempmap.setmapmember_4(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, water);
					issave = false;

				}
			}
			else
			{
				if (isOK())
				{
					tempmap.setmember(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, water);
					issave = false;
				}
			}
		}
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 8 + 40)
		{
			if (bigsize)
			{
				if (isOK_4())
				{
					tempmap.setmapmember_4(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, grass);
					issave = false;
				}
			}
			else
			{
				if (isOK())
				{
					tempmap.setmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, grass);
					issave = false;
				}
			}
		}
		else if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 16 + 120)
		{
			if (isOK_4_player1())
			{
				tempmap.setmapmember_4_plus(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, player1born);
				issave = false;
			}
		}
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 16 + 120)
		{
			if (isOK_4_player2())
			{
				tempmap.setmapmember_4_plus(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, player2born);
				issave = false;
			}
		}

		if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 20 + 160)
		{
			if (bigsize)
			{
				if (isOK_4())
				{
					tempmap.setmapmember_4(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, land);
					tempmap.setmapmember_4(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, land);
					issave = false;
				}
			}
			else
				if (isOK())
				{
					tempmap.setmember(0, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, land);
					tempmap.setmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20, land);
					issave = false;
				}

		}


		if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 20 + 160)
			init();

		if (cursor2_y == map_y + 24 + 200)
		{
			tempmap.save_design();
			issave = true;
			saveOK = true;
		}

		if (cursor2_y == map_y + 28 + 240)
		{
			if (issave)
				isover = true;
			else
			{
				isoverloop(*this);
				music.init();
				music.mu_Switch();
			}
		}
	}
}

void designer_PVP::key_ESC(key_msg key)
{
	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		if (issave)
			isover = true;
		else
		{
			music.mu_Switch();
			isoverloop(*this);
			music.init();
			music.mu_Switch();
		}
	}
}

void designer_PVP::key_Shift(key_msg key)
{
	if (key.key == key_shift&&key.msg == key_msg_down)
	{
		if (cursor1_y >= map_y + 24 * 20 + 4)
			cursor1_y = map_y + 24 * 20;
		if (cursor1_x >= map_x + 24 * 20 + 4)
			cursor1_x = map_x + 24 * 20;
		bigsize = !bigsize;
		music.mu_Switch();
	}
}

void designer_PVP::render()
{
	picture.clear();

	mainface();
	tempmap.rendAll(picture);

	rendCursor1();
	rendCursor2();

	picture.rend();
}


void designer_PVP::mainface()
{
	rend_bar(map_x, map_y, 20 * 26, 20 * 26);
	rend_bar(Win_W - 136, map_y, 92, 312);
	rend_bar(Win_W - 136, map_y + 344, 92, 92 / 2);

	putimage_withalpha(NULL, picture.wall_stone_4, Win_W - 136 + 4, map_y + 4);
	putimage_withalpha(NULL, picture.water_4, Win_W - 136 + 4, map_y + 8 + 40);
	putimage_withalpha(NULL, picture.home, Win_W - 136 + 4, map_y + 12 + 80);
	putimage_withalpha(NULL, picture.player1born, Win_W - 136 + 4, map_y + 16 + 120);
	putimage_withalpha(NULL, picture.d_delete, Win_W - 136 + 4, map_y + 20 + 160);


	putimage_withalpha(NULL, picture.wall_steel_4, Win_W - 136 + 8 + 40, map_y + 4);
	putimage_withalpha(NULL, picture.grass_4, Win_W - 136 + 8 + 40, map_y + 8 + 40);
	putimage_withalpha(NULL, picture.enemyborn, Win_W - 136 + 8 + 40, map_y + 12 + 80);
	putimage_withalpha(NULL, picture.player2born, Win_W - 136 + 8 + 40, map_y + 16 + 120);
	putimage_withalpha(NULL, picture.d_clean, Win_W - 136 + 8 + 40, map_y + 20 + 160);

	putimage_withalpha(NULL, picture.d_save, Win_W - 136 + 4, map_y + 24 + 200);
	putimage_withalpha(NULL, picture.d_return, Win_W - 136 + 4, map_y + 28 + 240);

	rend_information();

}

void designer_PVP::rend_information()
{
	//文字
	setcolor(WHITE);
	setfont(25, 0, "楷体");
	setbkmode(TRANSPARENT);

	if (saveOK)
	{
		setfont(20, 0, "楷体");
		outtextxy(Win_W - 135, map_y + 354, "保存成功!");
	}
	else
	{
		if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 4)
			outtextxy(Win_W - 120, map_y + 354, "砖 墙");
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 4)
			outtextxy(Win_W - 120, map_y + 354, "钢 墙");
		else if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 8 + 40)
			outtextxy(Win_W - 120, map_y + 354, " 水");
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 8 + 40)
			outtextxy(Win_W - 120, map_y + 354, "草 丛");
		else if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 12 + 80)
			outtextxy(Win_W - 120, map_y + 354, "基 地");
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 12 + 80)
		{
			setfont(16, 0, "楷体");
			outtextxy(Win_W - 133, map_y + 359, "敌人出生点");
		}
		else if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 16 + 120)
		{
			setfont(16, 0, "楷体");
			outtextxy(Win_W - 135, map_y + 359, "玩家1出生点");
		}
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 16 + 120)
		{
			setfont(16, 0, "楷体");
			outtextxy(Win_W - 135, map_y + 359, "玩家2出生点");
		}
		else if (cursor2_x == Win_W - 136 + 4 && cursor2_y == map_y + 20 + 160)
			outtextxy(Win_W - 120, map_y + 354, "删 除");
		else if (cursor2_x == Win_W - 136 + 8 + 40 && cursor2_y == map_y + 20 + 160)
			outtextxy(Win_W - 120, map_y + 354, "清 空");
		else if (cursor2_y == map_y + 24 + 200)
			outtextxy(Win_W - 120, map_y + 354, "保 存");
		else if (cursor2_y == map_y + 28 + 240)
			outtextxy(Win_W - 120, map_y + 354, "返 回");
	}

	setfont(20, 0, "楷体");
	outtextxy(Win_W - 200, map_y + 420, "左光标WASD操控");
	outtextxy(Win_W - 200, map_y + 450, "右光标方向键操控");
	outtextxy(Win_W - 200, map_y + 480, "空格键确认");
	outtextxy(Win_W - 195, map_y + 510, "ESC键退出");

	outtextxy(170, Win_H - 30, "（建议在英文模式下编辑）");
}

void designer_PVP::rendCursor1()
{
	if (bigsize)
		rend_bar(cursor1_x, cursor1_y, 40, 40);
	else
		rend_bar(cursor1_x, cursor1_y, 20, 20);
}

void designer_PVP::rendCursor2()
{
	if (cursor2_y >= map_y + 24 + 200)
		rend_bar(Win_W - 136 + 4, cursor2_y, 84, 40);
	else
		rend_bar(cursor2_x, cursor2_y, 40, 40);
}

void designer_PVP::rend_bar(int x, int y, int w, int h, int n, color_t color)
{
	setfillcolor(color);
	bar(x - n, y - n, x + w + n, y);
	bar(x - n, y + h, x + w + n, y + h + n);
	bar(x - n, y - n, x, y + h + n);
	bar(x + w + n, y - n, x + w, y + h + n);
}

bool designer_PVP::isOK()
{
	if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home)
		if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home_h)
			if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != enemyborn)
				if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player1born)
					if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player2born)
						return true;
	return false;
}

bool designer_PVP::isOK_4()
{
	if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home)
		if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home_h)
			if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != enemyborn)
				if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player1born)
					if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player2born)
						if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != home)
							if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != home_h)
								if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != enemyborn)
									if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != player1born)
										if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != player2born)
											if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != home)
												if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != home_h)
													if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != enemyborn)
														if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != player1born)
															if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != player2born)
																if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != home)
																	if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != home_h)
																		if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != enemyborn)
																			if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != player1born)
																				if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != player2born)
																					return true;
	return false;
}

bool designer_PVP::isOK_4_home()
{

	if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != enemyborn)
		if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player1born)
			if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player2born)
				if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != enemyborn)
					if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != player1born)
						if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != player2born)
							if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != enemyborn)
								if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != player1born)
									if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != player2born)
										if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != enemyborn)
											if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != player1born)
												if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != player2born)
													return true;
	return false;
}

bool designer_PVP::isOK_4_player1()
{
	if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home)
		if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home_h)
			if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != enemyborn)
				if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player2born)
					if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != home)
						if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != home_h)
							if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != enemyborn)
								if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != player2born)
									if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != home)
										if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != home_h)
											if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != enemyborn)
												if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != player2born)
													if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != home)
														if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != home_h)
															if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != enemyborn)
																if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != player2born)
																	return true;
	return false;
}

bool designer_PVP::isOK_4_player2()
{
	if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home)
		if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home_h)
			if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != enemyborn)
				if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player1born)
					if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != home)
						if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != home_h)
							if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != enemyborn)
								if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20) != player1born)
									if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != home)
										if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != home_h)
											if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != enemyborn)
												if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20 + 1) != player1born)
													if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != home)
														if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != home_h)
															if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != enemyborn)
																if (tempmap.getmember(1, (cursor1_x - map_x) / 20 + 1, (cursor1_y - map_y) / 20 + 1) != player1born)
																	return true;
	return false;
}

bool designer_PVP::isOK_4_delete()
{
	if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home)
		if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != home_h)
			if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player1born)
				if (tempmap.getmember(1, (cursor1_x - map_x) / 20, (cursor1_y - map_y) / 20) != player2born)
					return true;
	return false;
}