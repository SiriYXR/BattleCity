#include"designer_PVE.h"
#include"designer_PVP.h"
#include"isover_design.h"
#include"functions.h"

void isoverloop(designer_PVE& des)
{
	isover_design scene;

	key_msg key = { 0 };
	for (; is_run(); delay_fps(60))
	{

		if (kbmsg())
		{
			key = getkey();
			scene.onKey(key);
			if ((key.key == key_enter|| key.key == key_space)&&key.msg == key_msg_down)
			{
				if (scene.getCursor_x() == (Win_W - scene.get_w()) / 2 + 6)
				{
					des.tempmap.save_design();
					des.isover = true;
					break;
				}
				else if (scene.getCursor_x() == (Win_W - scene.get_w()) / 2 + 6 + (scene.get_w() - 12) / 3 + 6)
				{
					des.isover = true;
					break;
				}
				else if (scene.getCursor_x() == (Win_W - scene.get_w()) / 2 + 6 + ((scene.get_w() - 12) / 3 + 6) * 2)
				{
					des.isover = false;
					break;
				}
			}
		}

		if (scene.isOver())
		{
			des.isover = false;
			break;
		}

		scene.update();

		des.render();
		scene.render();
	}
}

void isoverloop(designer_PVP& des)
{
	isover_design scene;

	key_msg key = { 0 };
	for (; is_run(); delay_fps(60))
	{

		if (kbmsg())
		{
			key = getkey();
			scene.onKey(key);
			if (key.key == key_space&&key.msg == key_msg_down)
			{
				if (scene.getCursor_x() == (Win_W - scene.get_w()) / 2 + 6)
				{
					des.tempmap.save_design();
					des.isover = true;
					break;
				}
				else if (scene.getCursor_x() == (Win_W - scene.get_w()) / 2 + 6 + (scene.get_w() - 12) / 3 + 6)
				{
					des.isover = true;
					break;
				}
				else if (scene.getCursor_x() == (Win_W - scene.get_w()) / 2 + 6 + ((scene.get_w() - 12) / 3 + 6) * 2)
				{
					des.isover = false;
					break;
				}
			}
		}

		if (scene.isOver())
		{
			des.isover = false;
			break;
		}

		scene.update();

		des.render();
		scene.render();
	}
}