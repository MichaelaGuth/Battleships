//
// Created by kimiko on 25.11.19.
//

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "printGUI.h"
#include "player.h"
#include "ship.h"

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H

int add_ship_to_board(Plan *my_plan, Ship ship);
Boolean check_ship_collision(Plan plan, Ship ship);
Boolean check_boundaries(Ship ship);
int fire(Player *my_player, Player *opponent, Coordinate target);
void update_ship_status(Player opponent, Ship *ship);

int find_ship_index(char ship_symbol, Coordinate target, Plan plan);

Boolean test_game_over(Player player);
void update_info_board(Player *player, Ship ship);

void save_game(Player p1, Player p2);
void save_player(FILE *file, Player player);
void save_ship(FILE *file, Ship ship);

#endif //BATTLESHIP_GAME_H