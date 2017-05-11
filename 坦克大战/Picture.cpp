#include"Picture.h"
#include"functions.h"

Picture::Picture()
{

	//爆炸
	//----------------------------
	getimage(explode_1, "资源包\\图片\\爆炸\\1.png");
	getimage(explode_2, "资源包\\图片\\爆炸\\2.png");
	getimage(explode_3, "资源包\\图片\\爆炸\\3.png");
	getimage(explode_4, "资源包\\图片\\爆炸\\4.png");
	getimage(explode_5, "资源包\\图片\\爆炸\\5.png");
	getimage(explode_6, "资源包\\图片\\爆炸\\6.png");
	getimage(explode_7, "资源包\\图片\\爆炸\\7.png");
	getimage(explode_8, "资源包\\图片\\爆炸\\8.png");

	//道具
	//-----------------------------
	getimage(bomb, "资源包\\图片\\道具\\bomb.png");
	getimage(life, "资源包\\图片\\道具\\life.png");
	getimage(shield, "资源包\\图片\\道具\\shield.png");
	getimage(star, "资源包\\图片\\道具\\star.png");
	getimage(timer, "资源包\\图片\\道具\\timer.png");

	//地图
	//-----------------------------
	////20X20
	getimage(wall_steel_2, "资源包\\图片\\地图\\20X20\\wall_steel_2.png");
	getimage(wall_stone_2, "资源包\\图片\\地图\\20X20\\wall_stone_2.png");
	getimage(grass_2, "资源包\\图片\\地图\\20X20\\grass_2.png");
	getimage(water_2, "资源包\\图片\\地图\\20X20\\water_2.png");

	////40X40
	getimage(wall_steel_4, "资源包\\图片\\地图\\40X40\\wall_steel_4.png");
	getimage(wall_stone_4, "资源包\\图片\\地图\\40X40\\wall_stone_4.png");
	getimage(destory, "资源包\\图片\\地图\\40X40\\destory.png");
	getimage(grass_4, "资源包\\图片\\地图\\40X40\\grass_4.png");
	getimage(water_4, "资源包\\图片\\地图\\40X40\\water_4.png");
	getimage(home, "资源包\\图片\\地图\\40X40\\home.png");
	getimage(enemyborn, "资源包\\图片\\地图\\40X40\\enemyborn.png");
	getimage(player1born, "资源包\\图片\\地图\\40X40\\player1born.png");
	getimage(player2born, "资源包\\图片\\地图\\40X40\\player2born.png");
	getimage(d_delete, "资源包\\图片\\地图\\40X40\\delete.png");
	getimage(d_save, "资源包\\图片\\地图\\40X40\\save.png");
	getimage(d_return, "资源包\\图片\\地图\\40X40\\return.png");
	getimage(d_clean, "资源包\\图片\\地图\\40X40\\clean.png");

	////地图预览
	//////PVE
	getimage(map_PVE_1, "资源包\\图片\\地图\\地图预览\\PVE\\1.jpg");
	getimage(map_PVE_2, "资源包\\图片\\地图\\地图预览\\PVE\\2.jpg");
	getimage(map_PVE_3, "资源包\\图片\\地图\\地图预览\\PVE\\3.jpg");
	getimage(map_PVE_4, "资源包\\图片\\地图\\地图预览\\PVE\\4.jpg");
	getimage(map_PVE_5, "资源包\\图片\\地图\\地图预览\\PVE\\5.jpg");
	getimage(map_PVE_6, "资源包\\图片\\地图\\地图预览\\PVE\\6.jpg");
	getimage(map_PVE_7, "资源包\\图片\\地图\\地图预览\\PVE\\7.jpg");
	getimage(map_PVE_8, "资源包\\图片\\地图\\地图预览\\PVE\\8.jpg");
	getimage(map_PVE_9, "资源包\\图片\\地图\\地图预览\\PVE\\9.jpg");
	getimage(map_PVE_10, "资源包\\图片\\地图\\地图预览\\PVE\\10.jpg");
	getimage(map_PVE_11, "资源包\\图片\\地图\\地图预览\\PVE\\11.jpg");
	getimage(map_PVE_12, "资源包\\图片\\地图\\地图预览\\PVE\\12.jpg");
	getimage(map_PVE_13, "资源包\\图片\\地图\\地图预览\\PVE\\13.jpg");
	getimage(map_PVE_14, "资源包\\图片\\地图\\地图预览\\PVE\\14.jpg");
	getimage(map_PVE_15, "资源包\\图片\\地图\\地图预览\\PVE\\15.jpg");
	getimage(map_PVE_16, "资源包\\图片\\地图\\地图预览\\PVE\\16.jpg");
	getimage(map_PVE_17, "资源包\\图片\\地图\\地图预览\\PVE\\17.jpg");
	getimage(map_PVE_18, "资源包\\图片\\地图\\地图预览\\PVE\\18.jpg");
	getimage(map_PVE_19, "资源包\\图片\\地图\\地图预览\\PVE\\19.jpg");
	getimage(map_PVE_20, "资源包\\图片\\地图\\地图预览\\PVE\\20.jpg");

	getimage(map_lock, "资源包\\图片\\地图\\地图预览\\lock.jpg");



	//界面
	//-----------------------------
	getimage(over, "资源包\\图片\\界面\\over.png");

	getimage(selects, "资源包\\图片\\界面\\selects.png");
	getimage(solo_selects, "资源包\\图片\\界面\\solo_selects.png");
	getimage(design_selects, "资源包\\图片\\界面\\design_selects.png");

	getimage(title, "资源包\\图片\\界面\\title.png");
	getimage(end, "资源包\\图片\\界面\\end.png");
	getimage(BattleCity, "资源包\\图片\\界面\\BattleCity.png");
	getimage(selecttank, "资源包\\图片\\界面\\selecttank.png");
	getimage(copyright, "资源包\\图片\\界面\\copyright.png");

	getimage(instruction_solo, "资源包\\图片\\界面\\instruction_solo.png");
	//坦克
	//-----------------------------
	////出生
	getimage(born_1, "资源包\\图片\\坦克\\出生\\1.png");
	getimage(born_2, "资源包\\图片\\坦克\\出生\\2.png");
	getimage(born_3, "资源包\\图片\\坦克\\出生\\3.png");
	getimage(born_4, "资源包\\图片\\坦克\\出生\\4.png");

	////敌人
	////---------------------------
	////普通坦克
	////---------------------------
	//////1
	getimage(ordinary_1_A, "资源包\\图片\\坦克\\敌人\\普通坦克\\1\\A.png");
	getimage(ordinary_1_D, "资源包\\图片\\坦克\\敌人\\普通坦克\\1\\D.png");
	getimage(ordinary_1_S, "资源包\\图片\\坦克\\敌人\\普通坦克\\1\\S.png");
	getimage(ordinary_1_W, "资源包\\图片\\坦克\\敌人\\普通坦克\\1\\W.png");
	//////2
	getimage(ordinary_2_A, "资源包\\图片\\坦克\\敌人\\普通坦克\\2\\A.png");
	getimage(ordinary_2_D, "资源包\\图片\\坦克\\敌人\\普通坦克\\2\\D.png");
	getimage(ordinary_2_S, "资源包\\图片\\坦克\\敌人\\普通坦克\\2\\S.png");
	getimage(ordinary_2_W, "资源包\\图片\\坦克\\敌人\\普通坦克\\2\\W.png");
	//////3
	getimage(ordinary_3_A, "资源包\\图片\\坦克\\敌人\\普通坦克\\3\\A.png");
	getimage(ordinary_3_D, "资源包\\图片\\坦克\\敌人\\普通坦克\\3\\D.png");
	getimage(ordinary_3_S, "资源包\\图片\\坦克\\敌人\\普通坦克\\3\\S.png");
	getimage(ordinary_3_W, "资源包\\图片\\坦克\\敌人\\普通坦克\\3\\W.png");
	////重型坦克
	////---------------------------
	//////1
	getimage(heavy_1_A, "资源包\\图片\\坦克\\敌人\\重型坦克\\1\\A.png");
	getimage(heavy_1_D, "资源包\\图片\\坦克\\敌人\\重型坦克\\1\\D.png");
	getimage(heavy_1_S, "资源包\\图片\\坦克\\敌人\\重型坦克\\1\\S.png");
	getimage(heavy_1_W, "资源包\\图片\\坦克\\敌人\\重型坦克\\1\\W.png");
	//////2
	getimage(heavy_2_A, "资源包\\图片\\坦克\\敌人\\重型坦克\\2\\A.png");
	getimage(heavy_2_D, "资源包\\图片\\坦克\\敌人\\重型坦克\\2\\D.png");
	getimage(heavy_2_S, "资源包\\图片\\坦克\\敌人\\重型坦克\\2\\S.png");
	getimage(heavy_2_W, "资源包\\图片\\坦克\\敌人\\重型坦克\\2\\W.png");
	//////3
	getimage(heavy_3_A, "资源包\\图片\\坦克\\敌人\\重型坦克\\3\\A.png");
	getimage(heavy_3_D, "资源包\\图片\\坦克\\敌人\\重型坦克\\3\\D.png");
	getimage(heavy_3_S, "资源包\\图片\\坦克\\敌人\\重型坦克\\3\\S.png");
	getimage(heavy_3_W, "资源包\\图片\\坦克\\敌人\\重型坦克\\3\\W.png");

	////玩家
	////-----------------------------
	//////玩家1
	getimage(player_1_A, "资源包\\图片\\坦克\\玩家\\玩家1\\A.png");
	getimage(player_1_D, "资源包\\图片\\坦克\\玩家\\玩家1\\D.png");
	getimage(player_1_S, "资源包\\图片\\坦克\\玩家\\玩家1\\S.png");
	getimage(player_1_W, "资源包\\图片\\坦克\\玩家\\玩家1\\W.png");
	//////玩家2
	getimage(player_2_A, "资源包\\图片\\坦克\\玩家\\玩家2\\A.png");
	getimage(player_2_D, "资源包\\图片\\坦克\\玩家\\玩家2\\D.png");
	getimage(player_2_S, "资源包\\图片\\坦克\\玩家\\玩家2\\S.png");
	getimage(player_2_W, "资源包\\图片\\坦克\\玩家\\玩家2\\W.png");

	////子弹
	////----------------------------
	//////敌人
	getimage(E_missile, "资源包\\图片\\坦克\\子弹\\敌人\\missile.png");
	//////玩家
	getimage(P_missile, "资源包\\图片\\坦克\\子弹\\玩家\\missile.png");

}

Picture::~Picture()
{
	//画布
	delimage(canvas);

	//爆炸
	//----------------------------
	delimage(explode_1);
	delimage(explode_2);
	delimage(explode_3);
	delimage(explode_4);
	delimage(explode_5);
	delimage(explode_6);
	delimage(explode_7);
	delimage(explode_8);

	//道具
	//-----------------------------
	delimage(bomb);
	delimage(life);
	delimage(shield);
	delimage(star);
	delimage(timer);

	//地图
	//-----------------------------
	////20X20
	delimage(wall_steel_2);
	delimage(wall_stone_2);
	delimage(grass_2);
	delimage(water_2);

	////40X40
	delimage(wall_steel_4);
	delimage(wall_stone_4);
	delimage(destory);
	delimage(grass_4);
	delimage(water_4);
	delimage(home);
	delimage(enemyborn);
	delimage(player1born);
	delimage(player2born);
	delimage(d_clean);
	delimage(d_delete);
	delimage(d_return);
	delimage(d_save);

	////地图预览
	//////PVE
	delimage(map_PVE_1);
	delimage(map_PVE_2);
	delimage(map_PVE_3);
	delimage(map_PVE_4);
	delimage(map_PVE_5);
	delimage(map_PVE_6);
	delimage(map_PVE_7);
	delimage(map_PVE_8);
	delimage(map_PVE_9);
	delimage(map_PVE_10);
	delimage(map_PVE_11);
	delimage(map_PVE_12);
	delimage(map_PVE_13);
	delimage(map_PVE_14);
	delimage(map_PVE_15);
	delimage(map_PVE_16);
	delimage(map_PVE_17);
	delimage(map_PVE_18);
	delimage(map_PVE_19);
	delimage(map_PVE_20);

	delimage(map_lock);

	//界面
	//-----------------------------
	delimage(over);

	delimage(selects);
	delimage(solo_selects);
	delimage(design_selects);

	delimage(title);
	delimage(end);
	delimage(BattleCity);
	delimage(selecttank);
	delimage(copyright);

	delimage(instruction_solo);

	//坦克
	//-----------------------------
	////出生
	delimage(born_1);
	delimage(born_2);
	delimage(born_3);
	delimage(born_4);

	////敌人
	////---------------------------
	////普通坦克
	////---------------------------
	//////1
	delimage(ordinary_1_A);
	delimage(ordinary_1_D);
	delimage(ordinary_1_S);
	delimage(ordinary_1_W);
	//////2
	delimage(ordinary_2_A);
	delimage(ordinary_2_D);
	delimage(ordinary_2_S);
	delimage(ordinary_2_W);
	//////3
	delimage(ordinary_3_A);
	delimage(ordinary_3_D);
	delimage(ordinary_3_S);
	delimage(ordinary_3_W);
	////重型坦克
	////---------------------------
	//////1
	delimage(heavy_1_A);
	delimage(heavy_1_D);
	delimage(heavy_1_S);
	delimage(heavy_1_W);
	//////2
	delimage(heavy_2_A);
	delimage(heavy_2_D);
	delimage(heavy_2_S);
	delimage(heavy_2_W);
	//////3
	delimage(heavy_3_A);
	delimage(heavy_3_D);
	delimage(heavy_3_S);
	delimage(heavy_3_W);

	////玩家
	////-----------------------------
	//////玩家1
	delimage(player_1_A);
	delimage(player_1_D);
	delimage(player_1_S);
	delimage(player_1_W);
	//////玩家2
	delimage(player_2_A);
	delimage(player_2_D);
	delimage(player_2_S);
	delimage(player_2_W);

	////子弹
	////----------------------------
	//////敌人
	delimage(E_missile);
	//////玩家
	delimage(P_missile);
}

void Picture::clear()
{
	cleardevice();
	cleardevice(canvas);
	settarget(canvas);
}

void Picture::rend()
{
	settarget(NULL);
	putimage(0, 0, canvas);
}
