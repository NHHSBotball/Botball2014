#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>

#include "claw-utils.h"

int main(int argc, char** argv) {
    //Test the claw for botguy robot (link 103)
    
    move_botguy_claw_amount(500); //should become a constant.
    msleep(1000);
    raise_botguy_to(1000);
    
    
    //create_spin_CW(100);
    //msleep(2040);   //This is the     ORIGINAL  REAL SUPER GOOD   code the make a 90% turn.
    //disable_servos();
    return 0;
}


