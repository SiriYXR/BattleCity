#pragma once
#include"tank.h"


class tanke_enemy :public tank
{
public:
	tanke_enemy(myQueue& bornQueue, map& map, int(*tankmap)[26]);
	~tanke_enemy();

	void update(map & map, int(*tankmap)[26], int(*bulletmap)[26], tank_player& player_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, myQueue & bornQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void render(Picture& picture);

	void update_xy();
	void update_speed();

	void AI_bullte();

public:
	bool isHeavy;
	int level;

	int ai_bullte_count;

};

