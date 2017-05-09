#pragma once
#include"designer_PVE.h"

struct isover_design_menber;

class isover_design
{
public:
	Music music;

	isover_design();
	~isover_design();

	void onKey(key_msg key);
	void update();
	void render();
	bool isOver();

	int getCursor_x();
	int getCursor_y();
	int get_w();

private:
	void rend_mainface();
	void rendCursor();

	void rend_bar(int x, int y, int w, int h, int n=4, color_t color=WHITE);
private:
	isover_design_menber *member;
};