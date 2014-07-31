/* 
 * File:   botguy-primary.c
 * Author: Henry
 *
 * Created on July 14, 2014, 9:04 AM
 */
#include "camera-approach.h"


int wait = 0;
void kill();

void shutDownAfter(int seconds) {
    wait = seconds;
    thread tr = thread_create(kill);
    thread_start(tr);
}

void kill() {
    printf("killing in %i.", wait * 1000);
    msleep(wait * 1000);
    printf("killing program.\n");
    disable_servos();
    create_drive_straight(0);
    motor(0, 0);
    motor(1, 0);
    motor(2, 0);
    motor(3, 0);
    exit(1);
}

/*
 * 
 */
int main(int argc, char** argv) {

    shutDownAfter(119);
    msleep(1000);  //Wait for  other robot to finish.  Should be 30s (3000).  Is only 1000 for testing
    raise_botguy_to(BOTGUY_CLAW_UP);

    enable_servos();
    printf("camera open response: %i\n", camera_open());
    printf("driving to pos.\n");
    driveStraight();
    msleep(3700);
    stop();
    turnInPlaceCCW();
    msleep(700);
    stop();
    driveStraight();
    msleep(1900); //was 1500
    stop();
    turnInPlaceCW();
    msleep(580);
    stop();
    msleep(1000);
    raise_botguy_to(BOTGUY_CLAW_DOWN);
    driveStraight();
    msleep(1100);

    stop();
    close_botguy_claw();
    hold_botguy_claw_closed();
    //preformApproachBotguy(false, 0);
    driveBackward();
    msleep(700);
    raise_botguy_to(BOTGUY_CLAW_MID_UP);
    msleep(900);
    raise_botguy_to(BOTGUY_CLAW_FULL_UP);



    turnInPlaceCCW();
    msleep(600);
    stop();
    driveBackward();
    msleep(1000);
    stop();
    preformApproachCube(false, 1);
    stop();
    return 0;
    turnInPlaceCW();
    msleep(700);
    driveStraight();
    msleep(3000);

    turnInPlaceCCW();
    msleep(700);
    driveStraight();
    msleep(1700);
    stop();
    msleep(500);
    raise_botguy_to(BOTGUY_CLAW_MID_UP);
    return (EXIT_SUCCESS);
}

