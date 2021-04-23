//
// Created by kimiko on 30.12.19.
//

#ifndef BATTLESHIP_MY_TESTS_H
#define BATTLESHIP_MY_TESTS_H

#include "game.h"
#include <unistd.h>
#include <string.h>
#include "utils.h"

Boolean test_if_save_file_exists();
void test_create_AI();
Boolean test_find_ship_index();
void test_load_game();
void test_dest_place();
void test_AI_fire();
void test_update_info_board();
void test();
void test_destroy_game();



#endif //BATTLESHIP_MY_TESTS_H
