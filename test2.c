#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>

#include "claw-utils.h"

int main(int argc, char** argv) {
   
    create_connect();
    create_drive_straight(-70);
    msleep(1700);
    move_claw_amount(-CLAW_CLOSE_AMOUNT);
    msleep(100);
    create_drive_straight(0);
    return 0;
}


