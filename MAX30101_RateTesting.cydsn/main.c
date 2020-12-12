/**
*   Main file for testing MAX30101 Library.
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

CY_ISR_PROTO(MAX30101_ISR);

uint8_t flag_temp = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    MAX30101_Start();
    UART_Debug_Start();
    Timer_SR_Start();

    CyDelay(100);
    
    // Variables
    char msg[50];
    void (*print_ptr)(const char*) = &(UART_Debug_PutString);
    uint8_t active_leds = 2;
    uint8_t rp, wp, flag = 0;
    
    
    debug_print("**************************\r\n");
    debug_print("   MAX30101 SAMPLE RATE    \r\n");
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
        
        debug_print("Registers before configuration\r\n");
        MAX30101_LogRegisters(print_ptr);
        
        // Soft reset sensor
        MAX30101_Reset();
        CyDelay(100);
        
        // Wake up sensor
        MAX30101_WakeUp();
        
        MAX30101_DisableALCOverflowInt();
        MAX30101_DisableTempReadyInt();
        MAX30101_DisablePPGReadyInt();
        MAX30101_DisableFIFOAFullInt();
     
        // set 28 samples to trigger interrupt
        MAX30101_SetFIFOAlmostFull(28);

        // enable fifo rollover
        MAX30101_EnableFIFORollover();
        
        // 1 sample averaged
        MAX30101_SetSampleAverage(MAX30101_SAMPLE_AVG_1);
        
        // Set LED Power level
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_1, 0x1F);
        
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_2, 0x1F);
        
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_3, 0x1F);
        
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_4, 0x1F);
        
        // Set ADC Range
        MAX30101_SetSpO2ADCRange(MAX30101_ADC_RANGE_16384);
        
        // Pulse width
        MAX30101_SetSpO2PulseWidth(MAX30101_PULSEWIDTH_69);
        
        // Set Sample Rate
        MAX30101_SetSpO2SampleRate(MAX30101_SAMPLE_RATE_50);
        
        // Set mode
        MAX30101_SetMode(MAX30101_HR_MODE);
        
        // Disable Slots
        MAX30101_DisableSlots();
        
        debug_print("Registers after configuration\r\n");
        MAX30101_LogRegisters(print_ptr);
    }
    
    debug_print("\r\n\r\n");

    // Enable interrupt
    isr_MAX30101_StartEx(MAX30101_ISR);
    // Clear FIFO
    MAX30101_ClearFIFO();
    
    uint16_t total_samples = 0;
    uint32_t start_time = 0;
    uint8_t first_time = 0;
    
    for(;;)
    {
       
        if (flag_temp == 1)
        {
            MAX30101_IsFIFOAFull(&flag);
            if (flag > 0)
            {   

                MAX30101_ReadReadPointer(&rp);
                MAX30101_ReadWritePointer(&wp);
                //Calculate the number of readings we need to get from sensor
                int num_samples = wp - rp;
                if (num_samples <= 0) 
                    num_samples += 32; //Wrap condition
                total_samples += num_samples;
                uint8_t raw_bytes[num_samples*active_leds*3];
                MAX30101_ReadRawFIFOBytes(num_samples, active_leds,raw_bytes);
                
                if (first_time == 0)
                {
                    start_time = Timer_SR_ReadCounter();
                    first_time = 1;
                }
            }
            
            flag_temp = 0;
            flag = 0;
        }   
        
        if (total_samples > 200)
        {
            int32_t diff =  start_time - Timer_SR_ReadCounter();
            
            sprintf(msg, "%d - Hz: %d\r\n", total_samples, (int)((total_samples-28) / (diff/1000000.0)));
            debug_print(msg);
            total_samples = 0;
            first_time = 0;  
        }
        
    }
    
    
}

CY_ISR(MAX30101_ISR)
{
    Connection_LED_Write(!Connection_LED_Read());
    MAX30101_INT_ClearInterrupt();
    flag_temp = 1;
}

/* [] END OF FILE */
