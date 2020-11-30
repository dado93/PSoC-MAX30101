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

#include "I2C_Interface.h"
#include "MAX30101.h"

uint8_t MAX30101_Start(void)
{
    I2C_Peripheral_Start();
    return MAX30101_OK;
}

uint8_t MAX30101_IsDevicePresent(void)
{
    if (I2C_Peripheral_IsDeviceConnected(MAX30101_I2C_ADDRESS) == I2C_NO_ERROR)
    {
        return MAX30101_OK;
    }
    
    return MAX30101_DEV_NOT_FOUND;
}

// Set current mode of operation
uint8_t MAX30101_SetMode(uint8_t mode)
{
    // Read register
    uint8_t error = MAX30101_OK;
    uint8_t reg_data;
    error = I2C_Peripheral_ReadRegister(MAX30101_I2C_ADDRESS, MAX30101_MODE_CONF, &reg_data);
    if (error == I2C_NO_ERROR)
    {
        reg_data |= mode;
        if(I2C_Peripheral_WriteRegister(MAX30101_I2C_ADDRESS, MAX30101_MODE_CONF, reg_data) != I2C_NO_ERROR)
        {
          error = MAX30101_ERROR;
        }
    }
    else
    {
        error = MAX30101_DEV_NOT_FOUND;
    }
    return error;
}

// Set pulse amplitude for a channel
uint8_t MAX30101_SetLEDPulseAmplitude(uint8_t led_channel, uint8_t pa)
{
    // Read register
    uint8_t error = MAX30101_OK;
    uint8_t reg_data;
    error = I2C_Peripheral_ReadRegister(MAX30101_I2C_ADDRESS, MAX30101_LED1_PA + led_channel, &reg_data);
    if (error == I2C_NO_ERROR)
    {
        reg_data |= pa;
        if(I2C_Peripheral_WriteRegister(MAX30101_I2C_ADDRESS, MAX30101_LED1_PA + led_channel, reg_data) != I2C_NO_ERROR)
        {
          error = MAX30101_ERROR;
        }
    }
    else
    {
        error = MAX30101_DEV_NOT_FOUND;
    }
    return error;
}

uint8_t MAX30101_ReadPartID(uint8_t* part_id)
{
    uint8_t error = MAX30101_OK;
    uint8_t reg_data;
    if(I2C_Peripheral_ReadRegister(MAX30101_I2C_ADDRESS, MAX30101_PART_ID, &reg_data) == I2C_NO_ERROR)
    {
        *part_id = reg_data;
    }
    else
    {
        error = MAX30101_DEV_NOT_FOUND;
    }
    return error;
    
}
    
uint8_t MAX30101_ReadRevisionID(uint8_t* revision_id)
{
    uint8_t error = MAX30101_OK;
    uint8_t reg_data;
    if(I2C_Peripheral_ReadRegister(MAX30101_I2C_ADDRESS, MAX30101_REVISION_ID, &reg_data) == I2C_NO_ERROR)
    {
        *revision_id = reg_data;
    }
    else
    {
        error = MAX30101_DEV_NOT_FOUND;
    }
    return error;
    
}
    
/* [] END OF FILE */
