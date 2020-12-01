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
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    MAX30101_Start();
    UART_Debug_Start();
    CyDelay(100);
    char msg[50];
    
    
    UART_Debug_PutString("**************************\r\n");
    UART_Debug_PutString("         MAX30101         \r\n");
    UART_Debug_PutString("**************************\r\n");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    if (MAX30101_IsDevicePresent() == MAX30101_OK)
    {
        UART_Debug_PutString("Device found on I2C bus\r\n");
        Connection_LED_Write(1);
        MAX30101_SetMode(MAX30101_SPO2_MODE);
        for (uint8_t i = 0; i < 0xFF; i++)
        {
            MAX30101_SetLEDPulseAmplitude(MAX30101_LED_1, i);
            MAX30101_SetLEDPulseAmplitude(MAX30101_LED_2, i);
            CyDelay(500);
            
        }
        uint8_t rev_id, part_id = 0;
        MAX30101_ReadPartID(&part_id);
        MAX30101_ReadRevisionID(&rev_id);
        sprintf(msg,"Revision ID: 0x%02X\r\n", rev_id);
        UART_Debug_PutString(msg);
        sprintf(msg,"Part ID: 0x%02X\r\n", part_id);
        UART_Debug_PutString(msg);
    }
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
