
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <kovan/kovan.h>

int main(int argc, char** argv) {
    alloff();
    disable_servos();
    create_connect();
    create_drive_straight(0);
    create_disconnect();
    return 0;
}

