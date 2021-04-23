//
// Created by kimiko on 30.12.19.
//

#ifndef BATTLESHIP_PRINT_H
#define BATTLESHIP_PRINT_H

#include "game.h"

void print_Boolean(Boolean bool);
void print_coord(Coordinate coord);
void print_err_coord(Coord_error coord);

void print_Game(Game *game);
void print_AI(Computer *player_AI);
void print_player(Player *player);
void print_ship(Ship *ship);



#endif //BATTLESHIP_PRINT_H
