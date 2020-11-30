/**
*   \file MAX30101_Defs.h
*   
*   \brif Defines for MAX30101 Library.
*/

#ifndef __MAX30101_DEFS_H__
    #define __MAX30101_DEFS_H__
    
    #include "cytypes.h"
    
    //==============================================
    //              MAX30101 ERRORS
    //==============================================
    /**
    *   \brief I2C Address of MAX30101.
    */
    #define MAX30101_I2C_ADDRESS 0x57
    
    /**
    *   \brief Error condition triggered when device is not found on I2C bus.
    */
    #define MAX30101_DEV_NOT_FOUND 1
    
    /**
    *   \brief No error generated.
    */
    #define MAX30101_OK 0
    
    /**
    *   \brief Generic error condition related to MAX30101.
    */
    #define MAX30101_ERROR 2
    
    //==============================================
    //           MAX30101 I2C REGISTERS
    //==============================================
    
    /**
    *   \brief Interrupt Status 1 register.
    *
    *   Whenever an interrupt is triggered, the MAX30101 pulls the active-low
    *   interrupt pin into its low state until the interrupt is cleared. This
    *   register contains the status of the interrupts.
    *
    *   The register is structured as follows:
    *   |   B7   |   B6   |    B5  |   B4   |   B3   |   B2   |   B1   |   B0   |
    *   | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | 
    *   | A_FULL | PPG_RDY | ALC_OVF | | | | |PWR_RDY |
    *
    *   **A_FULL: FIFO Almost Full Flag**
    *
    *   In SpO2 and HR modes, this interrupt triggers when the FIFO write pointer 
    *   has a certain number of free spaces remaining. The trigger number can be set by the 
    *   #MAX3031_FIFO_CONF register. The interrupt is cleared by reading the #MAX30101_INT_ST_1 register.
    *
    *   **PPG_RDY: New FIFO Data Ready**
    *
    *   In SpO2 and HR modes, this interrupt triggers when there is a new sample in the data FIFO. 
    *   The interrupt is cleared by reading the #MAX30101_INT_ST_1, or by reading the #MAX30101_FIFO_DATA register.
    *
    *   **ALC_OVF: Ambient Light Cancellation Overflow**
    *
    *   This interrupt triggers when the ambient light cancellation function 
    *   of the SpO2/HR photodiode has reached its maximum limit,
    *   and therefore, ambient light is affecting the output of the ADC.
    *   The interrupt is cleared by reading the #MAX30101_INT_ST_1.
    *
    *   **PWR_RDY: Power Ready Flag**
    *
    *   On power-up or after a brownout condition, when the supply voltage VDD transitions
    *   from below the undervoltage lockout (UVLO) voltage to above the UVLO voltage, a 
    *   power-ready interrupt is triggered to signal that the module is powered-up and ready to collect data.
    */
    #define MAX30101_INT_ST_1 0x00
    
    /**
    *   \brief Interrupt Status 2 register.
    *
    *   The register is structured as follows:
    *   |   B7   |   B6   |    B5  |   B4   |   B3   |   B2   |   B1   |   B0   |
    *   | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | 
    *   |        |         |         | | | | DIE_TMP_RDY | |
    *
    *   **DIE_TEMP_RDY: Internal Temperature Ready Flag**
    *
    *   When an internal die temperature conversion is finished, 
    *   this interrupt is triggered so the processor can read the temperature data registers. 
    *   The interrupt is cleared by reading either the #MAX30101_INT_ST_2 or the #MAX3031_TFRAC register.
    */
    #define MAX30101_INT_ST_2 0x01
    
    /**
    *   \brief Interrupt Enable 1 register.
    *
    *
    */
    #define MAX30101_INT_EN_1
    
    /**
    *   \brief Interrupt Enable 2 register.
    *
    *
    */
    #define MAX30101_INT_EN_2
    
#endif

/* [] END OF FILE */
