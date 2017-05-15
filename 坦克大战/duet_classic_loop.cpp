#include"functions.h"
#include"duetScene_classic.h"


void  duet_classic_loop()
{
	duetScene_classic scene;

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