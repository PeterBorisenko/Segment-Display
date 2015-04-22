/* 
 * File:   Config.h
 * Author: Disgust
 *
 * Created on September 3, 2014, 5:51 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Macro.h"

#include <xc.h>

#if (EEPROM_SIZE > 0)
#define USE_EEPROM
#endif

#define SHIFT_DATA_DIR       TRISA
#define SHIFT_DATA_PORT      PORTA
#define SHIFT_DATA_ANSEL     (ANSEL)
#define SHIFT_DATA      (PORTAbits.RA5)
#define SHIFT_DATA_PIN  5
#define SHIFT_DATA_AN   NONE

#define SHIFT_LATCH_DIR       TRISC
#define SHIFT_LATCH_PORT      PORTC
#define SHIFT_LATCH_ANSEL     (ANSEL)
#define SHIFT_LATCH     (PORTCbits.RC5)
#define SHIFT_LATCH_PIN 5
#define SHIFT_LATCH_AN  NONE

#define SHIFT_CLK_DIR       TRISC
#define SHIFT_CLK_PORT      PORTC
#define SHIFT_CLK_ANSEL     (ANSEL)
#define SHIFT_CLK       (PORTCbits.RC4)
#define SHIFT_CLK_PIN   4
#define SHIFT_CLK_AN    NONE

//#define SOFT_PWM_DIR    (TRISA)
//#define SOFT_PWM_PORT   (PORTA)
//#define SOFT_PWM_ANSEL  (ANSEL)
//#define SOFT_PWM        (PORTAbits.RA4)
//#define SOFT_PWM_PIN    4
//#define SOFT_PWM_AN     3


#define SEG_DIR     TRISC
#define SEG_PORT    PORTC
#define SEG_ANSEL   ANSEL
//#define SEG_0 (PORTCbits.RC0)
//#define SEG_1 (PORTCbits.RC1)
//#define SEG_2 (PORTCbits.RC2)
//#define SEG_3 (PORTCbits.RC3)
#define SEG_0   (1 << 0)
#define SEG_1   (1 << 1)
#define SEG_2   (1 << 2)
#define SEG_3   (1 << 3)
#define S0_AN   (1 << 4)
#define S1_AN   (1 << 5)
#define S2_AN   (1 << 6)
#define S3_AN   (1 << 7)

#define ADC_ANSEL ANSEL
#define ADC0   (0)
#define ADC0_TRIS  TRISA
#define ADC0_PIN    (0)

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

