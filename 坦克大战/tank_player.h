#pragma once
#include"tank.h"

class tank_player :public tank
{
public:
	tank_player();
	~tank_player();
	void init_tank_player(myQueue& bornQueue, map& map, direction direct = Up);
	void init_tank_player(myQueue& bornQueue, map& map, bool isfalse, direction direct = Up);
	void init_xy();

	void update(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void render(Picture& picture);

	void update_xy();
private:
	bool player1;
};

