/**
*   \file MAX30101.h
*   
*   \brif Header file for MAX30101 Library.
*/


#ifndef __MAX30101_H__
    #define __MAX30101_H__
    
    #include "cytypes.h"
    #include "MAX30101_Defs.h"
    
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
    //  MAX30101 MACROS FOR REGISTERS CONFIGURATION
    //==============================================
    
    /**
    *   \brief MAX30101 Heart Rate mode.
    */
    #define MAX30101_HR_MODE 0x02
    
    /**
    *   \brief MAX30101 SpO2 mode. mode.
    */
    #define MAX30101_SPO2_MODE 0x03

    /**
    *   \brief MAX30101 Multi LED mode.
    */
    #define MAX30101_MULTI_MODE 0x08
    
    /**
    *   \brief MAX30101 LED channel 1 (RED).
    */
    #define MAX30101_LED_1 0x00
    
    /**
    *   \brief MAX30101 LED channel 2 (IR).
    */
    #define MAX30101_LED_2 0x01
    
    /**
    *   \brief MAX30101 LED channel 3 (GREEN).
    */
    #define MAX30101_LED_3 0x02
    
    /**
    *   \brief MAX30101 LED channel 4 (GREEN).
    */
    #define MAX30101_LED_4 0x03
    
    /**
    *   \brief MAX30101 no average in FIFO.
    */
    #define MAX30101_SAMPLE_AVG_1 0x00
    
    /**
    *   \brief MAX30101 no average in FIFO.
    */
    #define MAX30101_SAMPLE_AVG_2 0x20
    
    /**
    *   \brief MAX30101 no average in FIFO.
    */
    #define MAX30101_SAMPLE_AVG_4 0x40
    
    /**
    *   \brief MAX30101 no average in FIFO.
    */
    #define MAX30101_SAMPLE_AVG_8 0x60
    
    /**
    *   \brief MAX30101 no average in FIFO.
    */
    #define MAX30101_SAMPLE_AVG_16 0x80
    
    /**
    *   \brief MAX30101 no average in FIFO.
    */
    #define MAX30101_SAMPLE_AVG_32 0xA0
    
    /**
    *   \brief Start the MAX30101.
    *   \retval #MAX30101_OK
    */
    uint8_t MAX30101_Start(void);
    
    /**
    *   \brief Check if MAX30101 is present on I2C bus.
    *
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsDevicePresent(void);
    
    //==============================================
    //          MAX30101 INTERRUPT FUNCTIONS
    //==============================================
    
    /**
    *   Check if FIFO A Full interrupt was set.
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsFIFOAFull(uint8_t* flag);
    
    /**
    *   Check if PPG Ready interrupt was set.
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsPPGReady(uint8_t* flag);
    
    /**
    *   Check if ALC Overflow interrupt was set.
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsALCOverflow(uint8_t* flag);
    
    /**
    *   Check if power ready interrupt was set.
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsPowerReady(uint8_t* flag);
    
    /**
    *   Check if temperature ready interrupt was set.
    *   \param flag pointer to variable where result of the check will be placed. 1 equal to true.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsTempReady(uint8_t* flag);
    
    /**
    *   Enable FIFO A Full interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnableFIFOAFullInt(void);
    
    /**
    *   Enable PPG Ready interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnablePPGReadyInt(void);
    
    /**
    *   Enable ALC Overflow interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnableALCOverflowInt(void);
    
    /**
    *   Enable Temperature ready interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_EnableTempReadyInt(void);
    
    /**
    *   Disable FIFO A Full interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_DisableFIFOAFullInt(void);
    
    /**
    *   Disable PPG ready interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_DisablePPGReadyInt(void);
    
    /**
    *   Disable ALC Overflow interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_DisableALCOverflowInt(void);
    
    /**
    *   Disable temperature ready interrupt.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_DisableTempReadyInt(void);
    
    //==============================================
    //          MAX30101 FIFO FUNCTIONS
    //==============================================
    
    /**
    *   Read FIFO Write pointer.
    *   \param wr pointer to variable where the write pointer will be saved.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadWritePointer(uint8_t* wr);
    
    /**
    *   Read FIFO Overflow counter.
    *   \param oc pointer to variable where the overflow counter will be saved.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadOverflowCounter(uint8_t* oc);
    
    /**
    *   Read FIFO read pointer.
    *   \param oc pointer to variable where the read pointer will be saved.
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.  
    */
    uint8_t MAX30101_ReadReadPointer(uint8_t* rr);
    
    //==============================================
    //          MAX30101 CONFIGURATION FUNCTIONS
    //==============================================
    
    /**
    *   \brief Set the number of samples averaged per sample in FIFO.
    *   
    *   This function sets the number of samples to be averaged per FIFO sample.
    *   Available choices go from 1 to 32.
    *   \param samples number of samples to be averaged.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetSampleAverage(uint8_t samples);
    
    /**
    *   \brief Enable FIFO Rollover.
    *   
    *   This function enables FIFO Rollover. When enabled, 
    *   the FIFO Address rolls over to zero and the FIFO continues to fill with new data. 
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_EnableFIFORollover(void);
    
    /**
    *   \brief Disable FIFO Rollover.
    *
    *   This function disables FIFO Rollover. When disabled, 
    *   FIFO is not updated until #MAX30101_FIFO_DATA is read or the 
    *   #MAX30101_WP or #MAX30101_RP positions are changed.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    */
    uint8_t MAX30101_DisableFIFORollover(void);
    
    /**
    *   \brief Set the operation mode for the MAX30101.
    *   
    *   This function sets the current LED pulse amplitude mode for 
    *   the MAX30101. Available choices are:
    *       - #MAX30101_HR_MODE: RED Led ON
    *       - #MAX30101_SPO2_MODE: RED and IR Led ON
    *       - #MAX30101_MULTI_MODE: configurable Leds
    *   \param mode mode to be set in the #MAX30101_MODE_CONF register
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetMode(uint8_t mode);
    
    /**
    *   \brief Set the pulse amplitude for a MAX30101 channel.
    *   
    *   This function sets the current LED pulse amplitude a given
    *   channel of the MAX30101.
    *   Pulse amplitude values range from 0x00 to 0xFF.
    *   \param led_channel the channel for which to set the pulse amplitude.
    *   \param pa the value of pulse amplitude to be set,.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_SetLEDPulseAmplitude(uint8_t led_channel, uint8_t pa);
    
    /**
    *   \brief Read Part ID number from MAX30101.
    *   
    *   \param part_id pointer to variable where part ID value will be stored.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_ReadPartID(uint8_t* part_id);
    
    /**
    *   \brief Read Revision ID number from MAX30101.
    *   
    *   \param revision_id pointer to variable where revision ID value will be stored.
    *   \retval #MAX30101_OK if no error occurred.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present on the I2C bus.
    *   \retval #MAX30101_ERROR if error occurred during configuration.
    */
    uint8_t MAX30101_ReadRevisionID(uint8_t* revision_id);
    
#endif
/* [] END OF FILE */
