//
// Created by kimiko on 03.12.19.
//

#include "ship.h"
#include "player.h"

Coordinate create_coordinate(int x, int y) {
    Coordinate result;
    result.x = x;
    result.y = y;
    return result;
}

Boolean compare_coordinates(Coordinate coord1, Coordinate coord2) {
    Boolean res = FALSE;
    if (coord1.x == coord2.x && coord1.y == coord2.y) {
        res = TRUE;
    }
    return res;
}

Ship create_ship(ShipType type, Coordinate start, Direction dir) {
    Ship ship;
    ship.type = type;
    ship.start = start;
    ship.direction = dir;
    ship.ship_destroyed = FALSE;
    return ship;
}

ShipType create_ship_type(char symbol, char *name, int len) {
    ShipType type;
    type.len = len;
    type.symbol = symbol;
    type.name = name;
    return type;
}

ShipType get_carrier() {
    ShipType type = create_ship_type(CARR, CARR_NAME, CARR_L);
    return type;
}

ShipType get_battleship() {
    ShipType type = create_ship_type(BATT, BATT_NAME, BATT_L);
    return type;
}

ShipType get_destroyer() {
    ShipType type = create_ship_type(DEST, DEST_NAME, DEST_L);
    return type;
}

ShipType get_submarine() {
    ShipType type = create_ship_type(SUBM, SUBM_NAME, SUBM_L);
    return type;
}

ShipType get_patrol_boat() {
    ShipType type = create_ship_type(PATR, PATR_NAME, PATR_L);
    return type;
}


