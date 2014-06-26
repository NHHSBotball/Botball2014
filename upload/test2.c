#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#include <sys/time.h>

#include "Constants.h"
#include "claw-utils.h"


#define DRIVE_SPEED_FORWARD -7
#define DRIVE_SPEED_BACKWARD 11

#define SPIN_SPEED 3

int main(int argc, char** argv) {
    printf("starting\n");
    motor(0, 5);
    msleep(1000);
    raise_claw_to(400);
    enable_servos();
    create_connect();
    printf("create connected\n");
    create_drive_straight(0);
    //move_claw_amount(CLAW_CLOSE_AMOUNT);
    //motor(0, 5);
    msleep(1000);
    raise_claw_to(410);
    struct timeval current_time;
    struct timeval start_time;
    gettimeofday(&start_time, NULL);
    while (true) {
        if (abs(analog(CLAW_FRONT_BACK) - CLAW_FRONT_THREASHOLD) < TOLERANCE_MARGEN && abs(analog(CLAW_LEFT_RIGHT) - CLAW_LEFT_THREASHOLD) < TOLERANCE_MARGEN) {
            printf("value out of all loops\n");
            break;
        }
        while (true) {
            gettimeofday(&current_time, NULL);
            if (current_time.tv_usec - start_time.tv_usec > 10000000) {
                printf("time out\n");
                break;
            }
            if (abs(analog(CLAW_FRONT_BACK) - CLAW_FRONT_THREASHOLD) < TOLERANCE_MARGEN) {
                printf("value out\n");
                break;
            }

            int driveTime;
            bool firstTime = true;
            if (analog(CLAW_FRONT_BACK) > CLAW_FRONT_THREASHOLD) {
                printf("1front back drive forward: %i\n", analog(CLAW_FRONT_BACK));
                create_drive_straight(DRIVE_SPEED_FORWARD);
                if (firstTime) {
                    while (analog(CLAW_FRONT_BACK) > CLAW_FRONT_THREASHOLD + TOLERANCE_MARGEN) {

                        printf("front back drive forward: %i\n", analog(CLAW_FRONT_BACK));
                    }
                    create_drive_straight(0);
                } else {
                    struct timeval drive_start;
                    gettimeofday(&drive_start, NULL);
                    printf("driving half of last time and breaking out\n");
                    struct timeval drive_current;
                    gettimeofday(&drive_current, NULL);
                    while (drive_start.tv_usec - drive_current.tv_usec < driveTime / 2) {
                        gettimeofday(&drive_current, NULL);
                    }
                    create_drive_straight(0);
                    break;
                }

            } else {
                firstTime = false;
                printf("1front back drive beckward: %i\n", analog(CLAW_FRONT_BACK));
                struct timeval drive_start;

                struct timeval drive_finish;


                gettimeofday(&drive_start, NULL);
                create_drive_straight(DRIVE_SPEED_BACKWARD);
                while (analog(CLAW_FRONT_BACK) + TOLERANCE_MARGEN < CLAW_FRONT_THREASHOLD) {
                    printf("front back drive beckward: %i\n", analog(CLAW_FRONT_BACK));
                }
                gettimeofday(&drive_finish, NULL);
                create_drive_straight(0);
                driveTime = drive_finish.tv_usec - drive_start.tv_usec;
            }
        }
        if (abs(analog(CLAW_FRONT_BACK) - CLAW_FRONT_THREASHOLD) < TOLERANCE_MARGEN && abs(analog(CLAW_LEFT_RIGHT) - CLAW_LEFT_THREASHOLD) < TOLERANCE_MARGEN) {
            printf("value out of all loops\n");
            break;
        }
        while (true) {
            gettimeofday(&current_time, NULL);
            if (current_time.tv_usec - start_time.tv_usec > 10000000) {
                printf("time out\n");
                break;
            }
            if (abs(analog(CLAW_LEFT_RIGHT) - CLAW_LEFT_THREASHOLD) < TOLERANCE_MARGEN) {
                printf("value out\n");
                break;
            }
            if (analog(CLAW_LEFT_RIGHT) > CLAW_LEFT_THREASHOLD) {
                printf("1left right drive forward: %i\n", analog(CLAW_LEFT_RIGHT));
                create_spin_CW(SPIN_SPEED);
                while (analog(CLAW_LEFT_RIGHT) > CLAW_LEFT_THREASHOLD + TOLERANCE_MARGEN) {
                    create_spin_CW(SPIN_SPEED);
                    printf("left right drive forward: %i\n", analog(CLAW_LEFT_RIGHT));
                }
                create_drive_straight(0);
            } else {
                //drive forward block
                printf("1left right drive beckward: %i\n", analog(CLAW_LEFT_RIGHT));
                create_spin_CW(-SPIN_SPEED);
                while (analog(CLAW_LEFT_RIGHT) + TOLERANCE_MARGEN < CLAW_LEFT_THREASHOLD) {
                    create_spin_CW(-SPIN_SPEED);
                    printf("left right drive beckward: %i\n", analog(CLAW_LEFT_RIGHT));
                }
                create_drive_straight(0);
            }
        }
    }

    /*if (analog(CLAW_LEFT_RIGHT) > CLAW_LEFT_THREASHOLD) {
        int difference = -1 * (CLAW_LEFT_THREASHOLD - analog(CLAW_LEFT_RIGHT));
        create_spin_CW(SPIN_SPEED);
        while (analog(CLAW_LEFT_RIGHT)- TOLERANCE_MARGEN > CLAW_LEFT_THREASHOLD) {
            printf("left right: %i\n", analog(CLAW_LEFT_RIGHT));

        }
        create_drive_straight(0);
    } else {
        int difference = (CLAW_LEFT_THREASHOLD - analog(CLAW_LEFT_RIGHT));
        create_spin_CW(-SPIN_SPEED);

        while (analog(CLAW_LEFT_RIGHT) < CLAW_LEFT_THREASHOLD - TOLERANCE_MARGEN) {

            printf("left right: %i\n", analog(CLAW_LEFT_RIGHT));
        }
        create_drive_straight(0);
    }*/

    move_claw_amount(CLAW_OPEN_AMOUNT);


    return 0;
}


