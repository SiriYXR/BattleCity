#include"functions.h"
#include"duetScene_main.h"
#include"mainScene.h"

void mainScene::Duet()
{
	duetScene_main scene;

	key_msg key = { 0 };
	for (; is_run(); delay_fps(60))
	{

		if (kbmsg())
		{
			key = getkey();
			scene.onKey(key);
		}

		if (scene.isOver())
			break;

		scene.update();

		scene.render();
	}

}