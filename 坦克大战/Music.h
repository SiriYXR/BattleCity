#pragma once
#include"functions.h"

class Music
{
public:
	Music();
	~Music();

	void mu_Add();
	void mu_Start();
	void mu_Switch();
	void mu_Hit_Wall();
	void mu_Hit_Tank();
	void mu_Lose();
	void mu_Dead_Enemy();
	void mu_Dead_Player();
	void mu_Prop_Appear();
	void mu_Prop_get();

	void init();
};