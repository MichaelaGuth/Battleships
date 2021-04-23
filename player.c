//
// Created by kimiko on 03.12.19.
//

#include "player.h"

void create_board(char board[SIZE][SIZE], char symbol) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = symbol;
        }
    }
}

void init_info_board(char info_on_enemy_board[SIZE][SIZE]) {
    create_board(info_on_enemy_board, NOT_TESTED);
}

void init_player_board(char player_board[SIZE][SIZE]) {
    create_board(player_board, EMPTY);
}

void change_board(char board[SIZE][SIZE], char new_board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            board[row][col] = new_board[row][col];
        }
    }
}   // bude v C funkce??

Plan init_plan() {
    Plan plan;
    plan.num_of_ships = 0;
    plan.ships = malloc((C_MAX + B_MAX + D_MAX + S_MAX + P_MAX) * sizeof(Ship));
    init_player_board(plan.board);
    return plan;
}   // TODO: check with Honza

Player create_Player(char *username) {
    Player player;
    init_info_board(player.info_on_enemy_board);
    player.username = username;
    player.my_plan = init_plan();
    return player;
}

void destroy_player(Player *player) {
    free(player->username);
    free(player->my_plan.ships);
}