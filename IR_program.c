/**********************************************************/
/* Author    : Toka Medhat                                */
/* Date      : 29 NOV 2020                                */
/* Version   : V01                                        */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "EXTI0_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"

#include "IR_interface.h"
#include "IR_config.h"
#include "IR_private.h"

static void (* IR_CallBack) (void) = NULL ;

volatile u8   u8StartFlag       = 0;
volatile u32  u32FrameData[50]  = {0};
volatile u8   u8EdgeCounter     = 0;
volatile u8   u8Data            = 0;

void IR_voidInit(void)
{
	/* EXTI Initializtion */
	MEXTI_voidSetCallBack(voidGetFrame);
	MEXTI_voidInit(); /* A0 EXTI0 Enabled / Falling Edge */

	/* Enable EXTI0 from NVIC */
	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(6); /* EXTI0 */

	/* SysTick Init */
	MSTK_voidInit(); /* Enable SysTick AHB/8 = 1MHZ */
}



static void voidGetFrame(void)
{
	if (u8StartFlag == 0)
	{
		/* Start Timer */
		MSTK_voidSetIntervalSingle(1000000,voidTakeAction);
		u8StartFlag = 1;
	}

	else
	{
		u32FrameData[u8EdgeCounter] = MSTK_u32GetElapsedTime();
		MSTK_voidSetIntervalSingle(1000000,voidTakeAction);
		u8EdgeCounter++;
	}

}


void IR_voidSetCallBack(void (*ptr)(void))
{
	IR_CallBack = ptr;
	
}


static void voidTakeAction(void)
{
	u8 i;
	u8Data = 0;

	if ( (u32FrameData[0] >= 10000) && (u32FrameData[0] <= 14000) )
	{
		for (i=0;i<8;i++)
		{
			if (  (u32FrameData[17+i] >= 2000) && (u32FrameData[17+i] <=2300) )
			{
				SET_BIT(u8Data,i);
			}

			else
			{
				CLR_BIT(u8Data,i);
			}
		}

		IR_voidDoFunc();
	}

	else
	{
		/* Invalid Frame */
	}

	u8StartFlag     = 0;
	u32FrameData[0] = 0;
	u8EdgeCounter   = 0;
}



static void IR_voidDoFunc(void)
{
	IR_CallBack();
}





