#pragma once
#include"functions.h"
#include"Picture.h"
#include"Music.h"

enum duetScene_main_state;

class duetScene_main
{
public:
	duetScene_main();
	~duetScene_main();

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

	duetScene_main_state state;
	int time;
	int cursor_y;
	bool isover;
};

