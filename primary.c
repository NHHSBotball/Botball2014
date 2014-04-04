
#include <stdlib.h>
#include <stdio.h>
#include <kovan/kovan.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void move_claw_amount(int amount);
void raw_raise_claw_to(int pos);
void raise_claw_to(int pos);

int main(int argc, char** argv) {
    printf("starting v 5.\n");
    enable_servos();
    raw_raise_claw_to(0);
    //set_servos_enabled(true);
    int* val = malloc(sizeof(int));
    char cmd[50];
    while (true) {
        printf("read analog sensor val as: %i\n", analog10(0));
        scanf("%s %i", cmd, val);
        
        if (cmd[0] == 'c' || cmd[0] == 'C') {
        move_claw_amount(*val);
        } else if (cmd[0] == 's' || cmd[0] == 'S') {
            raise_claw_to(*val);
        }
    }
    return (EXIT_SUCCESS);
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

void raw_raise_claw_to(int pos) {
    
    printf("raising claw to: %i\n", pos);
        set_servo_position(0, pos);
        set_servo_position(1, pos);
        set_servo_position(2, 2047 - pos);
        set_servo_position(3, 2047 - pos);
}


void move_claw_amount(int amount) {
    printf("opening claw to: %i\n", amount);
    if (amount < 0) {
            motor(0, -100);
            msleep(-amount);
        } else {
            motor(0, 100);
            msleep(amount);
        }
    
        motor(0, 0);
}