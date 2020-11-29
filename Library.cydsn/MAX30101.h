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
    
#endif
/* [] END OF FILE */
