#include"mainScene.h"

enum mainScenestate
{
	null,
	solo,
	duet,
	design
};

void mainScene::update()
{
	switch (state)
	{
	case solo:
		Solo();
		init();
		music.mu_Switch();
		break;
	case duet:
		Duet();
		init();
		music.mu_Switch();
		break;
	case design:
		Design();
		init();
		music.mu_Switch();
		break;
	}

	update_time();

}

void mainScene::update_time()
{
	time++;
	if (time > 60)
		time = 0;
}

void mainScene::onKey(key_msg key)
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
			state = solo;
			music.mu_Switch();
			break;
		case 294 + 65:
			state = duet;
			music.mu_Switch();
			break;
		case 294+130:
			state = design;
			music.mu_Switch();
			break;
		case 294 + 195:
			state = null;
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

bool mainScene::isOver()
{
	return isover;
}

void mainScene::render()
{
	picture.clear();

	rendMainface();
	movieShine(time);
	movieBomb(time);
	rendCursor();

	picture.rend();
}

void mainScene::rendMainface()
{
	int x, y;

	x = (Win_W - 345) / 2;
	y = 80;
	putimage_withalpha(NULL, picture.BattleCity, x, y);

	x = (Win_W - 146) / 2;
	y = 300;
	putimage_withalpha(NULL, picture.selects, x, y);

	x = (Win_W - 265) / 2;
	y = Win_H-50;
	putimage_withalpha(NULL, picture.copyright, x, y);
}

void mainScene::rendCursor()
{
	putimage_withalpha(NULL, picture.selecttank, (Win_W - 146) / 2-60, cursor_y);
}

mainScene::mainScene()
{
	time = 0;
	state = null;
	isover = false;
	cursor_y = 294;
}

void mainScene::init()
{
	music.init();
	time = 0;
	state = null;
	isover = false;
	cursor_y = 294;
}

mainScene::~mainScene()
{}
