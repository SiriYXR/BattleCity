#include"Picture.h"
#include"map.h"
#include"functions.h"

struct mapdata
{
	texture map[2][map_H][map_W] = { land };
	point enemy[3];
	point player[2];
	point home[2];
	mode gamemode;
};

map::map()
{
	member = new mapdata;
	member->gamemode = PVE;
}


void map::init(mode mode)
{
	delete member;
	member = new mapdata;
	if (mode == PVE)
	{
		member->gamemode = PVE;
		setmapmember_4_plus(1, 12, 24, home);
		setmapmember_4_plus(1, 9, 24, player1born);
		setmapmember_4_plus(1, 15, 24, player2born);
		
	}
	else if (mode == PVP)
	{
		member->gamemode = PVP;
		setmapmember_4_plus(1, 0, 12, home);
		setmapmember_4_plus(1, 24, 12, home);
		setmapmember_4_plus(1, 0, 9, player1born);
		setmapmember_4_plus(1, 24, 15, player2born);
		
	}
}

void map::init_point()
{
	for (int i = 0; i < 3; i++)
	{
		member->enemy[i].x = -1;
		member->enemy[i].y = -1;
	}
	for (int i = 0; i < 2; i++)
	{
		member->player[i].x = -1;
		member->player[i].y = -1;
	}
	for (int i = 0; i < 2; i++)
	{
		member->home[i].x = -1;
		member->home[i].y = -1;
	}
}

map::~map()
{
	delete member;
}

void map::rendermap1(Picture& picture)
{
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[0][i][j] == water)
				putimage_withalpha(NULL, picture.water_2, map_x + i * 20, map_y + j * 20);
			else if (member->map[0][i][j] == stone)
				putimage_withalpha(NULL, picture.wall_stone_2, map_x + i * 20, map_y + j * 20);
			else if (member->map[0][i][j] == steel)
				putimage_withalpha(NULL, picture.wall_steel_2, map_x + i * 20, map_y + j * 20);
		}
}

void map::rendermap2(Picture& picture)
{
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == grass)
				putimage_withalpha(NULL, picture.grass_2, map_x + i * 20, map_y + j * 20);
		}
}

int map::rendermaphome(Picture & picture)
{
	for (int i = 0; i < map_W - 1; i++)
		for (int j = 0; j < map_H - 1; j++)
		{
			if (member->map[1][i][j] == home_h)
			{
				putimage_withalpha(NULL, picture.home, map_x + i * 20, map_y + j * 20);
			}
			if (member->map[1][i][j] == destory_h)
			{
				putimage_withalpha(NULL, picture.destory, map_x + i * 20, map_y + j * 20);
			}
		}
	return 0;
}

int map::rendermapenemyborn(Picture & picture)
{
	int count = 0;
	for (int i = 0; i < map_W - 1; i++)
		for (int j = 0; j < map_H - 1; j++)
		{
			if (count == 3)
			{
				return 0;
			}

			if (member->map[1][i][j] == enemyborn_h)
			{
				putimage_withalpha(NULL, picture.enemyborn, map_x + i * 20, map_y + j * 20);
				j++;
				count++;
			}
		}
	return 0;
}

int map::rendermapplayer1born(Picture & picture)
{
	for (int i = 0; i < map_W - 1; i++)
		for (int j = 0; j < map_H - 1; j++)
		{
			if (member->map[1][i][j] == player1born)
			{
				putimage_withalpha(NULL, picture.player1born, map_x + i * 20, map_y + j * 20);
				return 0;
			}
		}
	return 0;
}

int map::rendermapplayer2born(Picture & picture)
{
	for (int i = 0; i < map_W - 1; i++)
		for (int j = 0; j < map_H - 1; j++)
		{
			if (member->map[1][i][j] == player2born)
			{
				putimage_withalpha(NULL, picture.player2born, map_x + i * 20, map_y + j * 20);
				return 0;
			}
		}
	return 0;
}

void map::autoclearhome()
{
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == home || member->map[1][i][j] == home_h)
			{
				member->map[0][i][j] = land;
				member->map[1][i][j] = land;
			}
		}
}

void map::autoclearplayer1()
{
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == player1born)
			{
				member->map[0][i][j] = land;
				member->map[1][i][j] = land;
			}
		}
}

void map::autoclearplayer2()
{
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == player2born)
			{
				member->map[0][i][j] = land;
				member->map[1][i][j] = land;
			}
		}
}

void map::Search()
{
	init_point();
	int n;
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == player1born)
			{
				member->player[0].x =i ;
				member->player[0].y = j;
				i = map_W;
				j = map_H;
			}
		}
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == player2born)
			{
				member->player[1].x = i;
				member->player[1].y = j;
				i = map_W;
				j = map_H;
			}
		}
	n = 0;
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == enemyborn_h)
			{
				member->enemy[n].x = i;
				member->enemy[n].y = j;
				n++;
			}
		}
	n = 0;
	for (int i = 0; i < map_W; i++)
		for (int j = 0; j < map_H; j++)
		{
			if (member->map[1][i][j] == home_h)
			{
				member->home[n].x = i;
				member->home[n].y = j;
				n++;
			}
		}
	if (member->home[1].x != -1)
		member->gamemode = PVP;
	else
		member->gamemode = PVE;
}

void map::save_design()
{
	Search();
	FILE *fp;
	if (member->gamemode == PVE)
		fp = fopen("资源包\\maps\\custom\\custommap_PVE.dat", "wb");
	else
		fp = fopen("资源包\\maps\\custom\\custommap_PVP.dat", "wb");
	fwrite(member, sizeof(*member), 1, fp);
	fclose(fp);
}

void map::load_design()
{
	FILE *fp;
	if (member->gamemode == PVE)
		fp = fopen("资源包\\maps\\custom\\custommap_PVE.dat", "rb");
	else
		fp = fopen("资源包\\maps\\custom\\custommap_PVP.dat", "rb");
	fseek(fp, sizeof(*member)*(0), SEEK_SET);
	fread(member, sizeof(*member), 1, fp);
	fclose(fp);
}

void map::load_PVE(int level)
{
	FILE *fp;
	fp = fopen("资源包\\maps\\classic\\classicmap_PVE.dat", "rb");
	fseek(fp, sizeof(*member)*(level-1), SEEK_SET);
	fread(member, sizeof(*member), 1, fp);

	fclose(fp);
}

void map::load_PVP(int level)
{
	FILE *fp;
	fp = fopen("资源包\\maps\\classic\\classicmap_PVP.dat", "rb");
	fseek(fp, sizeof(*member)*(level - 1), SEEK_SET);
	fread(member, sizeof(*member), 1, fp);

	fclose(fp);
}

void map::rendAll(Picture & picture)
{
	rendermap1(picture);
	rendermap2(picture);
	rendermaphome(picture);
	rendermapenemyborn(picture);
	rendermapplayer1born(picture);
	rendermapplayer2born(picture);
}

mode map::getmode()
{
	return member->gamemode;
}

texture map::getmember(int i, int j, int k)
{
	return member->map[i][j][k];
}

int map::getHome_x(int n)
{
	return member->home[n].x;
}

int map::getHome_y(int n)
{
	return member->home[n].y;
}

int map::getPlayer_x(int n)
{
	return member->player[n].x;
}

int map::getPlayer_y(int n)
{
	return member->player[n].y;
}

int map::getEnemy_x(int n)
{
	return member->enemy[n].x;
}

int map::getEnemy_y(int n)
{
	return member->enemy[n].y;
}

void map::setmember(int i, int j, int k, texture tex)
{
	member->map[i][j][k] = tex;
}

void map::setmapmember_4(int i, int j, int k, texture tex)
{
	setmember(i, j, k, tex);
	setmember(i, j + 1, k, tex);
	setmember(i, j, k + 1, tex);
	setmember(i, j + 1, k + 1, tex);
}

void map::setmapmember_4_plus(int i, int j, int k, texture tex)
{
	if (tex == home&&member->gamemode==PVE)
		autoclearhome();
	else if (tex == player1born)
		autoclearplayer1();
	else if (tex == player2born)
		autoclearplayer2();

	if (tex == home)
		setmember(1, j, k, home_h);
	else
		setmember(1, j, k, tex);
	setmember(1, j + 1, k, tex);
	setmember(1, j, k + 1, tex);
	setmember(1, j + 1, k + 1, tex);
	setmember(0, j, k, land);
	setmember(0, j + 1, k, land);
	setmember(0, j, k + 1, land);
	setmember(0, j + 1, k + 1, land);
}

void map::setmapmember_4_enemy(int i, int j, int k)
{
	setmember(i, j, k, enemyborn_h);
	setmember(i, j + 1, k, enemyborn);
	setmember(i, j, k + 1, enemyborn);
	setmember(i, j + 1, k + 1, enemyborn);
	setmember(0, j, k, land);
	setmember(0, j + 1, k, land);
	setmember(0, j, k + 1, land);
	setmember(0, j + 1, k + 1, land);
}