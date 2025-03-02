#include "hal/led_control.h"
#include "hal/helper.h"
#include <errno.h>
#include <assert.h>


//initializing the LED path needed for the control of LED
static char *trigger_path(LED_color color){
    switch(color){
        case LED_GREEN:
            return GREEN_LED_TRIGGER_PATH;
        case LED_RED:
            return RED_LED_TRIGGER_PATH;
        default:
        //error message and exit
            assert(0 && "Invalid LED type in get_trigger_path");
    }
}

static char *brightness_path(LED_color color){
    switch(color){
        case LED_GREEN:
            return GREEN_LED_BRIGHTNESS_PATH;
        case LED_RED:
            return RED_LED_BRIGHTNESS_PATH;
        default:
        //error message and exit
            assert(0 && "Invalid LED type in get_brightness_path");
    }
}


int led_init(void){
    led_set_trigger(LED_GREEN, "none");
    led_off(LED_GREEN);
    led_off(LED_RED);
    return 0;
}

void led_cleanup(void){
    //turn off the LED
    led_off(LED_GREEN);
    led_off(LED_RED);
    //set the trigger to heartbeat for green
    led_set_trigger(LED_GREEN, "heartbeat");
}


void led_set_trigger(LED_color color, char* trigger){
    FILE *triggerFile = fopen(trigger_path(color), "w");
    if(triggerFile == NULL){
        perror("Error opening LED trigger file");
        exit(EXIT_FAILURE);
    }
    int charWritten = fprintf(triggerFile, "%s", trigger);
    if(charWritten<=0){
        fclose(triggerFile); //closing the file before exiting on writing failure
        perror("Error writing to LED trigger file");
        exit(EXIT_FAILURE);
    }
    fclose(triggerFile);
}

void led_on(LED_color color){
    FILE *brightnessFile = fopen(brightness_path(color), "w");
    if(brightnessFile == NULL){
        perror("Error opening LED brightness file");
        exit(EXIT_FAILURE);
    }
    int charWritten = fprintf(brightnessFile, "1");
    if(charWritten<=0){
        fclose(brightnessFile); //closing the file before exiting on writing failure
        perror("Error writing to  LED brightness file");
        exit(EXIT_FAILURE);
    }
    fclose(brightnessFile);
    //no delay as the LED should turn on instantly
}

void led_off(LED_color color){
    FILE *brightnessFile = fopen(brightness_path(color), "w");
    if(brightnessFile == NULL){
        perror("Error opening LED brightness file");
        exit(EXIT_FAILURE);
    }
    int charWritten = fprintf(brightnessFile, "0");
    if(charWritten<=0){
        fclose(brightnessFile); //closing the file before exiting on writing failure
        perror("Error writing to LED brightness file");
        exit(EXIT_FAILURE); 
    }
    fclose(brightnessFile);
    //no delay as the LED should turn off instantly
}

//flashing the LED
void led_flash(LED_color color, int num_flashes, int intervalMS){
    for(int i=0; i<num_flashes; i++){
        led_on(color);
        sleep_ms(intervalMS);
        led_off(color);
        sleep_ms(intervalMS);
    }
}

