#include"PVEselectlevelScene.h"
#include"PVPselectlevelScene.h"

int Selectlevelloop_PVE(int maxlevel)
{
	PVEselectlevelScene scene(maxlevel);

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

	return scene.get_n();
}

int Selectlevelloop_PVP()
{
	PVPselectlevelScene scene;

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

	return scene.get_n();
}