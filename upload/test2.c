
#include "starting-routine.h"

int main(int argc, char** argv) {

    printf("Create connecting...\n");
    create_connect();
    raise_claw_to(CLAW_UP_POSITION);
    //set_servo_position(CUBE_KNOCK_PORT, CUBE_KNOCK_UP); //was down
    enable_servo(CLAW_LEFT);
    enable_servo(CLAW_RIGHT);
    

    printf("waiting for input...\n");
    char s[20];
    scanf("%s", s);
    if (strcmp(s, "exit") == 0) {
        return 0;
    }
    preformStartingRoutine();
    return 0;
}


