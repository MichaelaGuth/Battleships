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
#define CRUI_NAME "Cruiser"

#define SAVE_FILE "save.txt"

typedef enum {
    FALSE, TRUE
} Boolean;

enum ship_max {
    C_MAX = 1, B_MAX = 1, D_MAX = 2, S_MAX = 2, CR_MAX = 2
};

typedef enum {
    HORIZONTAL, VERTICAL, NO
} Direction;

enum print_symbols {
    EMPTY = 'e', NOT_TESTED = '?', HIT = 'X', SHIP = '/', SHIP_DESTROYED = '#'
};

enum ship_symbol {
    CARR = 'c', BATT = 'b', DEST = 'd', SUBM = 's', CRUI = 'r'
};

enum ship_len {
    CARR_L = 5, BATT_L = 4, DEST_L = 1, SUBM_L = 2, CRUI_L = 3
};



#endif //BATTLESHIP_CONSTANTS_H
