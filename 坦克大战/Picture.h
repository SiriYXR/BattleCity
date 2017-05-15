#pragma once
#include"functions.h"

class Picture
{
public:
	Picture();
	~Picture();

	void clear();
	void rend();

	//画布
	PIMAGE canvas = newimage(Win_W, Win_H);

	//爆炸
	//----------------------------
	PIMAGE explode_1 = newimage();
	PIMAGE explode_2 = newimage();
	PIMAGE explode_3 = newimage();
	PIMAGE explode_4 = newimage();
	PIMAGE explode_5 = newimage();
	PIMAGE explode_6 = newimage();
	PIMAGE explode_7 = newimage();
	PIMAGE explode_8 = newimage();

	//道具
	//-----------------------------
	PIMAGE bomb = newimage();
	PIMAGE life = newimage();
	PIMAGE shield = newimage();
	PIMAGE star = newimage();
	PIMAGE timer = newimage();

	//地图
	//-----------------------------
	////20X20
	PIMAGE wall_steel_2 = newimage();
	PIMAGE wall_stone_2 = newimage();
	PIMAGE grass_2 = newimage();
	PIMAGE water_2 = newimage();

	////40X40
	PIMAGE wall_steel_4 = newimage();
	PIMAGE wall_stone_4 = newimage();
	PIMAGE destory = newimage();
	PIMAGE grass_4 = newimage();
	PIMAGE water_4 = newimage();
	PIMAGE home = newimage();
	PIMAGE enemyborn = newimage();
	PIMAGE player1born = newimage();
	PIMAGE player2born = newimage();
	PIMAGE d_delete = newimage();
	PIMAGE d_save = newimage();
	PIMAGE d_return = newimage();
	PIMAGE d_clean = newimage();

	//地图预览
	////PVE
	PIMAGE map_PVE_1 = newimage();
	PIMAGE map_PVE_2 = newimage();
	PIMAGE map_PVE_3 = newimage();
	PIMAGE map_PVE_4 = newimage();
	PIMAGE map_PVE_5 = newimage();
	PIMAGE map_PVE_6 = newimage();
	PIMAGE map_PVE_7 = newimage();
	PIMAGE map_PVE_8 = newimage();
	PIMAGE map_PVE_9 = newimage();
	PIMAGE map_PVE_10 = newimage();
	PIMAGE map_PVE_11 = newimage();
	PIMAGE map_PVE_12 = newimage();
	PIMAGE map_PVE_13 = newimage();
	PIMAGE map_PVE_14 = newimage();
	PIMAGE map_PVE_15 = newimage();
	PIMAGE map_PVE_16 = newimage();
	PIMAGE map_PVE_17 = newimage();
	PIMAGE map_PVE_18 = newimage();
	PIMAGE map_PVE_19 = newimage();
	PIMAGE map_PVE_20 = newimage();

	////PVP
	PIMAGE map_PVP_1 = newimage();
	PIMAGE map_PVP_2 = newimage();
	PIMAGE map_PVP_3 = newimage();
	PIMAGE map_PVP_4 = newimage();
	PIMAGE map_PVP_5 = newimage();

	PIMAGE map_lock = newimage();

	//界面
	//-----------------------------
	PIMAGE over = newimage();

	PIMAGE selects = newimage();
	PIMAGE solo_selects = newimage();
	PIMAGE design_selects = newimage();
	PIMAGE duet_main_selects = newimage();

	PIMAGE title = newimage();
	PIMAGE end = newimage();
	PIMAGE BattleCity = newimage();
	PIMAGE selecttank = newimage();
	PIMAGE copyright = newimage();

	PIMAGE instruction_solo = newimage();
	PIMAGE instruction_duet = newimage();

	//坦克
	//-----------------------------
	////出生
	PIMAGE born_1 = newimage();
	PIMAGE born_2 = newimage();
	PIMAGE born_3 = newimage();
	PIMAGE born_4 = newimage();

	////敌人
	////---------------------------
	////普通坦克
	////---------------------------
	//////1
	PIMAGE ordinary_1_A = newimage();
	PIMAGE ordinary_1_D = newimage();
	PIMAGE ordinary_1_S = newimage();
	PIMAGE ordinary_1_W = newimage();
	//////2
	PIMAGE ordinary_2_A = newimage();
	PIMAGE ordinary_2_D = newimage();
	PIMAGE ordinary_2_S = newimage();
	PIMAGE ordinary_2_W = newimage();
	//////3
	PIMAGE ordinary_3_A = newimage();
	PIMAGE ordinary_3_D = newimage();
	PIMAGE ordinary_3_S = newimage();
	PIMAGE ordinary_3_W = newimage();
	////重型坦克
	////---------------------------
	//////1
	PIMAGE heavy_1_A = newimage();
	PIMAGE heavy_1_D = newimage();
	PIMAGE heavy_1_S = newimage();
	PIMAGE heavy_1_W = newimage();
	//////2
	PIMAGE heavy_2_A = newimage();
	PIMAGE heavy_2_D = newimage();
	PIMAGE heavy_2_S = newimage();
	PIMAGE heavy_2_W = newimage();
	//////3
	PIMAGE heavy_3_A = newimage();
	PIMAGE heavy_3_D = newimage();
	PIMAGE heavy_3_S = newimage();
	PIMAGE heavy_3_W = newimage();

	////玩家
	////-----------------------------
	//////玩家1
	PIMAGE player_1_A = newimage();
	PIMAGE player_1_D = newimage();
	PIMAGE player_1_S = newimage();
	PIMAGE player_1_W = newimage();
	//////玩家2
	PIMAGE player_2_A = newimage();
	PIMAGE player_2_D = newimage();
	PIMAGE player_2_S = newimage();
	PIMAGE player_2_W = newimage();

	////子弹
	////----------------------------
	//////敌人
	PIMAGE E_missile = newimage();
	//////玩家
	PIMAGE P_missile = newimage();
};