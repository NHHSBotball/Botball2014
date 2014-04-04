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

/*
 * 
 */
int main(int argc, char** argv) {
    create_connect();
    create_drive_straight(0);

create_drive_straight(-300);

msleep(3140);

create_drive_straight(0);

create_spin_CW(150);

msleep(2860);

create_drive_straight(0);

create_drive_straight(-300);

msleep(3230);

create_drive_straight(0);

create_spin_CCW(150);

msleep(1220);

create_drive_straight(0);

create_drive_straight(-300);

msleep(480);

create_drive_straight(0);

create_spin_CCW(150);

msleep(1571);

create_drive_straight(0);

    return (EXIT_SUCCESS);
}

