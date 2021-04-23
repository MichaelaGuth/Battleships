//
// Created by kimiko on 03.12.19.
//

#include "coordinate.h"

#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

typedef struct ship_type {
    char symbol;
    int len;
    char *name;
} ShipType;

typedef struct ship {
    ShipType type;
    Coordinate start;
    Direction direction;
    Boolean ship_destroyed;
} Ship;

Ship create_ship(ShipType type, Coordinate start, Direction dir);
ShipType create_ship_type(char symbol, char *name, int len);
ShipType get_carrier();
ShipType get_battleship();
ShipType get_destroyer();
ShipType get_submarine();
ShipType get_cruiser();
ShipType get_ship_type(char symbol);

void update_ship_status(char info_board[SIZE][SIZE], Ship *ship);

#endif //BATTLESHIP_SHIP_H
