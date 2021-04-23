//
// Created by kimiko on 04.12.19.
//

#ifndef BATTLESHIP_ERROR_H
#define BATTLESHIP_ERROR_H

enum error_codes {
    UNKNOWN = -1, OK = 0, SHIP_OUT_OF_BOUNDARY = 101, SHIP_COLLISION = 102, INVALID_INPUT = 103, END_GAME = 104, UNKNOWN_DIRECTION = 105, NO_HITS = 106
};

#define UNKNOWN_TXT "Unknown Error!\n"
#define SHIP_OUT_OF_BOUNDARY_TXT "Cannot place out of board!\n"
#define SHIP_COLLISION_TXT "Cannot place ship next to or over another ship!\n"
#define INVALID_INPUT_TXT "Invalid input!\n"

#endif //BATTLESHIP_ERROR_H
