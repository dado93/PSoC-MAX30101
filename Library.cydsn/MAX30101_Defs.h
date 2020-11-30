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
    //     MAX30101 INTERRUPT STATUTS I2C REGISTERS
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
    *   #MAX30101_FIFO_CONF register. The interrupt is cleared by reading the #MAX30101_INT_ST_1 register.
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
    *   Whenever an interrupt is triggered, the MAX30101 pulls the active-low
    *   interrupt pin into its low state until the interrupt is cleared. This
    *   register contains the status of the interrupts.
    
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
    
    //==============================================
    //   MAX30101 INTERRUPT ENABLE I2C REGISTERS
    //==============================================
    /**
    *   \brief Interrupt Enable 1 register.
    *
    *   Each source of hardware interrupt, with the exception of power ready, can be disabled in a 
    *   software register within the MAX30101 IC. The power-ready interrupt cannot be disabled 
    *   because the digital state of the module is reset upon a brownout condition (low power supply voltage),
    *   and the default condition is that all the interrupts are disabled. 
    *   Also, it is important for the system to know that a brownout condition has occurred, 
    *   and the data within the module is reset as a result.
    *   The unused bits should always be set to zero for normal operation.
    *
    *   The register is structured as follows:
    *   |   B7   |   B6   |    B5  |   B4   |   B3   |   B2   |   B1   |   B0   |
    *   | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | 
    *   | A_FULL_EN | PPG_RDY_EN | ALC_OVF_EN | | | | | |
    *
    */
    #define MAX30101_INT_EN_1 0x02
    
    /**
    *   \brief Interrupt Enable 2 register.
    *
    *   Each source of hardware interrupt, with the exception of power ready, can be disabled in a 
    *   software register within the MAX30101 IC. The power-ready interrupt cannot be disabled 
    *   because the digital state of the module is reset upon a brownout condition (low power supply voltage),
    *   and the default condition is that all the interrupts are disabled. 
    *   Also, it is important for the system to know that a brownout condition has occurred, 
    *   and the data within the module is reset as a result.
    *   The unused bits should always be set to zero for normal operation.
    *
    *   The register is structured as follows:
    *   |   B7   |   B6   |    B5  |   B4   |   B3   |   B2   |   B1   |   B0   |
    *   | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | 
    *   |        |         |         | | | | DIE_TMP_RDY_EN | |
    */
    #define MAX30101_INT_EN_2 0x03
    
    //==============================================
    //        MAX30101 FIFO I2C REGISTERS
    //==============================================
    /**
    *   \brief FIFO write pointer register.
    *
    *   The FIFO Write Pointer points to the location where the MAX30101 writes the next sample. 
    *   This pointer advances for each sample pushed on to the FIFO.
    *   It can also be changed through the I2C interface when MODE[2:0] in #MAX30101_MODE_CONF is 010, 011, or 111.
    *
    *   The register is structured as follows:
        <table>
        <caption id="fifo_wp">MAX30101 FIFO Write Pointer Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td>-<td>-<td colspan=5, style="text-align:center">FIFO_WR_PTR[4:0]
        </table>
    */
    #define MAX30101_FIFO_WP 0x04
    
    /**
    *   \brief FIFO overflow counter register.
    *
    *   When the FIFO is full, samples are not pushed on to the FIFO, samples are lost. 
    *   OVF_COUNTER counts the number of samples lost. It saturates at 0x1F.
    *   When a complete sample is “popped” (i.e., removal of old FIFO data and shifting the samples down) 
    *   from the FIFO (when the read pointer advances), OVF_COUNTER is reset to zero.
    *
    *   The register is structured as follows:
        <table>
        <caption id="fifo_ovf">MAX30101 FIFO Overflow Counter Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td>-<td>-<td colspan=5, style="text-align:center">OVF_COUNTER[4:0]
        </table>
    */
    #define MAX30101_FIFO_OVF_CNT 0x05
    
    /**
    *   \brief FIFO read pointer register.
    *
    *   The FIFO Read Pointer points to the location from where the processor gets the next sample
    *   from the FIFO through the I2C interface. This advances each time a sample is popped from
    *   the FIFO. The processor can also write to this pointer after reading the samples 
    *   to allow rereading samples from the FIFO if there is a data communication error.
    *
    *   The register is structured as follows:
        <table>
        <caption id="fifo_rp">MAX30101 FIFO Read Pointer Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td>-<td>-<td>-<td colspan=5, style="text-align:center">FIFO_RD_PTR[4:0]
        </table>
    */
    #define MAX30101_FIFO_RP 0x06
    
    /**
    *   \brief FIFO data register.
    *
    *   The circular FIFO depth is 32 and can hold up to 32 samples of data.
    *   The sample size depends on the number of LED channels (a.k.a. channels) configured as active. 
    *   As each channel signal is stored as a 3-byte data signal, the FIFO width can be 3 bytes, 6 bytes, 9 bytes, 
    *   or 12 bytes in size. The #MAX30101_FIFO_DATA register in the I2C register map points to the next sample to be read 
    *   from the FIFO. #MAX30101_FIFO_RP points to this sample. Reading #MAX30101_FIFO_DATA register, 
    *   does not automatically increment the I2C register address. Burst reading this register, 
    *   reads the same address over and over.
    *   Each sample is 3 bytes of data per channel (i.e., 3 bytes for RED, 3 bytes for IR, etc.). 
    *   The FIFO registers (0x04–0x07) can all be written and read, but in practice only the #MAX30101_FIFO_RP
    *   register should be written to in operation. The others are automatically incremented or filled with data 
    *   by the MAX30101. When starting a new SpO2 or heart rate conversion, it is recommended to first clear 
    *   the #MAX30101_FIFO_WP, #MAX30101_OVF_CNT, and #MAX30101_FIFO_RP registers to all zeroes (0x00) 
    *   to ensure the FIFO is empty and in a known state. When reading the MAX30101 registers in one
    *   burst-read I2C transaction, the register address pointer typically increments so that the next byte of
    *   data sent is from the next register, etc. The exception to this is the #MAX30101_FIFO_DATA data register,
    *   register 0x07. When reading this register, the address pointer does not increment, but the #MAX30101_FIFO_RP does.
    *   So the next byte of data sent represents the next byte of data available in the FIFO.
    *
    *   The register is structured as follows:
        <table>
        <caption id="fifo_data">MAX30101 FIFO Data Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td colspan=8, style="text-align:center">FIFO_DATA[7:0]
        </table>
    */
    #define MAX30101_FIFO_DATA 0x07
    
    //==============================================
    //   MAX30101 CONFIGURATION I2C REGISTERS
    //==============================================
    
    /**
    *   \brief FIFO Configuration register.
    *   
    *   This register allows to configure the FIFO behaviour.
    
    *   It is structured as follows:
        <table>
        <caption id="fifo_conf">MAX30101 FIFO Configuration Register</caption>
        <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0
        <tr><td colspan=3, style="text-align:center">SMP_AVG[2:0]<td> FIFO_ROL_LOVER_EN<td colspan=4, style="text-align:center">FIFO_A_FULL[3:0]
        </table>
    *
    *   **Bits 7:5: Sample Averaging (SMP_AVE)**
    *
    *   To reduce the amount of data throughput, adjacent samples (in each individual channel)
    *   can be averaged and decimated on the chip by setting this register.
    *
    *   | SMP_AVG[2:0] | NO. OF SAMPLES AVG PER SAMPLE |
    *   |:------------:|:-----------------------------:|
    *   |   000        |  1 (no averaging)             |
    *   |   001        |                 2             |
    *   |   010        |                 4             |
    *   |   011        |                 8             |
    *   |   100        |                16             |
    *   |   101        |                32             |
    *   |   110        |                32             |
    *   |   111        |                32             |
    *
    *   **Bit 4: FIFO Rolls on Full (FIFO_ROLLOVER_EN)**
    *
    *   This bit controls the behavior of the FIFO when the FIFO becomes
    *   completely filled with data. If FIFO_ROLLOVER_EN is set (1), 
    *   the FIFO Address rolls over to zero and the FIFO continues to fill 
    *   with new data. If the bit is not set (0), then the FIFO is not updated 
    *   until FIFO_DATA is read or the WRITE/READ pointer positions are changed.
    *   
    *   **Bits 3:0: FIFO Almost Full Value (FIFO_A_FULL) **
    *   
    *   This register sets the number of data samples (3 bytes/sample) remaining in the FIFO when the interrupt is issued. 
    *   For example, if this field is set to 0x0, the interrupt is issued when there is 0 data samples remaining in the 
    *   FIFO (all 32 FIFO words have unread data). Furthermore, if this field is set to 0xF, the interrupt is issued when
    *   15 data samples are remaining in the FIFO (17 FIFO data samples have unread data).
    */
    #define MAX30101_FIFO_CONF 0x08
    
    /**
    *   \brief MAX30101 Mode COnfiguration.
    *
    *   This register is structured as follows:
    *
    *   |   B7   |   B6   |    B5  |   B4   |   B3   |   B2   |   B1   |   B0   |
    *   | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | 
    *   | SHDN | RESET | | | | MODE[2:0] |    
    *
    *   ** Bit 7: Shutdown Control (SHDN) **
    *
    *   The part can be put into a power-save mode by setting this bit to one. 
    *   While in power-save mode, all registers retain their values, and write/read operations function as normal.
    *   All interrupts are cleared to zero in this mode.
    *
    *   **Bit 6: Reset Control (RESET)**
    *   
    *   When the RESET bit is set to one, all configuration, threshold, and data registers are reset
    *   to their power-on-state through a power-on reset. The RESET bit is cleared automatically back 
    *   to zero after the reset sequence is completed. 
    *   Note: Setting the RESET bit does not trigger a PWR_RDY interrupt event.
    *
    *   **Bits 2:0: Mode Control**
    *
    *   These bits set the operating state of the MAX30101. Changing modes does not change any other setting,
    *   nor does it erase any previously stored data inside the data registers.
    *
       <table>
        <caption id="mode_table">MAX30101 Mode settings</caption>
        <tr><th>MODE[2:0]                      <th>MODE       <th>ACTIVE LED CHANNELS
        <tr><td>000<td colspan=2, style="text-align:center">Do not use
        <tr><td>001<td colspan=2, style="text-align:center">Do not use
        <tr><td>010<td> Heart Rate mode <td> Red only
        <tr><td>011<td> SpO2 mode <td> Red and IR
        <tr><td>100-110<td colspan=2, style="text-align:center">Do not use
        <tr><td>111<td> Multi-LED mode <td> Green, RED, and/or IR
        </table>
    */
    #define MAX30101_MODE_CONF 0x09
    
    /**
    *   \brief Sp02 Configuration register.
    *
    *   This register configures the sensor for SpO2 mode.
    *
    *   It is structured as follows:
    <table>
    <caption id="spo2 conf">MAX30101 SpO2 Configuration Register</caption>
    <tr><th>B7<th>B6<th>B5<th>B4<th>B3<th>B2<th>B1<th>B0                      
    <tr><td colspan=2,, style="text-align:center">SPO2_ADC_RGE[1:0]<td colspan=3, style="text-align:center">SPO2_SR[2:0]<td colspan=2, style="text-align:center"> LED_PW[1:0]
    </table>
        */
    #define MAX30101_SP02_CONF 0x0A
    
    //#define MAX30101_LED1_PA 0x0C
    
    
#endif

/* [] END OF FILE */
