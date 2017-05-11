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

	ai_bullte_count = 60;
	ai_move_count = 0;

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

void tanke_enemy::update(map & map, int(*tankmap)[26], int(*bulltemap)[26], tank_player& player_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, myQueue & bornQueue, gameState & state, int& playerlife, int& enemynum, int& score)
{
	AI_bullte();

	update_speed();
	update_move(map, tankmap);
	update_xy();
	init_xy();

	if (!bullte.Canfire())
	{
		bullte.update(map, tankmap, bulltemap, player_tank, enemyQueue, deadenemyQueue, bombQueue, bornQueue, state, playerlife, enemynum, score);
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
	if (level < 3)
		speed = 1;
	else
		speed = 2;
}

void tanke_enemy::update_move(map & map, int(*tankmap)[26])
{
	AI_direct(map, tankmap);
	AI_move();

	if (count == 0 && ai_move_count)
	{
		switch (direct)
		{
		case Up:
			if (canmove(map, tankmap))
			{
				aimy--;
				update_count();
			}
			break;
		case Down:
			if (canmove(map, tankmap))
			{
				aimy++;
				update_count();
			}
			break;
		case Right:
			if (canmove(map, tankmap))
			{
				aimx++;
				update_count();
			}
			break;
		case Left:
			if (canmove(map, tankmap))
			{
				aimx--;
				update_count();
			}
			break;
		}
		ai_move_count--;
	}
}

void tanke_enemy::update_count()
{
	count = 20 / speed;
}

void tanke_enemy::AI_bullte()
{
	if (ai_bullte_count)
		ai_bullte_count--;

	if (bullte.Canfire() && ai_bullte_count == 0)
	{

		if (level < 2)
			bullte.init(0, aimx, aimy, direct, 5);
		else
			bullte.init(0, aimx, aimy, direct, 10);

		ai_bullte_count = 200;
	}

}

void tanke_enemy::AI_direct(map & map, int(*tankmap)[26])
{

	if (ai_move_count == 0 && count == 0)
	{
		if (myrand_int(0, 10) > 4)
		{
			direct = Down;
		}
		else
		{
			if (myrand_int(0, 10) > 4)
			{
				if (myrand_int(0, 10) > 5)
					direct = Right;
				else
					direct = Left;
			}
			else
				direct = Up;
		}
	}
}

void tanke_enemy::AI_move()
{
	if (count == 0)
	{
		if (ai_move_count == 0)
		{
			ai_move_count = myrand_int(3, 20);
		}
		else
		{
			ai_move_count--;
		}
	}
}

void tanke_enemy::init_xy()
{
	if (count == 0)
	{
		x = map_x + aimx * 20;
		y = map_y + aimy * 20;
	}
}

bool tanke_enemy::canmove(map & map, int(*tankmap)[26])
{

	switch (direct)
	{
	case Up:
		if (aimy <= 0)
			return false;
		if (tankmap[aimx][aimy - 1] != 0 || tankmap[aimx + 1][aimy - 1] != 0)
			return false;
		if (map.getmember(0, aimx, aimy - 1) != land || map.getmember(0, aimx + 1, aimy - 1) != land)
			return false;
		if (map.getmember(1, aimx, aimy - 1) == home || map.getmember(1, aimx + 1, aimy - 1) == home)
			return false;
		if (map.getmember(1, aimx, aimy - 1) == home_h || map.getmember(1, aimx + 1, aimy - 1) == home_h)
			return false;
		break;
	case Down:
		if (aimy >= 24)
			return false;
		if (tankmap[aimx][aimy + 2] != 0 || tankmap[aimx + 1][aimy + 2] != 0)
			return false;
		if (map.getmember(0, aimx, aimy + 2) != land || map.getmember(0, aimx + 1, aimy + 2) != land)
			return false;
		if (map.getmember(1, aimx, aimy + 2) == home || map.getmember(1, aimx + 1, aimy + 2) == home)
			return false;
		if (map.getmember(1, aimx, aimy + 2) == home_h || map.getmember(1, aimx + 1, aimy + 2) == home_h)
			return false;
		break;
	case Right:
		if (aimx >= 24)
			return false;
		if (tankmap[aimx + 2][aimy] != 0 || tankmap[aimx + 2][aimy + 1] != 0)
			return false;
		if (map.getmember(0, aimx + 2, aimy) != land || map.getmember(0, aimx + 2, aimy + 1) != land)
			return false;
		if (map.getmember(1, aimx + 2, aimy) == home || map.getmember(1, aimx + 2, aimy + 1) == home)
			return false;
		if (map.getmember(1, aimx + 2, aimy) == home_h || map.getmember(1, aimx + 2, aimy + 1) == home_h)
			return false;
		break;
	case Left:
		if (aimx <= 0)
			return false;
		if (tankmap[aimx - 1][aimy] != 0 || tankmap[aimx - 1][aimy + 1] != 0)
			return false;
		if (map.getmember(0, aimx - 1, aimy) != land || map.getmember(0, aimx - 1, aimy + 1) != land)
			return false;
		if (map.getmember(1, aimx - 1, aimy) == home || map.getmember(1, aimx - 1, aimy + 1) == home)
			return false;
		if (map.getmember(1, aimx - 1, aimy) == home_h || map.getmember(1, aimx - 1, aimy + 1) == home_h)
			return false;
		break;
	}
	return true;
}
