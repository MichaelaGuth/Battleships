//
// Created by kimiko on 25.11.19.
//

#include <stdio.h>
#include "print_GUI.h"

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

typedef struct {
    Computer *AI;
    Player *player;
} Game;

void alloc_game(Game *game);
void destroy_game(Game *game);

Coordinate find_target_AI(Computer *AI);
void play_AI(Game *game);
char find_result_of_fire(Coordinate target, Computer *AI);
int init_potential_targets(Target *potential_targets, Computer *AI);

int add_ship_to_board(Plan *my_plan, Ship ship);
Boolean check_ship_collision(Plan *plan, Ship *ship);
Boolean check_boundaries(Ship *ship);
void fire(Player *my_player, Player *opponent, Coordinate target);

Boolean test_game_over(Player *player);

void save_game(Game *game);
void save_AI(FILE *file, Computer *AI);
void save_player(FILE *file, Player *player);
void save_plan(FILE *file, Plan *plan);
void save_ship(FILE *file, Ship *ship);

void load_game(char *file_name, Game *game);
void load_AI(FILE *file, Computer *AI);
void load_player(FILE *file, Player *player, Boolean is_AI);
void load_plan(FILE *file, Plan *plan);
void load_ship(FILE *file, Ship *ship);

#endif //BATTLESHIP_GAME_H