/* 
 * File:   calibrate.c
 * Author: Henry
 *
 * Created on July 11, 2014, 11:24 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#include <sys/time.h>

#include "Constants.h"
#include "claw-utils.h"
#include "drive-utils.h"

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Starting both motors at 75 power.\n");
    motor(BOTGUY_MOTOR_LEFT, 75);
    motor(BOTGUY_MOTOR_RIGHT, -75);
    int leftTPS = measureTicksPerASecond(BOTGUY_MOTOR_LEFT, 5000);
    int rightTPS = -measureTicksPerASecond(BOTGUY_MOTOR_RIGHT, -5000);
    bool leftWeelIncrease = false;
    if (leftTPS < rightTPS) {
        leftWeelIncrease = true;
    }

    int leftPower = 75, rightPower = -75;

    while (true) {
        if (leftWeelIncrease) {
            leftPower += 1;
            printf("increasing left wheel power to: %i.\n", leftPower);
        }
        else {
            rightPower -= 1;
            printf("increasing right wheel power to: %i.\n", rightPower);
        }
        motor(BOTGUY_MOTOR_LEFT, leftPower);
        motor(BOTGUY_MOTOR_RIGHT, rightPower);
        
        msleep(500);
        leftTPS = measureTicksPerASecond(BOTGUY_MOTOR_LEFT, 5000);
        rightTPS = -measureTicksPerASecond(BOTGUY_MOTOR_RIGHT, -5000);
        printf("current left TPS: %i  current right TPS: %i\n", leftTPS, rightTPS);
        if (leftWeelIncrease && leftTPS > rightTPS) {
            printf("found ideal motor speed and passed it (this run or the last run was right) (left wheel increase mode).\n");
            break;
        } else if (!leftWeelIncrease && leftTPS < rightTPS) {
            printf("found ideal motor speed and passed it (this run or the last run was right) (right wheel increase mode).\n");
           
            break;
        }
    }
    printf("final powers: left: %i, right:%i.\n", leftPower, rightPower);
    return (EXIT_SUCCESS);
}

