#define _CRT_SECURE_NO_WARNINGS 1
#ifndef _GAME_H_
#define _GAME_H_
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define COUNT 10 //²¼µÄÀ×Êý
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
void init_board(char board[ROWS][COLS], char set, int row, int col);
void display_board(char board[ROWS][COLS], int row, int col);
void mine_set(char mine[ROWS][COLS]);
int get_mine_count(char mine[ROWS][COLS], int x, int y);
#endif

