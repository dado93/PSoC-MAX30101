/**
*   \file MAX30101.h
*   
*   \brif Header file for MAX30101 Library.
*/


#ifndef __MAX30101_H__
    #define __MAX30101_H__
    
    #include "cytypes.h"
    #include "MAX30101_Defs.h"
    
    /**
    *   \brief Start the MAX30101.
    *   \retval #MAX30101_OK
    */
    uint8_t MAX30101_Start(void);
    
    /**
    *   \brief Check if MAX30101 is present on I2C bus.
    
    *   \retval #MAX30101_OK if device is present.
    *   \retval #MAX30101_DEV_NOT_FOUND if device is not present.
    */
    uint8_t MAX30101_IsDevicePresent(void);
    
    //==============================================
    //          MAX30101 INTERRUPT FUNCTIONS
    //==============================================
    
    uint8_t MAX30101_IsFIFOAFull(uint8_t* flag);
    uint8_t MAX30101_IsPPGReady(uint8_t* flag);
    uint8_t MAX30101_IsOverflow(uint8_t* flag);
    uint8_t MAX30101_IsPowerReady(uint8_t* flag);
    uint8_t MAX30101_IsTempReady(uint8_t* flag);
    
    uint8_t MAX30101_EnableFIFOAFullInt(void);
    uint8_t MAX30101_EnablePPGReadyInt(void);
    uint8_t MAX30101_EnableOverflowInt(void);
    uint8_t MAX30101_EnableTempReadyInt(void);
    
    //==============================================
    //          MAX30101 FIFO FUNCTIONS
    //==============================================
    
    /**
    *   \brief Set the operation mode for the MAX30101.
    *   
    *   This function sets the current LED pulse amplitude mode for 
    *   the MAX30101. Available choices are:
    *       - Heart Rate mode: RED Led ON
    *       - SpO2 mode: RED and IR Led ON
    *       - Multi LED mode: configurable Leds
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
