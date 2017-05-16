#include "duetScene_classic_PVE.h"

enum duetScenestate
{
	duet_null,
	duet_newgame,
	duet_continuegame,
	duet_selectlevel
};


duetScene_classic_PVE::duetScene_classic_PVE()
{
	state = duet_null;
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


duetScene_classic_PVE::~duetScene_classic_PVE()
{
}

void duetScene_classic_PVE::update()
{
	if (state != duet_null)
	{
		if (state == duet_newgame)
		{
			duet_PVEGameloop(1);
			music.mu_Switch();
		}
		else if (state == duet_continuegame)
		{
			duet_PVEGameloop(lastlevel);
			music.mu_Switch();
		}
		else if (state == duet_selectlevel)
		{
			int n;
			n = Selectlevelloop_PVE(maxlevel);
			if (n > 0)
			{
				duet_PVEGameloop(n);
			}

			music.mu_Switch();
		}

		init();
	}

	update_time();
}

void duetScene_classic_PVE::render()
{
	picture.clear();

	rendMainface();
	movieShine(time);
	movieBomb(time);
	rendCursor();

	picture.rend();
}

bool duetScene_classic_PVE::isOver()
{
	return isover;
}

void duetScene_classic_PVE::onKey(key_msg key)
{
	if ((key.key == key_down || key.key == key_S) && key.msg == key_msg_down&&cursor_y < 459)
	{
		cursor_y += 65;
		music.mu_Switch();
	}
	if ((key.key == key_up || key.key == key_W) && key.msg == key_msg_down&&cursor_y > 294)
	{
		cursor_y -= 65;
		music.mu_Switch();
	}

	if ((key.key == key_enter || key.key == key_space) && key.msg == key_msg_down)
		switch (cursor_y)
		{
		case 294:
			state = duet_newgame;
			music.mu_Switch();
			break;
		case 294 + 65:
			state = duet_continuegame;
			music.mu_Switch();
			break;
		case 294 + 130:
			state = duet_selectlevel;
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

void duetScene_classic_PVE::update_time()
{
	time++;
	if (time > 60)
		time = 0;
}

void duetScene_classic_PVE::rendMainface()
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

void duetScene_classic_PVE::rendCursor()
{
	putimage_withalpha(NULL, picture.selecttank, (Win_W - 146) / 2 - 60, cursor_y);
}

void duetScene_classic_PVE::init()
{
	music.init();
	state = duet_null;
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
