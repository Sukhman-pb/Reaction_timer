#ifndef JOY_STICK_CONTROL_H
#define JOY_STICK_CONTROL_H

#include <stdint.h>
#include <stdbool.h>
//for switcsh cases and modularity
typedef enum{
    UP,   //0
    DOWN, //1
    LEFT, //2
    RIGHT,//3
    CENTER//4
} Joystick_direction;

//initializing the joystick
//parameter description
//void = no parameters required
//returns the int file descriptor of the i2c bus
int joystick_init(void);

//gets the x direction of the joystick
//parameter description
//i2c_file_desc: the file descriptor of the i2c bus that we get from the joystick_init function
//returns left or right or center
Joystick_direction joystick_get_x(int i2c_file_desc);

//gets the y direction of the joystick
//parameter description
//i2c_file_desc: the file descriptor of the i2c bus that we get from the joystick_init function
//returns up or down or center
Joystick_direction joystick_get_y(int i2c_file_desc);


//checks if the joystick is pushed in any y axis and prompt the user to let go off joysick
//parameter description
//void : the file descriptor of the i2c bus
//prints let go of the joystick until the user doesn't let go of the joystick
void check_y_pushed(int i2c_file_desc);


//closes the joystick
//parameter description
//i2c_file_desc: the file descriptor of the i2c bus that we get from the joystick_init function
void joystick_close(int i2c_file_desc);
#endif