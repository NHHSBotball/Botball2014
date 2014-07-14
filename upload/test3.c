#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#include <sys/time.h>

#include "claw-utils.h"
#include "drive-utils.h"

int main(int argc, char** argv) {
    printf("tesfdaasdf\n");
    driveStraight();
    msleep(1000);
    
    return EXIT_SUCCESS;
    //Test the claw for botguy robot (link 103)
    raise_botguy_to(BOTGUY_CLAW_DOWN);
    move_botguy_claw_to(BOTGUY_CLAW_CLOSED); //should become a constant.
    enable_servos();
    msleep(1500);
    move_botguy_claw_to(BOTGUY_CLAW_CLOSED);
    raise_botguy_to(BOTGUY_CLAW_UP);


    //create_spin_CW(100);
    //msleep(2040);   //This is the     ORIGINAL  REAL SUPER GOOD   code the make a 90% turn.
    //disable_servos();
    return 0;
}


