#pragma once
#include"functions.h"
#include"Music.h"
#include"Picture.h"

class PVPselectlevelScene
{
public:
	PVPselectlevelScene();
	~PVPselectlevelScene();

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
	bool isover;
};

