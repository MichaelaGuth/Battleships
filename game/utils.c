//
// Created by kimiko on 30.12.19.
//

#include "utils.h"

void print_Boolean(Boolean bool) {
    printf("%s\n", bool == TRUE ? "TRUE" : "FALSE");
}

void print_coord(Coordinate coord) {
    printf("%i %i\n", coord.row, coord.col);
}

void print_err_coord(Coord_error coord) {
    printf("%c ", coord.error == NO_HITS ? 'Y' : 'N');
    print_coord(coord.coord);
}

void print_Game(Game *game) {
    print_player(game->player);
    print_AI(game->AI);
}

void print_AI(Computer *player_AI) {
    printf("AI memory:\n");
    printf("Coordinate: ");
    print_err_coord(player_AI->previous_target);
    print_player(player_AI->player);
}

void print_player(Player *player) {
    printf("Player:\n");
    printf("Username: %s\n", player->username);
    printf("Number of ships: %i\n", player->my_plan->num_of_ships);
    for (int i = 0; i < player->my_plan->num_of_ships; i++) {
        printf("Ship no.%i:\n", i + 1);
        print_ship(&player->my_plan->ships[i]);
    }
    printf("Plan:\n");
    print_board(player->my_plan->board);
    printf("Info board:\n");
    print_board(player->info_on_enemy_board);
}

void print_ship(Ship *ship) {
    printf("Ship name: %s\n", ship->type.name);
    printf("Ship length: %i\nShip symbol: %c\n", ship->type.len, ship->type.symbol);
    printf("Ship direction: %s\n", ship->direction == HORIZONTAL ? "HORIZONTAL" : "VERTICAL");
    printf("Ship is destroyed: ");
    print_Boolean(ship->ship_destroyed);
    printf("Ship start coordinate: (%i, %i)\n",ship->start.row, ship->start.col);
}


Boolean compare_game(Game *g1, Game *g2) {
    Boolean res = TRUE;

    if (compare_AI(g1->AI, g2->AI) == FALSE) {
        res = FALSE;
    }

    if (compare_player(g1->player, g2->player) == FALSE) {
        res = FALSE;
    }

    return res;
}

Boolean compare_AI(Computer *AI_1, Computer *AI_2) {
    Boolean res = TRUE;

    if (AI_1->previous_target.error != AI_2->previous_target.error) {
        res = FALSE;
    } else if (compare_coordinates(AI_1->previous_target.coord, AI_2->previous_target.coord) == FALSE) {
        res = FALSE;
    } else if (compare_player(AI_1->player, AI_2->player) == FALSE) {
        res = FALSE;
    }

    return res;
}

Boolean compare_player(Player *p1, Player *p2) {
    Boolean res = TRUE;

    if (strcmp(p1->username, p2->username) != 0) {
        res = FALSE;
    }

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (p1->info_on_enemy_board[row][col] != p2->info_on_enemy_board[row][col]) {
                res = FALSE;
            }
        }
    }

    if (compare_plan(p1->my_plan, p2->my_plan) == FALSE) {
        res = FALSE;
    }

    return res;
}

Boolean compare_plan(Plan *p1, Plan *p2) {
    Boolean res = TRUE;

    if (p1->num_of_ships != p2->num_of_ships) {
        res = FALSE;
    } else {
        for (int i = 0; i < p1->num_of_ships; i++) {
            if (compare_ships(&p1->ships[i], &p2->ships[i]) == FALSE) {
                res = FALSE;
            }
        }
    }

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (p1->board[row][col] != p2->board[row][col]) {
                res = FALSE;
            }
        }
    }

    return res;
}

Boolean compare_ships(Ship *ship_1, Ship *ship_2) {
    Boolean res = TRUE;

    if (compare_ship_types(ship_1->type, ship_2->type) == FALSE) {
        res = FALSE;
    } else if (ship_1->ship_destroyed != ship_2->ship_destroyed) {
        res = FALSE;
    } else if (compare_coordinates(ship_1->start, ship_2->start) == FALSE) {
        res = FALSE;
    } else if (ship_1->direction != ship_2->direction) {
        res = FALSE;
    }

    return res;
}

Boolean compare_ship_types(ShipType type_1, ShipType type_2) {
    Boolean res = TRUE;

    if (type_1.symbol != type_2.symbol) {
        res = FALSE;
    } else if (type_1.len != type_2.len) {
        res = FALSE;
    } else if (strcmp(type_1.name, type_2.name) != 0) {
        res = FALSE;
    }

    return res;
}
