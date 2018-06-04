#define _CRT_SECURE_NO_WARNINGS 1
#ifndef __GAME_H__
#define __GAME_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWS 3
#define COLS 3
void init_board(char board[ROWS][COLS], int row, int col);
void display_board(char board[ROWS][COLS], int row, int col);
void player_move(char board[ROWS][COLS], int row, int col);
void computer_move(char board[ROWS][COLS], int row, int col);
char check_win(char board[ROWS][COLS], int row, int col);
#endif
