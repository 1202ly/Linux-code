#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

void menu()
{
	printf("**************************************\n");
	printf("*************** 1.play ***************\n");
	printf("*************** 0.exit ***************\n");
	printf("**************************************\n");
}

void game()
{
	char mine[ROWS][COLS] = { 0 };//�׵���Ϣ
	char show[ROWS][COLS] = { 0 };//�ų��׵���Ϣ
	int x = 0;
	int y = 0;
	int count = 0;
	init_board(mine, '0', ROWS, COLS);
	init_board(show, '*', ROWS, COLS);
	mine_set(mine);
	display_board(mine, ROW, COL);
	int blank = ROW*COL - COUNT;
	while (blank)
	{
		printf("�����������\n ");
		scanf("%d%d", &x, &y);
		if (((x >= 1) && (x <= 9)) && ((y >= 1) && (y <= 9)))
		{
			if (mine[x][y] == '1')
			{
				display_board(mine, ROW, COL);
				printf("��Ϸ����\n");
				break;
			}
			else
			{
				count = count_mine(mine, x, y);//�׵ĸ���
				show[x][y] = count + '0';
				blank--;
				display_board(show, ROW, COL);
			}
		}
		else
		{
			printf("����Ƿ�\n");
		}
	}
	if (blank == 0)//�ж����Ƿ�������
	{
		printf("���׳ɹ�\n");
	}
}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��\n ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("ѡ�����\n");
			break;
		}

	} while (input);
}

int main()
{
	test();
	return 0;
}