/* 
 * File:   botguy-primary.c
 * Author: Henry
 *
 * Created on July 14, 2014, 9:04 AM
 */
#include "camera-approach.h"

/*
 * 
 */
int main(int argc, char** argv) {
    raise_botguy_to(BOTGUY_CLAW_UP);
    enable_servos();
    printf("camera open response: %i\n", camera_open());
    preformApproach(false, 0);
    return (EXIT_SUCCESS);
}

