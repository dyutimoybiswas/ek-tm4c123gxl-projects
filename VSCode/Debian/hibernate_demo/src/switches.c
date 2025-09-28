#include "switches.h"
#include "uart_logging.h"
#include "hibernate_mode.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/hibernate.h"
#include "inc/hw_memmap.h"


void systick_handler(void)
{	
	// RTC wake.
	if(!(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) & GPIO_PIN_4))
	{
		if(!HibernateIsActive())
		{
			hibernate_setup();
			
			// Configure RTC.
			HibernateRTCEnable();
			HibernateRTCSet(0);
			HibernateRTCMatchSet(0, HibernateRTCGet() + RTC_SECONDS);
		
			// Request hibernation.
			HibernateRequest();
			uart_write("Entering hibernate...");
			uart_write(newline_carriage_return);
		}
	}
}

void gpio_handler(void)
{
	// Clear interrupt bit.
	uint32_t status = GPIOIntStatus(GPIO_PORTF_BASE, true);
	GPIOIntClear(GPIO_PORTF_BASE, status);
	
	// Set value for 200ms debounce delay.
	SysTickPeriodSet(SYSTICK_PERIOD);
	SysTickEnable();
}

void switches_setup(void)
{
	// Configure SW1 and SW2 as inputs.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
	{
			// wait till peripheral is ready
	}
	
	// Set gpio interrupt.
	GPIOIntRegister(GPIO_PORTF_BASE, gpio_handler);
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_RISING_EDGE);
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
	
	// Set switch pins as input.
	GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	// Set systick_handler interrupt.
	SysTickIntRegister(systick_handler);
	SysTickIntEnable();
}
