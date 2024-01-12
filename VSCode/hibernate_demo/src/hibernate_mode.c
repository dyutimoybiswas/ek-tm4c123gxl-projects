#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"
#include "uart_logging.h"
#include "hibernate_mode.h"
#include "switches.h"


void hibernate_handler(void)
{
    uint32_t status = HibernateIntStatus(true);
    HibernateIntClear(status);

    // Print cause of wake.
    uart_write("Cause of wake: ");
    if (status & HIBERNATE_INT_PIN_WAKE)
    {			
        uart_write("Wake pin (SW2).");
				uart_write(newline_carriage_return);
			
				// Request hibernation.
				HibernateRequest();
				uart_write("Entering hibernate...");
				uart_write(newline_carriage_return);
    }
    if (status & HIBERNATE_INT_RTC_MATCH_0)
    {			
        uart_write("RTC 0 match.");
				uart_write(newline_carriage_return);
			
				// Enter hibernation again.
				HibernateRTCMatchSet(0, HibernateRTCGet() + RTC_SECONDS);
	
				// Request hibernation.
				HibernateRequest();
				uart_write("Entering hibernate...");
				uart_write(newline_carriage_return);
    }
}

void hibernate_setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE))
    {
        // wait for peripheral to be ready.
    }
    
    HibernateEnableExpClk(SysCtlClockGet());
    HibernateClockConfig(HIBERNATE_OSC_HIGHDRIVE);

    // Register interrupt handler.
    HibernateIntEnable(HIBERNATE_INT_PIN_WAKE | HIBERNATE_INT_RTC_MATCH_0);
    HibernateIntRegister(hibernate_handler);
		
		// Configure wake conditions.
		#ifdef SW2
    HibernateWakeSet(HIBERNATE_WAKE_PIN);
		#endif
}

int main(int argc, char const *argv[])
{
    // set processor clock frequency = 16 MHz.
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    uart_setup();

    if (HibernateIsActive())
    {
      uart_write("Hibernate active.\n\r");
    }
    else
    {
      uart_write("Hibernate inactive.\n\r");
    }
    
	
		#ifdef SW1
		switches_setup();
		#elif defined(SW2)
		hibernate_setup();
	
		// Request hibernation.
		HibernateRequest();
		uart_write("Entering hibernate...");
		uart_write(newline_carriage_return);
		#endif
	
    while (true)
    {
        //TODO
    }
    

    return 0;
}
