
#include <stdlib.h>
#include <stdio.h>
#include <kovan/kovan.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "claw-utils.h"


int main(int argc, char** argv) {
    
    //top hat is at 248 without cube and 190 with cube
    //servos are at pickup 1200, ground is  240, dropoff is 600
    printf("starting v 5.\n");
    raise_claw_to(240);
    enable_servo(0);
    enable_servo(2);
    raw_raise_claw_to(0);
    //set_servos_enabled(true);
    int* val = malloc(sizeof(int));
    char cmd[50];
    while (true) {
        printf("read analog sensor val as: %i\n", analog10(0));
        scanf("%s %i", cmd, val);
        
        if (cmd[0] == 'c' || cmd[0] == 'C') {
            move_claw_amount(*val);
        } else if (cmd[0] == 's' || cmd[0] == 'S') {
            raise_claw_to(*val);
        }
    }
    return (EXIT_SUCCESS);
}
