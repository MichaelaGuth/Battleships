//
// Created by kimiko on 30.12.19.
//

#ifndef BATTLESHIP_UTILS_H
#define BATTLESHIP_UTILS_H

#include "game.h"
#include <string.h>

void print_Boolean(Boolean bool);
void print_coord(Coordinate coord);
void print_err_coord(Coord_error coord);

void print_Game(Game *game);
void print_AI(Computer *player_AI);
void print_player(Player *player);
void print_ship(Ship *ship);


Boolean compare_game(Game *g1, Game *g2);
Boolean compare_AI(Computer *AI_1, Computer *AI_2);
Boolean compare_player(Player *p1, Player *p2);
Boolean compare_plan(Plan *p1, Plan *p2);
Boolean compare_ships(Ship *ship_1, Ship *ship_2);
Boolean compare_ship_types(ShipType type_1, ShipType type_2);


#endif //BATTLESHIP_UTILS_H
