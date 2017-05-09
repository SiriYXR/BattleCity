#include "tanke_enemy.h"



tanke_enemy::tanke_enemy(myQueue& bornQueue, map& map, int(*tankmap)[26])
{
	if (myrand_int(0, 10) > 6)
		isHeavy = true;
	else
		isHeavy = false;
	level = myrand_int(0, 10) % 3 + 1;
	direct = Down;
	count = 0;

	update_speed();

	while (true)
	{
		int n = myrand_int(0, 10) % 3;
		if (map.getEnemy_x(n) >= 0)
		{
			aimx = map.getEnemy_x(n);
			aimy = map.getEnemy_y(n);
			if (tankmap[aimx][aimy] == 0 && tankmap[aimx + 1][aimy] == 0 && tankmap[aimx][aimy + 1] == 0 && tankmap[aimx + 1][aimy + 1] == 0)
			{
				x = map_x + aimx * 20;
				y = map_y + aimy * 20;
				bornQueue.push(x, y);
				break;
			}
		}
	}

}


tanke_enemy::~tanke_enemy()
{
}

void tanke_enemy::update(map & map, int(*tankmap)[26], tank_player& palyer_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, gameState & state, int& playerlife, int& enemynum, int& score)
{
	update_speed();
	update_xy();
	if (!bullte.Canfire())
	{
		bullte.update(map, tankmap, palyer_tank, enemyQueue, deadenemyQueue, bombQueue, state, playerlife, enemynum, score);
	}
}

void tanke_enemy::render(Picture& picture)
{
	switch (direct)
	{
	case Up:
		if (isHeavy)
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.heavy_1_W, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.heavy_2_W, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.heavy_3_W, x, y);
				break;
			default:
				break;
			}
		else
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.ordinary_1_W, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.ordinary_2_W, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.ordinary_3_W, x, y);
				break;
			default:
				break;
			}
		break;
	case Down:
		if (isHeavy)
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.heavy_1_S, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.heavy_2_S, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.heavy_3_S, x, y);
				break;
			default:
				break;
			}
		else
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.ordinary_1_S, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.ordinary_2_S, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.ordinary_3_S, x, y);
				break;
			default:
				break;
			}
		break;
	case Right:
		if (isHeavy)
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.heavy_1_D, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.heavy_2_D, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.heavy_3_D, x, y);
				break;
			default:
				break;
			}
		else
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.ordinary_1_D, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.ordinary_2_D, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.ordinary_3_D, x, y);
				break;
			default:
				break;
			}
		break;
	case Left:
		if (isHeavy)
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.heavy_1_A, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.heavy_2_A, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.heavy_3_A, x, y);
				break;
			default:
				break;
			}
		else
			switch (level)
			{
			case 1:
				putimage_withalpha(NULL, picture.ordinary_1_A, x, y);
				break;
			case 2:
				putimage_withalpha(NULL, picture.ordinary_2_A, x, y);
				break;
			case 3:
				putimage_withalpha(NULL, picture.ordinary_3_A, x, y);
				break;
			default:
				break;
			}
		break;
	default:
		break;
	}

	if (!bullte.Canfire())
	{
		bullte.render(picture);
	}
}

void tanke_enemy::update_xy()
{
	if (count)
	{
		switch (direct)
		{
		case Up:
			y -= speed;
			break;
		case Down:
			y += speed;
			break;
		case Right:
			x += speed;
			break;
		case Left:
			x -= speed;
			break;
		}
		count--;
	}
}

void tanke_enemy::update_speed()
{
	if (level == 1)
		speed = 1;
	else if (level == 2)
		speed = 2;
	else
		speed = 4;
}
