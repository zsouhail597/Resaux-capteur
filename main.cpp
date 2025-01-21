/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
using namespace std::chrono;

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
Timer button_timer;
Ticker led_ticker; 
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
    led_ticker.detach();
    led = 1; 
    button_timer.reset(); 
    button_timer.start(); 
}
void flip(){
    led = !led;
}


void button_released()
{
    button_timer.stop(); 
    auto duration = duration_cast<milliseconds>(button_timer.elapsed_time());
    auto blink_interval = std::max(100ms, duration); // limite de clignotement est de 100ms
    led_ticker.attach(&flip, blink_interval);
    
}



int main()
{
    button.rise(&button_pressed); 
    button.fall(&button_released);

    while (true) {
        ThisThread::sleep_for(BLINKING_RATE);
    }

}



