/* 
 * File:   ShiftRegister.h
 * Author: Disgust
 *
 * Created on September 3, 2014, 5:45 PM
 */

#ifndef SHIFTREGISTER_H
#define	SHIFTREGISTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "AppConfig.h"
#include "Macro.h"

//#include "user.h"
    
#define IN  1
#define OUT 0

#define SHIFT_REG OUT

#define wide_t uint8_t

void shiftRegSetup();
void shiftOutThru(const uint8_t *, uint8_t);
void shiftOut(uint8_t);
wide_t shiftIn();

#ifdef	__cplusplus
}
#endif

#endif	/* SHIFTREGISTER_H */

