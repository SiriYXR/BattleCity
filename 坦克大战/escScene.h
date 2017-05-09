#pragma once
#include"functions.h"
#include"Music.h"
#include"Picture.h"

class escScene
{
public:
	bool state;
	escScene();
	~escScene();
	
	void onKey(key_msg key);
	void update();
	void render();
	bool isOver();
private:
	void rend_mainface();
	void rendCursor();

	void rend_bar(int x, int y, int w, int h, int n = 4, color_t color = WHITE);

private:
	Picture picture;
	Music music;

	int cursor_x;
	int cursor_y;
	int w;
	int h;
	
	bool isover;
};
