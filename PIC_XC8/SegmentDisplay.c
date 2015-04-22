#include "SegmentDisplay.h"

void displaySetup() {
#if (DIGITS_NUMBER > 1)
    digit_index= 0;
#endif
#if (DISPLAY_METHOD != STATIC)
    shiftRegSetup();
#if (DIGITS_NUMBER == 2)
    SEG_ANSEL&= ~(S0_AN|S1_AN);
    SEG_DIR&= ~(SEG_0|SEG_1);
    SEG_PORT&= ~(SEG_0|SEG_1);
#elif (DIGITS_NUMBER == 3)
    SEG_ANSEL&= ~(S0_AN|S1_AN|S2_AN);
    SEG_DIR&= ~(SEG_0|SEG_1|SEG_2);
    SEG_PORT&= ~(SEG_0|SEG_1|SEG_2);
#elif (DIGITS_NUMBER == 4)
    SEG_ANSEL&= ~(S0_AN|S1_AN|S2_AN|S3_AN);
    SEG_DIR&= ~(SEG_0|SEG_1|SEG_2|SEG_3);
    SEG_PORT&= ~(SEG_0|SEG_1|SEG_2|SEG_3);
#endif
#endif
//    for (int8_t i= 15; i >= 0; i--) {
//        numbers[i]= eeprom_read(i+ADDR_SHIFT);
//    }
}
/*
void displayPrint(uint8_t num) {
#ifdef USE_EEPROM

#else
    shiftOut(numbers[num%10]);
#endif
#if (DIGITS_NUMBER > 1)
    uint8_t a;
    //SEG_0= 1;
    SEG_PORT|= seg[0];
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
            if(num/=10) {
                a= num%10;
                //SEG_0= 0;
                SEG_PORT&= ~seg[0];
#ifdef USE_EEPROM

#else
                shiftOut(numbers[a]);
#endif
                //SEG_1= 1;
                SEG_PORT|= seg[1];
                for (uint8_t i = 20; i > 0; i--) {
                    asm("nop\n");
                }
#if (DIGITS_NUMBER == 2)
        //SEG_1 = 0;
                SEG_PORT&= ~seg[1];
#endif
#endif
#if (DIGITS_NUMBER > 2)
            if(num/=10) {
                a= num%10;
                //SEG_1= 0;
                SEG_PORT&= ~seg[1];
#ifdef USE_EEPROM

#else
                shiftOut(numbers[a]);
#endif
                //SEG_2= 1;
                SEG_PORT|= seg[2];
                for (uint8_t i = 20; i > 0; i--) {
                    asm("nop\n");
                }
#if (DIGITS_NUMBER == 3)
                //SEG_2 = 0;
                SEG_PORT&= ~seg[2];
#endif
#endif
#if (DIGITS_NUMBER > 3)
            if(num/=10) {
                a= num%10;
                //SEG_2= 0;
                SEG_PORT&= ~seg[2];
#ifdef USE_EEPROM

#else
                shiftOut(numbers[a]);
#endif
                //SEG_3= 1;
                SEG_PORT|= seg[3];
                for (uint8_t i = 20; i > 0; i--) {
                    asm("nop\n");
                }
                //SEG_3= 0;
                SEG_PORT&= ~seg[3];
            }
            else {
                return;
            }
#endif
#if (DIGITS_NUMBER > 2)
            }
            else {
                return;
            }
#endif
#if (DIGITS_NUMBER > 1)
            }
            else {
                return;
            }
#endif
    for (uint8_t i= 20; i > 0; i--) {
        asm("nop\n");
    }
    
}
*/
void displayPrintESR(int16_t num) {
    if (digit_index == 0) {
        segm_flag= DIGIT;
        if (num < 0) {
            calc_var= (uint16_t)(0 - num);
            negative= 1;
        }
        else {
            calc_var= num;
            negative= 0;
        }
    }
    if (digit_index < DIGITS_NUMBER) {
        if (segm_flag&DIGIT) {
            uint8_t a= calc_var%10;
#ifdef USE_EEPROM
            uint8_t b= eeprom_read(a);
            //seg[digit_index]= 0;
            SEG_PORT&= ~seg[prev_digit_index];
            shiftOut(b);
#else
        //seg[digit_index]= 0;
        SEG_PORT&= ~seg[prev_digit_index];
        shiftOut(numbers[a]);
#endif
        }
        else if (segm_flag&MINUS) {
            SEG_PORT &= ~seg[prev_digit_index];
            shiftOut(_minus);
        }
        else {
            SEG_PORT&= ~seg[prev_digit_index];
            shiftOut(0x00);
        }
        //seg[digit_index]= 1;
        SEG_PORT |= seg[digit_index];
        prev_digit_index= digit_index;
        digit_index++;
        if (digit_index == DIGITS_NUMBER) {
            digit_index= 0;
        }
        if (segm_flag&DIGIT) {
            calc_var/= 10;
            if (!calc_var) {
                if (negative) {
                    segm_flag= MINUS;
                }
                else {
                    segm_flag= SPACE;
                }
            }
        }
        else if (segm_flag&MINUS){
            if (prev_digit_index != (DIGITS_NUMBER - 1)){
                segm_flag= SPACE;
            }
        }
    }
}
/*
void displayPrintBCD(uint8_t num) {
    //BCDword(BCDbuf, num);
#if (DIGITS_NUMBER == 4)
#ifdef USE_EEPROM

#else
                shiftOut(numbers[BCDbuf[3]]);
#endif
    
    //SEG_3= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_3= 0;
#elif (DIGITS_NUMBER == 3)
#ifdef USE_EEPROM

#else
                shiftOut(numbers[BCDbuf[2]]);
#endif
    //SEG_2= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_2= 0;
#elif (DIGITS_NUMBER == 2)
#ifdef USE_EEPROM

#else
                shiftOut(numbers[BCDbuf[1]]);
#endif
    //SEG_1= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_1= 0;
#elif (DIGITS_NUMBER == 1)

#ifdef USE_EEPROM

#else
                shiftOut(numbers[BCDbuf[0]]);
#endif
    //SEG_0= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_0= 0;
#endif
}

void displayIdle();

void displayWait(uint8_t dir) {
    for (uint8_t i= DIGITS_NUMBER; i > 0; i--) {
        shiftOut(rotation[rot_index]);
    }
    if (dir > 0) { // If direction is CW
        if(++rot_index > 2) { // increment
            rot_index= 0;
        }
    }
    else { // if direction is CCW
        if(rot_index == 0) { // decrement
            rot_index= 2;
        }
        else {
            rot_index--;
        }
    } 
}
 */