#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#include <STD.h>

#define NVIC_EN1_REG 	   *(volatile u32 *) 0xE000E104

typedef struct{

	volatile u32 EN        [ 32 ];
	volatile u32 DIS       [ 32 ];
	volatile u32 PEND      [ 32 ];
	volatile u32 UNPEND    [ 32 ];
	volatile u32 ACTIVE    [ 32 ];
	volatile u32 RESERVED  [ 32 ];
	volatile u8  PRI       [128 ];

}NVIC_REG;

#define NVIC_REGs ((volatile NVIC_REG *)0xE000E100)

#endif
