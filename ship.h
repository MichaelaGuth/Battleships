//
// Created by kimiko on 03.12.19.
//

#include "constants.h"
#include "stdlib.h"

#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

typedef struct coordinate {
    int x;
    int y;
    int error;
} Coordinate;

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

Coordinate create_coordinate(int x, int y);
Boolean compare_coordinates(Coordinate coord1, Coordinate coord2);

Ship create_ship(ShipType type, Coordinate start, Direction dir);
ShipType create_ship_type(char symbol, char *name, int len);
ShipType get_carrier();
ShipType get_battleship();
ShipType get_destroyer();
ShipType get_submarine();
ShipType get_patrol_boat();

#endif //BATTLESHIP_SHIP_H
