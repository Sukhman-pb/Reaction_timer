#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hal/led_control.h" 
#include "hal/joy_stick_control.h"
#include "hal/helper.h"
#include <unistd.h>

//wait time for the reaction time
#define MAX_WAIT_TIME 5000

//delay time for the reaction time
#define FLASH_DELAY 250

//delay time for the reaction time
#define DELAY_WRONG 500

//delay time for the reaction time
#define RANDOM_MIN_DELAY 500
#define RANDOM_MAX_DELAY 3000
#define GENERAL_DELAY 20
#define LARGER_DELAY 1000

int main() {
    printf("Hello embedded world, from Sukhmanpreet Singh!\n");
    printf("\n");

    // Initialize the LED module.
    if (led_init() != 0) {
        fprintf(stderr, "Failed to initialize LED module.\n");
        return EXIT_FAILURE;
    }
    //initialize the joystick module.
    int i2c_file_desc = joystick_init();
    if (i2c_file_desc < 0) {
        fprintf(stderr, "Failed to initialize joystick module.\n");
        return EXIT_FAILURE;
    }

    long long best_time = MAX_WAIT_TIME; //pre setting to max time
    long long start_time = 0;
    long long reaction_time = 0;
    long long wait_time = 0;

    bool restart = false;

    Joystick_direction dir_x, dir_y, expected_direction;

    srand(time(NULL)); //seed for random number generation  
    //while loop to keep the game running
    printf("When the LEDs light up, press the joystick in that direction!\n");
    printf("(Press left or right to exit)\n");

    //loop 1  level 1
    while(true){
        printf("Get Ready!\n");
        //step 1: flashing the LED after get ready
        for(int i = 0 ; i < 4 ; i ++)
        {
            led_on(LED_GREEN);
            sleep_ms(FLASH_DELAY);
            check_y_pushed(i2c_file_desc);
            led_off(LED_GREEN);
            sleep_ms(FLASH_DELAY);
            check_y_pushed(i2c_file_desc);
            led_on(LED_RED);
            sleep_ms(FLASH_DELAY);
            check_y_pushed(i2c_file_desc);
            led_off(LED_RED);
            sleep_ms(FLASH_DELAY);
            check_y_pushed(i2c_file_desc);
        }
        //step 2 : check if the user pressed the joystick in y direction   
        check_y_pushed(i2c_file_desc);
        
        
        //step 3: random delay for the user to get ready
        //getting the value in range of minimum and maximum delay
        //need a better sleep as it doesn't read any x or y values while sleeping
        
        wait_time = (rand() % (RANDOM_MAX_DELAY - RANDOM_MIN_DELAY + 1)) + RANDOM_MIN_DELAY;
        start_time = get_time_in_ms();
        while(get_time_in_ms() - start_time < wait_time){
            dir_y = joystick_get_y(i2c_file_desc);
            if(dir_y != CENTER){
                printf("Too soon\n");
                restart = true;  
                led_off(LED_GREEN);    
                led_off(LED_RED);
                break;
            }
        }  
        
        if(restart == true)
        {
            //resetting to false for next scenario
            restart = false;
            continue; //restart the loop level 1
        }
        //get a random direction between UP and Down
        expected_direction = (rand() % 2) ? UP : DOWN;
        if(expected_direction == UP){
            printf("Press UP now!\n");
            dir_y = joystick_get_y(i2c_file_desc);
            if(dir_y != CENTER)
            {
                printf("Too soon \n");
            }
            led_on(LED_GREEN);
        }
        else{
            printf("Press DOWN now!\n");
            dir_y = joystick_get_y(i2c_file_desc);
            if(dir_y != CENTER)
            {
                printf("Too soon \n");
            }
            led_on(LED_RED);
        }
        start_time = get_time_in_ms();
        //loop 3 level 2
        while((get_time_in_ms() - start_time)< MAX_WAIT_TIME){
        dir_x = joystick_get_x(i2c_file_desc);
        dir_y = joystick_get_y(i2c_file_desc);
        if(dir_y != CENTER || dir_x != CENTER){
            //if there is any movement in the joystick
            //then quit
            //getting the reaction time 
            reaction_time = get_time_in_ms();
            led_off(LED_GREEN);led_off(LED_RED);
            sleep_ms(GENERAL_DELAY);
            break;
        }
    }
    //checking exit condition 1
    if(dir_x != CENTER)
    {
        led_off(LED_GREEN);led_off(LED_RED);
        printf("User selected to quit.\n");
        //breaking from the loop 1
        break;
    }
    //checking exit condition 2
    if(dir_y == CENTER)
    {
        led_off(LED_GREEN);led_off(LED_RED);
        printf("No input within 5000ms; quitting!\n");
        break;
    }
    //turning off both the leds in as doing a conditional statment was time consuming
  
    //checking if the user pressed the correct direction
    //leds are already off

    if(dir_y == expected_direction)
    {
        led_flash(LED_GREEN, 5, 100);   
        reaction_time = reaction_time - start_time;
        printf("Correct!\n");
        if(reaction_time < best_time){
            best_time = reaction_time;
            printf("New best time: %lldms\n", best_time);
        }
        printf("Your reaction time was %lldms; best so far is %lldms\n", reaction_time, best_time);
    }
    else{
        led_flash(LED_RED, 5, 100);
        printf("Incorrect!\n");
    }
}    
//clean up the led and joystick module
    led_cleanup();
    joystick_close(i2c_file_desc);
    return 0;
}

