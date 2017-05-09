#pragma once
#include"functions.h"
#include"Music.h"
#include"Picture.h"

class PVEselectlevelScene
{
public:
	PVEselectlevelScene(int maxlevel);
	~PVEselectlevelScene();

	void onKey(key_msg key);
	void update();
	void render();
	void rend_map();
	void rend_information();

	int get_n();

	bool isOver();

private:
	Music music;
	Picture picture;

	int level;
	int n;
	int maxlevel;
	bool isover;
};

