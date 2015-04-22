#include "ShiftRegister.h"


void shiftRegSetup() {
    //SHIFT_DIR|= (1 << SHIFT_DATA)|(1 << SHIFT_CLK)|(1 << SHIFT_LATCH);
#if (SHIFT_CLK_AN != NONE)
    SHIFT_CLK_ANSEL&= ~(1 << SHIFT_CLK_AN);
#endif
#if (SHIFT_DATA_AN != NONE)
    SHIFT_DATA_ANSEL&= ~(1 << SHIFT_DATA_AN);
#endif
#if (SHIFT_LATCH_AN != NONE)
    SHIFT_LETCH_ANSEL&= ~(1 << SHIFT_LATCH_AN);
#endif
    SHIFT_CLK_DIR&= ~(1 << SHIFT_CLK_PIN);
    SHIFT_LATCH_DIR&= ~(1 << SHIFT_LATCH_PIN);
#if (SHIFT_REG == IN) // TODO: replace for using more then 1 register with different directions
    SHIFT_DATA_DIR|= (1 << SHIFT_DATA_PIN);
#elif (SHIFT_REG == OUT)
    SHIFT_DATA_DIR&= ~(1 << SHIFT_DATA_PIN);
#endif
}
/*
void shiftOutThru(const uint8_t * buffer, uint8_t count) {
    SHIFT_LATCH= 0;
#if (BIT_ORDER == LSB)
    for (uint8_t i= count; i > 0; i--) {
        for (int i = 7; i >= 0; i++) {
#elif (BIT_ORDER == MSB)
    for (uint8_t i = 0; i < count; i--) {
        for (int i = 0; i <= 7; i++) {
#endif
            SHIFT_CLK = 0;
            SHIFT_DATA = ((*(buffer + count) >> i) & 0b01) ? 1 : 0;
            for (uint8_t i = 5; i > 0; i--) {
                asm("nop\n"); // Need 2us
            }
            SHIFT_CLK = 1;
            for (uint8_t i = 10; i > 0; i--) {
                asm("nop\n"); // Need 2us
            }
        }
    }
    SHIFT_LATCH= 1;
}
*/
void shiftOut(uint8_t data) {
    SHIFT_LATCH= 0;
#if (BIT_ORDER == LSB)
    for (int i = 0; i <= 7; i++) {
#elif (BIT_ORDER == MSB)
    uint8_t temp= data;
    for (int i = 7; i >= 0; i++) {
        data= temp;
#endif
        SHIFT_CLK= 0;
        SHIFT_DATA= ((data >> i) & 0b01)?1:0;

        for (uint8_t i= 5; i> 0; i--) {
            asm("nop\n"); // Need 2us
        }
        SHIFT_CLK= 1;
        for (uint8_t i= 10; i> 0; i--) {
            asm("nop\n"); // Need 2us
        }
    }
    SHIFT_LATCH= 1;
}
/*
wide_t shiftIn() {
    wide_t result= 0;
    SHIFT_LATCH= 1;
    for (uint8_t i= 200; i> 0; i--) {
        asm("nop\n"); // need 20us
    }
    SHIFT_LATCH= 0;

    for (int8_t n= 7; n >= 0; n--) {
        SHIFT_CLK= 0;
        for (uint8_t i= 20; i> 0; i--) {
            asm("nop\n"); // Need 2us
        }
        if (SHIFT_DATA == 1) {
            result|= (1 << n);
        }
        SHIFT_CLK= 1;
    }
    return result;
}
*/