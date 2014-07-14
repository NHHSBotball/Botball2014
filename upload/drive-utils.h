/* 
 * File:   drive-utils.h
 * Author: Henry
 *
 * Created on June 27, 2014, 9:59 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#ifndef DRIVE_UTILS_H
#define	DRIVE_UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TPS_TOLERANCE_MARGEN 100
#define MOTOR_SPEED_INCREMENT 1

#define BOTGUY_MOTOR_LEFT 0
#define BOTGUY_MOTOR_RIGHT 1

#define LEFT_WHEEL_POWER 83
#define RIGHT_WHEEL_POWER -79

    void driveStraight() {
        //motor(BOTGUY_MOTOR_LEFT, 0);
        //motor(BOTGUY_MOTOR_RIGHT, 0);
        motor(BOTGUY_MOTOR_LEFT, LEFT_WHEEL_POWER);
        motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER);
    }
    
    void driveSlow() {
        
        motor(BOTGUY_MOTOR_LEFT, LEFT_WHEEL_POWER / 2 + 11);
        motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER / 2);
    }
    
    void driveBackward() {

        motor(BOTGUY_MOTOR_LEFT, -LEFT_WHEEL_POWER);
        motor(BOTGUY_MOTOR_RIGHT, -RIGHT_WHEEL_POWER);
    }
    void stop() {
        
        motor(BOTGUY_MOTOR_LEFT, 0);
        motor(BOTGUY_MOTOR_RIGHT, 0);
    }

    double measureTicksPerASecond(int motor, int tickCount) {
        struct timeval start_time;
        struct timeval stop_time;

        clear_motor_position_counter(motor);
        gettimeofday(&start_time, NULL);

        int motorPos = get_motor_position_counter(motor);
        if (tickCount > 0) {
            while (motorPos < tickCount) {
                motorPos = get_motor_position_counter(motor);
            }
        } else {
            while (motorPos > tickCount) {
                motorPos = get_motor_position_counter(motor);
            }
        }
        gettimeofday(&stop_time, NULL);
        double travelTime = (stop_time.tv_sec + (double) stop_time.tv_usec / 1000000.0) - (start_time.tv_sec + (double) start_time.tv_usec / 1000000.0);
        double secondsPerATick = travelTime / tickCount;
        return 1 / secondsPerATick;
    }

    double getTicksPerASecond(int motorNum) {
        return measureTicksPerASecond(motorNum, 300);
    }

    int gmotorNum1 = -1, gmotorNum2 = -1, gticksPerASecond = -1, gstartingMotorPower = -1;

    void trueMavRunner() {
        int startingMotorPower = gstartingMotorPower;
        int ticksPerASecond = gticksPerASecond;
        int motorNum1 = gmotorNum1;
        int motorNum2 = gmotorNum2;
        int currentMotorPower1 = startingMotorPower;
        int currentMotorPower2 = startingMotorPower;
        int tps = 0;
        while (true) {

            tps = getTicksPerASecond(motorNum1);
            if (tps + TPS_TOLERANCE_MARGEN < ticksPerASecond) {
                printf("making ajustment1+\n");
                currentMotorPower1 += MOTOR_SPEED_INCREMENT;
                motor(motorNum1, currentMotorPower1);
                motor(motorNum2, currentMotorPower2);
                msleep(250);
            } else if (tps - TPS_TOLERANCE_MARGEN > ticksPerASecond) {
                currentMotorPower1 -= MOTOR_SPEED_INCREMENT;
                printf("making ajustment1-\n");
                motor(motorNum1, currentMotorPower1);
                motor(motorNum2, currentMotorPower2);
                msleep(250);
            }
            tps = getTicksPerASecond(motorNum2);
            if (tps + TPS_TOLERANCE_MARGEN < ticksPerASecond) {
                printf("making ajustment2+\n");
                currentMotorPower2 += MOTOR_SPEED_INCREMENT;
                motor(motorNum1, currentMotorPower1);
                motor(motorNum2, currentMotorPower2);
                msleep(250);
            } else if (tps - TPS_TOLERANCE_MARGEN > ticksPerASecond) {
                currentMotorPower2 -= MOTOR_SPEED_INCREMENT;
                printf("making ajustment2-\n");
                motor(motorNum1, currentMotorPower1);
                motor(motorNum2, currentMotorPower2);
                msleep(250);
            }
        }
    }

    thread trueMav(int motorNum1, int motorNum2, int ticksPerASecond) {

        thread t = thread_create(trueMavRunner);
        gmotorNum1 = motorNum1;
        gmotorNum2 = motorNum2;
        gticksPerASecond = ticksPerASecond;
        gstartingMotorPower = ticksPerASecond * 100 / 1200;
        motor(motorNum1, ticksPerASecond * 100 / 1200);
        motor(motorNum2, ticksPerASecond * 100 / 1200);
        thread_start(t);
        return t;
    }



#ifdef	__cplusplus
}
#endif

#endif	/* DRIVE_UTILS_H */

