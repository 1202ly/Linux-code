#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"
void init_board(char board[ROWS][COLS], int row, int col)
{
	memset(board, ' ', row*col*sizeof(char));
}
void display_board(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	for (i = 0; i<row; i++)
	{
		printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
		if (i != 2)
			printf("---|---|---\n");
	}
}
void player_move(char board[ROWS][COLS], int row, int col)
{
	while (1)
	{
		int x, y;
		printf("请输入坐标\n");
		scanf_s("%d%d", &x, &y);
		x -= 1;
		y -= 1;
		if (((x >= 0) && (x <= 2)) && ((y >= 0) && (y <= 2)))
		{
			if (board[x][y] == ' ')
			{
				board[x][y] = 'X';
				break;
			}
			else
				printf("下标错误，请重新输入\n");
		}
		else
			printf("下标错误，请重新输入\n");
	}
}
void computer_move(char board[ROWS][COLS], int row, int col)
{
	while (1)
	{
		int x = rand() % 3;
		int y = rand() % 3;
		if (board[x][y] == ' ')
		{
			board[x][y] = '0';
			break;
		}
	}
}
static int is_full(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i<row; i++)
	{
		for (j = 0; j<col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}
char check_win(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	for (i = 0; i<row; i++)
	{
		if ((board[i][0] == board[i][1])
			&& (board[i][1] == board[i][2])
			&& (board[i][1] != ' '))
			return board[i][1];
	}
	for (i = 0; i<col; i++)
	{
		if ((board[0][i] == board[1][i])
			&& (board[1][i] == board[2][i])
			&& (board[1][i] != ' '))
			return board[1][i];
	}
	if ((board[0][0] == board[1][1])
		&& (board[1][1] == board[2][2])
		&& (board[1][1] != ' '))
		return board[1][1];
	if ((board[0][2] == board[1][1])
		&& (board[1][1] == board[2][0])
		&& (board[1][1] != ' '))
		return board[1][1];
	if (is_full(board, row, col))
		return 'q';
	return ' ';
}
