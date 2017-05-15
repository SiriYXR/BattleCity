#include "gameScene_PVP.h"

gameScene_PVP::gameScene_PVP()
{
	map.init(PVP);
	map.load_design();

	isover = false;
	state = gaming;

	playerlife[0] = 5;
	playerlife[1] = 5;
	count_pass = 0;
	level = -1;

	inittankmap();
	initbulltemap();

	player_tank1.init_tank_player(bornQueue, map, Right);
	player_tank2.init_tank_player(bornQueue, map, Left, false);
	music.mu_Start();
}

gameScene_PVP::gameScene_PVP(int level)
{
	map.init(PVP);
	if (level > 0)
		map.load_PVP(level);
	else
		map.load_design();

	isover = false;
	state = gaming;

	playerlife[0] = 5;
	playerlife[1] = 5;
	count_pass = 0;
	this->level = level;

	inittankmap();
	initbulltemap();

	player_tank1.init_tank_player(bornQueue, map, Right);
	player_tank2.init_tank_player(bornQueue, map, Left, false);
	music.mu_Start();
}


gameScene_PVP::~gameScene_PVP()
{
}

void gameScene_PVP::update()
{
	if (state == gaming)
	{
		update_tankmap();
		update_bulletmap();
		player_tank1.update(map, tankmap, bulletmap, player_tank1, player_tank2, bombQueue, bornQueue, state, playerlife);
		update_tankmap();
		update_bulletmap();
		player_tank2.update(map, tankmap, bulletmap, player_tank1, player_tank2, bombQueue, bornQueue, state, playerlife);

		update_state();
	}

	if (state == lose1 || state == lose2)
	{
		if(!count_pass)
			music.mu_Lose();

		if (count_pass > 60)
		{
			ege::getch();
			isover = true;
		}
		count_pass++;
	}
}

void gameScene_PVP::render()
{
	picture.clear();

	rendMainface();
	map.rendermap1(picture);
	map.rendermaphome(picture);

	player_tank1.render(picture);
	player_tank2.render(picture);

	map.rendermap2(picture);
	rend_bomb();
	rend_born();

	if (state == pause)
		rend_pause();

	if (state == lose1 || state == lose2)
	{
		rend_end();
	}

	picture.rend();
}

bool gameScene_PVP::isOver()
{
	return isover;
}

void gameScene_PVP::onKey(key_msg key)
{
	if (state != lose1&&state != lose2)
	{
		if (state != pause)
		{
			onKey_Jand0(key);
			onKey_WASD(key);
			onKey_Direction(key);
		}
		onKey_P(key);
		onKey_ESC(key);
	}
}

void gameScene_PVP::update_tankmap()
{
	inittankmap();
	tankmap[player_tank1.aimx][player_tank1.aimy] = 1;
	tankmap[player_tank1.aimx + 1][player_tank1.aimy] = 1;
	tankmap[player_tank1.aimx][player_tank1.aimy + 1] = 1;
	tankmap[player_tank1.aimx + 1][player_tank1.aimy + 1] = 1;

	tankmap[player_tank2.aimx][player_tank2.aimy] = 1;
	tankmap[player_tank2.aimx + 1][player_tank2.aimy] = 1;
	tankmap[player_tank2.aimx][player_tank2.aimy + 1] = 1;
	tankmap[player_tank2.aimx + 1][player_tank2.aimy + 1] = 1;
}

void gameScene_PVP::update_bulletmap()
{
	initbulltemap();
	if (player_tank1.bullte.bullet)
		bulletmap[player_tank1.bullte.aimx][player_tank1.bullte.aimy] = 1;
	if (player_tank2.bullte.bullet)
		bulletmap[player_tank2.bullte.aimx][player_tank2.bullte.aimy] = 1;
}

void gameScene_PVP::update_state()
{
	isEnd();
}

void gameScene_PVP::onKey_Jand0(key_msg key)
{
	if (player_tank1.bullte.Canfire())
		if (key.key == key_J&&key.msg == key_msg_down)
		{
			if (player_tank1.level == 1)
				player_tank1.bullte.init(1, player_tank1.aimx, player_tank1.aimy, player_tank1.direct, 10);
			else
				player_tank1.bullte.init(1, player_tank1.aimx, player_tank1.aimy, player_tank1.direct, 20);
		}
	if (player_tank2.bullte.Canfire())
		if (key.key == key_num0&&key.msg == key_msg_down)
		{
			if (player_tank2.level == 1)
				player_tank2.bullte.init(1, player_tank2.aimx, player_tank2.aimy, player_tank2.direct, 10);
			else
				player_tank2.bullte.init(1, player_tank2.aimx, player_tank2.aimy, player_tank2.direct, 20);
		}
}

void gameScene_PVP::onKey_WASD(key_msg key)
{
	if (player_tank1.count == 0)
	{
		if (key.key == key_S&&key.msg == key_msg_down)
		{
			player_tank1.direct = Down;
			if (canmove1(key))
			{
				player_tank1.init_xy();
				player_tank1.aimy++;
				player_tank1.update_count();

			}
		}
		if (key.key == key_W&&key.msg == key_msg_down)
		{
			player_tank1.direct = Up;
			if (canmove1(key))
			{
				player_tank1.init_xy();
				player_tank1.aimy--;
				player_tank1.update_count();

			}
		}
		if (key.key == key_D&&key.msg == key_msg_down)
		{
			player_tank1.direct = Right;
			if (canmove1(key))
			{
				player_tank1.init_xy();
				player_tank1.aimx++;
				player_tank1.update_count();

			}
		}
		if (key.key == key_A&&key.msg == key_msg_down)
		{
			player_tank1.direct = Left;
			if (canmove1(key))
			{
				player_tank1.init_xy();
				player_tank1.aimx--;
				player_tank1.update_count();

			}
		}
	}
}

void gameScene_PVP::onKey_Direction(key_msg key)
{
	if (player_tank2.count == 0)
	{
		if (key.key == key_down&&key.msg == key_msg_down)
		{
			player_tank2.direct = Down;
			if (canmove2(key))
			{
				player_tank2.init_xy();
				player_tank2.aimy++;
				player_tank2.update_count();

			}
		}
		if (key.key == key_up&&key.msg == key_msg_down)
		{
			player_tank2.direct = Up;
			if (canmove2(key))
			{
				player_tank2.init_xy();
				player_tank2.aimy--;
				player_tank2.update_count();

			}
		}
		if (key.key == key_right&&key.msg == key_msg_down)
		{
			player_tank2.direct = Right;
			if (canmove2(key))
			{
				player_tank2.init_xy();
				player_tank2.aimx++;
				player_tank2.update_count();

			}
		}
		if (key.key == key_left&&key.msg == key_msg_down)
		{
			player_tank2.direct = Left;
			if (canmove2(key))
			{
				player_tank2.init_xy();
				player_tank2.aimx--;
				player_tank2.update_count();

			}
		}
	}
}

void gameScene_PVP::onKey_P(key_msg key)
{
	if (key.key == key_P&&key.msg == key_msg_down)
	{
		if (state == gaming)
			state = pause;
		else if (state == pause)
			state = gaming;
	}
}

void gameScene_PVP::onKey_ESC(key_msg key)
{
	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		if (Escloop(*this))
			isover = true;
		music.init();
		player_tank1.bullte.music.init();
		player_tank2.bullte.music.init();
	}
}

void gameScene_PVP::rendMainface()
{
	rend_bar(map_x, map_y, 20 * 26, 20 * 26);
	rendInformation();
}

void gameScene_PVP::rendInformation()
{
	setfillcolor(EGERGB(0xFB, 0xF8, 0xF1));
	bar(Win_W - 225, 0, Win_W, Win_H);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(EGERGB(0x92, 0x8B, 0x7B));
	setfont(25, 0, "楷体");

	if (level > 0)
		sprintf(str, "--第%d关--", level);
	else
		sprintf(str, "--自定义--");
	outtextxy(Win_W - 185, 50, str);
	outtextxy(Win_W - 185, 150, "-玩家1生命-");
	sprintf(str, "%d", playerlife[0]);
	outtextxy(Win_W - 130, 200, str);
	outtextxy(Win_W - 185, 250, "-玩家2生命-");
	sprintf(str, "%d", playerlife[1]);
	outtextxy(Win_W - 130, 300, str);

	putimage_withalpha(NULL, picture.instruction_duet, Win_W - 225, Win_H - 250);
}

void gameScene_PVP::rend_bar(int x, int y, int w, int h, int n, color_t color)
{
	setfillcolor(color);
	bar(x - n, y - n, x + w + n, y);
	bar(x - n, y + h, x + w + n, y + h + n);
	bar(x - n, y - n, x, y + h + n);
	bar(x + w + n, y - n, x + w, y + h + n);
}

void gameScene_PVP::rend_bomb()
{
	int size = bombQueue.getsize();
	for (int i = 0; i < size; i++)
	{
		if (bombQueue.front_count() == 0)
			bombQueue.pop();
		else
		{
			movieBomb(bombQueue.front_count(), bombQueue.front_x(), bombQueue.front_y(), picture);
			bombQueue.push(bombQueue.front_x(), bombQueue.front_y(), bombQueue.front_count() - 1);
			bombQueue.pop();
		}
	}
}

void gameScene_PVP::rend_born()
{
	int size = bornQueue.getsize();
	for (int i = 0; i < size; i++)
	{
		if (bornQueue.front_count() == 0)
			bornQueue.pop();
		else
		{
			movieBorn(bornQueue.front_count(), bornQueue.front_x(), bornQueue.front_y(), picture);
			bornQueue.push(bornQueue.front_x(), bornQueue.front_y(), bornQueue.front_count() - 1);
			bornQueue.pop();
		}
	}
}

void gameScene_PVP::rend_end()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(WHITE);

	setfont(100, 0, "楷体");
	if (state == lose1)
		outtextxy((Win_W - 500) / 2, 200, "玩家2获胜！");
	else
		outtextxy((Win_W - 360) / 2, 150, "玩家1获胜！");

	if (count_pass > 50)
	{
		setfont(40, 0, "楷体");
		outtextxy((Win_W - 240) / 2, Win_H - 70, "按任意键退出");
	}

	delimage(blackbar);
}

void gameScene_PVP::rend_pause()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);
	setfont(60, 0, "楷体");
	outtextxy((Win_W - 360) / 2, (Win_H - 60) / 2, "按P键继续");
	delimage(blackbar);
}

void gameScene_PVP::isEnd()
{
	if (playerlife[0] == 0)
		state = lose1;
	else if (playerlife[1] == 0)
		state = lose2;
}

void gameScene_PVP::init()
{
	isover = false;
	state = gaming;

	count_pass = 0;

	inittankmap();
	initbulltemap();

	player_tank1.init_tank_player(bornQueue, map);
	player_tank2.init_tank_player(bornQueue, map);
	music.init();
	music.mu_Start();
}

void gameScene_PVP::initgame()
{
	init();
	if (level)
		map.load_PVP(level);
	else
		map.load_design();
}

void gameScene_PVP::inittankmap()
{
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			tankmap[i][j] = 0;
}

void gameScene_PVP::initbulltemap()
{
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			bulletmap[i][j] = 0;
}

bool gameScene_PVP::canmove1( key_msg key)
{
	if (player_tank1.count == 0)
	{
		switch (key.key)
		{
		case key_W:
			if (player_tank1.aimy <= 0)
				return false;
			if (tankmap[player_tank1.aimx][player_tank1.aimy - 1] != 0 || tankmap[player_tank1.aimx + 1][player_tank1.aimy - 1] != 0)
				return false;
			if (map.getmember(0, player_tank1.aimx, player_tank1.aimy - 1) != land || map.getmember(0, player_tank1.aimx + 1, player_tank1.aimy - 1) != land)
				return false;
			if (map.getmember(1, player_tank1.aimx, player_tank1.aimy - 1) == home || map.getmember(1, player_tank1.aimx + 1, player_tank1.aimy - 1) == home)
				return false;
			if (map.getmember(1, player_tank1.aimx, player_tank1.aimy - 1) == home_h || map.getmember(1, player_tank1.aimx + 1, player_tank1.aimy - 1) == home_h)
				return false;
			break;
		case key_S:
			if (player_tank1.aimy >= 24)
				return false;
			if (tankmap[player_tank1.aimx][player_tank1.aimy + 2] != 0 || tankmap[player_tank1.aimx + 1][player_tank1.aimy + 2] != 0)
				return false;
			if (map.getmember(0, player_tank1.aimx, player_tank1.aimy + 2) != land || map.getmember(0, player_tank1.aimx + 1, player_tank1.aimy + 2) != land)
				return false;
			if (map.getmember(1, player_tank1.aimx, player_tank1.aimy + 2) == home || map.getmember(1, player_tank1.aimx + 1, player_tank1.aimy + 2) == home)
				return false;
			if (map.getmember(1, player_tank1.aimx, player_tank1.aimy + 2) == home_h || map.getmember(1, player_tank1.aimx + 1, player_tank1.aimy + 2) == home_h)
				return false;
			break;
		case key_D:
			if (player_tank1.aimx >= 24)
				return false;
			if (tankmap[player_tank1.aimx + 2][player_tank1.aimy] != 0 || tankmap[player_tank1.aimx + 2][player_tank1.aimy + 1] != 0)
				return false;
			if (map.getmember(0, player_tank1.aimx + 2, player_tank1.aimy) != land || map.getmember(0, player_tank1.aimx + 2, player_tank1.aimy + 1) != land)
				return false;
			if (map.getmember(1, player_tank1.aimx + 2, player_tank1.aimy) == home || map.getmember(1, player_tank1.aimx + 2, player_tank1.aimy + 1) == home)
				return false;
			if (map.getmember(1, player_tank1.aimx + 2, player_tank1.aimy) == home_h || map.getmember(1, player_tank1.aimx + 2, player_tank1.aimy + 1) == home_h)
				return false;
			break;
		case key_A:
			if (player_tank1.aimx <= 0)
				return false;
			if (tankmap[player_tank1.aimx - 1][player_tank1.aimy] != 0 || tankmap[player_tank1.aimx - 1][player_tank1.aimy + 1] != 0)
				return false;
			if (map.getmember(0, player_tank1.aimx - 1, player_tank1.aimy) != land || map.getmember(0, player_tank1.aimx - 1, player_tank1.aimy + 1) != land)
				return false;
			if (map.getmember(1, player_tank1.aimx - 1, player_tank1.aimy) == home || map.getmember(1, player_tank1.aimx - 1, player_tank1.aimy + 1) == home)
				return false;
			if (map.getmember(1, player_tank1.aimx - 1, player_tank1.aimy) == home_h || map.getmember(1, player_tank1.aimx - 1, player_tank1.aimy + 1) == home_h)
				return false;
			break;
		}
		return true;
	}
	else
		return false;
}

bool gameScene_PVP::canmove2(key_msg key)
{
	if (player_tank2.count == 0)
	{
		switch (key.key)
		{
		case key_up:
			if (player_tank2.aimy <= 0)
				return false;
			if (tankmap[player_tank2.aimx][player_tank2.aimy - 1] != 0 || tankmap[player_tank2.aimx + 1][player_tank2.aimy - 1] != 0)
				return false;
			if (map.getmember(0, player_tank2.aimx, player_tank2.aimy - 1) != land || map.getmember(0, player_tank2.aimx + 1, player_tank2.aimy - 1) != land)
				return false;
			if (map.getmember(1, player_tank2.aimx, player_tank2.aimy - 1) == home || map.getmember(1, player_tank2.aimx + 1, player_tank2.aimy - 1) == home)
				return false;
			if (map.getmember(1, player_tank2.aimx, player_tank2.aimy - 1) == home_h || map.getmember(1, player_tank2.aimx + 1, player_tank2.aimy - 1) == home_h)
				return false;
			break;
		case key_down:
			if (player_tank2.aimy >= 24)
				return false;
			if (tankmap[player_tank2.aimx][player_tank2.aimy + 2] != 0 || tankmap[player_tank2.aimx + 1][player_tank2.aimy + 2] != 0)
				return false;
			if (map.getmember(0, player_tank2.aimx, player_tank2.aimy + 2) != land || map.getmember(0, player_tank2.aimx + 1, player_tank2.aimy + 2) != land)
				return false;
			if (map.getmember(1, player_tank2.aimx, player_tank2.aimy + 2) == home || map.getmember(1, player_tank2.aimx + 1, player_tank2.aimy + 2) == home)
				return false;
			if (map.getmember(1, player_tank2.aimx, player_tank2.aimy + 2) == home_h || map.getmember(1, player_tank2.aimx + 1, player_tank2.aimy + 2) == home_h)
				return false;
			break;
		case key_right:
			if (player_tank2.aimx >= 24)
				return false;
			if (tankmap[player_tank2.aimx + 2][player_tank2.aimy] != 0 || tankmap[player_tank2.aimx + 2][player_tank2.aimy + 1] != 0)
				return false;
			if (map.getmember(0, player_tank2.aimx + 2, player_tank2.aimy) != land || map.getmember(0, player_tank2.aimx + 2, player_tank2.aimy + 1) != land)
				return false;
			if (map.getmember(1, player_tank2.aimx + 2, player_tank2.aimy) == home || map.getmember(1, player_tank2.aimx + 2, player_tank2.aimy + 1) == home)
				return false;
			if (map.getmember(1, player_tank2.aimx + 2, player_tank2.aimy) == home_h || map.getmember(1, player_tank2.aimx + 2, player_tank2.aimy + 1) == home_h)
				return false;
			break;
		case key_left:
			if (player_tank2.aimx <= 0)
				return false;
			if (tankmap[player_tank2.aimx - 1][player_tank2.aimy] != 0 || tankmap[player_tank2.aimx - 1][player_tank2.aimy + 1] != 0)
				return false;
			if (map.getmember(0, player_tank2.aimx - 1, player_tank2.aimy) != land || map.getmember(0, player_tank2.aimx - 1, player_tank2.aimy + 1) != land)
				return false;
			if (map.getmember(1, player_tank2.aimx - 1, player_tank2.aimy) == home || map.getmember(1, player_tank2.aimx - 1, player_tank2.aimy + 1) == home)
				return false;
			if (map.getmember(1, player_tank2.aimx - 1, player_tank2.aimy) == home_h || map.getmember(1, player_tank2.aimx - 1, player_tank2.aimy + 1) == home_h)
				return false;
			break;
		}
		return true;
	}
	else
		return false;
}

