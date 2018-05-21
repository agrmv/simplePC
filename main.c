#include <stdio.h>
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include "interface.h"
#include "handler.h"
#include "transale/asm.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "sat") == 0) {
            if (argc != 4) {
                printf("Error\n");
                return 1;
            }
            if (asm_to_object(argv[2], argv[3]) == 0)
                printf("Successful!\n");
            else
                printf("Fail!\n");
            return 0;
        }
    }
    sc_memoryInit();
    sc_regInit();
    sc_regSet(FLAG_IGNORE_CLOCK, 1);
    interfaceLoad(DEFAULT, DEFAULT);
    initHandler();
    return 0;
}