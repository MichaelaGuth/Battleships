//
// Created by kimiko on 28.11.19.
//

#include "game.h"

#ifndef BATTLESHIP_INTERACTIONS_H
#define BATTLESHIP_INTERACTIONS_H

void menu();
void start_new_game();
void start_game(Game *game);

void start_planning(Player *player);
int play(Game *game);
Boolean start_round(Game *game);
int place_ship(Plan *plan, ShipType type);

Boolean read_coordinates(Coordinate *coord);
Boolean read_string(char *buffer, int buffer_size);
Boolean read_number(int *number);
Boolean read_choice(int *num, int max);

#endif //BATTLESHIP_INTERACTIONS_H
