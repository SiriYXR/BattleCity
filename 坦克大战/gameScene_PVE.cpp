#include "gameScene_PVE.h"



gameScene_PVE::gameScene_PVE()
{
	map.load_PVE(1);

	isover = false;
	state = gaming;

	playerlife = 5;
	score= 0;
	historyscore = 0;
	enemynum = 20;
	count_pass = 0;

	inittankmap();
	initbulltemap();

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	historyscore = atoi(result["score"].c_str());

	playertank.init_tank_player(bornQueue, map);
	music.mu_Start();
}

gameScene_PVE::gameScene_PVE(int level)
{
	map.load_PVE(level);

	this->level = level;
	isover = false;
	state = gaming;

	playerlife = 5;
	score= 0;
	historyscore = 0;
	enemynum = 20;
	count_pass = 0;

	inittankmap();
	initbulltemap();

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	historyscore = atoi(result["score"].c_str());

	playertank.init_tank_player(bornQueue, map);
	music.mu_Start();
}

void gameScene_PVE::init()
{
	isover = false;
	state = gaming;

	historyscore = 0;
	enemynum = 20;
	count_pass = 0;

	inittankmap();
	initbulltemap();

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	historyscore = atoi(result["score"].c_str());

	playertank.init_tank_player(bornQueue, map);
	delete_enemy();
	music.init();
	music.mu_Start();
}

void gameScene_PVE::initgame()
{
	init();
	map.load_PVE(level);
}

void gameScene_PVE::inittankmap()
{
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			tankmap[i][j] = 0;
}

void gameScene_PVE::initbulltemap()
{
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			bulltemap[i][j] = 0;
}

void gameScene_PVE::delete_enemy()
{
	while (!enemyQueue.empty())
	{
		delete enemyQueue.front();
		enemyQueue.pop();
	}

	while (!deadenemyQueue.empty())
	{
		delete deadenemyQueue.front();
		deadenemyQueue.pop();
	}
}


gameScene_PVE::~gameScene_PVE()
{
	delete_enemy();
}

void gameScene_PVE::update()
{
	if (state == gaming)
	{
		update_tankmap();
		update_bulltemap();
		playertank.update(map, tankmap,bulltemap, playertank,enemyQueue,deadenemyQueue, bombQueue,bornQueue, state,playerlife,enemynum,score);
		update_tankmap();
		update_bulltemap();
		update_enemyborn();

		int n = enemyQueue.size();
		while (n--)
		{
			update_tankmap();
			update_bulltemap();
			enemyQueue.front()->update(map, tankmap, bulltemap, playertank,enemyQueue,deadenemyQueue, bombQueue,bornQueue, state,playerlife,enemynum,score);
			enemyQueue.push(enemyQueue.front());
			enemyQueue.pop();
		}

		update_state();
	}
	
	if (state == pass)
	{
		if (count_pass > 60)
		{
			level++;
			char buffer[255];
			sprintf(buffer, "update battle_city set lastlevel = ('%d') where mainKey = 1", level);
			DB.query(buffer);

			int maxlevel;
			auto result = DB.query("select * from battle_city where mainKey=1");
			result.next();
			maxlevel = atoi(result["maxlevel"].c_str());

			if (level > maxlevel)
			{
				sprintf(buffer, "update battle_city set maxlevel = ('%d') where mainKey = 1", level);
				DB.query(buffer);
			}

			char ch;
			ch = ege::getch();
			if (ch == 27)
				isover = true;
			else
				initgame();
		}
		count_pass++;
	}

}

void gameScene_PVE::render()
{
	picture.clear();

	rendMainface();
	map.rendermap1(picture);
	map.rendermaphome(picture);

	playertank.render(picture);
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
		rend_pass();

	picture.rend();
}

bool gameScene_PVE::isOver()
{
	return isover;
}

void gameScene_PVE::onKey(key_msg key)
{
	if (state != lose)
	{
		if (state != pause)
		{
			onKey_J(key);
			onKey_WASD(key);
		}
		onKey_P(key);
		onKey_ESC(key);
	}
	else
	{
		if (key.msg == key_msg_down)
			isover = true;
	}

}


void gameScene_PVE::onKey_J(key_msg key)
{

	if (playertank.bullte.Canfire())
		if (key.key == key_J&&key.msg == key_msg_down)
		{
			playertank.bullte.init(1, playertank.aimx, playertank.aimy, playertank.direct, 2 * playertank.speed);
		}
}

void gameScene_PVE::onKey_WASD(key_msg key)
{

	if (key.key == key_S&&key.msg == key_msg_down)
	{
		playertank.direct = Down;
		if (canmove(playertank.aimx, playertank.aimy, key))
		{
			playertank.init_xy();
			playertank.aimy++;
			playertank.update_count();
			
		}
	}
	if (key.key == key_W&&key.msg == key_msg_down)
	{
		playertank.direct = Up;
		if (canmove(playertank.aimx, playertank.aimy, key))
		{
			playertank.init_xy();
			playertank.aimy--;
			playertank.update_count();
			
		}
	}
	if (key.key == key_D&&key.msg == key_msg_down)
	{
		playertank.direct = Right;
		if (canmove(playertank.aimx, playertank.aimy, key))
		{
			playertank.init_xy();
			playertank.aimx++;
			playertank.update_count();
			
		}
	}
	if (key.key == key_A&&key.msg == key_msg_down)
	{
		playertank.direct = Left;
		if (canmove(playertank.aimx, playertank.aimy, key))
		{
			playertank.init_xy();
			playertank.aimx--;
			playertank.update_count();
			
		}
	}
}

void gameScene_PVE::onKey_P(key_msg key)
{
	if (key.key == key_P&&key.msg == key_msg_down)
	{
		if (state == gaming)
			state = pause;
		else if (state == pause)
			state = gaming;
	}
}

void gameScene_PVE::onKey_ESC(key_msg key)
{
	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		if (Escloop(*this))
			isover = true;
		music.init();
		playertank.bullte.music.init();
	}
}

void gameScene_PVE::update_enemyborn()
{
	static int count = 100;
	if (enemynum>enemyQueue.size())
	{
		if (enemyQueue.size() < 5)
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

void gameScene_PVE::update_tankmap()
{
	inittankmap();
	tankmap[playertank.aimx][playertank.aimy] = 1;
	tankmap[playertank.aimx+1][playertank.aimy] = 1;
	tankmap[playertank.aimx][playertank.aimy+1] = 1;
	tankmap[playertank.aimx+1][playertank.aimy+1] = 1;
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

void gameScene_PVE::update_bulltemap()
{
	initbulltemap();
	if(playertank.bullte.bullet)
	bulltemap[playertank.bullte.aimx][playertank.bullte.aimy] = 1;
	int n = enemyQueue.size();
	while (n--)
	{
		if (enemyQueue.front()->bullte.bullet)
		bulltemap[enemyQueue.front()->bullte.aimx][enemyQueue.front()->bullte.aimy] = 1;
		enemyQueue.push(enemyQueue.front());
		enemyQueue.pop();
	}
}

void gameScene_PVE::update_state()
{
	isLose();
	isPass();
}

void gameScene_PVE::rendMainface()
{
	rend_bar(map_x, map_y, 20 * 26, 20 * 26);
	rendInformation();
}

void gameScene_PVE::rendInformation()
{
	setfillcolor(EGERGB(0xFB, 0xF8, 0xF1));
	bar(Win_W - 225, 0, Win_W, Win_H);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(EGERGB(0x92, 0x8B, 0x7B));
	setfont(25, 0, "楷体");

	sprintf(str, "--第%d关--", level);
	outtextxy(Win_W - 185, 50, str);
	outtextxy(Win_W - 185, 150, "-玩家生命-");
	sprintf(str, "%d", playerlife);
	outtextxy(Win_W - 130, 200, str);
	outtextxy(Win_W - 185, 250, "-玩家得分-");
	sprintf(str, "%d", score);
	outtextxy(Win_W - 150, 300, str);
	outtextxy(Win_W - 185, 350, "-敌人数量-");
	sprintf(str, "%d", enemynum);
	outtextxy(Win_W - 130, 400, str);

	putimage_withalpha(NULL, picture.instruction_solo, Win_W - 225, Win_H - 170);
}

void gameScene_PVE::rend_bar(int x, int y, int w, int h, int n, color_t color)
{
	setfillcolor(color);
	bar(x - n, y - n, x + w + n, y);
	bar(x - n, y + h, x + w + n, y + h + n);
	bar(x - n, y - n, x, y + h + n);
	bar(x + w + n, y - n, x + w, y + h + n);
}

void gameScene_PVE::rend_bomb()
{
	int size = bombQueue.getsize();
	for (int i = 0; i < size; i++)
	{
		if (bombQueue.front_count() == 0)
			bombQueue.pop();
		else
		{
			//time_t start = clock();
			movieBomb(bombQueue.front_count(), bombQueue.front_x(), bombQueue.front_y(),picture);
			//time_t end1 = clock();
			bombQueue.push(bombQueue.front_x(), bombQueue.front_y(), bombQueue.front_count() - 1);
			//time_t end2 = clock();
			bombQueue.pop();
			/*time_t end3 = clock();
			char buffer[100];
			sprintf(buffer, "%d %d %d\n",end1-start,end2-end1,end3-end2);
			OutputDebugStringA(buffer);*/

		}
	}
}

void gameScene_PVE::rend_born()
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

void gameScene_PVE::rend_lose()
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

void gameScene_PVE::rend_pass()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);

	setbkmode(TRANSPARENT);
	char str[20];
	setcolor(WHITE);

	setfont(100, 0, "楷体");
	outtextxy((Win_W - 160) / 2,100, "过关！");

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
		outtextxy((Win_W - 520) / 2, Win_H - 70, "按任意键开始下一关，ESC退出");
	}

	delimage(blackbar);
}

void gameScene_PVE::rend_pause()
{
	PIMAGE blackbar = newimage(Win_W, Win_H);
	putimage_alphablend(NULL, blackbar, 0, 0, 200);
	setfont(60, 0, "楷体");
	outtextxy((Win_W - 360) / 2, (Win_H - 60) / 2, "按任P键继续");
	delimage(blackbar);
}

void gameScene_PVE::isLose()
{
	if (playerlife == 0)
		state = lose;
}

void gameScene_PVE::isPass()
{
	if (enemynum == 0)
		state = pass;
}

bool gameScene_PVE::canmove(int aimx, int aimy, key_msg key)
{
	if (playertank.count == 0)
	{
		switch (key.key)
		{
		case key_W:
			if (playertank.aimy <= 0)
				return false;
			if (tankmap[aimx][aimy - 1] != 0 || tankmap[aimx + 1][aimy - 1] != 0)
				return false;
			if (map.getmember(0, aimx, aimy - 1) != land || map.getmember(0, aimx + 1, aimy - 1) != land)
				return false;
			if (map.getmember(1, aimx, aimy - 1) == home || map.getmember(1, aimx + 1, aimy - 1) == home)
				return false;
			if (map.getmember(1, aimx, aimy - 1) == home_h || map.getmember(1, aimx + 1, aimy - 1) == home_h)
				return false;
			break;
		case key_S:
			if (playertank.aimy >= 24)
				return false;
			if (tankmap[aimx][aimy + 2] != 0 || tankmap[aimx + 1][aimy + 2] != 0)
				return false;
			if (map.getmember(0, aimx, aimy + 2) != land || map.getmember(0, aimx + 1, aimy + 2) != land)
				return false;
			if (map.getmember(1, aimx, aimy + 2) == home || map.getmember(1, aimx + 1, aimy + 2) == home)
				return false;
			if (map.getmember(1, aimx, aimy + 2) == home_h || map.getmember(1, aimx + 1, aimy + 2) == home_h)
				return false;
			break;
		case key_D:
			if (playertank.aimx >= 24)
				return false;
			if (tankmap[aimx + 2][aimy] != 0 || tankmap[aimx + 2][aimy + 1] != 0)
				return false;
			if (map.getmember(0, aimx + 2, aimy) != land || map.getmember(0, aimx + 2, aimy + 1) != land)
				return false;
			if (map.getmember(1, aimx + 2, aimy) == home || map.getmember(1, aimx + 2, aimy + 1) == home)
				return false;
			if (map.getmember(1, aimx + 2, aimy) == home_h || map.getmember(1, aimx + 2, aimy + 1) == home_h)
				return false;
			break;
		case key_A:
			if (playertank.aimx <= 0)
				return false;
			if (tankmap[aimx - 1][aimy] != 0 || tankmap[aimx - 1][aimy + 1] != 0)
				return false;
			if (map.getmember(0, aimx - 1, aimy) != land || map.getmember(0, aimx - 1, aimy + 1) != land)
				return false;
			if (map.getmember(1, aimx - 1, aimy) == home || map.getmember(1, aimx - 1, aimy + 1) == home)
				return false;
			if (map.getmember(1, aimx - 1, aimy) == home_h || map.getmember(1, aimx - 1, aimy + 1) == home_h)
				return false;
			break;
		}
		return true;
	}
	else
		return false;
}

bool gameScene_PVE::enemycanBorn()
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
