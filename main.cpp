/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
Timer button_timer;
 // Initialise the digital pin LED1 as an output
#ifdef LED1
    DigitalOut led(LED1);
#else
     bool led;
#endif

#ifdef BUTTON1
    InterruptIn button(BUTTON1);
#else
     bool button;
#endif

void button_pressed()
{
    led = 1; 
    button_timer.reset(); 
    button_timer.start(); 
}


void button_released()
{
    button_timer.stop(); 
    led = 0; 
    
}

int main()
{
    button.rise(&button_pressed);
    button.fall(&button_released);

    while (true) {
        
        if (!button.read()) { 
            printf("Bouton relâché. Durée de l'appui : %lld ms\n", 
                   duration_cast<milliseconds>(button_timer.elapsed_time()).count());
            button_timer.reset();   
        }
        ThisThread::sleep_for(BLINKING_RATE);
    }

}



