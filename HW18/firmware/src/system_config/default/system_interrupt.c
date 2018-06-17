/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

 
void __ISR(_USB_1_VECTOR, ipl4AUTO) _IntHandlerUSBInstance0(void)
{
    DRV_USBFS_Tasks_ISR(sysObj.drvUSBObject);
}

void __ISR(_TIMER_4_VECTOR, IPL4SOFT) Timer4ISR(void) {
    
    //  COM controller feeds into motor controller
    
    //  COM PI controller
    float error = 0, ierror = 0;
    float errorR, errorL, ierrorR = 0, ierrorL = 0;
    float right, left;
    float refR, refL;
    float kp_c = 1, ki_c = 0.5;
    float kp = 1, ki = 0.5;
    int MAX_DUTY = 1000;
    extern volatile int rxVal;
   
    
    error = rxVal - 150;        // app testing shows 160 is middle of the screen
    
    if (error<-50) {             // slow down the left motor to steer to the left
        error = (error+50);
        error = -error;
        //ierror += error;
        //ierror = -ierror;
        refL = MAX_DUTY - kp*error;// - ki*ierror; 
        refR = MAX_DUTY;
        if (refL < 0)   {
            refL = 0;
        }
    }
    else if (error>50)  {        // slow down the right motor to steer to the right
        error = error - 50;
        //ierror += error;
        refR = MAX_DUTY - kp*error;// - ki*ierror;
        refL = MAX_DUTY;
        if (refR<0) {
            refR = 0;
        }
    }
    else {
        refR = MAX_DUTY/2;
        refL = MAX_DUTY/2;
    }
    //  Motor PI controller
            
    errorR = refR - (TMR3/TMR4);
    errorL = refL - (TMR5/TMR4);
    
    //ierrorR += errorR;
    //ierrorL += errorL;
    
    right = (kp*errorR);//+ (ki*ierrorR);
    left = (kp*errorL);// + (ki*ierrorL);
    
    if (right > 2399) {
        right = 2399;
    }
    else if (right < 0)    {
        right = 0;
    }
    
    if (left > 2399) {
        left = 2399;
    }
    else if (left < 0)    {
        left = 0;
    }
    
    OC1RS = (int) left;
    OC4RS = (int) right;
     
    IFS0bits.T4IF = 0;                      //  clear interrupt flag
    TMR3 = 0;                               //  reset timer
    TMR5 = 0;
}

/*******************************************************************************
 End of File
*/