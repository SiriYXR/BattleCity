#include"functions.h"
#include "Music.h"

Music::Music()
{
	mciSendString(TEXT("open 资源包\\音频\\add.wav alias add"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\start.wav alias start"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\switch.wav alias switch"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\hit_wall.wav alias hit_wall"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\hit_tank.wav alias hit_tank"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\lose.wav alias lose"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\dead_enemy.wav alias dead_enemy"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\dead_player.wav alias dead_player"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\prop_appear.wav alias prop_appear"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\prop_get.wav alias prop_get"), NULL, 0, NULL);

}
Music::~Music()
{
	mciSendString(TEXT("close add"), NULL, 0, NULL);
	mciSendString(TEXT("close start"), NULL, 0, NULL);
	mciSendString(TEXT("close switch"), NULL, 0, NULL);
	mciSendString(TEXT("close hit_wall"), NULL, 0, NULL);
	mciSendString(TEXT("close hit_tank"), NULL, 0, NULL);
	mciSendString(TEXT("close lose"), NULL, 0, NULL);
	mciSendString(TEXT("close dead_enemy"), NULL, 0, NULL);
	mciSendString(TEXT("close dead_player"), NULL, 0, NULL);
	mciSendString(TEXT("close prop_appear"), NULL, 0, NULL);
	mciSendString(TEXT("close prop_get"), NULL, 0, NULL);
}

void Music::init()
{
	mciSendString(TEXT("open 资源包\\音频\\add.wav alias add"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\start.wav alias start"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\switch.wav alias switch"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\hit_wall.wav alias hit_wall"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\hit_tank.wav alias hit_tank"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\lose.wav alias lose"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\dead_enemy.wav alias dead_enemy"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\dead_player.wav alias dead_player"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\prop_appear.wav alias prop_appear"), NULL, 0, NULL);
	mciSendString(TEXT("open 资源包\\音频\\prop_get.wav alias prop_get"), NULL, 0, NULL);

}

void Music::mu_Add()
{
	mciSendString(TEXT("seek add to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play add"), NULL, 0, NULL);
}

void Music::mu_Start()
{
	mciSendString(TEXT("seek start to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play start"), NULL, 0, NULL);
}

void Music::mu_Switch()
{
	mciSendString(TEXT("seek switch to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play switch"), NULL, 0, NULL);
}

void Music::mu_Hit_Wall()
{
	mciSendString(TEXT("seek hit_wall to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play hit_wall"), NULL, 0, NULL);
}

void Music::mu_Hit_Tank()
{
	mciSendString(TEXT("seek hit_tank to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play hit_tank"), NULL, 0, NULL);
}

void Music::mu_Lose()
{
	mciSendString(TEXT("seek lose to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play lose"), NULL, 0, NULL);
}

void Music::mu_Dead_Enemy()
{
	mciSendString(TEXT("seek dead_enemy to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play dead_enemy"), NULL, 0, NULL);
}

void Music::mu_Dead_Player()
{
	mciSendString(TEXT("seek dead_player to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play dead_player"), NULL, 0, NULL);
}

void Music::mu_Prop_Appear()
{
	mciSendString(TEXT("seek prop_appear to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play prop_appear"), NULL, 0, NULL);
}

void Music::mu_Prop_get()
{
	mciSendString(TEXT("seek prop_get to 0"), NULL, 0, NULL);
	mciSendString(TEXT("play prop_get"), NULL, 0, NULL);
}
