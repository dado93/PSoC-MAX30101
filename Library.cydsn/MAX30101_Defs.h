/**
*   \file MAX30101_Defs.h
*   
*   \brif Defines for MAX30101 Library.
*/

#ifndef __MAX30101_DEFS_H__
    #define __MAX30101_DEFS_H__
    
    #include "cytypes.h"
    
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
    
#endif

/* [] END OF FILE */
