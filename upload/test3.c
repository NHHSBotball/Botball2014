#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>

#include "claw-utils.h"

int main(int argc, char** argv) {
       create_connect();
    create_drive_straight(-50);
    msleep(2000);
    
    motor(0, 10);
    msleep(1000);
    
    
    raise_claw_to(CLAW_UP_POSITION);
    enable_servos();

    create_drive_straight(-50);
    msleep(5000);
    move_claw_amount(CLAW_OPEN_AMOUNT);

    //create_spin_CW(100);
    //msleep(2040);   //This is the     ORIGINAL  REAL SUPER GOOD   code the make a 90% turn.
    //disable_servos();
    return 0;
}


