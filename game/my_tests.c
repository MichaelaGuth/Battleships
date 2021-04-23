//
// Created by kimiko on 30.12.19.
//

#include "my_tests.h"
#include "interactions.h"


Boolean test_if_save_file_exists() {
    Game game;
    alloc_game(&game);
    init_AI(game.AI, 1);
    init_player(game.player, "Kimiko");

    save_game(&game);

    if (access(SAVE_FILE, F_OK) != -1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void test_create_AI() {
    Computer AI;
    alloc_AI(&AI);
    init_AI(&AI, 1);

    printf("%s\n", AI.player->username);
    printf("%i\n", AI.player->my_plan->num_of_ships);
    for (int i = 0; i < AI.player->my_plan->num_of_ships; i++) {
        print_ship(&AI.player->my_plan->ships[i]);
    }

    print_board(AI.player->my_plan->board);
    print_board(AI.player->info_on_enemy_board);
}

Boolean test_find_ship_index() {
    Boolean res = FALSE;

    Plan plan;
    alloc_plan(&plan);
    change_board(plan.board, BOARD_1);

    Ship ship = create_ship(get_carrier(), create_coordinate(0, 0), HORIZONTAL);
    plan.ships[plan.num_of_ships] = ship;
    plan.num_of_ships++;

    Coordinate coord = create_coordinate(0,1);
    int i = find_ship_index_in_plan(CARR, coord, &plan);

    if (i == -1) {
        printf("EMPTY\n");
    }

    for (int j = 0; j < plan.ships[i].type.len; j++) {
        if (plan.ships[i].direction == HORIZONTAL) {
            if (plan.board[plan.ships[i].start.row][plan.ships[i].start.col + j] == plan.board[coord.row][coord.col]) {
                res = TRUE;
            }
        } else {
            if (plan.board[plan.ships[i].start.row + j][plan.ships[i].start.col] == plan.board[coord.row][coord.col]) {
                res = TRUE;
            }
        }
    }

    print_coord(coord);
    print_board(plan.board);

    /**
    coord = create_coordinate(0,1);
    i = find_ship_index_in_plan(CARR, coord, plan);
    for (int j = 0; j < plan.ships[i].type.len; j++) {
        if (plan.ships[i].direction == HORIZONTAL) {
            if (plan.board[plan.ships[i].start.row][plan.ships[i].start.col + j] == plan.board[coord.row][coord.col]) {
                res = TRUE;
            }
        } else {
            if (plan.board[plan.ships[i].start.row + j][plan.ships[i].start.col] == plan.board[coord.row][coord.col]) {
                res = TRUE;
            }
        }
    }
     */

    return res;
}

void test_load_game() {
    Game g1;
    alloc_game(&g1);

    init_AI(g1.AI, 1);
    init_player(g1.player, "Kimiko");
    change_board(g1.player->my_plan->board, BOARD_5);

    fire(g1.player, g1.AI->player, create_coordinate(2, 8));
    save_game(&g1);

    Game g2;
    alloc_game(&g2);
    load_game(SAVE_FILE, &g2);

    print_Boolean(compare_game(&g1, &g2));

    //print_Game(&g2);
}


void test_dest_place() {
    Plan plan;
    alloc_plan(&plan);

    Ship ship = create_ship(get_destroyer(), create_coordinate(0,0), HORIZONTAL);

    add_ship_to_board(&plan, ship);
    print_board(plan.board);
};

void test_AI_fire() {
    Game game;
    alloc_game(&game);

    init_AI(game.AI, 1);
    init_player(game.player, "Kimiko");
    change_board(game.player->my_plan->board, BOARD_5);

    play_AI(&game);
    play_AI(&game);
    play_AI(&game);
}

void test_update_info_board() {
    Game game;
    alloc_game(&game);

    init_AI(game.AI, 1);

    fire(game.AI->player, game.player, create_coordinate(9, 3));
    update_AI_info_board(game.AI->player->info_on_enemy_board);
    print_board(game.AI->player->info_on_enemy_board);
}

void test() {
    Game game;
    alloc_game(&game);

    init_AI(game.AI, 1);

    Computer player;
    alloc_AI(&player);

    char *username = malloc(20 * sizeof(char));
    username[0] = 'K';
    username[1] = 'O';
    username[2] = '\0';

    player.player->username = username;

    init_AI(&player, 1);

    game.player = player.player;

    for (int i = 0; i < game.AI->player->my_plan->num_of_ships - 1; i++) {
        for (int j = 0; j < game.AI->player->my_plan->ships[i].type.len; j++) {
            if (game.AI->player->my_plan->ships[i].direction == HORIZONTAL) {
                fire(game.player, game.AI->player, create_coordinate(game.AI->player->my_plan->ships[i].start.row, game.AI->player->my_plan->ships[i].start.col + j));
            } else {
                fire(game.player, game.AI->player, create_coordinate(game.AI->player->my_plan->ships[i].start.row + j, game.AI->player->my_plan->ships[i].start.col));
            }
        }
    }

    Ship ship = game.AI->player->my_plan->ships[game.AI->player->my_plan->num_of_ships - 1];

    start_game(&game);
}

void test_destroy_game() {
    Game game;
    alloc_game(&game);

    init_AI(game.AI, 1);

    Computer player;
    alloc_AI(&player);

    char *username = malloc(20 * sizeof(char));
    username[0] = 'K';
    username[1] = 'O';
    username[2] = '\0';

    player.player->username = username;

    init_AI(&player, 5);

    destroy_player(game.player, FALSE);
    free(game.player);
    game.player = NULL;

    game.player = player.player;

    for (int i = 0; i < game.AI->player->my_plan->num_of_ships - 1; i++) {
        for (int j = 0; j < game.AI->player->my_plan->ships[i].type.len; j++) {
            if (game.AI->player->my_plan->ships[i].direction == HORIZONTAL) {
                fire(game.player, game.AI->player, create_coordinate(game.AI->player->my_plan->ships[i].start.row, game.AI->player->my_plan->ships[i].start.col + j));
            } else {
                fire(game.player, game.AI->player, create_coordinate(game.AI->player->my_plan->ships[i].start.row + j, game.AI->player->my_plan->ships[i].start.col));
            }
        }
    }

    destroy_game(&game);

    if (game.AI == NULL) {
        printf("OK\n");
    }

    if (game.player == NULL) {
        printf("OK\n");
    }
}