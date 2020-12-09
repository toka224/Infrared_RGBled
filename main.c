/**********************************************************/
/* Author    : Toka Medhat                                */
/* Date      : 9 DEC 2020                                 */
/* Version   : V01                                        */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "EXTI0_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"

extern u8 u8Data;


void voidPlay(void)
{
	switch (u8Data)
	{
		case 69:GPIO_voidSetPinValue(GPIOA,1,0);
				GPIO_voidSetPinValue(GPIOA,2,0);
				GPIO_voidSetPinValue(GPIOA,3,0);
				break;
		case 22:GPIO_voidSetPinValue(GPIOA,1,1); break;
		case 24:GPIO_voidSetPinValue(GPIOA,2,1); break;
		case 94:GPIO_voidSetPinValue(GPIOA,3,1); break;



	}
}


void main(void)
{
	/* RCC Initialize */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);   /* GPIOA Enable Clock */
	RCC_voidEnableClock(RCC_APB2, 3);  /* GPIOB Enable Clock */

	/* IO Pins Initialization */
	GPIO_voidSetPinDirection(GPIOA,0,0b0100);/* A0 Input Floating        */
	GPIO_voidSetPinDirection(GPIOA,1,0b0010); /* A1 Output PP "RED"       */
	GPIO_voidSetPinDirection(GPIOA,2,0b0010); /* A1 Output PP "GREEN"     */
	GPIO_voidSetPinDirection(GPIOA,3,0b0010); /* A1 Output PP "BLUE"      */

	IR_voidSetCallBack(voidPlay);

	IR_voidInit();

	while(1)
	{

	}

}
