#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#include <sys/time.h>

#include "Constants.h"
#include "claw-utils.h"


#define DRIVE_SPEED 30.0
#define SPIN_SPEED 20.0

int main(int argc, char** argv) {
    printf("starting\n");
    raise_claw_to(400);
    enable_servos();
    create_connect();
    printf("create connected\n");
    create_drive_straight(0);
    //move_claw_amount(CLAW_CLOSE_AMOUNT);
    motor(0, 5);
    msleep(1000);
    raise_claw_to(400);
    struct timeval current_time;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    while (true) {
        gettimeofday(&current_time, NULL);
        if (current_time.tv_usec - start_time.tv_usec > 100000) {
            break;
        }
        if (analog(CLAW_FRONT_BACK) > CLAW_FRONT_THREASHOLD) {
            double difference = analog(CLAW_FRONT_BACK) - CLAW_FRONT_THREASHOLD;
            create_drive_straight((int) (-DRIVE_SPEED * difference / 500.0));
            while (analog(CLAW_FRONT_BACK) > CLAW_FRONT_THREASHOLD) {
                difference = analog(CLAW_FRONT_BACK) - CLAW_FRONT_THREASHOLD;
                create_drive_straight((int) (-DRIVE_SPEED * difference / 500.0));

            }
            create_drive_straight(0);
        } else {

            int difference = CLAW_FRONT_THREASHOLD - analog(CLAW_FRONT_BACK);
            create_drive_straight((int)(DRIVE_SPEED * difference / 500.0));
            while (analog(CLAW_FRONT_BACK) < CLAW_FRONT_THREASHOLD) {
                difference = CLAW_FRONT_THREASHOLD - analog(CLAW_FRONT_BACK);
                create_drive_straight((int)(DRIVE_SPEED * difference / 500.0));
            }
            create_drive_straight(0);
        }


        if (analog(CLAW_LEFT_RIGHT) > CLAW_LEFT_THREASHOLD) {
            int difference = -1 * (CLAW_LEFT_THREASHOLD - analog(CLAW_LEFT_RIGHT));
            create_spin_CW((int)(SPIN_SPEED * difference / 500.0));
            while (analog(CLAW_LEFT_RIGHT) > CLAW_LEFT_THREASHOLD) {
                difference = -1 * (CLAW_LEFT_THREASHOLD - analog(CLAW_LEFT_RIGHT));
                create_spin_CW((int)(SPIN_SPEED * difference / 500.0));

            }
            create_drive_straight(0);
        } else {
            int difference = (CLAW_LEFT_THREASHOLD - analog(CLAW_LEFT_RIGHT));
            create_spin_CW((int)(-SPIN_SPEED * difference / 500.0));

            while (analog(CLAW_LEFT_RIGHT) < CLAW_LEFT_THREASHOLD) {
                difference = (CLAW_LEFT_THREASHOLD - analog(CLAW_LEFT_RIGHT));
                create_spin_CW((int)(-SPIN_SPEED * difference / 500.0));

            }
            create_drive_straight(0);
        }
    }
    move_claw_amount(CLAW_OPEN_AMOUNT);


    return 0;
}


