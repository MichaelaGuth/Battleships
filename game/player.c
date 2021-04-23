//
// Created by kimiko on 03.12.19.
//

#include "player.h"

void alloc_AI(Computer *AI) {
    AI->previous_target = create_coord_with_error(create_coordinate(-1, -1), NO_HITS);

    AI->player = malloc(sizeof(Player));
    AI->player->username = "AI";
    init_info_board(AI->player->info_on_enemy_board);
    AI->player->my_plan = malloc(sizeof(Plan));
    alloc_plan(AI->player->my_plan);
}

void alloc_player(Player *player) {
    player->username = NULL;
    player->my_plan = malloc(sizeof(Plan));
    alloc_plan(player->my_plan);
    init_info_board(player->info_on_enemy_board);
}

void alloc_plan(Plan *plan) {
    plan->ships = malloc(sizeof(Ship) * (D_MAX + C_MAX + CR_MAX + S_MAX + B_MAX));
    plan->num_of_ships = 0;
    init_player_board(plan->board);
}

void init_player(Player *player, char *username) {
    player->username = username;
}

void init_AI(Computer *AI, int lvl) {
    switch (lvl) {
        case 1:
            init_AI_plan(AI->player->my_plan, BOARD_1);
            break;
        case 2:
            init_AI_plan(AI->player->my_plan, BOARD_2);
            break;
        case 3:
            init_AI_plan(AI->player->my_plan, BOARD_3);
            break;
        case 4:
            init_AI_plan(AI->player->my_plan, BOARD_4);
            break;
        case 5:
            init_AI_plan(AI->player->my_plan, BOARD_5);
            break;
        default:
            exit(-1);
    }
}

/**
 * Initializes the struct Plan in AI.
 * @param plan The Plan we want to initialize.
 * @param board The board we want to attach to Plan.
 */
void init_AI_plan(Plan *plan, const char board[SIZE][SIZE]) {

    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {

            if (board[row][col] != EMPTY) {

                Coordinate tmp = create_coordinate(row, col);
                if (check_if_ship_is_in_plan(board[row][col], tmp, plan) == FALSE) {

                    if (col + 1 >= SIZE || board[row][col + 1] != board[row][col]) {
                        plan->ships[plan->num_of_ships] = create_ship(get_ship_type(board[row][col]), tmp, VERTICAL);
                    } else {
                        plan->ships[plan->num_of_ships] = create_ship(get_ship_type(board[row][col]), tmp, HORIZONTAL);
                    }

                    plan->num_of_ships++;
                }
            }
        }
    }

    change_board(plan->board, board);
}


/**
 * Changes the values of given board to the values of another given board. (AKA copies the second board to the first one)
 * @param board The board we want to change values in.
 * @param new_board The board with the values we want to copy.
 */
void change_board(char board[SIZE][SIZE], const char new_board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            board[row][col] = new_board[row][col];
        }
    }
}

/**
 * Fills the board SIZE x SIZE with given symbol.
 * @param board The board we want to fill.
 * @param symbol The given symbol.
 */
void fill_board(char board[SIZE][SIZE], char symbol) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            board[row][col] = symbol;
        }
    }
}

/**
 * Initializes the info_on_enemy_board for struct player. (Fills the board with NOT_TESTED symbol)
 * @param info_on_enemy_board The board that we want to initialize.
 */
void init_info_board(char info_on_enemy_board[SIZE][SIZE]) {
    fill_board(info_on_enemy_board, NOT_TESTED);
}

/**
 * Initializes the player_board for struct Plan. (Fills the board with EMPTY symbol)
 * @param player_board The board that we want to initialize.
 */
void init_player_board(char player_board[SIZE][SIZE]) {
    fill_board(player_board, EMPTY);
}


/**
 * Finds the index in the array of Ships of targeted Ship.
 * @param ship_symbol The symbol of targeted ship.
 * @param target The target coordinates.
 * @param plan The plan with the array of ships.
 * @return The index of the targeted ship if found
 *         else -1
 */
int find_ship_index_in_plan(char ship_symbol, Coordinate target, Plan *plan) {
    Coordinate tmp;
    int res = -1;
    for (int i = 0; i < plan->num_of_ships; ++i) {
        if (plan->ships[i].type.symbol == ship_symbol) {
            for (int j = 0; j < plan->ships[i].type.len; j++) {
                if (plan->ships[i].direction == HORIZONTAL) {
                    tmp = create_coordinate(plan->ships[i].start.row, plan->ships[i].start.col + j);
                    if (compare_coordinates(tmp, target) == TRUE) {
                        res = i;
                    }
                }
                else {
                    tmp = create_coordinate(plan->ships[i].start.row + j, plan->ships[i].start.col);
                    if (compare_coordinates(tmp, target) == TRUE) {
                        res = i;
                    }
                }
            }
        }
    }
    return res;
}

/**
 * Checks if the targeted ship is in plan.
 * @param symbol The symbol of targeted ship.
 * @param target The target coordinates.
 * @param plan The plan we wish to check.
 * @return TRUE if the ship is in plan,
 *         else FALSE
 */
Boolean check_if_ship_is_in_plan(char symbol, Coordinate target, Plan *plan) {
    Boolean res;
    int check = find_ship_index_in_plan(symbol, target, plan);

    if (check == -1) {
        res = FALSE;
    } else {
        res = TRUE;
    }

    return res;
}


/**
 * Updates the ship symbol to destroyed if the target ship is destroyed
 * @param player Pointer to the attacking player
 * @param ship The attacked ship
 */
void update_info_board(Player *player, Ship ship) {
    if (ship.ship_destroyed == TRUE) {
        for (int i = 0; i < ship.type.len; i++) {
            if (ship.direction == HORIZONTAL) {
                player->info_on_enemy_board[ship.start.row][ship.start.col + i] = SHIP_DESTROYED;
            } else {
                player->info_on_enemy_board[ship.start.row + i][ship.start.col] = SHIP_DESTROYED;
            }
        }
    }
}

/**
 * Updates AI info_on_enemy_board.
 * @param info_board The info_board.
 */
void update_AI_info_board(char info_board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (info_board[row][col] == SHIP_DESTROYED) {

                if (info_board[row - 1][col] == NOT_TESTED) {
                    info_board[row - 1][col] = EMPTY;
                }

                if (info_board[row + 1][col] == NOT_TESTED) {
                    info_board[row + 1][col] = EMPTY;
                }

                if (info_board[row][col - 1] == NOT_TESTED) {
                    info_board[row][col - 1] = EMPTY;
                }

                if (info_board[row][col + 1] == NOT_TESTED) {
                    info_board[row][col + 1] = EMPTY;
                }
            }
        }
    }
}


// memory free
void destroy_AI(Computer *AI) {
    destroy_player(AI->player, TRUE);
    free(AI->player);
    AI->player = NULL;

    free(AI);
}

// memory free
void destroy_player(Player *player, Boolean is_AI) {
    if (is_AI == FALSE) {
        free(player->username);
        player->username = NULL;
    }

    free(player->my_plan->ships);
    player->my_plan->ships = NULL;

    free(player->my_plan);
    player->my_plan = NULL;
}
