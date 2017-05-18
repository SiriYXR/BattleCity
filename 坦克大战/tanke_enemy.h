#pragma once
#include"tank.h"


class tanke_enemy :public tank
{
public:
	tanke_enemy(myQueue& bornQueue, map& map, int(*tankmap)[26]);
	~tanke_enemy();

	void update(map & map, int(*tankmap)[26], int(*bulletmap)[26], tank_player& player_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, queue<prop*>& propertyQueue, myQueue & bombQueue, myQueue & bornQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void update(map & map, int(*tankmap)[26], int(*bulletmap)[26], tank_player& player_tank1, tank_player& player_tank2, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, myQueue & bornQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void render(Picture& picture);

	void update_xy();
	void update_speed();
	void update_move(map & map, int(*tankmap)[26]);
	void update_count();

	void AI_bullte();
	void AI_direct(map & map, int(*tankmap)[26]);
	void AI_move();

	void init_xy();

	bool canmove(map & map, int(*tankmap)[26]);
public:
	bool isHeavy;
	int level;

	int ai_bullte_count;
	int ai_move_count;

};

