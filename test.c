/* 
 * File:   test.c
 * Author: Henry
 *
 * Created on April 3, 2014, 5:10 PM
 */

#include <stdlib.h>
#include <stdio.h>
#include <kovan/kovan.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <libusb-1.0/libusb.h>

#include "claw-utils.h"

/*
 * 
 */

#define CUBE_SIZE_DIFFERENCE .3


#define AREA_MISSMATCH_TOLERANCE 19
#define X_MISSMATCH_TOLERANCE 20

#define SLEEP_TIME 30

#define DRIVE_TOLERANCE 15

#define APPROACH_TOLERANCE 10

int average(int i1, int i2, int i3);

void openingRouteen() {
    create_drive_straight(0);
    create_drive_straight(-300);
    msleep(851);
    create_drive_straight(0);
    create_spin_CW(150);
    msleep(1291);
    create_drive_straight(0);
    create_drive_straight(-140);
    
    while (!digital(15)) {
        
    }
    
    //msleep(2031); //This block shoud be replcaed with a touch sensor check
    
    create_drive_straight(0);
    move_claw_amount(CLAW_CLOSE_AMOUNT);
}

void secondRouteen() {

create_drive_straight(0);

create_drive_straight(300);

msleep(511);

create_drive_straight(0);

create_spin_CCW(150);

msleep(1180);

create_drive_straight(0);

create_drive_straight(-300);

msleep(6500);

create_drive_straight(0);

create_drive_straight(300);

msleep(311);

create_drive_straight(0);

create_spin_CW(150);

msleep(1260);

create_drive_straight(0);

create_drive_straight(-300);

msleep(1080);

create_drive_straight(0);

}


void thirdRouteen() {
    create_drive_straight(0);

create_drive_straight(300);

msleep(1129);

create_drive_straight(0);

raise_claw_to(500);

create_drive_straight(0);

create_spin_CCW(150);

msleep(2472);

create_drive_straight(0);

create_drive_straight(-300);

msleep(661);

create_drive_straight(0);

move_claw_amount(-CLAW_CLOSE_AMOUNT);

create_drive_straight(0);

}

int main(int argc, char** argv) {
    create_connect();
    create_drive_straight(0);
    raise_claw_to(CLAW_UP_POSITION);
    enable_servos();
    msleep(2000);
    printf("camera open response: %i\n", camera_open());
    bool possibleApproach = false;
    while (true) {
        msleep(SLEEP_TIME);
        camera_update();
        int obj1Area, obj1X;
        if (get_object_count(0) > 1) {
            int lobj0Area = get_object_area(0,0);
            int lobj1Area = get_object_area(0,1);
            int lobj1X = get_object_center_x(0,1) - get_camera_width() / 2;
            int lobj0X = get_object_center_x(0,0) - get_camera_width() / 2;
            if (lobj0Area - lobj1Area < CUBE_SIZE_DIFFERENCE * lobj0Area) {
                printf("Detecting two cubes, going with one on left.  Areas are: %i, %i.  Xs are: %i, %i.\n", lobj0Area, lobj1Area, lobj0X, lobj1X);
                if (lobj0X < lobj1X) {
                    //Go with object 0
                    obj1X = lobj0X;
                    obj1Area = lobj0Area;
                } else {
                    //Go with object 1
                    
                    obj1X = lobj1X;
                    obj1Area = lobj1Area;
                }
            } else {
                obj1Area = get_object_area(0, 0);
                obj1X = get_object_center_x(0, 0) - get_camera_width() / 2;
            }
        } else if (get_object_count(0) > 0) {
            obj1Area = get_object_area(0,0);
            obj1X = get_object_center_x(0,0) - get_camera_width() / 2;
        } else {
            printf("did not find object\n");
            continue;
        }
        msleep(SLEEP_TIME);
        camera_update();
        
        int obj2Area, obj2X;
        if (get_object_count(0) > 1) {
            int lobj0Area = get_object_area(0,0);
            int lobj1Area = get_object_area(0,1);
            int lobj1X = get_object_center_x(0,1) - get_camera_width() / 2;
            int lobj0X = get_object_center_x(0,0) - get_camera_width() / 2;
            if (lobj0Area - lobj1Area < CUBE_SIZE_DIFFERENCE * lobj0Area) {
                printf("Detecting two cubes, going with one on left.  Areas are: %i, %i.  Xs are: %i, %i.\n", lobj0Area, lobj1Area, lobj0X, lobj1X);
                if (lobj0X < lobj1X) {
                    //Go with object 0
                    obj2X = lobj0X;
                    obj2Area = lobj0Area;
                } else {
                    //Go with object 1
                    
                    obj2X = lobj1X;
                    obj2Area = lobj1Area;
                }
            } else {
                obj2Area = get_object_area(0, 0);
                obj2X = get_object_center_x(0, 0) - get_camera_width() / 2;
            }
        } else if (get_object_count(0) > 0) {
            obj2Area = get_object_area(0,0);
            obj2X = get_object_center_x(0,0) - get_camera_width() / 2;
        } else {
            printf("did not find object\n");
            continue;
        }
        msleep(SLEEP_TIME);
        camera_update();
        int obj3Area, obj3X;
        
        
        
        if (get_object_count(0) > 1) {
            int lobj0Area = get_object_area(0,0);
            int lobj1Area = get_object_area(0,1);
            int lobj1X = get_object_center_x(0,1) - get_camera_width() / 2;
            int lobj0X = get_object_center_x(0,0) - get_camera_width() / 2;
            if (lobj0Area - lobj1Area < CUBE_SIZE_DIFFERENCE * lobj0Area) {
                printf("Detecting two cubes, going with one on left.  Areas are: %i, %i.  Xs are: %i, %i.\n", lobj0Area, lobj1Area, lobj0X, lobj1X);
                if (lobj0X < lobj1X) {
                    //Go with object 0
                    obj3X = lobj0X;
                    obj3Area = lobj0Area;
                } else {
                    //Go with object 1
                    
                    obj3X = lobj1X;
                    obj3Area = lobj1Area;
                }
            } else {
                obj3Area = get_object_area(0, 0);
                obj3X = get_object_center_x(0, 0) - get_camera_width() / 2;
            }
        } else if (get_object_count(0) > 0) {
            obj3Area = get_object_area(0,0);
            obj3X = get_object_center_x(0,0) - get_camera_width() / 2;
        } else {
            printf("did not find object\n");
            continue;
        }
        
        
        int averageArea = average(obj1Area, obj2Area, obj3Area);
        if (abs(averageArea - obj1Area) / averageArea >  AREA_MISSMATCH_TOLERANCE || abs(averageArea - obj2Area) / averageArea >  AREA_MISSMATCH_TOLERANCE || abs(averageArea - obj3Area) / averageArea >  AREA_MISSMATCH_TOLERANCE) {
            printf("Area mismatch: a1, a2, a3: %i, %i, %i\n", obj1Area, obj2Area, obj3Area);
            continue;
        }
        printf("area consistant at: %i\n", averageArea);
        
        int averageX = average(obj1X, obj2X, obj3X);
        
        if (abs(averageX - obj1X) >  X_MISSMATCH_TOLERANCE || abs(averageX - obj2X) >  X_MISSMATCH_TOLERANCE || abs(averageX - obj3X) >  X_MISSMATCH_TOLERANCE) {
            printf("X mismatch: a1, a2, a3: %i, %i, %i\n", obj1X, obj2X, obj3X);
            continue;
        }
        printf("X consistant at: %i\n", averageX);
        
        
        
        
        
        
        if (averageArea > 2000) {
            possibleApproach = true;
        }
        if (possibleApproach) {
            printf("initial approach complete.\n");
            printf("finished final approach routeen.\n");
            create_drive_straight(-60);
            while (analog(0) > 800) {
            }

            msleep(1000);
            create_drive_straight(0);
            move_claw_amount(CLAW_CLOSE_AMOUNT);
            return 0; 
        }
        
        if (abs(averageX) < DRIVE_TOLERANCE) {
            create_drive_straight(-60);
        } else if (averageX < 0) {
            create_drive(-60, (double)75000 / (double)averageX );
        } else {
            //positive radius
            create_drive(-60, (double)75000 / (double)averageX);
        }
        if (get_create_lbump() || get_create_rbump()) {
            break;
        }
    }
    
    camera_close();
    
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
    return (EXIT_SUCCESS);
}

int average(int i1, int i2, int i3) {
    return (i1 + i2 + i3) / 3;
}