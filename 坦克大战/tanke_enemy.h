#pragma once
#include"tank.h"


class tanke_enemy :public tank
{
public:
	tanke_enemy(myQueue& bornQueue, map& map, int(*tankmap)[26]);
	~tanke_enemy();

	void update(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void render(Picture& picture);

	void update_xy();
	void update_speed();

	bool isHeavy;
	int level;

};

