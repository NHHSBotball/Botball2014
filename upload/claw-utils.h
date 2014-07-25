/* 
 * File:   claw-utils.h
 * Author: Henry
 *
 * Created on April 8, 2014, 3:58 PM
 */

#ifndef CLAW_UTILS_H
#define	CLAW_UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <kovan/kovan.h>

#define CLAW_CLOSE_AMOUNT 400
#define CLAW_OPEN_AMOUNT -280

#define CLAW_UP_POSITION 450  //1300
#define CLAW_MIDDLE_POSITION 300  //350

#define BOTGUY_CLAW_PORT_LEFT 3
#define BOTGUY_CLAW_PORT_RIGHT 2
#define BOTGUY_GRAB_PORT 3

#define BOTGUY_CLAW_OPEN_AMOUNT -600
#define BOTGUY_CLAW_CLOSE_AMOUNT 900


#define BOTGUY_CLAW_DOWN 800
#define BOTGUY_CLAW_MID_UP 1000
#define BOTGUY_CLAW_UP 1400
#define BOTGUY_CLAW_FULL_UP 1750



#define CUBE_KNOCK_PORT 1  //Correct port is 1
#define CUBE_KNOCK_UP 1400
#define CUBE_KNOCK_UP2 1400
#define CUBE_KNOCK_DOWN 0   

    void raise_botguy_to(int rpos) {
        int lpos = rpos;
        set_servo_position(BOTGUY_CLAW_PORT_LEFT, 2047 - lpos);
        set_servo_position(BOTGUY_CLAW_PORT_RIGHT, rpos);
    }

    void move_botguy_claw_amount(int amount) {
        if (amount < 0) {
            motor(BOTGUY_GRAB_PORT, -100);
            msleep(-amount);
        } else {
            motor(BOTGUY_GRAB_PORT, 100);
            msleep(amount);
        }
        motor(BOTGUY_GRAB_PORT, 0);
    }

    void close_botguy_claw() {
        move_botguy_claw_amount(BOTGUY_CLAW_CLOSE_AMOUNT);
    }

    void open_botguy_claw() {
        move_botguy_claw_amount(BOTGUY_CLAW_OPEN_AMOUNT);
    }
    
    void hold_botguy_claw_closed() {
        motor(BOTGUY_GRAB_PORT, 40);
    }

    void raw_raise_claw_to(int pos) {
        set_servo_position(0, pos);
        //set_servo_position(1, pos);
        set_servo_position(2, 2047 - pos);
        //set_servo_position(3, 2047 - pos);
    }

    void raise_claw_to(int pos) {
        if (pos - get_servo_position(0) < -50) {
            raw_raise_claw_to(get_servo_position(0) - 50);
            msleep(100);
            raise_claw_to(pos);
        } else if (pos - get_servo_position(0) > 50) {
            raw_raise_claw_to(pos);

        } else {
            raw_raise_claw_to(pos);
        }
    }

    void move_claw_amount(int amount) {
        if (amount < 0) {
            motor(0, -100);
            msleep(-amount);
        } else {
            motor(0, 100);
            msleep(amount);
        }

        motor(0, 0);
    }



#ifdef	__cplusplus
}
#endif

#endif	/* CLAW_UTILS_H */

