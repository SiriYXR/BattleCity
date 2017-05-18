#pragma once
#include"functions.h"
#include"bulltes.h"
#include"Picture.h"
#include"map.h"

class tank
{
public:
	tank();
	~tank();
	void update_count();
public:
	bulltes bullte;
	direction direct;
	
	int x;
	int y;
	int aimx;
	int aimy;
	int count;
	int speed;
	int count_sheld;
};