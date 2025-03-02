#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//IF USING THE ON AND OFF FUNCTION TOGETHER THEN WE NEED A DELAY IN ORDER TO SHOW THE EFFECT
//trigger for controlling the trigger of LED i.e manual or heartbeat
//brightness for controlling the brightness of LED i.e 0 or 1
//for red light PWR
#define RED_LED_TRIGGER_PATH "/sys/class/leds/PWR/trigger"
#define RED_LED_BRIGHTNESS_PATH "/sys/class/leds/PWR/brightness"
//for green light ACT
#define GREEN_LED_TRIGGER_PATH "/sys/class/leds/ACT/trigger"
#define GREEN_LED_BRIGHTNESS_PATH "/sys/class/leds/ACT/brightness"

typedef enum{
    LED_GREEN,    
    LED_RED       
} LED_color;

//initializeing the LED
int led_init(void);

//parameter description  
//LED_color is the color of LED we want to control
//trigger is for the control of LED for which we can put the value of string as "none" or "heartbeat"
void led_set_trigger(LED_color color, char *trigger);

//parameter description
//LED_color is the color of LED we want to control
void led_on(LED_color color);

//parameter description
//LED_color is the color of LED we want to control
void led_off(LED_color color);

//parameter description
//LED_color is the color of LED we want to control
//num_flashes is the number of times we want to flash the LED
//intervalMS is the time interval between the flashes
void led_flash(LED_color color, int num_flashes, int intervalMS);


//dereference any pointer or any other cleanup
void led_cleanup(void);
#endif 