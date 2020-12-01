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

#define UART_DEBUG

#ifdef UART_DEBUG
    
    #define DEBUG_TEST 1
    
#else
    
    #define DEBUG_TEST 0
    
#endif

#define debug_print(msg) do { if (DEBUG_TEST) UART_Debug_PutString(msg);} while (0)

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    MAX30101_Start();
    UART_Debug_Start();
    CyDelay(100);
    char msg[50];
    
    
    debug_print("**************************\r\n");
    debug_print("         MAX30101         \r\n");
    debug_print("**************************\r\n");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    if (MAX30101_IsDevicePresent() == MAX30101_OK)
    {
        debug_print("Device found on I2C bus\r\n");
        Connection_LED_Write(1);
        MAX30101_SetMode(MAX30101_SPO2_MODE);
        
        uint8_t rev_id, part_id = 0;
        MAX30101_ReadPartID(&part_id);
        MAX30101_ReadRevisionID(&rev_id);
        sprintf(msg,"Revision ID: 0x%02X\r\n", rev_id);
        debug_print(msg);
        sprintf(msg,"Part ID: 0x%02X\r\n", part_id);
        debug_print(msg);
        
        // Start temperature conversion
        MAX30101_EnableTempReadyInt();
        MAX30101_StartTemperatureConversion();
        uint8_t flag = 0;
        while(flag == 0)
        {
            MAX30101_IsTempReady(&flag);
        }
        float temperature;
        MAX30101_ReadTemperature(&temperature);
        sprintf(msg,"Temperature: %d\r\n", (int)(temperature*1000));
        debug_print(msg);
        
    }
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
