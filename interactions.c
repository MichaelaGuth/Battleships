//
// Created by kimiko on 28.11.19.
//

#include "interactions.h"


/**
 * Starts the planning for the given player.
 * @param player Pointer to struct player.
 */
void start_planning(Player *player) {
    for (int k = 0; k < C_MAX; ++k) {
        place_ship(&player->my_plan, get_carrier());
    }

    for (int l = 0; l < B_MAX; ++l) {
        place_ship(&player->my_plan, get_battleship());
    }

    for (int m = 0; m < D_MAX; ++m) {
        place_ship(&player->my_plan, get_destroyer());
    }

    for (int i = 0; i < S_MAX; ++i) {
        place_ship(&player->my_plan, get_submarine());
    }

    for (int j = 0; j < P_MAX; ++j) {
        place_ship(&player->my_plan, get_patrol_boat());
    }
}

/**
 *
 */
void start_game() {
    printf("Enter your username (max. 20 characters): ");
    char *player_name = malloc(20 * sizeof(char));
    scanf("%s", player_name);
    // TODO: check if the player is retarded

    Player player = create_Player(player_name);
    start_planning(&player);

    Player AI = create_Player("AI");
    // TODO: assign bouard to AI

    Boolean check_end = TRUE;
    while (check_end == TRUE) {
        check_end = turn(&player, &AI);
    }

    destroy_player(&player);
    destroy_player(&AI);
}

/**
 *
 * @param player
 * @param AI
 * @return
 */
Boolean turn(Player *player, Player *AI) {

    // TODO: check error from play()
    play(player, AI);
    if (test_game_over(*AI) == TRUE) {
        //print_winner();
        return FALSE;
    }

    play_AI(AI, player);
    if (test_game_over(*player) == TRUE) {
        //print_game_over();
        return FALSE;
    }

    return TRUE;
}

/**
 *
 * @param player
 * @param opponent
 * @return
 */
int play(Player *player, Player *opponent) {
    int res = OK;

    printf("Do you wish to continue?\n");
    printf("1: Yes\n");
    printf("2: No\n");

    int choice;
    scanf("%d", &choice);
    // TODO: osetrit debilitu uzivatele

    if (choice == 2) {
        //save_game();

    } else {
        printf("Choose your fire target!\n");
        print_board(player->info_on_enemy_board);

        printf("Enter the coordinates of your target (ex.: A 10):");
        Coordinate target = read_coordinates();

        if (target.error == OK) {
            fire(player, opponent, target);
        }

        res = target.error;
    }

    return res;
}

/**
 *
 * @param me
 * @param opponent
 * @return
 */
int play_AI(Player *me, Player *opponent) {

    return OK;
}


int place_ship(Plan *plan, ShipType type) {
    print_enter_coord(type);

    Coordinate start = read_coordinates();

    print_dir_choice();
    int choice;
    int check = scanf("%i", &choice);


    if (check == 0)
        return WRONG_INPUT;

    getchar();          // kvůli '\n'

    Direction dir;
    switch (choice) {
        case 1:
            dir = HORIZONTAL;
            break;
        case 2:
            dir = VERTICAL;
            break;
        default:
            fprintf(stderr, "Error: Wrong choice!\n");
    }

    Ship ship = create_ship(type, start, dir);
    int err = add_ship_to_board(plan, ship);


    // TODO: watch out for memory and malloc
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

        printf("Error %i: %s ", err, err_txt);
        place_ship(plan, type);

    } else {
        printf("Your Board:\n");
        print_board(plan->board);
    }
}

/**
 *
 * @return
 */
Coordinate read_coordinates() {
    Coordinate target;
    char row;
    int tmp = scanf("%c %d", &row, &target.y);

    if (tmp == 0)
        target.error = WRONG_INPUT;

    target.x = row - 'A';
    target.y -= 1;

    if (check_coord_boundaries(target) == FALSE)
        target.error = WRONG_INPUT;

    return target;
}

/**
 *
 * @param coord
 * @return
 */
Boolean check_coord_boundaries(Coordinate coord) {
    Boolean check = TRUE;

    if (coord.x < 0 || coord.x >= SIZE)
        check = FALSE;

    if (coord.y < 0 || coord.y >= SIZE)
        check = FALSE;

    return check;
}

void print_enter_coord(ShipType type) {
    printf("Enter the start coordinates of %s (length of ship: %i)\n", type.name, type.len);
    printf("in this format:\nex.: A 1\n");
}

void print_dir_choice() {
    printf("Choose direction:\n");
    printf("1: Horizontal\n");
    printf("2: Vertical\n");
}