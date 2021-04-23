//
// Created by kimiko on 03.12.19.
//
#include "constants.h"
#include "ship.h"

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H

typedef struct plan {
    char board[SIZE][SIZE];
    Ship *ships;
    int num_of_ships;
} Plan;

typedef struct player {
    char *username;
    char info_on_enemy_board[SIZE][SIZE];
    Plan my_plan;
} Player;

Player create_Player(char *username);
void change_board(char board[SIZE][SIZE], char new_board[SIZE][SIZE]);
void create_board(char board[SIZE][SIZE], char symbol);
void init_info_board(char info_on_enemy_board[SIZE][SIZE]);
void init_player_board(char player_board[SIZE][SIZE]);
Plan init_plan();

void destroy_player(Player *player);

#endif //BATTLESHIP_PLAYER_H
