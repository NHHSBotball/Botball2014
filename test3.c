#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>

#include "claw-utils.h"

int main(int argc, char** argv) {
   
    create_connect();
    raise_claw_to(CLAW_UP_POSITION);
    enable_servos();
    create_drive_straight(-300);
    
    msleep(1700);
    create_drive_straight(150);
    msleep(500);

    create_spin_CW(100);
    msleep(2040);   //This is the     ORIGINAL  REAL SUPER GOOD   code the make a 90% turn.
    disable_servos();
    return 0;
}


