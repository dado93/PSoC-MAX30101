/**
*   This project allows you to compute
*   the effective sampling rate of the
*   MAX30101. Simply change the 
*   sample rate configuration, and see
*   the true sample rate printed out
*   on the serial port.
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


int main(void)
{
    CyGlobalIntEnable; // Enable global interrupts.

    MAX30101_Start();
    UART_Debug_Start();
    Timer_SR_Start();

    CyDelay(100);
    
    // Variables
    char msg[50];
    void (*print_ptr)(const char*) = &(UART_Debug_PutString);
    uint8_t active_leds = 1;
    uint8_t rp, wp, flag = 0;
    
    
    debug_print("**************************\r\n");
    debug_print("   MAX30101 SAMPLE RATE    \r\n");
    debug_print("**************************\r\n");
    
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
        MAX30101_EnableFIFOAFullInt();
     
        // set 28 samples to trigger interrupt
        MAX30101_SetFIFOAlmostFull(32);

        // enable fifo rollover
        MAX30101_EnableFIFORollover();
        
        // 8 samples averaged
        MAX30101_SetSampleAverage(MAX30101_SAMPLE_AVG_1);
        
        // Set LED Power level
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_1, 0x1F);
        
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_2, 0x1F);
        
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_3, 0x1F);
        
        MAX30101_SetLEDPulseAmplitude(MAX30101_LED_4, 0x1F);
        
        // Set ADC Range
        MAX30101_SetSpO2ADCRange(MAX30101_ADC_RANGE_4096);
        
        // Pulse width
        MAX30101_SetSpO2PulseWidth(MAX30101_PULSEWIDTH_69);
        
        // Set Sample Rate
        MAX30101_SetSpO2SampleRate(MAX30101_SAMPLE_RATE_3200);
        
        // Set mode
        MAX30101_SetMode(MAX30101_HR_MODE);
        
        // Enable Slots
        MAX30101_DisableSlots();
        
        debug_print("Registers after configuration\r\n");
        MAX30101_LogRegisters(print_ptr);
    }
    
    debug_print("\r\n\r\n");

    // Clear FIFO
    MAX30101_ClearFIFO();
    
    uint32_t start_time = 0;
    
    for(;;)
    {
        uint16_t samples = 0;
        start_time = Timer_SR_ReadCounter();
        
        while (samples < 100)
        {
            MAX30101_ReadReadPointer(&rp);
            MAX30101_ReadWritePointer(&wp);
            //Calculate the number of readings we need to get from sensor
            int num_samples = wp - rp;
            if (num_samples < 0) 
                num_samples += 32; //Wrap condition
            samples += num_samples;
            uint8_t raw_bytes[num_samples*active_leds*3];
            MAX30101_ReadRawFIFOBytes(num_samples, active_leds, raw_bytes);  
        }
        
        uint32_t end_time = Timer_SR_ReadCounter();
        int32_t diff =  start_time - end_time;
        float sr = (float)(samples) / (diff/1000000.0);
        sprintf(msg, "Hz: %d.%d\r\n", (int)(sr),((int)(sr*100)%100));
        debug_print(msg);
        
    }   

}

/* [] END OF FILE */
