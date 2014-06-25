
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "claw-utils.h"
#include <sys/time.h>
#include <kovan/kovan.h>


FILE* logfile;
void wait_for_char() {
    struct timeval start_time;
    struct timeval finish_time;
    gettimeofday(&start_time, NULL);
    getch();
    gettimeofday(&finish_time, NULL);
    printf("msleep(%i);\n\r", (int) ((finish_time.tv_sec - start_time.tv_sec) * 1000 + ((finish_time.tv_usec - start_time.tv_usec) / 1000)));
    fprintf(logfile, "msleep(%i);\n\r", (int) ((finish_time.tv_sec - start_time.tv_sec) * 1000 + ((finish_time.tv_usec - start_time.tv_usec) / 1000)));


}



int main(int argc, char** argv) {
    
    initscr();
    noecho();
    printf("welcome to create drive v6 (custom)\n\r");
    printf("the controls are wasd for driving and g for claw middle, t for claw up\n\r");
    refresh();
    logfile = fopen("/kovan/logs/log1.txt", "w");
    if (logfile != NULL) {
        printf("logging to log /kovan/logs/log1.txt\n\r");
    } else {
        printf("error logging to log /kovan/logs/log1.txt\n\r");
    }
    refresh();
    msleep(2000);
    printf("connecting to create...\n\r");
    refresh();
    create_connect();
    printf("create connection sucessfull!\n\r");
    
    printf("connecting to camera...");
    if (camera_open() == 1) {
        printf("camera connection sucessfull!\n\r");
    } else {
        printf("error connecting to camera.\n\r");
    }
    clear();
    raise_claw_to(CLAW_UP_POSITION);
    enable_servos();
    while (true) {
        refresh();
        create_drive_straight(0);
        printf("create_drive_straight(0);\n\r");
        fprintf(logfile, "create_drive_straight(0);\n\r");
        char ch = getch();
        switch (ch) {
            case 'w':
                printf("create_drive_straight(-300);\n\r");
                fprintf(logfile, "create_drive_straight(-300);\n\r");
                create_drive_straight(-300);
                wait_for_char();
                break;
            case 's':
                printf("create_drive_straight(300);\n\r");
                fprintf(logfile, "create_drive_straight(300);\n\r");
                create_drive_straight(300);
                wait_for_char();
                break;
            case 'a':
                printf("create_spin_CCW(150);\n\r");
                fprintf(logfile, "create_spin_CCW(150);\n\r");
                create_spin_CCW(150);
                wait_for_char();
                break;
            case 'd':
                printf("create_spin_CW(150);\n\r");
                fprintf(logfile, "create_spin_CW(150);\n\r");
                create_spin_CW(150);
                wait_for_char();
                break;
            case 'x':
                printf("create_drive_straight(500);\n\r");
                fprintf(logfile, "create_drive_straight(500);\n\r");
                create_drive_straight(500);
                wait_for_char();
                break;
                
            case 't':
                printf("raise_claw_to(1200);\n\r");
                fprintf(logfile, "raise_claw_to(1200);\n\r");
                raise_claw_to(CLAW_UP_POSITION);
                break;
            case 'g':
                printf("raise_claw_to(500);\n\r");
                fprintf(logfile, "raise_claw_to(500);\n\r");
                raise_claw_to(CLAW_MIDDLE_POSITION);
                break;
            case 'h' :
                printf("move_claw_amount(700);\n\r");
                fprintf(logfile, "move_claw_amount(700);\n\r");
                move_claw_amount(500);
                break;
            case 'j' :
                printf("move_claw_amount(-700);\n\r");
                fprintf(logfile, "move_claw_amount(-700);\n\r");
                move_claw_amount(-500);
                break;
                
            case '1':
                fclose(logfile);
                endwin();
                return 0;
        }
    }
    
}
