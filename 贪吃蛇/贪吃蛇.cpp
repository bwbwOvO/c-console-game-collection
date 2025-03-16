#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#define HIGH 20 //地图高度
#define WIDE 60 //地图宽度

struct BODY//蛇的身体位置
{
	int X, Y;//蛇身体的坐标
};

struct SNAKE//蛇
{
	struct BODY body[HIGH * WIDE];//蛇
	int size = 0;//蛇的长度
}snake;

struct FOOD//食物
{
	int X, Y;//食物的坐标
}food;

int score = 0;//分数
int kx = 0, ky = 0, speed = 180;
int dx = 0, dy = 0, gmspeed;
int speedminus = 2;

void initsnake(void)//蛇出生
{
	snake.size = 2;
	snake.body[0].Y = HIGH / 2;
	snake.body[0].X = WIDE / 2;

	snake.body[1].Y = HIGH / 2 - 0;
	snake.body[1].X = WIDE / 2 - 1;

};

void initfood(void)//
{
	food.Y = rand() % HIGH;
	food.X = rand() % WIDE;
	for (size_t i = 0; i < snake.size; i++)
	{
		if (food.X == snake.body[i].X && food.Y == snake.body[i].Y) //判断是否撞身体
		{
			initfood();
		}
	}
	return;
};

void initmap(void)//绘制地图
{
	COORD coord = { 0 };
	int i;
	for (i = 0; i < snake.size; i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	coord.X = dx;
	coord.Y = dy;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar(' ');
	coord.X = food.X;
	coord.Y = food.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	putchar('#');
	coord.X = WIDE + 1;
	coord.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf(" 当前成绩为 %d 分      ", score);
	coord.Y += 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("  当前速度 %d         ",200 - speed);
	coord.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf(" 每吃一次加 %d 输入'0'暂停游戏   ", speedminus);
	coord.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("(超199或达150阈值不再自动增加)");
	coord.X = 0;
	coord.Y = HIGH+1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void initwall(void) {
	for (size_t i = 0; i <= HIGH; i++)
	{
		for (size_t j = 0; j <= WIDE; j++)
		{
			if (j == WIDE) {
				printf("|");
			}
			else if (i == HIGH)
			{
				printf("—");
			}
			else
			{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void playgame(void)
{
	char sr = 'd';
	while (snake.body[0].X >= 0 && snake.body[0].X < WIDE && snake.body[0].Y >= 0 && snake.body[0].Y < HIGH)//判断是否撞墙
	{
		initmap();
		Sleep(speed);
		if (_kbhit()) {
			char oldsr = sr;
			sr = _getch();
			if (sr == '0') { 
				printf("请输入(1—199)自定义速度,(200-299)改速度变化值           ");
				initmap();
				printf("请输入(1—199)自定义速度,(200-299)改速度变化值");
				scanf("%d", &gmspeed);
				initmap();
				if (gmspeed > 0 && gmspeed <= 199) {
					printf("gm修改成功！! 速度已从%d修改为%d！                       ",200-speed,gmspeed);
					speed = 200 - gmspeed;
				}
				else if (gmspeed >= 200 && gmspeed <= 299)
				{
					printf("gm修改成功！! 变化值已从%d修改为%d！                       ", speedminus, gmspeed - 200);
					speedminus=gmspeed - 200;
				}else { printf("ERROR!输入无效!修改失败！                        "); }
				sr = oldsr; }
			if ((sr == 'w' && oldsr == 's') || (sr == 's' && oldsr == 'w')) { sr = oldsr; }
			if ((sr == 'a' && oldsr == 'd') || (sr == 'd' && oldsr == 'a')) { sr = oldsr; }
		}
		switch (sr)
		{
		case 'w':kx = 0; ky = -1; break;
		case 's':kx = 0; ky = +1; break;
		case 'a':kx = -1; ky = 0; break;
		case 'd':kx = +1; ky = 0; break;
		default:break;
		}
		for (size_t i = 1; i < snake.size; i++)
		{
			if (snake.body[0].X == snake.body[i].X && snake.body[0].Y == snake.body[i].Y) //判断是否撞身体
			{
				return;
			}
		}
		if (snake.body[0].X == food.X && snake.body[0].Y == food.Y)//判断是否吃到食物
		{
			initfood();
			snake.size++;
			score += 100;
			if (speed >= 50&&speed-speedminus>0) { speed -= speedminus; }
		}

		dx = snake.body[snake.size - 1].X;
		dy = snake.body[snake.size - 1].Y;

		for (size_t i = snake.size - 1; i > 0; i--)
		{
			snake.body[i].X = snake.body[i - 1].X;
			snake.body[i].Y = snake.body[i - 1].Y;
		}
		snake.body[0].X = snake.body[0].X + kx;
		snake.body[0].Y = snake.body[0].Y + ky;
	}
}

void againgame() {
	system("cls");
	score = 0;//清空分数
	srand(time(0));
	initfood();
	initsnake();
	initwall();
	initmap();
	playgame();
	printf("\n你还要继续玩?继续请输入99(输入其他任意按键退出)\n");
	int again;
	scanf("%d", &again);
	if (again == 99) {
		speed = 180; 
		againgame();
	}
	else
	{
		printf("再见!");
		Sleep(1000);
		return;
	}
}

int main(void)
{
	againgame();
	system("pause");
};

