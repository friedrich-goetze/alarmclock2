/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.0
        Device            :  PIC16F19156
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.10 and above
        MPLAB             :  MPLAB X 5.35

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"




void (*IOCBF1_InterruptHandler)(void);
void (*IOCBF2_InterruptHandler)(void);
void (*IOCBF3_InterruptHandler)(void);
void (*IOCBF4_InterruptHandler)(void);

#if (__XC8_VERSION <= 1410) 

typedef union {
    struct {
        unsigned T2INPPS                :6;
    };
    struct {
        unsigned T2INPPS0               :1;
        unsigned T2INPPS1               :1;
        unsigned T2INPPS2               :1;
        unsigned T2INPPS3               :1;
        unsigned T2INPPS4               :1;
        unsigned T2INPPS5               :1;
    };
} T2INPPSbits_t;
extern volatile T2INPPSbits_t T2INPPSbits @ (&T2AINPPS);

typedef union {
    struct {
        unsigned T4INPPS                :6;
    };
    struct {
        unsigned T4INPPS0               :1;
        unsigned T4INPPS1               :1;
        unsigned T4INPPS2               :1;
        unsigned T4INPPS3               :1;
        unsigned T4INPPS4               :1;
        unsigned T4INPPS5               :1;
    };
} T4INPPSbits_t;
extern volatile T4INPPSbits_t T4INPPSbits @ (&T4AINPPS);
#endif

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x20;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0xDF;
    TRISB = 0xDF;
    TRISC = 0x8B;

    /**
    ANSELx registers
    */
    ANSELC = 0x00;
    ANSELB = 0x00;
    ANSELA = 0x1D;

    /**
    WPUx registers
    */
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x1C;
    WPUC = 0x00;

    /**
    ODx registers
    */
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xDF;
    SLRCONB = 0xFF;
    SLRCONC = 0xDF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xDF;
    INLVLE = 0x08;


    /**
    IOCx registers 
    */
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF1 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF2 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF3 = 0;
    //interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF4 = 0;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN1 = 1;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN2 = 1;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN3 = 1;
    //interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN4 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP1 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP2 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP3 = 1;
    //interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP4 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF1_SetInterruptHandler(IOCBF1_DefaultInterruptHandler);
    IOCBF2_SetInterruptHandler(IOCBF2_DefaultInterruptHandler);
    IOCBF3_SetInterruptHandler(IOCBF3_DefaultInterruptHandler);
    IOCBF4_SetInterruptHandler(IOCBF4_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
	
    SSP1CLKPPS = 0x12;   //RC2->MSSP1:SCK1;    
    RX1PPS = 0x17;   //RC7->EUSART1:RX1;    
    RC4PPS = 0x14;   //RC4->MSSP1:SDO1;    
    RC2PPS = 0x13;   //RC2->MSSP1:SCK1;    
    RC6PPS = 0x0D;   //RC6->EUSART1:TX1;    
    SSP1DATPPS = 0x13;   //RC3->MSSP1:SDI1;    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCBF1
    if(IOCBFbits.IOCBF1 == 1)
    {
        IOCBF1_ISR();  
    }	
	// interrupt on change for pin IOCBF2
    if(IOCBFbits.IOCBF2 == 1)
    {
        IOCBF2_ISR();  
    }	
	// interrupt on change for pin IOCBF3
    if(IOCBFbits.IOCBF3 == 1)
    {
        IOCBF3_ISR();  
    }	
	// interrupt on change for pin IOCBF4
    if(IOCBFbits.IOCBF4 == 1)
    {
        IOCBF4_ISR();  
    }	
}

/**
   IOCBF1 Interrupt Service Routine
*/
void IOCBF1_ISR(void) {

    // Add custom IOCBF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF1_InterruptHandler)
    {
        IOCBF1_InterruptHandler();
    }
    IOCBFbits.IOCBF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF1 at application runtime
*/
void IOCBF1_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF1
*/
void IOCBF1_DefaultInterruptHandler(void){
    // add your IOCBF1 interrupt custom code
    // or set custom function using IOCBF1_SetInterruptHandler()
}

/**
   IOCBF2 Interrupt Service Routine
*/
void IOCBF2_ISR(void) {

    // Add custom IOCBF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF2_InterruptHandler)
    {
        IOCBF2_InterruptHandler();
    }
    IOCBFbits.IOCBF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF2 at application runtime
*/
void IOCBF2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF2
*/
void IOCBF2_DefaultInterruptHandler(void){
    // add your IOCBF2 interrupt custom code
    // or set custom function using IOCBF2_SetInterruptHandler()
}

/**
   IOCBF3 Interrupt Service Routine
*/
void IOCBF3_ISR(void) {

    // Add custom IOCBF3 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF3_InterruptHandler)
    {
        IOCBF3_InterruptHandler();
    }
    IOCBFbits.IOCBF3 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF3 at application runtime
*/
void IOCBF3_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF3_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF3
*/
void IOCBF3_DefaultInterruptHandler(void){
    // add your IOCBF3 interrupt custom code
    // or set custom function using IOCBF3_SetInterruptHandler()
}

/**
   IOCBF4 Interrupt Service Routine
*/
void IOCBF4_ISR(void) {

    // Add custom IOCBF4 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF4_InterruptHandler)
    {
        IOCBF4_InterruptHandler();
    }
    IOCBFbits.IOCBF4 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF4 at application runtime
*/
void IOCBF4_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCBF4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF4
*/
void IOCBF4_DefaultInterruptHandler(void){
    // add your IOCBF4 interrupt custom code
    // or set custom function using IOCBF4_SetInterruptHandler()
}

/**
 End of File
*/