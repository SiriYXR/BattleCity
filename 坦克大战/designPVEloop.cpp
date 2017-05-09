#include"designer_PVE.h"
#include"designScene.h"
#include"functions.h"

void designPVEloop()
{
	designer_PVE scene;

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