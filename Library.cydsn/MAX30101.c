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

/* [] END OF FILE */
