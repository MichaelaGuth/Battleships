//
// Created by kimiko on 25.11.19.
//

#include "game.h"
#include "utils.h"

/**
 * Initializes AI's turn.
 * @param AI Pointer to the struct Computer AI.
 * @param player Pointer to the struct Player of opponent.
 */
void play_AI(Game *game) {
    update_AI_info_board(game->AI->player->info_on_enemy_board);

    Coordinate target = find_target_AI(game->AI);

    printf("%s fires on coordinates %c %i in %s's board!\n", game->AI->player->username, target.row + 'A', target.col + 1, game->player->username);
    fire(game->AI->player, game->player, target);
    print_board(game->AI->player->info_on_enemy_board);
    printf("\n");

    switch (find_result_of_fire(target, game->AI)) {
        case HIT:
            game->AI->previous_target = create_coord_with_error(target, OK);
            break;
        case SHIP_DESTROYED:
            game->AI->previous_target = create_coord_with_error(create_coordinate(-1, -1), NO_HITS);
            break;
    }
}

/**
 * Finds the result of target hit.
 * @param target The target coordinates.
 * @param AI The attacking AI.
 * @return
 */
char find_result_of_fire(Coordinate target, Computer *AI) {
    return AI->player->info_on_enemy_board[target.row][target.col];
}

/**
 * Finds target coordinates for AI to fire.
 * @param AI The attacking Computer AI.
 * @return The target Coordinate.
 */
Coordinate find_target_AI(Computer *AI) {
    Coordinate target = {-1, -1};

    if (AI->previous_target.error == NO_HITS) {
        Boolean check = FALSE;
        while (check == FALSE) {
            target = create_random_coordinate();
            if (AI->player->info_on_enemy_board[target.row][target.col] == NOT_TESTED) {
                check = TRUE;
            }
        }

    } else {
        Target *potential_targets = malloc(sizeof(Target) * 4);
        int size = init_potential_targets(potential_targets, AI);

        Boolean check = FALSE;
        for (int i = 0; i < size; i++) {
            if (potential_targets[i].symbol == NOT_TESTED) {
                target = potential_targets[i].coord;
                check = TRUE;
                break;
            }
        }

        if (check == FALSE) {
            for (int i = 0; i < 4; i++) {
                if (potential_targets[i].symbol == HIT) {
                    AI->previous_target = create_coord_with_error(potential_targets[i].coord, OK);
                    free(potential_targets);
                    potential_targets = NULL;
                    target = find_target_AI(AI);
                    break;
                }
            }
        }

        if (potential_targets != NULL) {
            free(potential_targets);
        }
    }

    return target;
}

/**
 * Initializes the array of potential_targets for AI.
 * @param potential_targets The array of potential targets.
 * @param AI The attacking Computer AI.
 * @return The size of the potential_targets array. (number of elements)
 */
int init_potential_targets(Target *potential_targets, Computer *AI) {
    Coordinate tmp = AI->previous_target.coord;
    int size = 4;

    int i = 0;

    if (tmp.row == 0) {
        size--;
        realloc(potential_targets, size * sizeof(Target));
    } else {
        potential_targets[i] = create_target(tmp.row - 1, tmp.col, AI->player->info_on_enemy_board[tmp.row - 1][tmp.col]);
        i++;
    }

    if (tmp.row == SIZE - 1) {
        size--;
        realloc(potential_targets, size * sizeof(Target));
    } else {
        potential_targets[i] = create_target(tmp.row + 1, tmp.col, AI->player->info_on_enemy_board[tmp.row + 1][tmp.col]);
        i++;
    }

    if (tmp.col == 0) {
        size--;
        realloc(potential_targets, size * sizeof(Target));
    } else {
        potential_targets[i] = create_target(tmp.row, tmp.col - 1, AI->player->info_on_enemy_board[tmp.row][tmp.col - 1]);
        i++;
    }

    if (tmp.col == SIZE - 1) {
        size--;
        realloc(potential_targets, size * sizeof(Target));
    } else {
        potential_targets[i] = create_target(tmp.row, tmp.col + 1, AI->player->info_on_enemy_board[tmp.row][tmp.col + 1]);
    }

    return size;
}

/**
 * Tests if all ships from given player are destroyed.
 * @param player Pointer to the struct player of given player.
 * @return TRUE if all ships are destroyed
 *         else FALSE
 */
Boolean test_game_over(Player *player) {
    Boolean res = TRUE;
    if (player->my_plan->num_of_ships == 0) {
        res = FALSE;
    } else {
        for (int i = 0; i < player->my_plan->num_of_ships; ++i) {
            if (player->my_plan->ships[i].ship_destroyed == FALSE)
                res = FALSE;
        }
    }

    return res;
}

/**
 * Fires on the given target coordinates in opponent's plan and changes the status on target coordinates in info_on_enemy_board
 * @param my_player The attacking player
 * @param opponent The attacked player
 * @param target The Coordinates of fire target
 * @return error code
 */
void fire(Player *my_player, Player *opponent, Coordinate target) {
    char test = opponent->my_plan->board[target.row][target.col];

    switch (test) {
        case CARR:
        case BATT:
        case DEST:
        case SUBM:
        case CRUI:
            {
                // changes the value on target coordinates in info_on_enemy_board
                my_player->info_on_enemy_board[target.row][target.col] = HIT;

                //  updates the status of the attacked ship
                int ship_index = find_ship_index_in_plan(test, target, opponent->my_plan);
                update_ship_status(my_player->info_on_enemy_board, &opponent->my_plan->ships[ship_index]);
                update_info_board(my_player, opponent->my_plan->ships[ship_index]);

                break;
            }
        case EMPTY:
            {
                my_player->info_on_enemy_board[target.row][target.col] = EMPTY;
                break;
            }
        default:
            return;
    }
}

/**
 * Checks if the ship we wish to place to our PLan is not next to or over another ship
 * @param plan The plan of the player
 * @param ship The ship we wish to place
 * @return TRUE if the collision did not occur
 *         else FALSE
 */
Boolean check_ship_collision(Plan *plan, Ship *ship) {
    int row = ship->start.row;
    int col = ship->start.col;
    for (int i = 0; i < ship->type.len; i++) {               // for comments: point = board[x][y]

        if (ship->direction == HORIZONTAL) {

            // checks if the point is empty
            if (plan->board[row][col] != EMPTY) {
                return FALSE;
            }

            // checks if the point bellow is empty
            if (row != SIZE - 1 && plan->board[row + 1][col] != EMPTY) {
                return FALSE;
            }

            // checks if the point above is empty
            if (row != 0 && plan->board[row - 1][col] != EMPTY) {
                return FALSE;
            }

            if (ship->type.len == DEST_L) {
                if (col != 0 && plan->board[row][col - 1] != EMPTY) {
                    return FALSE;
                }
                if (col == SIZE - 1 && plan->board[row][col + 1] != EMPTY) {
                    return FALSE;
                }
            }

            // checks if on the left side of the start point is a point that is empty
            if (i == 0 && col != 0 && plan->board[row][col - 1] != EMPTY) {
                return FALSE;
            }

            // checks if on the right side of the end point is a point that is empty
            if (i == SIZE-1 && col != SIZE - 1 && plan->board[row][col + 1] != EMPTY) {
                return FALSE;
            }

            col += 1;

        } else {

            // checks if the point is empty
            if (plan->board[row][col] != EMPTY) {
                return FALSE;
            }

            // checks if the point on the left is empty
            if (col != 0 && plan->board[row][col - 1] != EMPTY) {
                return FALSE;
            }

            // checks if the point on the right is empty
            if (col != SIZE - 1 && plan->board[row][col + 1] != EMPTY) {
                return FALSE;
            }

            // checks if the point above start point is a point that is empty
            if (i == 0 && row != 0 && plan->board[row - 1][col] != EMPTY) {
                return FALSE;
            }

            // checks if the point below end point is a point that is empty
            if (i == SIZE-1 && row != SIZE - 1 && plan->board[row + 1][col] != EMPTY) {
                return FALSE;
            }

            row += 1;
        }
    }
    return TRUE;
}

/**
 * Checks if the ship we wish to place to our plan is in playing board boundaries.
 * @param ship The ship we wish to place to our plan.
 * @return TRUE if ship is in boundaries
 *         else FALSE
 */
Boolean check_boundaries(Ship *ship) {
    Boolean check = TRUE;

    if (ship->start.row < 0 || ship->start.col < 0) {
        check = FALSE;
    }
    else if (ship->start.col + ship->type.len > SIZE && ship->direction == HORIZONTAL) {
        check = FALSE;
    }
    else if (ship->start.row + ship->type.len > SIZE && ship->direction == VERTICAL) {
        check = FALSE;
    }

    return check;
}

/**
 * Adds the given ship to the given plan.
 * @param my_plan Pointer to struct Plan
 * @param ship The ship we want to add.
 * @return error code
 */
int add_ship_to_board(Plan *my_plan, Ship ship) {
    int err = OK;
    Boolean check;

    check = check_boundaries(&ship);
    if (check == FALSE) {
        err = SHIP_OUT_OF_BOUNDARY;
    }

    check = check_ship_collision(my_plan, &ship);
    if (check == FALSE) {
        err = SHIP_COLLISION;
    }

    if (err == OK) {
        for (int i = 0; i < ship.type.len; ++i) {
            switch (ship.direction) {
                case HORIZONTAL:
                    my_plan->board[ship.start.row][ship.start.col + i] = ship.type.symbol;
                    break;
                case VERTICAL:
                    my_plan->board[ship.start.row + i][ship.start.col] = ship.type.symbol;
                    break;
                case NO:
                    my_plan->board[ship.start.row][ship.start.col] = ship.type.symbol;
                    break;
                default:
                    err = UNKNOWN_DIRECTION;
            }
        }

        my_plan->ships[my_plan->num_of_ships] = ship;
        my_plan->num_of_ships++;
    }

    return err;
}

/**
 * Saves the game to text file.
 * @param p1 The struct player of first player
 * @param p2 The struct player of second player
 */
void save_game(Game *game) {
    FILE *save;

    remove(SAVE_FILE);
    save = fopen(SAVE_FILE, "w");

    save_player(save, game->player);
    save_AI(save, game->AI);

    fclose(save);
}

void save_AI(FILE *file, Computer *AI) {
    fprintf(file, "%i %i %c\n", AI->previous_target.coord.row, AI->previous_target.coord.col, AI->previous_target.error == OK ? 'K' : 'F');
    save_player(file, AI->player);
}

void save_player(FILE *file, Player *player) {
    fprintf(file, "%s\n", player->username);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fprintf(file, "%c ", player->info_on_enemy_board[i][j]);
        }
        fprintf(file, "\n");
    }

    save_plan(file, player->my_plan);
}

void save_plan(FILE *file, Plan *plan) {
    fprintf(file, "%d\n", plan->num_of_ships);
    for (int i = 0; i < plan->num_of_ships; i++) {
        save_ship(file, &plan->ships[i]);
        fprintf(file, "\n");
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fprintf(file, "%c ", plan->board[i][j]);
        }
        fprintf(file, "\n");
    }
}

void save_ship(FILE *file, Ship *ship) {
    fprintf(file, "%c %i\n", ship->type.symbol, ship->type.len);
    fprintf(file, "%c\n", ship->direction == HORIZONTAL ? 'H' : 'V');
    fprintf(file, "%c\n", ship->ship_destroyed == TRUE ? 'T' : 'F');
    fprintf(file, "%i %i", ship->start.row, ship->start.col);
}

void load_game(char *file_name, Game *game) {
    FILE *file;
    file = fopen(file_name, "r");

    load_player(file, game->player, FALSE);
    load_AI(file, game->AI);

    fclose(file);

}

void load_AI(FILE *file, Computer *AI) {

    char c;
    fscanf(file, "%i %i %c", &AI->previous_target.coord.row, &AI->previous_target.coord.col, &c);

    AI->previous_target.error = (c == 'K' ? OK : NO_HITS);

    load_player(file, AI->player, TRUE);

}

void load_plan(FILE *file, Plan *plan) {
    fscanf(file, "%i", &plan->num_of_ships);
    fgetc(file);

    for (int i = 0; i < plan->num_of_ships; i++) {
        load_ship(file, &plan->ships[i]);
    }


    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fscanf(file, "%c ", &plan->board[i][j]);
        }
    }
}

void load_player(FILE *file, Player *player, Boolean is_AI) {
    char *username = malloc(20 * sizeof(char));
    fscanf(file, "%s", username);
    char c = fgetc(file);

    if (is_AI == FALSE) {
        init_player(player, username);
    } else {
        free(username);
        username = NULL;
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fscanf(file, "%c ", &player->info_on_enemy_board[i][j]);
        }
    }

    load_plan(file, player->my_plan);
}

void load_ship(FILE *file, Ship *ship) {
    ShipType type;
    fscanf(file, "%c %i", &type.symbol, &type.len);

    switch (type.symbol) {
        case CARR:
            type.name = CARR_NAME;
            break;
        case BATT:
            type.name = BATT_NAME;
            break;
        case DEST:
            type.name = DEST_NAME;
            break;
        case CRUI:
            type.name = CRUI_NAME;
            break;
        case SUBM:
            type.name = SUBM_NAME;
            break;
    }

    char tmp;
    Direction dir;
    fgetc(file);
    fscanf(file, "%c", &tmp);

    if (tmp == 'H') {
        dir = HORIZONTAL;
    } else {
        dir = VERTICAL;
    }

    Boolean ship_destroyed;
    fgetc(file);
    fscanf(file, "%c", &tmp);
    fgetc(file);

    if (tmp == 'T') {
        ship_destroyed = TRUE;
    } else {
        ship_destroyed = FALSE;
    }

    Coordinate coord;
    fscanf(file, "%i %i", &coord.row, &coord.col);
    fgetc(file);

    ship->ship_destroyed = ship_destroyed;
    ship->start = coord;
    ship->type = type;
    ship->direction = dir;
}

void alloc_game(Game *game) {
    game->player = malloc(sizeof(Player));
    alloc_player(game->player);

    game->AI = malloc(sizeof(Computer));
    alloc_AI(game->AI);
}

void destroy_game(Game *game) {
    destroy_player(game->player, FALSE);
    free(game->player);
    game->player = NULL;

    destroy_AI(game->AI);
    game->AI = NULL;
}