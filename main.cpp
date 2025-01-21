/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms


int main()
{
    // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
     printf("Erreur : LED1 n'est pas définie.\n");
#endif

#ifdef BUTTON1
    DigitalIn button(BUTTON1);  
#else
     printf("Erreur : BUTTON1 n'est pas définie.\n");
#endif

    while (true) {
        if(button.read()==1){
            led=1;
            printf("led on\n");
        }
        else{
            led=0;
            printf("led off\n");
        }
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
