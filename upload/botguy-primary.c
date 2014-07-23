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
    
    enable_servos();
    printf("camera open response: %i\n", camera_open());
    printf("driving to pos.\n");
    driveStraight();
    msleep(2000);
    stop();
    turnInPlaceCCW();
    msleep(700);
    stop();
    driveStraight();
    msleep(1500);
    stop();
    turnInPlaceCW();
    msleep(500);
    stop();
    msleep(1000);
    preformApproachBotguy(false, 0);
    driveBackward();
    msleep(1500);
    raise_botguy_to(BOTGUY_CLAW_MID_UP);
    msleep(100);
   raise_botguy_to(BOTGUY_CLAW_FULL_UP);
    
    
   
    turnInPlaceCCW();
    msleep(1100); 
    stop();
    msleep(200);
    preformApproachCube(false, 1);
    stop();
    turnInPlaceCCW();
    msleep(300);
    driveStraight();
    msleep(3000);
    
    turnInPlaceCW();
    msleep(700);
    driveStraight();
    msleep(1700);
    stop();
    msleep(500);
    raise_botguy_to(BOTGUY_CLAW_MID_UP);
    return (EXIT_SUCCESS);
}

