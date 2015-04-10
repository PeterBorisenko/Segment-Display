#include "SegmentDisplay.h"

void displaySetup() {
    shiftRegSetup();
#if (DISPLAY_METHOD != STATIC)
#if (DIGITS_NUMBER == 2)
    SEG_DIR|= (1 << SEG_0)|(1 << SEG_1);
#elif (DIGITS_NUMBER == 3)
    SEG_DIR|= (1 << SEG_0)|(1 << SEG_1)|(1 << SEG_2);
#elif (DIGITS_NUMBER == 4)
    SEG_DIR|= (1 << SEG_0)|(1 << SEG_1)|(1 << SEG_2)|(1 << SEG_3);
#endif
#endif
//    for (int8_t i= 15; i >= 0; i--) {
//        numbers[i]= eeprom_read(i+ADDR_SHIFT);
//    }
}

void displayPrint(uint8_t num) {
    shiftOut(numbers[num%10]);
    // TODO: Check delay
#if (DIGITS_NUMBER > 1)
    uint8_t a;
    SEG_0= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
            if(num/=10) {
                a= num%10;
                SEG_0= 0;
                shiftOut(numbers[a]);
                SEG_1= 1;
                for (uint8_t i = 20; i > 0; i--) {
                    asm("nop\n");
                }
#if (DIGITS_NUMBER == 2)
        SEG_1 = 0;
#endif
#endif
#if (DIGITS_NUMBER > 2)
            if(num/=10) {
                a= num%10;
                SEG_1= 0;
                shiftOut(numbers[a]);
                SEG_2= 1;
                for (uint8_t i = 20; i > 0; i--) {
                    asm("nop\n");
                }
#if (DIGITS_NUMBER == 3)
                SEG_2 = 0;
#endif
#endif
#if (DIGITS_NUMBER > 3)
            if(num/=10) {
                a= num%10;
                SEG_2= 0;
                shiftOut(numbers[a]);
                SEG_3= 1;
                for (uint8_t i = 20; i > 0; i--) {
                    asm("nop\n");
                }
                SEG_3= 0;
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

void displayPrintESR(uint8_t num) {
    if (digit_index == 0) {
        calc_var= num;
    }
    if (digit_index < DIGITS_NUMBER) {
        uint8_t a= calc_var%10;
        uint8_t b= eeprom_read(a+ADDR_SHIFT);
        seg[digit_index]= 0;
        //shiftOut(numbers[a]);
        shiftOut(b);
        seg[digit_index]= 1;
        if (calc_var/10) {
            digit_index++;
        }
        else {
            digit_index= 0;
        }
    }
}

void displayPrintBCD(uint8_t num) {
    //BCDword(BCDbuf, num);
#if (DIGITS_NUMBER == 4)
    shiftOut(numbers[BCDbuf[3]]);
    //SEG_3= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_3= 0;
#elif (DIGITS_NUMBER == 3)
    shiftOut(numbers[BCDbuf[2]]);
    //SEG_2= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_2= 0;
#elif (DIGITS_NUMBER == 2)
    shiftOut(numbers[BCDbuf[1]]);
    //SEG_1= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_1= 0;
#endif
    shiftOut(numbers[BCDbuf[0]]);
    //SEG_0= 1;
    for (uint8_t i = 20; i > 0; i--) {
        asm("nop\n");
    }
    //SEG_0= 0;
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