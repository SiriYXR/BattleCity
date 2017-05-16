#include"functions.h"
#include"duetScene_classic_PVE.h"

void duet_classic_PVE_loop()
{
	duetScene_classic_PVE scene;

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