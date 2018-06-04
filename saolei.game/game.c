#define _CRT_SECURE_NO_WARNINGS 1
#include "game.h"

void init_board(char board[ROWS][COLS], char ch, int row, int col)
{
	memset(board, ch, sizeof(board[0][0])*row*col);
}

void display_board(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("  ");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

void mine_set(char mine[ROWS][COLS])
{
	int count = COUNT;
	int x = 0;
	int y = 0;
	while (count > 0)
	{
		x = rand() % ROW + 1;
		y = rand() % COL + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

int count_mine(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y - 1] + mine[x][y - 1] +
		mine[x + 1][y - 1] + mine[x + 1][y] +
		mine[x + 1][y + 1] + mine[x][y + 1] +
		mine[x - 1][y + 1] + mine[x - 1][y] - 8 * '0';
}

