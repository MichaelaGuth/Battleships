//
// Created by kimiko on 25.11.19.
//

#include "printGUI.h"

void print_intro() {
    printf("Welcome to Battleships game.\n");
}

void print_rules() {
    printf("");
}

int print_menu() {
    printf("Menu\n");
    printf("1: New Game\n");
    printf("2: Continue\n");
    printf("3: Exit\n");

    int choice;
    int check = scanf("%d", &choice);

    if (check != 1)
        return 101;

    return choice;
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
                case PATR:
                    printf("| %c ", SHIP);
                    break;
                default:
                    printf("| %c ", board[row][col]);
                    break;
            }
        }
        printf("|\n");
    }
}

