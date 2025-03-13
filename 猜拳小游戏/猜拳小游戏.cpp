#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <stdio.h>
#include <string.h>
static int HP = 10;
static int gamenum = 0;
int airandnum()
{
	int a = rand() % 3 + 1;
	return a;
}
char* gametext(int a)
{
	static char b[10];
	switch (a)
	{
	case 1:strcpy(b, "石头");
		break;
	case 2:strcpy(b, "剪刀");
		break;
	case 3:strcpy(b, "布");
		break;
	default:
		break;
	}
	return b;
}
int gameover(int ai, int play)
{
	if (ai - play == 1 || ai - play == -2) {
		printf("真是侥幸让你赢了");
		HP++;
	}
	else
	{
		if (ai - play == 0) {
			printf("平局");
		}
		else
		{
			printf("不是牢弟，人机都打不过????");
			HP--;
		}
	}
	printf("\n");
	return 0;
}
int guize() {
	if (gamenum == 1) {
		printf("我们来玩猜拳游戏吧\n游戏规则 1;代表石头 2；代表剪刀 3；代表布\n你先出(输入99可以结束游戏)\n");
	}
	else
	{
		printf("来继续！！！(准备进行第%d回合)\n\n", gamenum);
	}
	printf("                                    (归零则结束)当前积分=%d\n", HP);
	return 0;
}
int game() {
	gamenum++;
	guize();
	int sr, playnum;
	do {
		sr = 0;
		if (scanf("%d", &playnum) != 1) {
			while (getchar() != '\n'); // 清理输入缓冲区
			sr = 1;
			printf("输入无效，请输入一个整数！\n");
		}
		else if (playnum == 99) {
			return 1;
		}
		else if (playnum < 1 || playnum > 3 || playnum % 1 != 0) {
			sr = 1;
			printf("别乱输############!!!!!!!!!\n");
		}
	} while (sr == 1);
	int ainum = airandnum();
	char aitext[10];
	strcpy(aitext, gametext(ainum));
	char* playtext = gametext(playnum);
	printf("你出的是 %s ai出的是%s\n", playtext, aitext);
	gameover(ainum, playnum);
	return 0;
}
int main()
{
	srand(time(0));
	do {
		int fh = game();
		if (fh == 1) {
			printf("再见!");
			Sleep(1000);
			break;
		}
	} while (HP > 0);
	return 0;
}