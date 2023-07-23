#include "color_generator.h"

// Note: D = 0 and D = 1 cannot be generated with PWM

void setup()
{
    // set system clock frequency and PWM clock frequency
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Port F GPIO
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait for peripheral to be enabled
    }

    // Port F PWM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1))
    {
        // wait for peripheral to be enabled
    }
}

void init_wifi_started()
{
    // red - 255, green - 102, blue - 255

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED, RED_LED | BLUE_LED);

    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GREEN_LED);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet() / FREQ);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * GREEN_WIFI_STARTED);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
}

void init_http_started()
{
    // red - 255, green - 255, blue - 51

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | GREEN_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | GREEN_LED, RED_LED | GREEN_LED);

    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinTypePWM(GPIO_PORTF_BASE, BLUE_LED);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet() / FREQ);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * BLUE_HTTP_STARTED);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
}

void init_wifi_connected()
{
    // red - 0, green - 255, blue - 153

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GREEN_LED);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
    
    GPIOPinConfigure(GPIO_PF2_M1PWM6);
    GPIOPinTypePWM(GPIO_PORTF_BASE, BLUE_LED);

    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet() / FREQ);
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3) * BLUE_WIFI_CONNECTED);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
}
