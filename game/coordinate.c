//
// Created by kimiko on 03.01.20.
//

#include "coordinate.h"

Coordinate create_coordinate(int row, int col) {
    Coordinate result;
    result.row = row;
    result.col = col;
    return result;
}

Coordinate create_random_coordinate() {
    srand(time(0));
    return create_coordinate(rand() % SIZE, rand() % SIZE);
}

Boolean compare_coordinates(Coordinate coord1, Coordinate coord2) {
    Boolean res = FALSE;
    if (coord1.row == coord2.row && coord1.col == coord2.col) {
        res = TRUE;
    }
    return res;
}

Target create_target(int row, int col, char symbol) {
    Target target;
    target.coord.col = col;
    target.coord.row = row;
    target.symbol = symbol;
    return target;
}

Coord_error create_coord_with_error(Coordinate coord, int error) {
    Coord_error res;
    res.error = error;
    res.coord = coord;
    return res;
}