#include "duetScene_main.h"

enum duetScene_main_state
{
	duet_main_null,
	duet_main_custom,
	duet_main_classic
};

duetScene_main::duetScene_main()
{
	state = duet_main_null;
	time = 0;
	cursor_y = 294;

	isover = false;
}

void duetScene_main::init()
{
	music.init();
	time = 0;
	state = duet_main_null;
	isover = false;
	cursor_y = 294;
}

duetScene_main::~duetScene_main()
{
}

void duetScene_main::update()
{
	switch (state)
	{
	case duet_main_custom:
		duet_custom_loop();
		init();
		music.mu_Switch();
		break;
	case duet_main_classic:
		duet_classic_loop();
		init();
		music.mu_Switch();
		break;
	}

	update_time();

}

void duetScene_main::render()
{
	picture.clear();

	rendMainface();
	movieShine(time);
	movieBomb(time);
	rendCursor();

	picture.rend();
}

bool duetScene_main::isOver()
{
	return isover;
}

void duetScene_main::onKey(key_msg key)
{
	if ((key.key == key_down || key.key == key_S) && key.msg == key_msg_down&&cursor_y < 394)
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
			state = duet_main_classic;
			music.mu_Switch();
			break;
		case 294 + 65:
			state = duet_main_custom;
			music.mu_Switch();
			break;
		case 294 + 130:
			state = duet_main_null;
			isover = true;
			music.mu_Switch();
			break;
		}

	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		music.mu_Switch();
		isover = true;
	}
}

void duetScene_main::update_time()
{
	time++;
	if (time > 60)
		time = 0;
}

void duetScene_main::rendMainface()
{
	int x, y;

	x = (Win_W - 345) / 2;
	y = 80;
	putimage_withalpha(NULL, picture.BattleCity, x, y);

	x = (Win_W - 146) / 2;
	y = 300;
	putimage_withalpha(NULL, picture.duet_main_selects, x, y);

	x = (Win_W - 265) / 2;
	y = Win_H - 50;
	putimage_withalpha(NULL, picture.copyright, x, y);
}

void duetScene_main::rendCursor()
{
	putimage_withalpha(NULL, picture.selecttank, (Win_W - 146) / 2 - 60, cursor_y);
}


