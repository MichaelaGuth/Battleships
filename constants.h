//
// Created by kimiko on 25.11.19.
//

#include "error.h"

#ifndef BATTLESHIP_CONSTANTS_H
#define BATTLESHIP_CONSTANTS_H

#define SIZE 10

#define CARR_NAME "Carrier"
#define BATT_NAME "Battleship"
#define DEST_NAME "Destroyer"
#define SUBM_NAME "Submarine"
#define PATR_NAME "Patrol boat"

#define SAVE_FILE "save.txt"

typedef enum {
    FALSE, TRUE
} Boolean;

enum ship_max {
    C_MAX = 1, B_MAX = 1, D_MAX = 2, S_MAX = 2, P_MAX = 2
};

typedef enum {
    HORIZONTAL, VERTICAL
} Direction;

enum print_symbols {
    EMPTY = ' ', NOT_TESTED = '?', HIT = 'X', SHIP = '/', SHIP_DESTROYED = '#'
};

enum ship_symbol {
    CARR = 'c', BATT = 'b', DEST = 'd', SUBM = 's', PATR = 'p'
};

enum ship_len {
    CARR_L = 5, BATT_L = 4, DEST_L = 3, SUBM_L = 2, PATR_L = 1
};




#endif //BATTLESHIP_CONSTANTS_H
