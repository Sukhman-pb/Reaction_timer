// TLA2024 Sample Code
// THIS CODE IS FROM THE TLA2024 SAMPLE CODE from the solution section of the course
//https://opencoursehub.cs.sfu.ca/bfraser/solutions/433/guide-code/i2c_adc_tla2024/
// - Configure DAC to continuously read an input channel on the BeagleY-AI

#ifndef I2C_HELPER_H
#define I2C_HELPER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

// I2C bus and device address
#define I2CDRV_LINUX_BUS "/dev/i2c-1"
#define JOYSTICK_ADDRESS 0x48

// Register in TLA
#define REG_CONFIGURATION 0x01
#define REG_DATA 0x00

// Configuration reg contents for continuously sampling different channels
#define CHANNEL_Y 0x83C2   //Y axis
#define CHANNEL_X 0x83D2   //X axis

// Initializes the I2C bus and returns the file descriptor
//parameter description
//bus: the I2c bus to be used
//address: the address of the device
int init_i2c_bus(char* bus, int address);

// Writes a 16-bit value to an I2C register
//parameter description
//i2c_file_desc: the file descriptor of the i2c bus
//reg_addr: the address of the register to write to
void write_register(int i2c_file_desc, uint8_t reg_addr, uint16_t value);

// Reads a 16-bit value from an I2C register
//already have a 5 ms delay betweeen the writes and reads in order to get the current written value
//parameter description
//i2c_file_desc: the file descriptor of the i2c bus
//reg_addr: the address of the register to read from
uint16_t read_register(int i2c_file_desc, uint8_t reg_addr);

void close_i2c_bus(int address);

#endif // I2C_HELPER_H
