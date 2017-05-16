#pragma once
#include"functions.h"
#include"Picture.h"
#include"Music.h"

enum duetScenestate;

class duetScene_classic_PVE
{
public:
	duetScene_classic_PVE();
	~duetScene_classic_PVE();

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

	duetScenestate state;
	int time;
	int cursor_y;
	int lastlevel;
	int maxlevel;
	bool isover;
};

