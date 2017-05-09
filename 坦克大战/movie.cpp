#include"functions.h"
#include"Picture.h"

void movieTitle()
{
	Picture p;
	int x, y;
	x = (Win_W - 438) / 2;
	y = (Win_H - 162) / 2;
	ege::cleardevice();
	putimage_withalpha(NULL, p.title, x, y);
	delay_ms(1500);
	ege::cleardevice();
}

void movieEnd()
{
	Picture p;
	int x, y;
	x = (Win_W - 438) / 2;
	y = (Win_H - 162) / 2;
	ege::cleardevice();
	putimage_withalpha(NULL, p.end, x, y);
	delay_ms(1000);
	ege::cleardevice();
}

void movieShine(int time)
{
	static Picture p;
	static int x;
	static int y;
	
	if (time == 0)
	{
		x = myrand_int(150,Win_W-200);
		y = myrand_int(50,200);
	}

	if (time > 0 && time < 5)
		putimage_withalpha(NULL,p.born_1, x, y);
	else if (time > 5 && time < 10)
		putimage_withalpha(NULL, p.born_2, x, y);
	else if (time > 10 && time < 15)
		putimage_withalpha(NULL, p.born_3, x, y);
	else if (time > 15 && time < 20)
		putimage_withalpha(NULL, p.born_4, x, y);
	else if (time > 20 && time < 25)
		putimage_withalpha(NULL, p.born_3, x, y);
	else if (time > 25 && time < 30)
		putimage_withalpha(NULL, p.born_2, x, y);
	else if (time > 30 && time < 35)
		putimage_withalpha(NULL, p.born_1, x, y);

}

void movieBorn(int time, int x, int y, Picture& picture)
{
	time = 60 - time;
	if (time > 0 && time < 10)
		putimage_withalpha(NULL, picture.born_1, x, y);
	else if (time > 10 && time < 20)
		putimage_withalpha(NULL, picture.born_2, x, y);
	else if (time > 20 && time < 30)
		putimage_withalpha(NULL, picture.born_3, x, y);
	else if (time > 30 && time < 40)
		putimage_withalpha(NULL, picture.born_4, x, y);
	else if (time > 40 && time < 50)
		putimage_withalpha(NULL, picture.born_3, x, y);
	else if (time > 50 && time < 60)
		putimage_withalpha(NULL, picture.born_2, x, y);
}

void movieBomb(int time)
{
	static Picture p;
	static int x;
	static int y;
	time -= 10;
	if (time == 0)
	{
		x = myrand_int(150, Win_W - 200);
		y = myrand_int(50, 200);
	}

	if (time > 0 && time < 3)
		putimage_withalpha(NULL, p.explode_1, x, y);
	else if (time > 3 && time < 6)
		putimage_withalpha(NULL, p.explode_3, x, y);
	else if (time > 6 && time < 12)
		putimage_withalpha(NULL, p.explode_5, x, y);
	else if (time > 12 && time < 15)
		putimage_withalpha(NULL, p.explode_7, x, y);
	else if (time > 15 && time < 18)
		putimage_withalpha(NULL, p.explode_8, x, y);
	else if (time > 18 && time < 24)
		putimage_withalpha(NULL, p.explode_7, x, y);
	else if (time > 24 && time < 30)
		putimage_withalpha(NULL, p.explode_6, x, y);
	else if (time > 30 && time < 39)
		putimage_withalpha(NULL, p.explode_5, x, y);
	else if (time > 39 && time < 42)
		putimage_withalpha(NULL, p.explode_4, x, y);
	else if (time > 42 && time < 45)
		putimage_withalpha(NULL, p.explode_3, x, y);
	else if (time > 45 && time < 48)
		putimage_withalpha(NULL, p.explode_2, x, y);
}

void movieBomb(int time, int x, int y, Picture& picture)
{
	time = 60 - time;
	if (time > 0 && time < 3)
		putimage_withalpha(NULL, picture.explode_1, x, y);
	else if (time > 3 && time < 6)
		putimage_withalpha(NULL, picture.explode_3, x, y);
	else if (time > 6 && time < 12)
		putimage_withalpha(NULL, picture.explode_5, x, y);
	else if (time > 12 && time < 15)
		putimage_withalpha(NULL, picture.explode_7, x, y);
	else if (time > 15 && time < 18)
		putimage_withalpha(NULL, picture.explode_8, x, y);
	else if (time > 18 && time < 24)
		putimage_withalpha(NULL, picture.explode_7, x, y);
	else if (time > 24 && time < 30)
		putimage_withalpha(NULL, picture.explode_6, x, y);
	else if (time > 30 && time < 39)
		putimage_withalpha(NULL, picture.explode_5, x, y);
	else if (time > 39 && time < 42)
		putimage_withalpha(NULL, picture.explode_4, x, y);
	else if (time > 42 && time < 45)
		putimage_withalpha(NULL, picture.explode_3, x, y);
	else if (time > 45 && time < 48)
		putimage_withalpha(NULL, picture.explode_2, x, y);
}

void movie_Loding()
{
	setbkmode(TRANSPARENT);
	setcolor(WHITE);
	cleardevice();
	setfont(60, 0, "¿¬Ìå");
	outtextxy((Win_W - 240) / 2, (Win_H-60)/2, "¼ÓÔØÖÐ...");
	delay_ms(1000);
}