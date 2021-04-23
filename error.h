//
// Created by kimiko on 04.12.19.
//

#ifndef BATTLESHIP_ERROR_H
#define BATTLESHIP_ERROR_H

enum error_codes {
    OK = 0, SHIP_OUT_OF_BOUNDARY = 101, SHIP_COLLISION = 102, WRONG_INPUT = 103, INVALID_TARGET = 104
};

#define UNKNOWN "Unknown Error!\n"
#define SHIP_OUT_OF_BOUNDARY_TXT "Cannot place out of board!\n"
#define SHIP_COLLISION_TXT "Cannot place ship next to or over another ship!\n"

#endif //BATTLESHIP_ERROR_H
