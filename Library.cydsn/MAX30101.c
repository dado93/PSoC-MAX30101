/**
*   Source file for the MAX30101 library.
*/

#include "I2C_Interface.h"
#include "MAX30101.h"

//==============================================
//          MACROS
//==============================================

/**
*   \brief Mask for Power Ready interrupt.
*/
#define MAX30101_PWR_RDY_MASK   0xFE

/**
*   \brief Mask for FIFO A FULL interrupt.
*/
#define MAX30101_FIFO_A_FULL_MASK   0x7F

/**
*   \brief Enable FIFO A FULL interrupt.
*/
#define MAX30101_FIFO_A_FULL_ENABLE 0x80

/**
*   \brief Disable FIFO A FULL interrupt.
*/
#define MAX30101_FIFO_A_FULL_DISABLE 0x00

/**
*   \brief Mask for PPG ready interrupt.
*/
#define MAX30101_PPG_RDY_MASK     0xBF

/**
*   \brief Enable PPG ready interrupt.
*/
#define MAX30101_PPG_RDY_ENABLE 0x40

/**
*   \brief Disable PPG ready interrupt.
*/
#define MAX30101_PPG_RDY_DISABLE 0x00

/**
*   \brief Mask for FIFO overflow interrupt.
*/
#define MAX30101_ALC_OVF_MASK     0xDF

/**
*   \brief Enable OVERFLOW interrupt.
*/
#define MAX30101_ALC_OVF_ENABLE 0x20

/**
*   \brief Disable OVERFLOW interrupt.
*/
#define MAX30101_ALC_OVF_DISABLE 0x00

/**
*   \brief Mask for temperature data ready interrupt.
*/
#define MAX30101_TMP_RDY_MASK     0xFD

/**
*   \brief Enable temperature ready interrupt.
*/
#define MAX30101_TMP_RDY_ENABLE 0x02

/**
*   \brief Disable temperature ready interrupt.
*/
#define MAX30101_TMP_RDY_DISABLE 0x00

/**
*   \brief Mask for sample average settings.
*/
#define MAX30101_SMP_AVG_MASK    0x1F

/**
*   \brief Mask for fifo rollover.
*/
#define MAX30101_FIFO_ROLLOVER_MASK    0xEF

/**
*   \brief Mask for sample average settings.
*/
#define MAX30101_FIFO_ROLLOVER_ENABLE    0x10

/**
*   \brief Mask for sample average settings.
*/
#define MAX30101_FIFO_ROLLOVER_DISABLE    0x00




//==============================================
//          FUNCTION PROTOTYPESS
//==============================================
static uint8_t MAX30101_ReadRegister(uint8_t reg_addr, uint8_t* reg_value);
static uint8_t MAX30101_BitMask(uint8_t reg_addr, uint8_t mask, uint8_t thing);
static uint8_t MAX30101_WriteRegister(uint8_t reg_addr, uint8_t reg_data);

// Start the device
uint8_t MAX30101_Start(void)
{
    I2C_Peripheral_Start();
    return MAX30101_OK;
}

// Check if device is present on I2C bus
uint8_t MAX30101_IsDevicePresent(void)
{
    if (I2C_Peripheral_IsDeviceConnected(MAX30101_I2C_ADDRESS) == I2C_NO_ERROR)
    {
        return MAX30101_OK;
    }
    
    return MAX30101_DEV_NOT_FOUND;
}

//==============================================
//          INTERRUPT RELATED FUNCTIONS
//==============================================

// Check interrupt status
uint8_t MAX30101_IsFIFOAFull(uint8_t* flag)
{
    // Read register
    uint8_t temp;
    uint8_t error = MAX30101_ReadRegister(MAX30101_INT_ST_1, &temp);
    *flag = temp & (~MAX30101_FIFO_A_FULL_MASK);
    return error;
    
}

uint8_t MAX30101_IsPPGReady(uint8_t* flag)
{
    // Read register
    uint8_t temp;
    uint8_t error = MAX30101_ReadRegister(MAX30101_INT_ST_1, &temp);
    *flag = temp & (~MAX30101_PPG_RDY_MASK);
    return error;
}
uint8_t MAX30101_IsALCOverflow(uint8_t* flag)
{
    // Read register
    uint8_t temp;
    uint8_t error = MAX30101_ReadRegister(MAX30101_INT_ST_1, &temp);
    *flag = temp & (~MAX30101_ALC_OVF_MASK);
    return error;
}
uint8_t MAX30101_IsPowerReady(uint8_t* flag)
{
    // Read register
    uint8_t temp;
    uint8_t error = MAX30101_ReadRegister(MAX30101_INT_ST_1, &temp);
    *flag = temp & (~MAX30101_PWR_RDY_MASK);
    return error;
}
uint8_t MAX30101_IsTempReady(uint8_t* flag)
{
    // Read register
    uint8_t temp;
    uint8_t error = MAX30101_ReadRegister(MAX30101_INT_ST_2, &temp);
    *flag = temp & (~MAX30101_TMP_RDY_MASK);
    return error;
}
    
// Enable interrupts
uint8_t MAX30101_EnableFIFOAFullInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_FIFO_A_FULL_MASK, MAX30101_FIFO_A_FULL_ENABLE);
}
uint8_t MAX30101_EnablePPGReadyInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_PPG_RDY_MASK, MAX30101_PPG_RDY_ENABLE);
}
uint8_t MAX30101_EnableALCOverflowInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_ALC_OVF_MASK, MAX30101_ALC_OVF_ENABLE);
}

uint8_t MAX30101_EnableTempReadyInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_2, MAX30101_TMP_RDY_MASK, MAX30101_TMP_RDY_ENABLE);
}

// Disable interrupts
uint8_t MAX30101_DisableFIFOAFullInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_FIFO_A_FULL_MASK, MAX30101_FIFO_A_FULL_DISABLE);
}

uint8_t MAX30101_DisablePPGReadyInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_PPG_RDY_MASK, MAX30101_PPG_RDY_DISABLE);
}

uint8_t MAX30101_DisableALCOverflowInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_ALC_OVF_MASK, MAX30101_ALC_OVF_DISABLE);
}

uint8_t MAX30101_DisableTempReadyInt(void)
{
    return MAX30101_BitMask(MAX30101_INT_EN_1, MAX30101_TMP_RDY_MASK, MAX30101_TMP_RDY_DISABLE);
}

//==============================================
//          FIFO FUNCTIONS
//==============================================
uint8_t MAX30101_ReadWritePointer(uint8_t* wr)
{
    return MAX30101_ReadRegister(MAX30101_FIFO_WP, wr);
}

uint8_t MAX30101_ReadOverflowCounter(uint8_t* oc)
{
    return MAX30101_ReadRegister(MAX30101_FIFO_OVF_CNT, oc);
}

uint8_t MAX30101_ReadReadPointer(uint8_t* rr)
{
    return MAX30101_ReadRegister(MAX30101_FIFO_RP, rr);
}


//==============================================
//          CONFIGURATION FUNCTIONS
//==============================================

/// Set number of averaged samples
uint8_t MAX30101_SetSampleAverage(uint8_t samples)
{
    return MAX30101_BitMask(MAX30101_FIFO_CONF, MAX30101_SMP_AVG_MASK, samples);
}

uint8_t MAX30101_EnableFIFORollover(void)
{
    return MAX30101_BitMask(MAX30101_MODE_CONF, MAX30101_FIFO_ROLLOVER_MASK, MAX30101_FIFO_ROLLOVER_ENABLE);
}

uint8_t MAX30101_DisableFIFORollover(void)
{
    return MAX30101_BitMask(MAX30101_MODE_CONF, MAX30101_FIFO_ROLLOVER_MASK, MAX30101_FIFO_ROLLOVER_DISABLE);
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

// Read part ID number
uint8_t MAX30101_ReadPartID(uint8_t* part_id)
{
    return MAX30101_ReadRegister(MAX30101_PART_ID, part_id);
    
}

// Read revision ID number
uint8_t MAX30101_ReadRevisionID(uint8_t* revision_id)
{
    return MAX30101_ReadRegister(MAX30101_REVISION_ID, revision_id);
}

// Simple helper function to read a register from the MAX30101
static uint8_t MAX30101_ReadRegister(uint8_t reg_addr, uint8_t* reg_value)
{
    uint8_t error = MAX30101_OK;
    uint8_t reg_data;
    if(I2C_Peripheral_ReadRegister(MAX30101_I2C_ADDRESS, reg_addr, &reg_data) == I2C_NO_ERROR)
    {
        *reg_value = reg_data;
    }
    else
    {
        error = MAX30101_DEV_NOT_FOUND;
    }
    return error;
}

// Simple helper function to write a register to the MAX30101
static uint8_t MAX30101_WriteRegister(uint8_t reg_addr, uint8_t reg_data)
{
    uint8_t error = MAX30101_OK;
    if(I2C_Peripheral_WriteRegister(MAX30101_I2C_ADDRESS, reg_addr, reg_data) != I2C_NO_ERROR)
    {
        error = MAX30101_DEV_NOT_FOUND;
    }
    return error;
}

// Simple helper function to perform bit mask operations
static uint8_t MAX30101_BitMask(uint8_t reg_addr, uint8_t mask, uint8_t thing)
{
    uint8_t reg_data;
    uint8_t error = MAX30101_ReadRegister(reg_addr, &reg_data);
    if (error == MAX30101_OK)
    {
        reg_data = reg_data & mask;
        error = MAX30101_WriteRegister(reg_addr, reg_data | thing);
    }
    return error;
}
/* [] END OF FILE */
