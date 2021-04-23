//
// Created by kimiko on 03.01.20.
//

#ifndef BATTLESHIP_COORDINATE_H
#define BATTLESHIP_COORDINATE_H

#include "constants.h"
#include <time.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
} Coordinate;

typedef struct coordinate {
    Coordinate coord;
    int error;
} Coord_error;

typedef struct {
    Coordinate coord;
    char symbol;
} Target;

Coordinate create_coordinate(int row, int col);
Coordinate create_random_coordinate();
Boolean compare_coordinates(Coordinate coord1, Coordinate coord2);

Coord_error create_coord_with_error(Coordinate coord, int error);

Target create_target(int row, int col, char symbol);

#endif //BATTLESHIP_COORDINATE_H
