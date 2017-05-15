#include"functions.h"
#include"soloScene.h"

enum soloScenestate
{
	solo_null,
	solo_newgame,
	solo_continuegame,
	solo_selectlevel
};


void soloScene::update()
{
	if (state != solo_null)
	{
		if (state == solo_newgame)
		{
			char buffer[255];
			sprintf(buffer, "update battle_city set lastlevel = ('%d') where mainKey = 1", 1);
			DB.query(buffer);
			soloGameloop(1);
			music.mu_Switch();
		}
		else if (state == solo_continuegame)
		{
			soloGameloop(lastlevel);
			music.mu_Switch();
		}
		else if (state == solo_selectlevel)
		{
			int n;
			n = Selectlevelloop_PVE(maxlevel);
			if (n > 0)
			{
				char buffer[255];
				sprintf(buffer, "update battle_city set lastlevel = ('%d') where mainKey = 1", n);
				DB.query(buffer);
				soloGameloop(n);
			}

			music.mu_Switch();
		}

		init();
	}

	update_time();
}

void soloScene::onKey(key_msg key)
{
	if ((key.key == key_down|| key.key == key_S)&&key.msg == key_msg_down&&cursor_y < 459)
	{
		cursor_y += 65;
		music.mu_Switch();
	}
	if ((key.key == key_up|| key.key == key_W)&&key.msg == key_msg_down&&cursor_y > 294)
	{
		cursor_y -= 65;
		music.mu_Switch();
	}

	if ((key.key == key_enter|| key.key == key_space)&&key.msg == key_msg_down)
		switch (cursor_y)
		{
		case 294:
			state = solo_newgame;
			music.mu_Switch();
			break;
		case 294 + 65:
			state = solo_continuegame;
			music.mu_Switch();
			break;
		case 294 + 130:
			state = solo_selectlevel;
			music.mu_Switch();
			break;
		case 294 + 195:
			isover = true;
			break;
		}

	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		isover = true;
	}
}

void soloScene::update_time()
{
	time++;
	if (time > 60)
		time = 0;
}

bool soloScene::isOver()
{
	return isover;
}

void soloScene::render()
{
	picture.clear();

	rendMainface();
	movieShine(time);
	movieBomb(time);
	rendCursor();

	picture.rend();
}

void soloScene::rendMainface()
{
	int x, y;

	x = (Win_W - 345) / 2;
	y = 80;
	putimage_withalpha(NULL, picture.BattleCity, x, y);

	x = (Win_W - 146) / 2;
	y = 300;
	putimage_withalpha(NULL, picture.solo_selects, x, y);

	x = (Win_W - 265) / 2;
	y = Win_H - 50;
	putimage_withalpha(NULL, picture.copyright, x, y);
}

void soloScene::rendCursor()
{
	putimage_withalpha(NULL, picture.selecttank, (Win_W - 146) / 2 - 60, cursor_y);
}

soloScene::soloScene()
{
	state = solo_null;
	time = 0;
	cursor_y = 294;
	lastlevel = 1;
	maxlevel = 1;

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	lastlevel = atoi(result["lastlevel"].c_str());
	maxlevel = atoi(result["maxlevel"].c_str());

	isover = false;
}

void soloScene::init()
{
	music.init();
	state = solo_null;
	time = 0;
	cursor_y = 294;
	lastlevel = 1;
	maxlevel = 1;

	auto result = DB.query("select * from battle_city where mainKey=1");
	result.next();
	lastlevel =atoi(result["lastlevel"].c_str());
	maxlevel = atoi(result["maxlevel"].c_str());

	isover = false;
}

soloScene::~soloScene()
{
}
