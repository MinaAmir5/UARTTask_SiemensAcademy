/*
 * main.c
 *
 *  Created on: 2/10/2022
 *      Author: Mina AMir Girgis
 */
/*************************************************-INLUDED_DRIVERS-*************************************************/

#include <STD.h>
#include <SysTick_Private.h>
#include <GPIO_Private.h>
#include <UART_Private.h>
#include <NVIC_Private.h>
/*************************************************-FUNCTIONS_PROTOTYPES-********************************************/
void Delay(unsigned long counter);
char UART5_Receiver(void);
void UART5_Transmitter(unsigned char data);
void printstring(char *str);
void UART5_Handler(void);
/*************************************************-MAIN_FUNCTION-**************************************************/
int main(void)
{
  RCGCUART_REG |= 0x20;  /* enable clock to UART5 */
  RCGCGPIO_REG |= 0x10;  /* enable clock to PORTE for PE4/Rx and RE5/Tx */
  Delay(1);
  /* UART0 initialization */
  UART5_CTL_REG = 0;         /* UART5 module disbable */
  UART5_IBRD_REG = 104;      /* for 9600 baud rate, integer = 104 */
  UART5_FBRD_REG = 11;       /* for 9600 baud rate, fractional = 11*/
  UART5_CC_REG = 0;          /*select system clock*/
  UART5_LCRH_REG = 0x60;     /* data lenght 8-bit, not parity bit, no FIFO */
  UART5_CTL_REG = 0x301;     /* Enable UART5 module, Rx and Tx */

  /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
  GPIOE_DEN_REG = 0x30;      /* set PE4 and PE5 as digital */
  GPIOE_AFSEL_REG = 0x30;    /* Use PE4,PE5 alternate function */
  GPIOE_AMSEL_REG = 0;    /* Turn off analg function*/
  GPIOE_PCTL_REG = 0x00110000;     /* configure PE4 and PE5 for UART */
	  
	// enable interrupt 
  UART5_ICR_REG &= ~(0x0780);; // Clear receive interrupt
  UART5_IM_REG  = 0x0010;
  NVIC_EN1_REG |= 0x20000000; /* enable IRQ61 for UART0 */
	
	UART5_Transmitter('A');
	
	Delay(10); 
	while(1)
	{
	}
}
/*************************************************-UART_ISR-*************************************************/
void UART5_Handler( void )
{
unsigned char rx_data = 0;
UART5_ICR_REG &= ~(0x010); // Clear receive interrupt
rx_data = UART5_DR_REG ; // get the received data byte
if(rx_data >= 97 && rx_data <= 122)
	UART5_Transmitter(rx_data-32);
else if(rx_data >= 65 && rx_data <= 89)
	UART5_Transmitter(rx_data+1);
}

void UART5_Transmitter(unsigned char data)  
{
    while((UART5_FR_REG & (1<<5)) != 0); /* wait until Tx buffer not full */
    UART5_DR_REG = data;                  /* before giving it another byte */
}

void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter; i++);
}
