#pragma once
#include"Picture.h"
#include"map.h"
#include"Music.h"

class designer_PVE
{

public:
	map tempmap;
	bool isover;

	designer_PVE();
	~designer_PVE();

	void update();
	void render();
	bool isOver();

	void onKey(key_msg key);

private:
	void key_direction(key_msg key);
	void key_WASD(key_msg key);
	void key_Space(key_msg key);
	void key_ESC(key_msg key);
	void key_Shift(key_msg key);

	void mainface();
	void rend_information();
	void rendCursor1();
	void rendCursor2();
	void rend_bar(int x,int y,int w,int h,int n=4,color_t color=WHITE);

	bool isOK();
	bool isOK_4( );
	bool isOK_4_home( );
	bool isOK_4_player1( );
	bool isOK_4_player2( );
	bool isOK_4_delete();

	void update_size();
	void update_saveOK();

	void init();
	
private:
	Picture picture;
	Music music;


	int cursor1_x, cursor1_y;
	int cursor2_x, cursor2_y;

	int enemynum;
	bool bigsize;
	bool issave;
	bool saveOK;
};

void isoverloop(designer_PVE& des);