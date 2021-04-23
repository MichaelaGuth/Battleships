//
// Created by kimiko on 25.11.19.
//

#include "print_GUI.h"

void print_intro() {
    printf("Welcome to Battleships game.\n");
}

void print_rules() {
    printf("Rules:\n");

    printf("#1: There are five types of ship in this game.\n");
    printf("    Carrier:     | / | / | / | / | / |\n");
    printf("    Battleship:  | / | / | / | / |\n");
    printf("    Cruiser:     | / | / | / |\n");
    printf("    Submarine:   | / | / |\n");
    printf("    Destroyer:   | / |\n");
    printf("    There can only be %i Carrier, %i Battleship, %i Cruisers, %i Submarines and %i Destroyers.\n", C_MAX, B_MAX, CR_MAX, S_MAX, D_MAX);

    printf("#2: Players can fire wherever they want, but it has to be within the board boundaries.\n");

    printf("#3: The game ends when one of the players looses all of his/her ships.\n");

    printf("#4: The winner is the player that survived.\n");

    printf("#5: When placing ship in player's board, player can only place his/her ship within the board's boundaries.\n");
    printf("    The ship cannot be placed next to or over another ship in the board.\n");

    printf("#6: Sign explanation:\n");
    printf("    Your board signs:\n");
    printf("    | / | means that you have a ship on these coordinates.\n");
    printf("    Enemy board signs:\n");
    printf("    | X | means that you hit the opponent's ship on these coordinates\n");
    printf("    | ? | means that you haven't fired on these coordinates yet\n");
    printf("    | # | means that opponent's ship is sunk on these coordinates\n");
    printf("    Universal signs:\n");
    printf("    |   | means that these coordinates are empty\n");
}

void print_tutorial() {
    printf("TUTORIAL:\n");
    printf("---------\n");
    printf("Placing ships:\n");
    printf("    Game starts with Player planning how to place his/her ships into his/her board.\n");
    printf("    The board starts with empty slots:\n");
    print_board_for_rules(EMPTY_BOARD, "   ");
    printf("    Player places his/her ships in the board by entering the start coordinates and then chooses the direction of placing the ship.\n");
    printf("    ex.: Enter the start coordinates of Carrier (length of ship: 5)\n");
    printf("         > A 1\n");
    printf("         Choose direction:\n");
    printf("         1: Horizontal\n");
    printf("         2: Vertical\n");
    printf("         > 1\n");
    print_board_for_rules(TUTORIAL_BOARD, "        ");
    printf("\n");

    printf("Firing at target coordinates:\n");
    printf("    The player is asked each turn to fire at opponent's board.\n");
    printf("    The player fires by entering the target coordinates.\n");
    printf("    ex.: Choose your fire target!\n");
    print_board_for_rules(NOT_TESTED_BOARD, "        ");
    printf("         Enter the coordinates of your target (ex.: A 10):\n");
    printf("         > A 1\n");
    printf("         Tutorial_Player fires on coordinates A 1 in Tutorial_Opponent's board!\n");
    print_board_for_rules(TUTORIAL_BOARD_2, "        ");
}

void print_board_for_rules(const char board[SIZE][SIZE], char *tab) {
    printf("%s   ", tab);
    for (int i = 0; i < SIZE; ++i) {
        printf(" %2d ", i + 1);
    }
    printf("\n");

    char abc = 'A';
    for (int row = 0; row < SIZE; row++) {
        printf("%s %c ", tab, abc++);
        for (int col = 0; col < SIZE; col++) {
            switch (board[row][col]) {
                case CARR:
                case BATT:
                case DEST:
                case SUBM:
                case CRUI:
                    printf("| %c ", SHIP);
                    break;
                case EMPTY:
                    printf("|   ");
                    break;
                default:
                    printf("| %c ", board[row][col]);
                    break;
            }
        }
        printf("|\n");
    }
}

void print_menu() {
    printf("Menu:\n");
    printf("1: New Game\n");
    printf("2: Continue\n");
    printf("3: Rules\n");
    printf("4: Tutorial\n");
    printf("5: Exit\n");
}

void print_menu_2() {
    printf("Menu:\n");
    printf("1: New Game\n");
    printf("2: Rules\n");
    printf("3: Tutorial\n");
    printf("4: Exit\n");
}

void print_winner(Player player) {
    printf("\n");
    printf("Game over!\n");
    printf("Winner is %s.\n1Congratulations!\n", player.username);
    printf("\n");
}

void print_board(char board[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; ++i) {
        printf(" %2d ", i + 1);
    }
    printf("\n");

    char abc = 'A';
    for (int row = 0; row < SIZE; ++row) {
        printf(" %c ", abc);
        abc++;
        for (int col = 0; col < SIZE; ++col) {
            switch (board[row][col]) {
                case CARR:
                case BATT:
                case DEST:
                case SUBM:
                case CRUI:
                    printf("| %c ", SHIP);
                    break;
                case EMPTY:
                    printf("|   ");
                    break;
                default:
                    printf("| %c ", board[row][col]);
                    break;
            }
        }
        printf("|\n");
    }
}

void print_error(int error_code, char *error_text) {
    printf("Error %i: %s", error_code, error_text);
}

void print_coord_choice(ShipType type) {
    printf("Enter the start coordinates of %s (length of ship: %i)\n", type.name, type.len);
    printf("in this format:\nex.: A 1\n");
}

void print_dir_choice() {
    printf("Choose direction:\n");
    printf("1: Horizontal\n");
    printf("2: Vertical\n");
}

void print_lvl_choice(int lvl) {
    printf("%i: Level %i\n", lvl, lvl);
}