//
// Created by kimiko on 28.11.19.
//

#include <unistd.h>
#include "interactions.h"


/**
 * Starts the planning for the given player.
 * @param player Pointer to struct player.
 */
void start_planning(Player *player) {
    for (int k = 0; k < C_MAX; ++k) {
        place_ship(player->my_plan, get_carrier());
    }

    for (int l = 0; l < B_MAX; ++l) {
        place_ship(player->my_plan, get_battleship());
    }

    for (int m = 0; m < CR_MAX; ++m) {
        place_ship(player->my_plan, get_cruiser());
    }

    for (int i = 0; i < S_MAX; ++i) {
        place_ship(player->my_plan, get_submarine());
    }

    for (int j = 0; j < D_MAX; ++j) {
        place_ship(player->my_plan, get_destroyer());
    }
}

/**
 * Starts menu options.
 */
void menu() {
    Boolean check = FALSE;
    int choice = 0;
    while (check == FALSE) {
        if (access(SAVE_FILE, F_OK) != -1) {
            print_menu();

            check = read_choice(&choice, 5);

            if (check == FALSE) {
                print_error(INVALID_INPUT, INVALID_INPUT_TXT);
                printf("Try again!\n");
            }
        } else {
            print_menu_2();

            check = read_choice(&choice, 5);

            if (check == FALSE) {
                print_error(INVALID_INPUT, INVALID_INPUT_TXT);
                printf("Try again!\n");
            }
        }
    }

    switch (choice) {
        case 1:
            start_new_game();
            break;
        case 2:
            {
                Game game;
                alloc_game(&game);
                load_game(SAVE_FILE, &game);
                start_game(&game);
            }
        case 3:
            print_rules();
            menu();
            break;
        case 4:
            print_tutorial();
            menu();
            break;
        case 5:
            exit(0);
        default:
            print_error(UNKNOWN, UNKNOWN_TXT);
            exit(-1);
    }
}


/**
 * Starts and creates new game.
 */
void start_new_game() {
    Game game;
    alloc_game(&game);

    Boolean check = FALSE;
    char *player_name = malloc(20 * sizeof(char));

    while (check == FALSE) {
        printf("Enter your username (max. 20 characters): ");
        check = read_string(player_name, 21);
        if (check == FALSE) {
            print_error(INVALID_INPUT, INVALID_INPUT_TXT);
            printf("Try again!\n");
        }
    }

    init_player(game.player, player_name);
    start_planning(game.player);

    check = FALSE;
    int lvl = 1;

    while (check == FALSE) {
        printf("Choose level:\n");
        for (int i = 1; i <= 5; i++) {
            print_lvl_choice(i);
        }

        check = read_number(&lvl);
        if (check == FALSE) {
            print_error(INVALID_INPUT, INVALID_INPUT_TXT);
            printf("Try again!\n");
        }
    }

    init_AI(game.AI, lvl);

    start_game(&game);
}

/**
 * Starts given game.
 * @param game Pointer to given game.
 */
void start_game(Game *game) {
    Boolean check_end = TRUE;

    while (check_end == TRUE) {
        check_end = start_round(game);
    }

    destroy_game(game);

    menu();
}

/**
 * Starts the round of the given game.
 * @param game Pointer to the given struct Game
 * @return
 */
Boolean start_round(Game *game) {
    Boolean res = TRUE;

    if (play(game) == END_GAME) {
        res = FALSE;
    } else if (test_game_over(game->AI->player) == TRUE) {
        res = FALSE;
        print_winner(*game->player);
    } else {
        play_AI(game);
        if (test_game_over(game->player) == TRUE) {
            res = FALSE;
        }
    }

    return res;
}

/**
 * Starts the play etap of the real player.
 * @param game Pointer to the given struct Game
 * @return
 */
int play(Game *game) {
    int res = OK;

    Boolean check = FALSE;
    Coordinate target = {-1, -1};

    while (check == FALSE) {
        printf("Choose your fire target!\n");
        print_board(game->player->info_on_enemy_board);

        printf("Enter the coordinates of your target (ex.: A 10):\n");
        check = read_coordinates(&target);

        if (check == FALSE) {
            print_error(INVALID_INPUT, INVALID_INPUT_TXT);
            printf("Try again!\n");

            int choice = 0;
            Boolean check_continue = FALSE;
            while (check_continue == FALSE) {
                printf("Do you wish to continue playing the game?\n");
                printf("1: Yes\n");
                printf("2: No\n");

                check_continue = read_choice(&choice, 2);

                if (check_continue == FALSE) {
                    print_error(INVALID_INPUT, INVALID_INPUT_TXT);
                    printf("Try again!\n");
                }
            }

            if (choice == 2) {
                save_game(game);
                res = END_GAME;
                check = TRUE;
            } else {
                printf("%s fires on coordinates %c %i in %s's board!\n", game->player->username, target.row + 'A', target.col + 1, game->AI->player->username);
                fire(game->player, game->AI->player, target);
                print_board(game->player->info_on_enemy_board);
                printf("\n");
            }
        } else {
            printf("%s fires on coordinates %c %i in %s's board!\n", game->player->username, target.row + 'A', target.col + 1, game->AI->player->username);
            fire(game->player, game->AI->player, target);
            print_board(game->player->info_on_enemy_board);
            printf("\n");
        }
    }

    return res;
}


/**
 * Places
 * @param plan
 * @param type
 * @return
 */
int place_ship(Plan *plan, ShipType type) {
    Boolean check = FALSE;
    Coordinate start;
    while (check == FALSE) {
        print_coord_choice(type);
        check = read_coordinates(&start);

        if (check == FALSE) {
            print_error(INVALID_INPUT, INVALID_INPUT_TXT);
            printf("Try again!\n");
        }
    }

    Direction dir;

    if (type.len > 1) {
        check = FALSE;
        int choice = 0;
        while (check == FALSE) {
            print_dir_choice();
            check = read_choice(&choice, 2);

            if (check == FALSE) {
                print_error(INVALID_INPUT, INVALID_INPUT_TXT);
            }
        }

        switch (choice) {
            case 1:
                dir = HORIZONTAL;
                break;
            case 2:
                dir = VERTICAL;
                break;
            default:
                print_error(INVALID_INPUT, INVALID_INPUT_TXT);
                exit(INVALID_INPUT);
        }
    } else {
        dir = NO;
    }

    Ship ship = create_ship(type, start, dir);
    int err = add_ship_to_board(plan, ship);


    if (err != OK) {
        char *err_txt;
        switch (err) {
            case SHIP_COLLISION:
                err_txt = SHIP_COLLISION_TXT;
                break;
            case SHIP_OUT_OF_BOUNDARY:
                err_txt = SHIP_OUT_OF_BOUNDARY_TXT;
                break;
            default:
                err_txt = UNKNOWN;
        }

        print_error(err, err_txt);
        place_ship(plan, type);

    } else {
        printf("Your Board:\n");
        print_board(plan->board);
    }
}

Boolean read_string(char *buffer, int buffer_size) {
    Boolean end_of_line = FALSE;
    if (fgets(buffer, buffer_size, stdin)) {
        for (int i = 0; i < buffer_size; i++) {
            if (*(buffer + i) == '\n') {
                end_of_line = TRUE;
                *(buffer + i) = '\0';
                break;
            }
        }
        while ((end_of_line == FALSE) && (getchar() != '\n'));
        return TRUE;
    }

    return FALSE;
}

Boolean read_number(int *number) {
    Boolean result = FALSE;
    int input_size = 0;
    Boolean end_of_line = FALSE;
    char buf[3];

    *number = -1;

    if (fgets(buf, 3, stdin)) {
        for (int i = 0; i < 3; i++) {
            input_size++;
            if (buf[i] == '\n') {
                end_of_line = TRUE;
                buf[i] = '\0';
                break;
            }
        }

        // reads the rest of the line
        while ((end_of_line == FALSE) && ((getchar()) != '\n')) {
            input_size++;
        }

        // checks if the input is within valid length
        if (input_size <= 3) {
            char *endptr;
            *number = strtol(buf, &endptr, 10);

            // checks if the reading finished correctly
            if (endptr == buf || (*endptr && *endptr != '\n')) {
                result = FALSE;
            } else {
                result = TRUE;
            }
        }
        else {
            result = FALSE;
        }

    }

    return result;
}

Boolean read_choice(int *num, int max) {
    Boolean res = FALSE;
    res = read_number(num);
    if (*num < 1 || *num > max) {
        res = FALSE;
    }
    return res;
}

Boolean read_coordinates(Coordinate *coord) {
    Boolean res = FALSE;

    coord->row = -1;
    coord->col = -1;

    char row;
    int col;
    if (scanf("%c %2d", &row, &col) == 2) {
        res = TRUE;
        col--;

        // reads the rest of line
        if (getchar() != '\n') {
            while (getchar() != '\n');
        }

        // checks if row is valid
        if ((row < 'A' || row > 'J') && (row < 'a' || row > 'j')) {
            res = FALSE;
        } else {
            if (row >= 'A' && row <= 'J') {
                coord->row = row - 'A';
            } else {
                coord->row = row - 'a';
            }
        }

        // checks if col is valid
        if (col < 0 || col >= SIZE) {
            res = FALSE;
        } else {
            coord->col = col;
        }
    }
    else {
        res = FALSE;
        if (getchar() != '\n') {
            while (getchar() != '\n');
        }
    }

    return res;
}