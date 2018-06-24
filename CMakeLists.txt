cmake_minimum_required(VERSION 3.11)
project(mySimpleComputer)

set(CMAKE_C_STANDARD 11)
link_libraries("-lm")
add_executable(main main.c interface.c handler.c IO.c cpu.c transale/asm.c
        transale/rpn.c transale/basic.c transale/rpn.c)

add_subdirectory(myTerm)
add_subdirectory(myBigChars)
add_subdirectory(mySimpleComputer)
add_subdirectory(myReadKey)
add_subdirectory(transale)
target_link_libraries(main myTerm myBigChars mySimpleComputer myReadKey)