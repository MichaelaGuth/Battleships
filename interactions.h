//
// Created by kimiko on 28.11.19.
//

#include <stdio.h>
#include "constants.h"
#include "game.h"
#include "printGUI.h"

#ifndef BATTLESHIP_INTERACTIONS_H
#define BATTLESHIP_INTERACTIONS_H


int place_ship(Plan *plan, ShipType type);

void end_game(Player winner);
void start_game();
void start_planning(Player *player);
int play(Player *player, Player *opponent);
int play_AI(Player *me, Player *opponent);
Player check_game_over(Player p1, Player p2);
Boolean turn(Player *player, Player *AI);

void print_enter_coord(ShipType type);
void print_dir_choice();

Coordinate read_coordinates();
Boolean check_coord_boundaries(Coordinate coord);

#endif //BATTLESHIP_INTERACTIONS_H
