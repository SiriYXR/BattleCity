#include "gameScene_PVE_duet.h"

gameScene_PVE_duet::gameScene_PVE_duet()
{
	map.init(PVE);
	map.load_design();
	this->level = -1;

	isover = false;
	state = gaming;

	playerlife = 10;
	score = 0;
	historyscore = 0;
	enemynum = 20;
	count_pass = 0;
	count_enemypause = 0;

	inittankmap();
	initbulletmap();

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	historyscore = atoi(result["score"].c_str());

	player_tank1.init_tank_player(bornQueue, map, Up);
	player_tank2.init_tank_player(bornQueue, map, Up, false);
	delete_enemy();
	delete_property();
	music.mu_Start();
}

gameScene_PVE_duet::gameScene_PVE_duet(int level)
{
	map.init(PVE);
	if (level > 0)
	{
		map.load_PVE(level);
		char buffer[255];
		sprintf(buffer, "update battle_city set lastlevel = ('%d') where mainKey = 1", level);
		DB.query(buffer);
	}
	else
		map.load_design();

	this->level = level;
	isover = false;
	state = gaming;

	playerlife = 10;
	score = 0;
	historyscore = 0;
	enemynum = 20;
	count_pass = 0;
	count_enemypause = 0;

	inittankmap();
	initbulletmap();

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	historyscore = atoi(result["score"].c_str());

	player_tank1.init_tank_player(bornQueue, map, Up);
	player_tank2.init_tank_player(bornQueue, map, Up, false);
	delete_enemy();
	delete_property();
	music.mu_Start();
}


gameScene_PVE_duet::~gameScene_PVE_duet()
{
	delete_enemy();
	delete_property();
}

void gameScene_PVE_duet::update()
{
	if (state == gaming)
	{
		update_tankmap();
		update_bulletmap();
		player_tank1.update(map, tankmap, bulletmap, player_tank1, player_tank2, enemyQueue, deadenemyQueue,propertyQueue, bombQueue, bornQueue, state, playerlife, enemynum, score);
		update_tankmap();
		update_bulletmap();
		player_tank2.update(map, tankmap, bulletmap, player_tank1, player_tank2, enemyQueue, deadenemyQueue, propertyQueue, bombQueue, bornQueue, state, playerlife, enemynum, score);
		update_tankmap();
		update_bulletmap();
		update_enemyborn();

		if (!count_enemypause)
		{
			int n = enemyQueue.size();
			while (n--)
			{
				update_tankmap();
				update_bulletmap();
				enemyQueue.front()->update(map, tankmap, bulletmap, player_tank1, player_tank2, enemyQueue, deadenemyQueue, propertyQueue, bombQueue, bornQueue, state, playerlife, enemynum, score);
				enemyQueue.push(enemyQueue.front());
				enemyQueue.pop();
			}
		}
		else
			count_enemypause--;

		update_state();
	}

	if (state == pass)
	{
		if (count_pass > 60)
		{
			char ch;

			if (level > 20 || level < 0)
			{
				ege::getch();
				isover = true;
			}
			else
			{
				ch = ege::getch();
				if (ch == 27)
					isover = true;
				else
				{
					level++;
					int maxlevel;
					char buffer[255];

					sprintf(buffer, "update battle_city set lastlevel = ('%d') where mainKey = 1", level);
					DB.query(buffer);

					auto result = DB.query("select * from battle_city where mainKey=1");
					result.next();
					maxlevel = atoi(result["maxlevel"].c_str());

					if (level > maxlevel)
					{
						sprintf(buffer, "update battle_city set maxlevel = ('%d') where mainKey = 1", level);
						DB.query(buffer);
					}
					initgame();
				}
			}
		}
		count_pass++;
	}
}

void gameScene_PVE_duet::render()
{
	picture.clear();

	rendMainface();
	map.rendermap1(picture);
	map.rendermaphome(picture);

	rend_prop();

	player_tank1.render(picture);
	player_tank2.render(picture);
	int n = enemyQueue.size();
	while (n--)
	{
		enemyQueue.front()->render(picture);
		enemyQueue.push(enemyQueue.front());
		enemyQueue.pop();
	}

	map.rendermap2(picture);
	rend_bomb();
	rend_born();

	if (state == lose)
		rend_lose();

	if (state == pause)
		rend_pause();

	if (state == pass)
	{
		if (level == 20)
		{
			rend_through();
		}
		else
		{
			rend_pass();
		}
	}

	picture.rend();
}

bool gameScene_PVE_duet::isOver()
{
	return isover;
}

void gameScene_PVE_duet::onKey(key_msg key)
{
	if (state != lose)
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
	else if (state == lose)
	{
		ege::getch();
		isover = true;
	}
}

void gameScene_PVE_duet::update_enemyborn()
{
	static int count = 100;
	if (enemynum > enemyQueue.size())
	{
		if (enemyQueue.size() < 4)
		{
			count++;
			if (count > 100 && enemycanBorn())
			{
				tanke_enemy *t = new tanke_enemy(bornQueue, map, tankmap);
				enemyQueue.push(t);
				count = 0;
			}
		}
	}
}

void gameScene_PVE_duet::update_tankmap()
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
	int n = enemyQueue.size();
	while (n--)
	{
		tankmap[enemyQueue.front()->aimx][enemyQueue.front()->aimy] = 1;
		tankmap[enemyQueue.front()->aimx + 1][enemyQueue.front()->aimy] = 1;
		tankmap[enemyQueue.front()->aimx][enemyQueue.front()->aimy + 1] = 1;
		tankmap[enemyQueue.front()->aimx + 1][enemyQueue.front()->aimy + 1] = 1;
		enemyQueue.push(enemyQueue.front());
		enemyQueue.pop();
	}
}

void gameScene_PVE_duet::update_bulletmap()
{
	initbulletmap();
	if (player_tank1.bullte.bullet)
		bulletmap[player_tank1.bullte.aimx][player_tank1.bullte.aimy] = 1;
	if (player_tank2.bullte.bullet)
		bulletmap[player_tank2.bullte.aimx][player_tank2.bullte.aimy] = 1;
	int n = enemyQueue.size();
	while (n--)
	{
		if (enemyQueue.front()->bullte.bullet)
			bulletmap[enemyQueue.front()->bullte.aimx][enemyQueue.front()->bullte.aimy] = 1;
		enemyQueue.push(enemyQueue.front());
		enemyQueue.pop();
	}
}

void gameScene_PVE_duet::update_state()
{
	isLose();
	isPass();
}

void gameScene_PVE_duet::update_proptime()
{
	int n = propertyQueue.size();
	while (n--)
	{
		if (propertyQueue.front()->time)
		{
			propertyQueue.front()->time--;
			propertyQueue.push(propertyQueue.front());
			propertyQueue.pop();
		}
		else
		{
			prop *p;
			p = propertyQueue.front();
			delete p;
			p = NULL;
			propertyQueue.pop();
		}
	}
}

void gameScene_PVE_duet::onKey_Jand0(key_msg key)
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

void gameScene_PVE_duet::onKey_WASD(key_msg key)
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
				getProp(player_tank1);
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
				getProp(player_tank1);
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
				getProp(player_tank1);
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
				getProp(player_tank1);
				player_tank1.update_count();
			}
		}
	}
}

void gameScene_PVE_duet::onKey_Direction(key_msg key)
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
				getProp(player_tank2);
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
				getProp(player_tank2);
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
				getProp(player_tank2);
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
				getProp(player_tank2);
				player_tank2.update_count();
			}
		}
	}
}

void gameScene_PVE_duet::onKey_P(key_msg key)
{
	if (key.key == key_P&&key.msg == key_msg_down)
	{
		if (state == gaming)
			state = pause;
		else if (state == pause)
			state = gaming;
	}
}

void gameScene_PVE_duet::onKey_ESC(key_msg key)
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

void gameScene_PVE_duet::rendMainface()
{
	rend_bar(map_x, map_y, 20 * 26, 20 * 26);
	rendInformation();
}

void gameScene_PVE_duet::rendInformation()
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
	outtextxy(Win_W - 185, 100, "-玩家生命-");
	sprintf(str, "%d", playerlife);
	outtextxy(Win_W - 130, 130, str);
	outtextxy(Win_W - 185, 180, "-玩家得分-");
	sprintf(str, "%d", score);
	outtextxy(Win_W - 150, 210, str);
	outtextxy(Win_W - 185, 280, "-敌人数量-");
	sprintf(str, "%d", enemynum);
	outtextxy(Win_W - 130, 310, str);

	putimage_withalpha(NULL, picture.instruction_duet, Win_W - 225, Win_H - 250);
}

void gameScene_PVE_duet::rend_bar(int x, int y, int w, int h, int n, color_t color)
{
	setfillcolor(color);
	bar(x - n, y - n, x + w + n, y);
	bar(x - n, y + h, x + w + n, y + h + n);
	bar(x - n, y - n, x, y + h + n);
	bar(x + w + n, y - n, x + w, y + h + n);
}

void gameScene_PVE_duet::rend_bomb()
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

void gameScene_PVE_duet::rend_born()
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

void gameScene_PVE_duet::rend_prop()
{
	int n = propertyQueue.size();
	while (n--)
	{
		switch (propertyQueue.front()->pro)
		{
		case tank:
			putimage(map_x + propertyQueue.front()->x * 20, map_y + propertyQueue.front()->y * 20, picture.life);
			break;
		case bomb:
			putimage(map_x + propertyQueue.front()->x * 20, map_y + propertyQueue.front()->y * 20, picture.bomb);
			break;
		case star:
			putimage(map_x + propertyQueue.front()->x * 20, map_y + propertyQueue.front()->y * 20, picture.star);
			break;
		case timer:
			putimage(map_x + propertyQueue.front()->x * 20, map_y + propertyQueue.front()->y * 20, picture.timer);
			break;
		case sheld:
			putimage(map_x + propertyQueue.front()->x * 20, map_y + propertyQueue.front()->y * 20, picture.shield);
			break;
		default:
			break;
		}
		propertyQueue.push(propertyQueue.front());
		propertyQueue.pop();
	}
}

void gameScene_PVE_duet::rend_lose()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);
	putimage_withalpha(NULL, picture.over, (Win_W - 437) / 2, 50);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(WHITE);

	if (score > historyscore)
	{
		setfont(50, 0, "楷体");
		sprintf(str, "新纪录：%d", score);
		outtextxy(230, 350, str);
		char buffer[255];
		sprintf(buffer, "update battle_city set score = ('%d') where mainKey = 1", score);
		DB.query(buffer);
	}
	else
	{
		setfont(40, 0, "楷体");
		sprintf(str, "历史最高分：%d", historyscore);
		outtextxy(230, 300, str);
		sprintf(str, "最终得分分：%d", score);
		outtextxy(230, 400, str);
	}

	setfont(40, 0, "楷体");
	outtextxy((Win_W - 240) / 2, Win_H - 70, "按任意键退出");
	delimage(blackbar);
}

void gameScene_PVE_duet::rend_pass()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(WHITE);

	setfont(100, 0, "楷体");
	outtextxy((Win_W - 160) / 2, 100, "过关！");

	if (score > historyscore)
	{
		setfont(50, 0, "楷体");
		sprintf(str, "新纪录：%d", score);
		outtextxy(230, 350, str);
		char buffer[255];
		sprintf(buffer, "update battle_city set score = ('%d') where mainKey = 1", score);
		DB.query(buffer);
	}
	else
	{
		setfont(40, 0, "楷体");
		sprintf(str, "历史最高分：%d", historyscore);
		outtextxy(230, 300, str);
		sprintf(str, "最终得分分：%d", score);
		outtextxy(230, 400, str);
	}

	if (count_pass > 50)
	{
		setfont(40, 0, "楷体");
		if (level > 0)
			outtextxy((Win_W - 520) / 2, Win_H - 70, "按任意键开始下一关，ESC退出");
		else
			outtextxy((Win_W - 240) / 2, Win_H - 70, "按任意键退出");
	}

	delimage(blackbar);
}

void gameScene_PVE_duet::rend_pause()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);
	setfont(60, 0, "楷体");
	outtextxy((Win_W - 360) / 2, (Win_H - 60) / 2, "按P键继续");
	delimage(blackbar);
}

void gameScene_PVE_duet::rend_through()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(WHITE);

	setfont(60, 0, "楷体");
	outtextxy((Win_W - 540) / 2, 100, "恭喜你通过最后一关！");

	if (score > historyscore)
	{
		setfont(50, 0, "楷体");
		sprintf(str, "新纪录：%d", score);
		outtextxy(230, 350, str);
		char buffer[255];
		sprintf(buffer, "update battle_city set score = ('%d') where mainKey = 1", score);
		DB.query(buffer);
	}
	else
	{
		setfont(40, 0, "楷体");
		sprintf(str, "历史最高分：%d", historyscore);
		outtextxy(230, 300, str);
		sprintf(str, "最终得分分：%d", score);
		outtextxy(230, 400, str);
	}

	if (count_pass > 50)
	{
		setfont(40, 0, "楷体");
		outtextxy((Win_W - 240) / 2, Win_H - 70, "按任意键退出");
	}

	delimage(blackbar);
}

void gameScene_PVE_duet::isLose()
{
	if (playerlife <= 0)
		state = lose;
}

void gameScene_PVE_duet::isPass()
{
	if (enemynum == 0)
		state = pass;
}

void gameScene_PVE_duet::init()
{
	isover = false;
	state = gaming;

	historyscore = 0;
	enemynum = 20;
	count_pass = 0;

	inittankmap();
	initbulletmap();

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	historyscore = atoi(result["score"].c_str());

	player_tank1.init_tank_player(bornQueue, map, Up);
	player_tank2.init_tank_player(bornQueue, map, Up, false);
	delete_enemy();
	music.init();
	music.mu_Start();
}

void gameScene_PVE_duet::initgame()
{
	init();
	if (level > 0)
		map.load_PVE(level);
	else
		map.load_design();
}

void gameScene_PVE_duet::inittankmap()
{
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			tankmap[i][j] = 0;
}

void gameScene_PVE_duet::initbulletmap()
{
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			bulletmap[i][j] = 0;
}

void gameScene_PVE_duet::delete_enemy()
{
	tanke_enemy *p;
	while (!enemyQueue.empty())
	{
		p=enemyQueue.front();
		delete p;
		enemyQueue.pop();
	}

	while (!deadenemyQueue.empty())
	{
		p=deadenemyQueue.front();
		delete p;
		deadenemyQueue.pop();
	}
	p = NULL;
}

void gameScene_PVE_duet::delete_property()
{
	prop *p;
	while (!propertyQueue.empty())
	{
		p = propertyQueue.front();
		delete p;
		propertyQueue.pop();
	}

	while (!propertyusedQueue.empty())
	{
		p = propertyusedQueue.front();
		delete p;
		propertyusedQueue.pop();
	}

	p = NULL;
}

bool gameScene_PVE_duet::canmove1(key_msg key)
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

bool gameScene_PVE_duet::canmove2(key_msg key)
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

bool gameScene_PVE_duet::enemycanBorn()
{
	int x, y, n, enemybornnum;
	n = 0;
	enemybornnum = 0;
	for (int i = 0; i < 3; i++)
	{
		x = map.getEnemy_x(i);
		y = map.getEnemy_y(i);

		if (x >= 0)
		{
			enemybornnum++;
			if (tankmap[x][y] == 1 || tankmap[x + 1][y] == 1 || tankmap[x][y + 1] == 1 || tankmap[x + 1][y + 1] == 1)
				n++;
		}
	}

	if (n == enemybornnum)
		return false;
	return true;
}

void gameScene_PVE_duet::getProp(tank_player & tank_player)
{
	int n = propertyQueue.size();
	while (n--)
	{
		if ((tank_player.aimx == propertyQueue.front()->x&&tank_player.aimy == propertyQueue.front()->y) || (tank_player.aimx + 1 == propertyQueue.front()->x&&tank_player.aimy == propertyQueue.front()->y) || (tank_player.aimx == propertyQueue.front()->x&&tank_player.aimy + 1 == propertyQueue.front()->y) || (tank_player.aimx + 1 == propertyQueue.front()->x&&tank_player.aimy + 1 == propertyQueue.front()->y))
		{
			music.mu_Prop_get();
			switch (propertyQueue.front()->pro)
			{
			case tank:
				prop_tank(tank_player);
				break;
			case bomb:
				prop_bomb(tank_player);
				break;
			case star:
				prop_star(tank_player);
				break;
			case timer:
				prop_timer(tank_player);
				break;
			case sheld:
				prop_sheld(tank_player);
				break;
			default:
				break;
			}
			propertyusedQueue.push(propertyQueue.front());
			propertyQueue.pop();
		}
		else
		{
			propertyQueue.push(propertyQueue.front());
			propertyQueue.pop();
		}
	}
}

void gameScene_PVE_duet::prop_tank(tank_player & tank_player)
{
	playerlife++;
}

void gameScene_PVE_duet::prop_star(tank_player & tank_player)
{
	tank_player.level = 2;
	tank_player.update_speed();
}

void gameScene_PVE_duet::prop_bomb(tank_player & tank_player)
{
	music.mu_Dead_Enemy();
	while (!enemyQueue.empty())
	{
		bombQueue.push(enemyQueue.front()->x, enemyQueue.front()->y);
		deadenemyQueue.push(enemyQueue.front());
		enemyQueue.pop();
		enemynum--;
	}
}

void gameScene_PVE_duet::prop_sheld(tank_player & tank_player)
{
	tank_player.count_sheld = 500;
}

void gameScene_PVE_duet::prop_timer(tank_player & tank_player)
{
	count_enemypause = 500;
}
