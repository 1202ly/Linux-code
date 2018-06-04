#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"game.h"
void game()
{
	char board[ROWS][COLS];
	char ret = 0;
	init_board(board, ROWS, COLS);
	display_board(board, ROWS, COLS);
	srand((unsigned int)time(NULL));
	while (1)
	{
		player_move(board, ROWS, COLS);
		ret = check_win(board, ROWS, COLS);
		if (ret != ' ')
			break;
		display_board(board, ROWS, COLS);
		computer_move(board, ROWS, COLS);
		ret = check_win(board, ROWS, COLS);
		if (ret != ' ')
			break;
		display_board(board, ROWS, COLS);
	}
	if (ret == 'X')
		printf("玩家赢\n");
	else if (ret == '0')
		printf("电脑赢\n");
	else if (ret == 'q')
		printf("平局\n");
	display_board(board, ROWS, COLS);
}
void menu()
{
	printf("1.play\n");
	printf("0.exit\n");
}
int main()
{
	int input = 0;
	do
	{
		menu();
		printf("请选择\n");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:

			break;
		default:
			printf("选择错误\n");
			break;
		}
	} while (input);
	return 0;
}