//
// Created by kimiko on 25.11.19.
//

#include "game.h"
#include "error.h"

int find_ship_len(char ship_symbol) {
    int res;
    switch (ship_symbol) {
        case CARR:
            res = CARR_L;
            break;
        case SUBM:
            res = SUBM_L;
            break;
        case DEST:
            res = DEST_L;
            break;
        case PATR:
            res = PATR_L;
            break;
        case BATT:
            res = BATT_L;
            break;
        default:
            res = -1;
    }
    return res;
}


/**
 * Finds the index in array of Ships of targeted Ship
 * @param ship_symbol The symbol of targeted ship
 * @param target the target coordinates
 * @param plan the plan
 * @return the index of the targeted ship
 */
int find_ship_index(char ship_symbol, Coordinate target, Plan plan) {
    Coordinate tmp;
    int res = -1;
    for (int i = 0; i < plan.num_of_ships; ++i) {
        if (plan.ships[i].type.symbol == ship_symbol) {
            for (int j = 0; j < plan.ships[i].type.len; j++) {
                if (plan.ships[i].direction == HORIZONTAL) {
                    tmp = create_coordinate(plan.ships[i].start.x + j, plan.ships[i].start.y);
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
 * Tests if all ships from given player are destroyed.
 * @param player The struct player
 * @return TRUE if all ships are destroyed
 *         else FALSE
 */
Boolean test_game_over(Player player) {
    Boolean res = TRUE;
    for (int i = 0; i < player.my_plan.num_of_ships; ++i) {
        if (player.my_plan.ships[i].ship_destroyed == FALSE)
            res = FALSE;
    }
    return res;
}

/**
 * Updates the status of attacked ship.
 * @param opponent The player which is attacking.
 * @param ship Pointer to the attacked ship.
 */
void update_ship_status(Player opponent, Ship *ship) {
    Boolean result = TRUE;
    for (int i = 0; i < ship->type.len; ++i) {
        if (ship->direction == HORIZONTAL) {
            if (opponent.info_on_enemy_board[ship->start.x + i][ship->start.y] != HIT) {
                result = FALSE;
            }
        } else {
            if (opponent.info_on_enemy_board[ship->start.x][ship->start.y + i] != HIT) {
                result = FALSE;
            }
        }
    }
    ship->ship_destroyed = result;
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
                player->info_on_enemy_board[ship.start.x + i][ship.start.y] = SHIP_DESTROYED;
            } else {
                player->info_on_enemy_board[ship.start.x][ship.start.y + i] = SHIP_DESTROYED;
            }
        }
    }
}

/**
 * Fires on the given target and changes the status of target in info_on_enemy_board
 * @param my_player The attacking player
 * @param opponent The attacked player
 * @param target The Coordinates of fire target
 * @return error code
 */
int fire(Player *my_player, Player *opponent, Coordinate target) {
    char test = opponent->my_plan.board[target.x][target.y];
    printf("%s fires on coordinates %c %i in %s's board!\n", my_player->username, target.x + 'A', target.y, opponent->username);

    int err = OK;

    switch (test) {
        case CARR:
        case BATT:
        case DEST:
        case SUBM:
        case PATR:
            {
                // changes the value in target on info_on_enemy_board
                my_player->info_on_enemy_board[target.x][target.y] = HIT;

                //  updates the status of the attacked ship
                int ship_index = find_ship_index(test, target, opponent->my_plan);
                update_ship_status(*my_player, &opponent->my_plan.ships[ship_index]);

                break;
            }
        case EMPTY:
            {
                my_player->info_on_enemy_board[target.x][target.y] = EMPTY;
                break;
            }
        default:
            err =  INVALID_TARGET;
    }

    print_board(my_player->info_on_enemy_board);
    return err;
}

/**
 * Checks if the ship we wish to place to our PLan is not next to or over another ship
 * @param plan The plan of the player
 * @param ship The ship we wish to place
 * @return TRUE if the collision did not occur
 *         else FALSE
 */
Boolean check_ship_collision(Plan plan, Ship ship) {
    int x = ship.start.x;
    int y = ship.start.y;
    for (int i = 0; i < ship.type.len; i++) {               // for comments: point = board[x][y]

        if (ship.direction == HORIZONTAL) {

            // checks if the point is empty
            if (plan.board[x][y] != EMPTY) {
                return FALSE;
            }

            // checks if the point bellow is empty
            if (x != SIZE-1 && plan.board[x + 1][y] != EMPTY) {
                return FALSE;
            }

            // checks if the point above is empty
            if (x != 0 && plan.board[x - 1][y] != EMPTY) {
                return FALSE;
            }

            if (ship.type.len == PATR_L) {
                if (y != 0 && plan.board[x][y - 1] != EMPTY) {
                    return FALSE;
                }
                if (y == SIZE-1 && plan.board[x][y + 1] != EMPTY) {
                    return FALSE;
                }
            }

            // checks if on the left side of the start point is a point that is empty
            if (i == 0 && y != 0 && plan.board[x][y - 1] != EMPTY) {
                return FALSE;
            }

            // checks if on the right side of the end point is a point that is empty
            if (i == SIZE-1 && y != SIZE-1 && plan.board[x][y + 1] != EMPTY) {
                return FALSE;
            }

            y += 1;

        } else {

            // checks if the point is empty
            if (plan.board[x][y] != EMPTY) {
                return FALSE;
            }

            // checks if the point on the left is empty
            if (y != 0 && plan.board[x][y - 1] != EMPTY) {
                return FALSE;
            }

            // checks if the point on the right is empty
            if (y != SIZE-1 && plan.board[x][y + 1] != EMPTY) {
                return FALSE;
            }

            // checks if the point above start point is a point that is empty
            if (i == 0 && x != 0 && plan.board[x - 1][y] != EMPTY) {
                return FALSE;
            }

            // checks if the point below end point is a point that is empty
            if (i == SIZE-1 && x != SIZE-1 && plan.board[x + 1][y] != EMPTY) {
                return FALSE;
            }

            x += 1;
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
Boolean check_boundaries(Ship ship) {
    if (ship.start.x < 0 || ship.start.y < 0) {
        return FALSE;
    }
    if (ship.start.y + ship.type.len > SIZE && ship.direction == HORIZONTAL) {
        return FALSE;
    }
    if (ship.start.x + ship.type.len > SIZE && ship.direction == VERTICAL) {
        return FALSE;
    }
    return TRUE;
}

/**
 * Adds the given ship to the given plan.
 * @param my_plan Pointer to struct Plan
 * @param ship The ship we want to add.
 * @return error code
 */
int add_ship_to_board(Plan *my_plan, Ship ship) {
    int x = ship.start.x;
    int y = ship.start.y;

    Boolean check;

    check = check_boundaries(ship);
    if (check == FALSE) {
        return SHIP_OUT_OF_BOUNDARY;
    }

    check = check_ship_collision(*my_plan, ship);
    if (check == FALSE) {
        return SHIP_COLLISION;
    }

    for (int i = 0; i < ship.type.len; ++i) {
        if (ship.direction == HORIZONTAL) {
            my_plan->board[ship.start.x][ship.start.y + i] = ship.type.symbol;
        } else {
            my_plan->board[ship.start.x + i][ship.start.y] = ship.type.symbol;
        }
    }

    my_plan->ships[my_plan->num_of_ships] = ship;
    my_plan->num_of_ships++;

    return OK;
}

/**
 * Saves the game to text file.
 * @param p1 The struct player of first player
 * @param p2 The struct player of second player
 */
void save_game(Player p1, Player p2) {
    FILE *save;
    save = fopen(SAVE_FILE, "w");

    save_player(save, p1);
    save_player(save, p2);

    fclose(save);
}

void save_player(FILE *file, Player player) {
    fprintf(file, "%s\n", player.username);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fprintf(file, "%c ", player.info_on_enemy_board[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "%d", player.my_plan.num_of_ships);
    for (int i = 0; i < player.my_plan.num_of_ships; i++) {
        save_ship(file, player.my_plan.ships[i]);
        fprintf(file, "\n");
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            fprintf(file, "%c ", player.my_plan.board[i][j]);
        }
        fprintf(file, "\n");
    }
}

void save_ship(FILE *file, Ship ship) {
    fprintf(file, "%s %c %i\n", ship.type.name, ship.type.symbol, ship.type.len);
    fprintf(file, "%c\n", ship.direction == HORIZONTAL ? 'H' : 'V');
    fprintf(file, "%c\n", ship.ship_destroyed == TRUE ? 'T' : 'F');
    fprintf(file, "%i %i", ship.start.x, ship.start.y);
}

void load_game(char *file_name) {
    FILE *file;
    fopen(file_name, "r");



}

// TODO: dodelat load

Player load_player(FILE *file) {
    char *username = malloc(20 * sizeof(char));
    fscanf(file, "%s", username);
    Player player = create_Player(username);
    //fscanf(file, );
}