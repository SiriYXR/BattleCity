#include "designScene.h"



designScene::designScene()
{
	music.init();
	time = 0;
	cursor_y = 294;
	isover = false;
}

void designScene::init()
{
	music.init();
	time = 0;
	cursor_y = 294;
	isover = false;
}


designScene::~designScene()
{
}

void designScene::update()
{
	update_time();
}

void designScene::update_time()
{
	time++;
	if (time > 60)
		time = 0;
}


void designScene::render()
{
	picture.clear();

	rendMainface();
	movieShine(time);
	movieBomb(time);
	rendCursor();

	picture.rend();
}

bool designScene::isOver()
{
	return isover;
}

void designScene::onKey(key_msg key)
{
	if ((key.key == key_down|| key.key == key_S)&&key.msg == key_msg_down&&cursor_y < 394)
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
			music.mu_Switch();
			designPVEloop();
			init();
			music.mu_Switch();
			break;
		case 294 + 65:
			music.mu_Switch();
			designPVPloop();
			init();
			music.mu_Switch();
			break;
		case 294 + 130:
			isover = true;
			music.mu_Switch();
			delay_ms(180);
			break;
		}

	if (key.key == key_esc&&key.msg == key_msg_down)
	{
		music.mu_Switch();
		delay_ms(180);
		isover = true;
	}
}


void designScene::rendMainface()
{
	int x, y;

	x = (Win_W - 345) / 2;
	y = 80;
	putimage_withalpha(NULL, picture.BattleCity, x, y);

	x = (Win_W - 146) / 2;
	y = 300;
	putimage_withalpha(NULL, picture.design_selects, x, y);

	x = (Win_W - 265) / 2;
	y = Win_H - 50;
	putimage_withalpha(NULL, picture.copyright, x, y);
}

void designScene::rendCursor()
{
	putimage_withalpha(NULL, picture.selecttank, (Win_W - 146) / 2 - 60, cursor_y);
}

