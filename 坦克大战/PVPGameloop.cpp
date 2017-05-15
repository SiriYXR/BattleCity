#include"functions.h"
#include"gameScene_PVP.h"

void PVPGameloop(int level)
{
	movie_Loding();
	gameScene_PVP scene(level);

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