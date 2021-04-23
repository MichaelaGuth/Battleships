//
// Created by kimiko on 27.11.19.
//

#include <stdio.h>
#include "player.h"
#include "constants.h"
#include "boards.h"

#ifndef BATTLESHIP_PRINTGUI_H
#define BATTLESHIP_PRINTGUI_H

void print_intro();
void print_rules();
void print_tutorial();
void print_menu();
void print_menu_2();

void print_error(int error_code, char *error_text);
void print_winner(Player player);

void print_lvl_choice(int lvl);
void print_dir_choice();
void print_coord_choice(ShipType type);

void print_board(char board[][SIZE]);
void print_board_for_rules(const char board[SIZE][SIZE], char* tab);


#endif //BATTLESHIP_PRINTGUI_H
