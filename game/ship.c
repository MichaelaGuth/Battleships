//
// Created by kimiko on 03.12.19.
//

#include <time.h>
#include "ship.h"
#include "player.h"



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

ShipType get_cruiser() {
    ShipType type = create_ship_type(CRUI, CRUI_NAME, CRUI_L);
    return type;
}

ShipType get_ship_type(char symbol) {
    ShipType result;

    switch (symbol) {
        case CARR:
            result = get_carrier();
            break;
        case BATT:
            result = get_battleship();
            break;
        case DEST:
            result = get_destroyer();
            break;
        case SUBM:
            result = get_submarine();
            break;
        case CRUI:
            result = get_cruiser();
            break;
        default:
            exit(-1);
    }

    return result;
}

/**
 * Updates the status of attacked ship.
 * @param info_board The board with info on enemy board.
 * @param ship Pointer to the attacked ship.
 */
void update_ship_status(char info_board[SIZE][SIZE], Ship *ship) {
    Boolean result = TRUE;
    for (int i = 0; i < ship->type.len; ++i) {
        if (ship->direction == HORIZONTAL) {
            if (info_board[ship->start.row][ship->start.col + i] != HIT && info_board[ship->start.row][ship->start.col + i] != SHIP_DESTROYED) {
                result = FALSE;
            }
        } else {
            if (info_board[ship->start.row + i][ship->start.col] != HIT && info_board[ship->start.row + i][ship->start.col] != SHIP_DESTROYED) {
                result = FALSE;
            }
        }
    }

    if (ship->ship_destroyed == TRUE) {

    }

    ship->ship_destroyed = result;
}
