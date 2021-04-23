//
// Created by kimiko on 30.12.19.
//

#include "print.h"

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
    printf("Number of ships: %i\n", player->my_plan.num_of_ships);
    for (int i = 0; i < player->my_plan.num_of_ships; i++) {
        printf("Ship no.%i:\n", i + 1);
        print_ship(&player->my_plan.ships[i]);
    }
    printf("Plan:\n");
    print_board(player->my_plan.board);
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


