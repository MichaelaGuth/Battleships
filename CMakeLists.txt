cmake_minimum_required(VERSION 3.10.2)
project(Battleship C)

set(CMAKE_C_STANDARD 99)

add_executable(Battleship game/game.c game/game.h game/print_GUI.c game/print_GUI.h game/constants.h game/interactions.c game/interactions.h game/ship.c game/ship.h game/player.c game/player.h game/error.h game/boards.c game/boards.h game/main.c game/my_tests.c game/my_tests.h game/utils.c game/utils.h game/coordinate.c game/coordinate.h)