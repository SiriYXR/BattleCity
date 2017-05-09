#include"escScene.h"
#include"gameScene_PVE.h"

bool Escloop(gameScene_PVE& gs)
{
	escScene scene;

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

		gs.render();
		scene.render();
	}
	return scene.state;
}