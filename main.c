/* 
 * File:   main.c
 * Author: Jake
 *
 * Created on April 25, 2014, 4:58 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <kovan/kovan.h>
#include <stdbool.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

void drive_direct(int a, int b);
void drive_straight(int speed);
void drive_spin(int speed);

/*
 * 
 */
int main(int argc, char** argv) {
    
    shut_down_in(120000);
    
    drive_straight(80);
    msleep(4000);
    
    drive_spin(50);
    msleep(500);
    
    drive_straight(100);
    msleep(10000);
    
    drive_spin(50);
    msleep(500);
    
    drive_straight(100);
    msleep(5000);
    
    drive_direct(20, 100);
    while (true) {}
    
    return (EXIT_SUCCESS);
}

void drive_direct(int a, int b) {
    motor(2, a);
    motor(3, b);
}

void drive_straight(int speed) {
    drive_direct(speed, speed);
}

void drive_spin(int speed) {
    drive_direct(speed, -speed);
}

