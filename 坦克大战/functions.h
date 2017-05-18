#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <Windows.h>
#include<queue>

#include<ege.h>
#include <graphics.h>

#include<conio.h>//can not include "conio.h" before "graphics.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "ADBConnector.h"
#include "AFormat.h"

#include"myQueue.h"

using namespace std;

enum mode
{
	PVE,
	PVP
};

enum texture
{
	land,
	water,
	stone,
	steel,
	home,
	home_h,
	destory,
	destory_h,
	grass,
	enemyborn_h,
	enemyborn,
	player1born,
	player2born

};

enum direction
{
	Up,
	Down,
	Right,
	Left,
	Stay
};

enum gameState
{
	gaming,
	pause,
	lose,
	lose1,
	lose2,
	pass
};

enum property
{
	tank,
	bomb,
	star,
	timer,
	sheld
};

struct point
{
	int x;
	int y;
};

struct prop
{
	property pro;
	int x;
	int y;
	int time;
};

struct mapdata;
class Picture;

extern athena::ADBConnector DB;

//窗口尺寸
const int Win_W = 26 * 20 + 4 + 280;
const int Win_H = 26 * 20 + 4 + 80;

const int  map_W = 26;
const int  map_H = 26;

//地图基座标
const int	map_x = 30;
const int	map_y = (Win_H - 20 * 26) / 2;

void mainloop();
void designPVEloop();
void designPVPloop();
void soloGameloop(int level=1);
void PVPGameloop(int level = -1);
void duet_PVEGameloop(int level = -1);
void duet_custom_loop();
void duet_classic_loop();
void duet_classic_PVE_loop();
int Selectlevelloop_PVE(int maxlevel);
int Selectlevelloop_PVP();

int myrand_int(int min, int max);

void movieTitle();
void movieEnd();
void movieShine(int time);
void movieBorn(int time, int x, int y, Picture& picture);
void movieBomb(int time);
void movieBomb(int time, int x, int y, Picture& picture);
void movie_Loding();