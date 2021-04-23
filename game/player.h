//
// Created by kimiko on 03.12.19.
//

#include "ship.h"
#include "boards.h"

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
    Plan *my_plan;
} Player;

typedef struct {
    Player *player;
    Coord_error previous_target;
} Computer;

void alloc_AI(Computer *AI);
void alloc_player(Player *player);
void alloc_plan(Plan *plan);

void init_player(Player *player, char *username);
void init_AI(Computer *AI, int lvl);
void init_AI_plan(Plan *plan, const char board[SIZE][SIZE]);

void change_board(char board[SIZE][SIZE], char const new_board[SIZE][SIZE]);
void fill_board(char board[SIZE][SIZE], char symbol);
void init_info_board(char info_on_enemy_board[SIZE][SIZE]);
void init_player_board(char player_board[SIZE][SIZE]);

int find_ship_index_in_plan(char ship_symbol, Coordinate target, Plan *plan);
Boolean check_if_ship_is_in_plan(char symbol, Coordinate target, Plan *plan);

void update_AI_info_board(char info_board[SIZE][SIZE]);
void update_info_board(Player *player, Ship ship);

void destroy_player(Player *player, Boolean is_AI);
void destroy_AI(Computer *player_AI);

#endif //BATTLESHIP_PLAYER_H
