#pragma once
#include"Music.h"
#include"tank_player.h"

class gameScene_PVP
{
public:
	gameScene_PVP();
	gameScene_PVP(int level);
	~gameScene_PVP();

	void update();
	void render();
	bool isOver();
	void onKey(key_msg key);


private:
	void update_tankmap();
	void update_bulletmap();
	void update_state();

	void onKey_Jand0(key_msg key);
	void onKey_WASD(key_msg key);
	void onKey_Direction(key_msg key);
	void onKey_P(key_msg key);
	void onKey_ESC(key_msg key);

	void rendMainface();
	void rendInformation();
	void rend_bar(int x, int y, int w, int h, int n = 4, color_t color = WHITE);
	void rend_bomb();
	void rend_born();
	void rend_end();
	void rend_pause();

	void isEnd();

	void init();
	void initgame();
	void inittankmap();
	void initbulltemap();

	bool canmove1(key_msg key);
	bool canmove2(key_msg key);
private:
	Picture picture;
	Music music;
	map map;
	tank_player player_tank1;
	tank_player player_tank2;

	myQueue bombQueue;
	myQueue bornQueue;

	gameState state;

	bool isover;

	int tankmap[26][26];
	int bulletmap[26][26];
	int playerlife[2];
	int count_pass;
	int level;
};

bool Escloop(gameScene_PVP& gs);