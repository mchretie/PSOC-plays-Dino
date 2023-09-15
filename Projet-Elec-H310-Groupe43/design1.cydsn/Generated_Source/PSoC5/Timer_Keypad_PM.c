/*******************************************************************************
* File Name: Timer_Keypad_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Keypad.h"

static Timer_Keypad_backupStruct Timer_Keypad_backup;


/*******************************************************************************
* Function Name: Timer_Keypad_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Keypad_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Keypad_SaveConfig(void) 
{
    #if (!Timer_Keypad_UsingFixedFunction)
        Timer_Keypad_backup.TimerUdb = Timer_Keypad_ReadCounter();
        Timer_Keypad_backup.InterruptMaskValue = Timer_Keypad_STATUS_MASK;
        #if (Timer_Keypad_UsingHWCaptureCounter)
            Timer_Keypad_backup.TimerCaptureCounter = Timer_Keypad_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Keypad_UDB_CONTROL_REG_REMOVED)
            Timer_Keypad_backup.TimerControlRegister = Timer_Keypad_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Keypad_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Keypad_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Keypad_RestoreConfig(void) 
{   
    #if (!Timer_Keypad_UsingFixedFunction)

        Timer_Keypad_WriteCounter(Timer_Keypad_backup.TimerUdb);
        Timer_Keypad_STATUS_MASK =Timer_Keypad_backup.InterruptMaskValue;
        #if (Timer_Keypad_UsingHWCaptureCounter)
            Timer_Keypad_SetCaptureCount(Timer_Keypad_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Keypad_UDB_CONTROL_REG_REMOVED)
            Timer_Keypad_WriteControlRegister(Timer_Keypad_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Keypad_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Keypad_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Keypad_Sleep(void) 
{
    #if(!Timer_Keypad_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Keypad_CTRL_ENABLE == (Timer_Keypad_CONTROL & Timer_Keypad_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Keypad_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Keypad_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Keypad_Stop();
    Timer_Keypad_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Keypad_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Keypad_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Keypad_Wakeup(void) 
{
    Timer_Keypad_RestoreConfig();
    #if(!Timer_Keypad_UDB_CONTROL_REG_REMOVED)
        if(Timer_Keypad_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Keypad_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
