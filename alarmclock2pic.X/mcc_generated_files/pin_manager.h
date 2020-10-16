/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F19156
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB 	          :  MPLAB X 5.35	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set AN_V_BAT_DIVIDED aliases
#define AN_V_BAT_DIVIDED_TRIS                 TRISAbits.TRISA0
#define AN_V_BAT_DIVIDED_LAT                  LATAbits.LATA0
#define AN_V_BAT_DIVIDED_PORT                 PORTAbits.RA0
#define AN_V_BAT_DIVIDED_WPU                  WPUAbits.WPUA0
#define AN_V_BAT_DIVIDED_OD                   ODCONAbits.ODCA0
#define AN_V_BAT_DIVIDED_ANS                  ANSELAbits.ANSA0
#define AN_V_BAT_DIVIDED_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define AN_V_BAT_DIVIDED_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define AN_V_BAT_DIVIDED_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define AN_V_BAT_DIVIDED_GetValue()           PORTAbits.RA0
#define AN_V_BAT_DIVIDED_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define AN_V_BAT_DIVIDED_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define AN_V_BAT_DIVIDED_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define AN_V_BAT_DIVIDED_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define AN_V_BAT_DIVIDED_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define AN_V_BAT_DIVIDED_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define AN_V_BAT_DIVIDED_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define AN_V_BAT_DIVIDED_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set BTN_MODE aliases
#define BTN_MODE_TRIS                 TRISBbits.TRISB1
#define BTN_MODE_LAT                  LATBbits.LATB1
#define BTN_MODE_PORT                 PORTBbits.RB1
#define BTN_MODE_WPU                  WPUBbits.WPUB1
#define BTN_MODE_OD                   ODCONBbits.ODCB1
#define BTN_MODE_ANS                  ANSELBbits.ANSB1
#define BTN_MODE_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define BTN_MODE_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define BTN_MODE_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define BTN_MODE_GetValue()           PORTBbits.RB1
#define BTN_MODE_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define BTN_MODE_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define BTN_MODE_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define BTN_MODE_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define BTN_MODE_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define BTN_MODE_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define BTN_MODE_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define BTN_MODE_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set BTN_SET aliases
#define BTN_SET_TRIS                 TRISBbits.TRISB2
#define BTN_SET_LAT                  LATBbits.LATB2
#define BTN_SET_PORT                 PORTBbits.RB2
#define BTN_SET_WPU                  WPUBbits.WPUB2
#define BTN_SET_OD                   ODCONBbits.ODCB2
#define BTN_SET_ANS                  ANSELBbits.ANSB2
#define BTN_SET_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define BTN_SET_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define BTN_SET_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define BTN_SET_GetValue()           PORTBbits.RB2
#define BTN_SET_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define BTN_SET_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define BTN_SET_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define BTN_SET_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define BTN_SET_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define BTN_SET_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define BTN_SET_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define BTN_SET_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set BTN_INC aliases
#define BTN_INC_TRIS                 TRISBbits.TRISB3
#define BTN_INC_LAT                  LATBbits.LATB3
#define BTN_INC_PORT                 PORTBbits.RB3
#define BTN_INC_WPU                  WPUBbits.WPUB3
#define BTN_INC_OD                   ODCONBbits.ODCB3
#define BTN_INC_ANS                  ANSELBbits.ANSB3
#define BTN_INC_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define BTN_INC_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define BTN_INC_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define BTN_INC_GetValue()           PORTBbits.RB3
#define BTN_INC_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define BTN_INC_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define BTN_INC_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define BTN_INC_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define BTN_INC_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define BTN_INC_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define BTN_INC_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define BTN_INC_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set BTN_DEC aliases
#define BTN_DEC_TRIS                 TRISBbits.TRISB4
#define BTN_DEC_LAT                  LATBbits.LATB4
#define BTN_DEC_PORT                 PORTBbits.RB4
#define BTN_DEC_WPU                  WPUBbits.WPUB4
#define BTN_DEC_OD                   ODCONBbits.ODCB4
#define BTN_DEC_ANS                  ANSELBbits.ANSB4
#define BTN_DEC_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define BTN_DEC_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define BTN_DEC_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define BTN_DEC_GetValue()           PORTBbits.RB4
#define BTN_DEC_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define BTN_DEC_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define BTN_DEC_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define BTN_DEC_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define BTN_DEC_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define BTN_DEC_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define BTN_DEC_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define BTN_DEC_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set MCP_CS aliases
#define MCP_CS_TRIS                 TRISBbits.TRISB5
#define MCP_CS_LAT                  LATBbits.LATB5
#define MCP_CS_PORT                 PORTBbits.RB5
#define MCP_CS_WPU                  WPUBbits.WPUB5
#define MCP_CS_OD                   ODCONBbits.ODCB5
#define MCP_CS_ANS                  ANSELBbits.ANSB5
#define MCP_CS_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define MCP_CS_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define MCP_CS_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define MCP_CS_GetValue()           PORTBbits.RB5
#define MCP_CS_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define MCP_CS_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define MCP_CS_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define MCP_CS_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define MCP_CS_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define MCP_CS_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define MCP_CS_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define MCP_CS_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RC2 procedures
#define RC2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RC2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RC2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RC2_GetValue()              PORTCbits.RC2
#define RC2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RC2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RC2_SetPullup()             do { WPUCbits.WPUC2 = 1; } while(0)
#define RC2_ResetPullup()           do { WPUCbits.WPUC2 = 0; } while(0)
#define RC2_SetAnalogMode()         do { ANSELCbits.ANSC2 = 1; } while(0)
#define RC2_SetDigitalMode()        do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set RC7 procedures
#define RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define RC7_GetValue()              PORTCbits.RC7
#define RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define RC7_SetPullup()             do { WPUCbits.WPUC7 = 1; } while(0)
#define RC7_ResetPullup()           do { WPUCbits.WPUC7 = 0; } while(0)
#define RC7_SetAnalogMode()         do { ANSELCbits.ANSC7 = 1; } while(0)
#define RC7_SetDigitalMode()        do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF1 pin functionality
 * @Example
    IOCBF1_ISR();
 */
void IOCBF1_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF1 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF1 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF1_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF1 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF1_SetInterruptHandler() method.
    This handler is called every time the IOCBF1 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF1_SetInterruptHandler(IOCBF1_InterruptHandler);

*/
extern void (*IOCBF1_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF1 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF1_SetInterruptHandler() method.
    This handler is called every time the IOCBF1 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF1_SetInterruptHandler(IOCBF1_DefaultInterruptHandler);

*/
void IOCBF1_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF2 pin functionality
 * @Example
    IOCBF2_ISR();
 */
void IOCBF2_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF2 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF2 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF2_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF2 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF2_SetInterruptHandler() method.
    This handler is called every time the IOCBF2 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF2_SetInterruptHandler(IOCBF2_InterruptHandler);

*/
extern void (*IOCBF2_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF2 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF2_SetInterruptHandler() method.
    This handler is called every time the IOCBF2 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF2_SetInterruptHandler(IOCBF2_DefaultInterruptHandler);

*/
void IOCBF2_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF3 pin functionality
 * @Example
    IOCBF3_ISR();
 */
void IOCBF3_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF3 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF3 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF3 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_InterruptHandler);

*/
extern void (*IOCBF3_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF3 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF3_SetInterruptHandler() method.
    This handler is called every time the IOCBF3 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF3_SetInterruptHandler(IOCBF3_DefaultInterruptHandler);

*/
void IOCBF3_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCBF4 pin functionality
 * @Example
    IOCBF4_ISR();
 */
void IOCBF4_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCBF4 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCBF4 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(MyInterruptHandler);

*/
void IOCBF4_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCBF4 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_InterruptHandler);

*/
extern void (*IOCBF4_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCBF4 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCBF4_SetInterruptHandler() method.
    This handler is called every time the IOCBF4 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCBF4_SetInterruptHandler(IOCBF4_DefaultInterruptHandler);

*/
void IOCBF4_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/