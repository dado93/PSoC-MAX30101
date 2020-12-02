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
#include "I2C_Interface.h"

#define UART_DEBUG

#ifdef UART_DEBUG
    
    #define DEBUG_TEST 1
    
#else
    
    #define DEBUG_TEST 0
    
#endif

#define debug_print(msg) do { if (DEBUG_TEST) UART_Debug_PutString(msg);} while (0)

void MAX30101_PrintRegister(uint8_t reg_addr)
{
    uint8_t value;
    MAX30101_ReadRegister(reg_addr, &value);
    char msg[20];
    sprintf(msg, "[0x%02X] - 0x%02X\r\n", reg_addr, value);
    debug_print(msg);
}

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
        // Check if device is present
        debug_print("Device found on I2C bus\r\n");
        Connection_LED_Write(1);
        
        // Read revision and part id
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
        
        // Soft reset sensor
        MAX30101_Reset();
        MAX30101_PrintRegister(MAX30101_MODE_CONF);
        CyDelay(100);
        
        // Wake up sensor
        //MAX30101_Shutdown();
        //MAX30101_PrintRegister(MAX30101_MODE_CONF);
        
        // enable fifo almost full interrupt
        MAX30101_EnableFIFOAFullInt();
        MAX30101_PrintRegister(MAX30101_INT_EN_1);
        // set only 1 sample to trigger interrupt
        MAX30101_SetFIFOAlmostFull(10);
        MAX30101_PrintRegister(MAX30101_FIFO_CONF);
        // enable fifo rollover
        MAX30101_EnableFIFORollover();
        MAX30101_PrintRegister(MAX30101_FIFO_CONF);
        // 8 samples averaged
        MAX30101_SetSampleAverage(MAX30101_SAMPLE_AVG_8);
        MAX30101_PrintRegister(MAX30101_FIFO_CONF);
        // Set LED Power level
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_1, 0x1F);
        MAX30101_PrintRegister(MAX30101_LED1_PA);
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_2, 0x1F);
        MAX30101_PrintRegister(MAX30101_LED2_PA);
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_3, 0x1F);
        MAX30101_PrintRegister(MAX30101_LED3_PA);
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_4, 0x1F);
        MAX30101_PrintRegister(MAX30101_LED4_PA);
        // Set ADC Range
        MAX30101_SetSpO2ADCRange(MAX30101_ADC_RANGE_4096);
        MAX30101_PrintRegister(MAX30101_SPO2_CONF);
        // Pulse width
        MAX30101_SetSpO2PulseWidth(MAX30101_PULSEWIDTH_411);
        MAX30101_PrintRegister(MAX30101_SPO2_CONF);
        // Set Sample Rate
        MAX30101_SetSpO2SampleRate(MAX30101_SAMPLE_RATE_100);
        MAX30101_PrintRegister(MAX30101_SPO2_CONF);
        
        // Set mode
        MAX30101_SetMode(MAX30101_MULTI_MODE);
        MAX30101_PrintRegister(MAX30101_MODE_CONF);
        
        // Enable Slots
        MAX30101_DisableSlots();
        MAX30101_EnableSlot(1, MAX30101_SLOT_RED);
        MAX30101_EnableSlot(2, MAX30101_SLOT_IR);
        MAX30101_EnableSlot(3, MAX30101_SLOT_GREEN);
        
        MAX30101_PrintRegister(MAX30101_MULTI_LED_1);
        MAX30101_PrintRegister(MAX30101_MULTI_LED_2);
        MAX30101_ClearFIFO();
        MAX30101_PrintRegister(MAX30101_FIFO_RP);
        MAX30101_PrintRegister(MAX30101_FIFO_WP);
        MAX30101_PrintRegister(MAX30101_FIFO_OVF_CNT); 
    }
    
    uint8_t active_leds = 3;
    uint8_t rp, wp, flag = 0;
    uint8_t data_to_send[5];
    data_to_send[0] = 0xA0;
    CyDelay(200);
    
    MAX30101_Data data;
    
    for(;;)
    {
        
        while(flag == 0)
        {
            MAX30101_IsFIFOAFull(&flag);
        }
        
        flag = 0;
        
        
        // Read read pointer and write pointer
        MAX30101_ReadReadPointer(&rp);
        MAX30101_ReadWritePointer(&wp);
        //Calculate the number of readings we need to get from sensor
        uint8_t num_samples = wp - rp;
        if (num_samples < 0) 
            num_samples += 32; //Wrap condition
        else if (num_samples > 0)
        {         
            MAX30101_ReadFIFO(num_samples, active_leds, &data);
            data_to_send[1] = 0;
            data_to_send[2] = data.red[data.head] >> 16;
            data_to_send[3] = data.red[data.head] >> 8;
            data_to_send[4] = data.red[data.head]  & 0xFF;
            //sprintf(msg, "%d\r\n", data.IR[data.head]);
            //UART_Debug_PutString(msg);
            UART_Debug_PutArray(data_to_send, 5);
        }
        
    }
}

/* [] END OF FILE */
