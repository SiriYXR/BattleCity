#pragma once
#include"functions.h"
#include"Picture.h"
#include"Music.h"
#include"map.h"

class tanke_enemy;
class tank_player;

class bulltes
{
public:
	bulltes();
	~bulltes();

	void update(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void render(Picture& picture);

	void init(int isplayer, int aimx, int aimy, direction direct, int speed);
	void BulletHit(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void BulletHitPlus(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	bool Canfire();
	bool Canmove(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);


	void update_move(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score);
	void update_xy();
public:
	Music music;
	direction direct;
	bool bullet;

	int x;
	int y;
	int aimx;
	int aimy;
	int count;
	int speed;
	int isplayer;
};

