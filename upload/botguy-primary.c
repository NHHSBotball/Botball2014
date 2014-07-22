/* 
 * File:   botguy-primary.c
 * Author: Henry
 *
 * Created on July 14, 2014, 9:04 AM
 */
#include "camera-approach.h"

/*
 * 
 */
int main(int argc, char** argv) {
    raise_botguy_to(BOTGUY_CLAW_UP);
    move_botguy_claw_to(BOTGUY_CLAW_OPEN);
    enable_servos();
    printf("camera open response: %i\n", camera_open());
    printf("starting approach\n");
    preformApproachBotguy(false, 0);
    msleep(600);
    raise_botguy_to(BOTGUY_CLAW_FULL_UP);
    turnInPlaceCCW();
    msleep(1400);
    stop();
    preformApproachCube(false, 1);
    
    return (EXIT_SUCCESS);
}

