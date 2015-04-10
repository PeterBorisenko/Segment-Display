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

#define SHIFT_DIR       TRISC
#define SHIFT_PORT      PORTC
#define SHIFT_ANSEL     (ANSEL)
#define SHIFT_DATA      (PORTCbits.RC5)
#define SHIFT_DATA_PIN  5
#define SHIFT_DATA_AN   NONE
#define SHIFT_LATCH     (PORTCbits.RC4)
#define SHIFT_LATCH_PIN 4
#define SHIFT_LATCH_AN  NONE
#define SHIFT_CLK       (PORTCbits.RC3)
#define SHIFT_CLK_PIN   3
#define SHIFT_CLK_AN    7


#define SEG_DIR TRISC
#define SEG_PORT PORTC
#define SEG_0 0
#define SEG_1 0
#define SEG_2 0
#define SEG_3 0

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

