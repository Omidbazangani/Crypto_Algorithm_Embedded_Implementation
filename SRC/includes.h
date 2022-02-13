/***************************************************************************
 **
 **
 **    Master inlude file
 **
 **    Used with ARM IAR C/C++ Compiler
 **
 **    (c) Copyright IAR Systems 2007
 **
 **    $Revision: 31601 $
 **
 ***************************************************************************/

#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <intrinsics.h>
#include <assert.h>
#include "lpc17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_clkpwr.h"
#include "lpc17xx_pinsel.h"
#include "peripherals.h"


//#include "stdio.h"
//#include "string.h"

#include "peripherals.h"
#define nop1 "nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n" //10
#define nop100 nop1 nop1 nop1 nop1 nop1 nop1 nop1 nop1 nop1 nop1	//100
#define nop500 nop100 nop100 nop100 nop100 nop100							//500
#define nop5000 nop500 nop500 nop500 nop500 nop500 nop500 nop500 nop500 nop500 nop500

#endif  // __INCLUDES_H
