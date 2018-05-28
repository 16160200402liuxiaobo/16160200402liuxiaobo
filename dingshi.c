#include"LPC11XX.H" 
#define LED1_ON()   LPC_GPIO2->DATA&= ~(1<<0)
#define LED1_OFF()  LPC_GPIO2->DATA |= (1<<0)
#define LED2_ON()   LPC_GPIO2->DATA&= ~(1<<1)
#define LED2_OFF()  LPC_GPIO2->DATA |= (1<<1)
#define LED3_ON()   LPC_GPIO2->DATA&= ~(1<<2)
#define LED3_OFF()  LPC_GPIO2->DATA |= (1<<2)
#define LED4_ON()   LPC_GPIO2->DATA&= ~(1<<3)
#define LED4_OFF()  LPC_GPIO2->DATA |= (1<<3)
#define LED5_ON()   LPC_GPIO2->DATA&= ~(1<<4)
#define LED5_OFF()  LPC_GPIO2->DATA |= (1<<4)
#define LED6_ON()   LPC_GPIO2->DATA&= ~(1<<5)
#define LED6_OFF()  LPC_GPIO2->DATA |= (1<<5)
#define LED7_ON()   LPC_GPIO2->DATA&= ~(1<<6)
#define LED7_OFF()  LPC_GPIO2->DATA |= (1<<6)
/********************************************
* FunctionName    :  LedInit()
* Description     :  LED初始化函数
* EntryParameter  :  None
* ReturnValue     :  None 
*********************************************/
void LedInit()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //使能IOCON时钟
	LPC_IOCON->PIO2_0 &= ~0x07;
	LPC_IOCON->PIO2_0 |= 0x00;
	LPC_SYSCON->SYSAHBCLKCTRL &= ~ (1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
	LPC_GPIO2->DIR |= (1<<0);
	LPC_GPIO2->DATA |= (1<<0);
}
	/******************************************
* FunctionName    :  T32B1_Init()
* Description     :  32位定时计数器初始化函数
* EntryParameter  :  None
* ReturnValue     :  None 
**********************************************/
	void T32B1_Init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<10);
	LPC_TMR32B1->IR = 0x01;
	LPC_TMR32B1->MCR = 0x04;
}
/********************************************
* FunctionName    :  T32B1_DelayMs()
* Description     :  32位定时计数器实现毫秒级延时函数
* EntryParameter  :  None
* ReturnValue     :  None 
**********************************************/
void T32B1_DelayMs(uint16_t ms)
{
	LPC_TMR32B1->TCR  = 0x02;
	LPC_TMR32B1->PR  = 0;
	LPC_TMR32B1->MR0 = ms* (SystemCoreClock/1000);
	LPC_TMR32B1->TCR = 0x01;
	while(LPC_TMR32B1->TCR & 0x01);
}
/********************************************
* FunctionName    :  main()
* Description     :  主函数
* EntryParameter  :  None
* ReturnValue     :  None 
***********************************************/
int main ()
{
	LedInit ();
	T32B1_Init ();
	while(1)
	{
		T32B1_DelayMs(1000);
		LED1_ON ();
		T32B1_DelayMs(1000);
		LED1_OFF ();
		T32B1_DelayMs(1000);
		LED2_ON ();
		T32B1_DelayMs(1000);
		LED2_OFF ();
  }
}