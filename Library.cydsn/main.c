/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "MAX30101.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    MAX30101_Start();
    UART_Debug_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    if (MAX30101_IsDevicePresent() == MAX30101_OK)
    {
        Connection_LED_Write(1);
    }
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
