/*
 * Shift7Segment.h
 *
 * Created: 8/30/2014 2:13:57 PM
 *  Author: Disgust
 */

#ifndef SEGMENTDISPLAY_H
#define	SEGMENTDISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
//#include "BCD.h"
#include "AppConfig.h"

#if (EEPROM_SIZE > 0)
    #include "eeprom_routines.h"
#endif
    
#define STATIC  0
#define DYNAMIC 1

#define ANODE   0
#define CATHODE 1

#define SERIAL      0
#define PARALLEL    1

#define LSB     0
#define MSB     1

#define DISPLAY_COMMON  CATHODE
#define DISPLAY_METHOD  STATIC
#define DISPLAY_BUS     SERIAL
#define DIGITS_NUMBER   1

#if (DISPLAY_BUS == SERIAL)
    #define BIT_ORDER LSB
    #include "ShiftRegister.h"
#endif

#if (DIGITS_NUMBER < 2)&&(DISPLAY_METHOD == DYNAMIC)
#error "Can not dynamic displaing with less then two digits"
#endif

/*
Segments position

       AAA
      F   B
      F   B
       GGG
      E   C
      E   C
       DDD  DP
*/

#if (EEPROM_SIZE > 0)
    // EEPROM VARIABLES : PROGRAM ONCE
//CATHODE
    // LSB
//__EEPROM_DATA(0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000);
//__EEPROM_DATA(0b11111110, 0b11110110, 0b11101110, 0b00111110, 0b10011100, 0b01111010, 0b10011110, 0b10001110);
    // MSB
//__EEPROM_DATA(0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111);
//__EEPROM_DATA(0b01111111, 0b01101111, 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001, 0b01110001);

//ANODE
    // LSB
//__EEPROM_DATA(0b00000011, 0b10011111, 0b00100101, 0b00001101, 0b10011001, 0b01001001, 0b01000001, 0b00011111);
//__EEPROM_DATA(0b00000001, 0b00001001, 0b00010001, 0b11000001, 0b01100011, 0b10000101, 0b01100001, 0b01110001);
    //MSB
//__EEPROM_DATA(0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b01100110, 0b10010010, 0b10000010, 0b11111000);
//__EEPROM_DATA(0b10000000, 0b10010000, 0b10001000, 0b10000011, 0b11000110, 0b10100001, 0b10000110, 0b10001110);
#else
    #define _0 0b11111100
    #define _1 0b01100000
    #define _2 0b11011010
    #define _3 0b11110010
    #define _4 0b01100110
    #define _5 0b10110110
    #define _6 0b10111110
    #define _7 0b11100000
    #define _8 0b11111110
    #define _9 0b11110110
    #define _A 0b11101110
    #define _B 0b00111110
    #define _C 0b00111110
    #define _D 0b01111010
    #define _E 0b10011110
    #define _F 0b10001110
#endif

#if (DISPLAY_COMMON == CATHODE)
#if (DISPLAY_BUS == SERIAL)
#if (BIT_ORDER == MSB)
#define ADDR_SHIFT 0
#define _dot 0b00000001
#elif (BIT_ORDER == LSB)
#define ADDR_SHIFT 16
#define _dot 0b10000000
#endif
#else
    #define ADDR_SHIFT 0
    #define _dot 0b00000001
#endif

#elif (DISPLAY_COMMON == ANODE)
#if (DISPLAY_BUS == SERIAL)
#if (BIT_ORDER == MSB)
#define ADDR_SHIFT 32
#define _dot 0b11111110
#elif (BIT_ORDER == LSB)
#define ADDR_SHIFT 48
#define _dot 0b01111111
#endif
#else
    #define ADDR_SHIFT 32
    #define _dot 0b11111110
#endif
#endif

unsigned seg[DIGITS_NUMBER];

#if (DIGITS_NUMBER == 2)
    seg[0]= SEG_0;
    seg[1]= SEG_1;
#elif (DIGITS_NUMBER == 3)
    seg[0]= SEG_0;
    seg[1]= SEG_1;
    seg[2]= SEG_2;
#elif (DIGITS_NUMBER == 4)
    seg[0]= SEG_0;
    seg[1]= SEG_1;
    seg[2]= SEG_2;
    seg[3]= SEG_3;
#endif

uint8_t numbers[16];
volatile static uint8_t digit_index= 0;
volatile static uint16_t calc_var;

uint8_t BCDbuf[DIGITS_NUMBER];

uint8_t rotation[]= {0b10010000, 0b01001000, 0b00100100};
volatile static uint8_t rot_index= 0;

void displaySetup();

void displayPrint(uint8_t);

void displayPrintESR(uint8_t);

void displayPrintBCD(uint8_t);

void displayWait(uint8_t);

//void displayIdle() {
//
//}

#ifdef	__cplusplus
}
#endif

#endif	/* SEGMENTDISPLAY_H */

