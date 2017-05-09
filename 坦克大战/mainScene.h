#pragma once
#include"functions.h"
#include"Picture.h"
#include"Music.h"

enum mainScenestate;

class mainScene
{
public:
	mainScene();
	~mainScene();

	void update();
	void update_time();
	void onKey(key_msg key);
	bool isOver();

	void render();
	void rendMainface();
	void rendCursor();

private:
	void init();
	void Solo();
	void Duet();
	void Design();

private:
	Picture picture;
	Music music;
	mainScenestate state;

	int cursor_y;
	int time;
	bool isover;
	
};