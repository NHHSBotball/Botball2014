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
    
#define CLAW_CLOSE_AMOUNT 700
#define CLAW_OPEN_AMOUNT -200

#define CLAW_UP_POSITION 1300
#define CLAW_MIDDLE_POSITION 600

    
void raw_raise_claw_to(int pos) {
        set_servo_position(0, pos);
        set_servo_position(1, pos);
        set_servo_position(2, 2047 - pos);
        set_servo_position(3, 2047 - pos);
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

