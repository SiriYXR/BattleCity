#include"functions.h"
#include"gameScene_PVE.h"

void soloGameloop(int level)
{
	movie_Loding();
	gameScene_PVE scene(level);

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