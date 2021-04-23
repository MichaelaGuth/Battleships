#include <stdio.h>
#include "game.h"
#include "printGUI.h"
#include "constants.h"
#include "interactions.h"
#include "AI_boards.h"

int main() {
    Player p1 = create_Player("Pyjoneer");
    change_board(p1.my_plan.board, BOARD_1);
    p1.my_plan.num_of_ships = C_MAX + D_MAX + B_MAX + P_MAX + S_MAX;


    Player p2 = create_Player("Pijonier");
    //change_board(p2.my_plan.board, BOARD_1);
    start_planning(&p2);

    Coordinate coord = create_coordinate(0,0);
    fire(&p1, &p2, coord);

    coord = create_coordinate(0,1);
    fire(&p1, &p2, coord);

    coord = create_coordinate(0,2);
    fire(&p1, &p2, coord);

    coord = create_coordinate(0,3);
    fire(&p1, &p2, coord);

    coord = create_coordinate(0,4);
    fire(&p1, &p2, coord);

    int index = find_ship_index(CARR, coord, p2.my_plan);
    if (p2.my_plan.ships[index].ship_destroyed == TRUE) {
        printf("OK.");
    }

    update_info_board(&p1, p2.my_plan.ships[index]);
    print_board(p1.info_on_enemy_board);

    return 0;
}