#pragma once
#include"functions.h"
#include"Picture.h"
#include"Music.h"

enum soloScenestate;

class soloScene
{
public:
	soloScene();
	~soloScene();

	void update();
	void render();
	bool isOver();
	void onKey(key_msg key);

private:
	void update_time();
	void rendMainface();
	void rendCursor();
	void init();


private:
	Picture picture;
	Music music;

	soloScenestate state;
	int time;
	int cursor_y;
	int lastlevel;
	int maxlevel;
	bool isover;
};
