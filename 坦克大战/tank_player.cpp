#include "tank_player.h"

void tank_player::init_tank_player(myQueue& bornQueue, map& map, direction direct)
{
	aimx = map.getPlayer_x(0);
	aimy = map.getPlayer_y(0);
	x = map_x + aimx * 20;
	y = map_y + aimy * 20;
	count = 0;
	speed = 2;
	level = 1;

	bornQueue.push(x, y);
	this->direct = direct;
	player1 = true;
	bullte.bullet = false;
}

void tank_player::init_tank_player(myQueue& bornQueue, map& map, direction direct, bool isfalse)
{
	aimx = map.getPlayer_x(1);
	aimy = map.getPlayer_y(1);
	x = map_x + aimx * 20;
	y = map_y + aimy * 20;
	count = 0;
	speed = 2;
	level = 1;

	bornQueue.push(x, y);
	this->direct = direct;
	player1 = false;
	bullte.bullet = false;
}

void tank_player::init_xy()
{
	x = map_x + aimx * 20;
	y = map_y + aimy * 20;
}

tank_player::tank_player()
{
}

tank_player::~tank_player()
{
}

void tank_player::update(map & map, int(*tankmap)[26], int(*bulltemap)[26], tank_player& player_tank, queue<tanke_enemy*>& enemyQueue, queue<tanke_enemy*>& deadenemyQueue, myQueue & bombQueue, myQueue & bornQueue, gameState & state, int& playerlife, int& enemynum, int& score)
{
	update_xy();
	if (!bullte.Canfire())
	{
		bullte.update(map, tankmap, bulltemap, player_tank, enemyQueue, deadenemyQueue, bombQueue, bornQueue, state, playerlife, enemynum, score);
	}
}

void tank_player::update(map & map, int(*tankmap)[26], int(*bulletmap)[26], tank_player & player_tank1, tank_player & player_tank2, myQueue & bombQueue, myQueue & bornQueue, gameState & state, int playerlife[])
{
	update_xy();
	if (!bullte.Canfire())
	{
		bullte.update(map, tankmap, bulletmap, player_tank1, player_tank2, bombQueue, bornQueue, state, playerlife);
	}
}

void tank_player::update_xy()
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
void tank_player::render(Picture& picture)
{
	switch (direct)
	{
	case Up:
		if (player1)
			putimage_withalpha(NULL, picture.player_1_W, x, y);
		else
			putimage_withalpha(NULL, picture.player_2_W, x, y);
		break;
	case Down:
		if (player1)
			putimage_withalpha(NULL, picture.player_1_S, x, y);
		else
			putimage_withalpha(NULL, picture.player_2_S, x, y);
		break;
	case Right:
		if (player1)
			putimage_withalpha(NULL, picture.player_1_D, x, y);
		else
			putimage_withalpha(NULL, picture.player_2_D, x, y);
		break;
	case Left:
		if (player1)
			putimage_withalpha(NULL, picture.player_1_A, x, y);
		else
			putimage_withalpha(NULL, picture.player_2_A, x, y);
		break;
	default:
		break;
	}

	if (!bullte.Canfire())
	{
		bullte.render(picture);
	}
}


