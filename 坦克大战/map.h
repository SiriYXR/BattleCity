#pragma once
#include"Picture.h"

class map
{
public:
	map();
	~map();

	void rendermap1(Picture& picture);
	void rendermap2(Picture& picture);
	int rendermaphome(Picture& picture);
	int rendermapenemyborn(Picture& picture);
	int rendermapplayer1born(Picture& picture);
	int rendermapplayer2born(Picture& picture);

	void rendAll(Picture& picture);

	mode getmode();
	texture getmember(int i, int j, int k);
	int getHome_x(int n);
	int getHome_y(int n);
	int getPlayer_x(int n);
	int getPlayer_y(int n);
	int getEnemy_x(int n);
	int getEnemy_y(int n);
	
	void setmember(int i, int j, int k, texture tex);
	void setmapmember_4(int i, int j, int k, texture tex);
	void setmapmember_4_plus(int i, int j, int k, texture tex);
	void setmapmember_4_enemy(int i, int j, int k);

	void autoclearhome();
	void autoclearplayer1();
	void autoclearplayer2();

	void Search();
	void save_design();
	void load_design();

	void load_PVE(int level);
	void load_PVP(int level);

	void init(mode mode);
	void init_point();

private:
	mapdata *member;
};