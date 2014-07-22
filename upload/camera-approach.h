/* 
 * File:   camera-approach.h
 * Author: Henry
 *
 * Created on July 14, 2014, 9:08 AM
 */

#ifndef CAMERA_APPROACH_H
#define	CAMERA_APPROACH_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#include <sys/time.h>

#include "Constants.h"
#include "claw-utils.h"
#include "drive-utils.h"



#define CUBE_SIZE_DIFFERENCE .3


#define AREA_MISSMATCH_TOLERANCE 19
#define X_MISSMATCH_TOLERANCE 20

#define SLEEP_TIME 10

#define DRIVE_TOLERANCE 15
#define CUBE_APPROACH_EXTRA_OFFSET 0
#define APPROACH_TOLERANCE 10

#define ARC_TURN_RADIUS_CONSTANT 50000 // 75000

#define MOTOR_POWER_LEVEL_MULTIPLIER 2

    struct timeval startTime;
    struct timeval currentTime;

    long getElapsedTimeMS();

    int average(int i1, int i2, int i3);
    int arrAverage(int* arr, int length);
    int preformApproachBotguy(bool leftCube, int channelNum);

    int preformApproachBotguy(bool leftCube, int channelNum) {
        bool possibleApproach = false;

        int objX[3] = {0, 0, 0};
        int objArea[3] = {0, 0, 0};

        int objDataIndex = 0;
        bool objDataInitialized = false;

        int xSum = 0;
        int xEarlySum = 0;
        
        gettimeofday(&startTime, NULL);

        while (true) {


            camera_update();
            msleep(SLEEP_TIME);
            // **** GET NEW VALUE ****
            if (get_object_count(channelNum) > 1) {
                
                int lobj0Area = get_object_area(channelNum, 0);
                int lobj1Area = get_object_area(channelNum, 1);
                int lobj1X = get_object_center_x(channelNum, 1) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
                int lobj0X = get_object_center_x(channelNum, 0) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
                if (lobj0Area - lobj1Area < CUBE_SIZE_DIFFERENCE * lobj0Area) {
                    printf("Detecting two cubes, going with one on right.  Areas are: %i, %i.  Xs are: %i, %i.\n", lobj0Area, lobj1Area, lobj0X, lobj1X);
                    if (leftCube ? lobj0X < lobj1X : lobj0X > lobj1X) {
                        //Go with object 0
                        objX[objDataIndex] = lobj0X;
                        objArea[objDataIndex] = lobj0Area;
                    } else {
                        //Go with object 1
                        objX[objDataIndex] = lobj1X;
                        objArea[objDataIndex] = lobj1Area;
                    }
                } else {
                    objArea[objDataIndex] = get_object_area(channelNum, 0);
                    objX[objDataIndex] = get_object_center_x(channelNum, 0) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
                }
            } else if (get_object_count(channelNum) > 0) {
                objArea[objDataIndex] = get_object_area(channelNum, 0);
                objX[objDataIndex] = get_object_center_x(channelNum, 0) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
            } else {
                printf("did not find object\n");
                continue;
            }

            // **** UPDATE DATA COUNTER ****
            if (!objDataInitialized) {
                objX[1] = objX[2] = objX[0];
                objArea[1] = objArea[2] = objArea[0];
                objDataInitialized = true;
            }
            objDataIndex = (objDataIndex + 1) % 3;

            // **** ADJUST CALIBRATION ****
            int averageArea = arrAverage(objArea, 3);
            if (abs(averageArea - objArea[0]) / averageArea > AREA_MISSMATCH_TOLERANCE || abs(averageArea - objArea[1]) / averageArea > AREA_MISSMATCH_TOLERANCE || abs(averageArea - objArea[2]) / averageArea > AREA_MISSMATCH_TOLERANCE) {
                printf("Area mismatch: a1, a2, a3: %i, %i, %i\n", objArea[0], objArea[1], objArea[2]);
                continue;
            }
            printf("area consistent at: %i\n", averageArea);

            int averageX = arrAverage(objX, 3);
            if (abs(averageX - objX[0]) > X_MISSMATCH_TOLERANCE || abs(averageX - objX[1]) > X_MISSMATCH_TOLERANCE || abs(averageX - objX[2]) > X_MISSMATCH_TOLERANCE) {
                printf("X mismatch: a1, a2, a3: %i, %i, %i\n", objX[0], objX[1], objX[2]);
                continue;
            }
            printf("X consistent at: %i\n", averageX);

            xSum += averageX;
            if (averageArea < 1800) {
                xEarlySum += averageX;
            }
            
            gettimeofday(&currentTime, NULL);
            
            if (getElapsedTimeMS() > 4000) {
                possibleApproach = true;
            }
            if (possibleApproach) {
                printf("initial approach complete.\n"); /////EXIT POINT
                driveStraight();
                raise_botguy_to(BOTGUY_CLAW_MID_UP);
                msleep(300);
                raise_botguy_to(BOTGUY_CLAW_DOWN);
                msleep(300);
                
                struct timeval that_start_time;
                gettimeofday(&that_start_time, NULL);
                struct timeval that_end_time;
                gettimeofday(&that_end_time, NULL);
                while (that_end_time.tv_sec - that_start_time.tv_sec < 2 && analog(0) > 500) {//            !!!!!!!!!!!!!!!!!was 840
                    gettimeofday(&that_end_time, NULL);
                }
                
                printf("xsum: %i\n", xSum);
                printf("xearly sum: %i\n", xEarlySum);
                //msleep(800);
                stop();
                close_botguy_claw();
                hold_botguy_claw_closed();
                //msleep(1000);
                //raise_botguy_to(BOTGUY_CLAW_UP);
                //motor(0, 4);  //Close the claw continuously around obj.
                printf("finished final approach routeen.\n");
                return xSum;
            }

            if (abs(averageX) < DRIVE_TOLERANCE) {
                driveSlow();
            } else if (averageX < 0) {
                //averageX is negative.
                //motor(BOTGUY_MOTOR_LEFT, (LEFT_WHEEL_POWER - averageX * MOTOR_POWER_LEVEL_MULTIPLIER));
                //motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER);
                motor(BOTGUY_MOTOR_LEFT, (LEFT_WHEEL_POWER) / 2);
                motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER);
                //create_drive(-60, (double) ARC_TURN_RADIUS_CONSTANT / (double) averageX);
            } else {
                //positive radius
                //create_drive(-60, (double) ARC_TURN_RADIUS_CONSTANT / (double) averageX);
                motor(BOTGUY_MOTOR_LEFT, (LEFT_WHEEL_POWER));
                motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER / 2);
                /*motor(BOTGUY_MOTOR_LEFT, LEFT_WHEEL_POWER);
                motor(BOTGUY_MOTOR_RIGHT, (RIGHT_WHEEL_POWER + averageX * MOTOR_POWER_LEVEL_MULTIPLIER));*/
            }

        }

        printf("APPROACH FAILED!\n");

        //printf("area: %i", get_object_area(0,0));
        /*
        raise_claw_to(CLAW_UP_POSITION);
        enable_servos();
        while (!digital(15)) {}
        move_claw_amount(CLAW_CLOSE_AMOUNT);*/
        //openingRouteen();
        //thirdRouteen();
        //move_claw_amount(CLAW_CLOSE_AMOUNT);
        //disable_servos();
        return (xSum);
    }
    
    
    int preformApproachCube(bool leftCube, int channelNum) {
        bool possibleApproach = false;

        int objX[3] = {0, 0, 0};
        int objArea[3] = {0, 0, 0};

        int objDataIndex = 0;
        bool objDataInitialized = false;

        int xSum = 0;
        int xEarlySum = 0;
        
        gettimeofday(&startTime, NULL);

        while (true) {


            camera_update();
            msleep(SLEEP_TIME);
            // **** GET NEW VALUE ****
            if (get_object_count(channelNum) > 1) {
                int lobj0Area = get_object_area(channelNum, 0);
                int lobj1Area = get_object_area(channelNum, 1);
                int lobj1X = get_object_center_x(channelNum, 1) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
                int lobj0X = get_object_center_x(channelNum, 0) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
                if (lobj0Area - lobj1Area < CUBE_SIZE_DIFFERENCE * lobj0Area) {
                    printf("Detecting two cubes, going with one on right.  Areas are: %i, %i.  Xs are: %i, %i.\n", lobj0Area, lobj1Area, lobj0X, lobj1X);
                    if (leftCube ? lobj0X < lobj1X : lobj0X > lobj1X) {
                        //Go with object 0
                        objX[objDataIndex] = lobj0X;
                        objArea[objDataIndex] = lobj0Area;
                    } else {
                        //Go with object 1
                        objX[objDataIndex] = lobj1X;
                        objArea[objDataIndex] = lobj1Area;
                    }
                } else {
                    objArea[objDataIndex] = get_object_area(channelNum, 0);
                    objX[objDataIndex] = get_object_center_x(channelNum, 0) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
                }
            } else if (get_object_count(channelNum) > 0) {
                objArea[objDataIndex] = get_object_area(channelNum, 0);
                objX[objDataIndex] = get_object_center_x(channelNum, 0) - get_camera_width() / 2 + CUBE_APPROACH_EXTRA_OFFSET;
            } else {
                printf("did not find object\n");
                continue;
            }

            // **** UPDATE DATA COUNTER ****
            if (!objDataInitialized) {
                objX[1] = objX[2] = objX[0];
                objArea[1] = objArea[2] = objArea[0];
                objDataInitialized = true;
            }
            objDataIndex = (objDataIndex + 1) % 3;

            // **** ADJUST CALIBRATION ****
            int averageArea = arrAverage(objArea, 3);
            if (abs(averageArea - objArea[0]) / averageArea > AREA_MISSMATCH_TOLERANCE || abs(averageArea - objArea[1]) / averageArea > AREA_MISSMATCH_TOLERANCE || abs(averageArea - objArea[2]) / averageArea > AREA_MISSMATCH_TOLERANCE) {
                printf("Area mismatch: a1, a2, a3: %i, %i, %i\n", objArea[0], objArea[1], objArea[2]);
                continue;
            }
            printf("area consistent at: %i\n", averageArea);

            int averageX = arrAverage(objX, 3);
            if (abs(averageX - objX[0]) > X_MISSMATCH_TOLERANCE || abs(averageX - objX[1]) > X_MISSMATCH_TOLERANCE || abs(averageX - objX[2]) > X_MISSMATCH_TOLERANCE) {
                printf("X mismatch: a1, a2, a3: %i, %i, %i\n", objX[0], objX[1], objX[2]);
                continue;
            }
            printf("X consistent at: %i\n", averageX);

            xSum += averageX;
            if (averageArea < 700) {
                xEarlySum += averageX;
            }
            
            gettimeofday(&currentTime, NULL);
            
            if (getElapsedTimeMS() > 4000) {
                possibleApproach = true;
            }
            if (possibleApproach) {
                printf("initial approach complete.\n"); /////EXIT POINT
                driveStraight();
                struct timeval that_start_time;
                gettimeofday(&that_start_time, NULL);
                struct timeval that_end_time;
                gettimeofday(&that_end_time, NULL);
                while (that_end_time.tv_sec - that_start_time.tv_sec < 3 && analog(0) > 500) {//            !!!!!!!!!!!!!!!!!was 840
                    gettimeofday(&that_end_time, NULL);
                }
                printf("xsum: %i\n", xSum);
                printf("xearly sum: %i\n", xEarlySum);
                //msleep(800);
                stop();
                //close_botguy_claw();
                
                //motor(0, 4);  //Close the claw continuously around obj.
                printf("finished final approach routeen.\n");
                return xSum;
            }

            if (abs(averageX) < DRIVE_TOLERANCE) {
                driveSlow();
            } else if (averageX < 0) {
                //averageX is negative.
                //motor(BOTGUY_MOTOR_LEFT, (LEFT_WHEEL_POWER - averageX * MOTOR_POWER_LEVEL_MULTIPLIER));
                //motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER);
                motor(BOTGUY_MOTOR_LEFT, (LEFT_WHEEL_POWER) / 2);
                motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER);
                //create_drive(-60, (double) ARC_TURN_RADIUS_CONSTANT / (double) averageX);
            } else {
                //positive radius
                //create_drive(-60, (double) ARC_TURN_RADIUS_CONSTANT / (double) averageX);
                motor(BOTGUY_MOTOR_LEFT, (LEFT_WHEEL_POWER));
                motor(BOTGUY_MOTOR_RIGHT, RIGHT_WHEEL_POWER / 2);
                /*motor(BOTGUY_MOTOR_LEFT, LEFT_WHEEL_POWER);
                motor(BOTGUY_MOTOR_RIGHT, (RIGHT_WHEEL_POWER + averageX * MOTOR_POWER_LEVEL_MULTIPLIER));*/
            }

        }

        printf("APPROACH FAILED!\n");

        //printf("area: %i", get_object_area(0,0));
        /*
        raise_claw_to(CLAW_UP_POSITION);
        enable_servos();
        while (!digital(15)) {}
        move_claw_amount(CLAW_CLOSE_AMOUNT);*/
        //openingRouteen();
        //thirdRouteen();
        //move_claw_amount(CLAW_CLOSE_AMOUNT);
        //disable_servos();
        return (xSum);
    }
    
    
    
    

    int average(int i1, int i2, int i3) {
        return (i1 + i2 + i3) / 3;
    }

    int arrAverage(int* arr, int length) {
        int avr = 0;
        for (int i = 0; i < length; i++) {
            avr += arr[i];
        }
        return avr / length;
    }

    void clearCamera() {
        int n = 0;
        while (n < 10) {
            camera_update();
            msleep(500);
            n++;

        }
    }

    long getMS(struct timeval time) {
        return time.tv_sec * 1000 + time.tv_usec / 1000;
    }

    long getElapsedTimeMS() {
        return getMS(currentTime) - getMS(startTime);
    }

#ifdef	__cplusplus
}
#endif

#endif	/* CAMERA_APPROACH_H */

