#ifndef UART_H_
#define UART_H_

#define UART5_IBRD_REG            *(volatile u32*)0x40011024
#define UART5_CTL_REG             *(volatile u32*)0x40011030
#define UART5_FBRD_REG            *(volatile u32*)0x40011028
#define UART5_CC_REG              *(volatile u32*)0x40011FC8
#define UART5_LCRH_REG            *(volatile u32*)0x4001102C
#define UART5_ICR_REG             *(volatile u32*)0x40011044
#define UART5_IM_REG              *(volatile u32*)0x40011038
#define UART5_DR_REG              *(volatile u32*)0x40011000
#define UART5_FR_REG              *(volatile u32*)0x40011018






#endif
