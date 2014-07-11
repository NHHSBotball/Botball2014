#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>
#include <sys/time.h>

#include "Constants.h"
#include "claw-utils.h"
#include "drive-utils.h"


#define DRIVE_SPEED_FORWARD -7
#define DRIVE_SPEED_BACKWARD 11

#define SPIN_SPEED 3

int main(int argc, char** argv) {
    thread m0t = trueMav(0, 2, 500);
    msleep(100000);
    thread_destroy(m0t);

    //msleep(500);
    motor(0, 0);
    motor(2, 0);

    return 0;
}


