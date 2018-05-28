#include"LPC11XX.H" //ͷ�ļ�
unsigned int status;
/*******
* FunctionName    :  LedInit()
* Description     :  ��ʼ��LED����
* EntryParameter  :  None
* ReturnValue     :  None 
*****/
void LedInit(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //ʹ��IOCONʱ��
	LPC_IOCON->PIO2_0 &= ~0x07;
	LPC_IOCON->PIO2_0 |= 0x00;
	LPC_IOCON->PIO2_1 &= ~0x07;
	LPC_IOCON->PIO2_1 |= 0x00;
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
	LPC_GPIO2->DIR |=(1<<0);
	LPC_GPIO2->DATA |=(1<<0);
	LPC_GPIO2->DIR |=(1<<1);
	LPC_GPIO2->DATA |=(1<<1);
}
	/*******
* FunctionName    :  SysTickInit()
* Description     :  ��ʼ��ϵͳ���Ķ�ʱ��
EntryParameter  :  None
* ReturnValue     :  None 
*****/
	void SysTickInit(void)
{
		SysTick->CTRL &=~(1<<2);
	  SysTick->LOAD = 12499999;
	  SysTick->VAL = 0;
	  SysTick->CTRL |=((1<<1)|(1<<0));
	NVIC_EnableIRQ(SysTick_IRQn);
}
/*******
* FunctionName    :  SysTick_Handler()
* Description     :  ϵͳ���Ķ�ʱ���жϷ�����
* EntryParameter  :  None
* ReturnValue     :  None 
*****/
void SysTick_Handler(void)
{
	status = LPC_GPIO2->DATA ;
	LPC_GPIO2->DATA = ~ status ;
}
/*******
* FunctionName    :  main()
* Description     :  ������
* EntryParameter  :  None
* ReturnValue     :  None 
*****/
int main (void)
{
	LedInit ();
	SystemInit ();
	while(1);
}
