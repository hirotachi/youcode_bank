cmake_minimum_required(VERSION 3.20)
project(youcode_bank C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(youcode_bank
        main.c command.c command.h bank.c bank.h helpers.c helpers.h account.c account.h)
