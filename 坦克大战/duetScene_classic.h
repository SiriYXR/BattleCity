#pragma once
#include"functions.h"
#include"Picture.h"
#include"Music.h"

class duetScene_classic
{
public:
	duetScene_classic();
	~duetScene_classic();

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

	int time;
	int cursor_y;
	bool isover;
};

