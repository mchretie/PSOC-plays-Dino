/*******************************************************************************
* File Name: Timer_audio_PM.c
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

#include "Timer_audio.h"

static Timer_audio_backupStruct Timer_audio_backup;


/*******************************************************************************
* Function Name: Timer_audio_SaveConfig
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
*  Timer_audio_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_audio_SaveConfig(void) 
{
    #if (!Timer_audio_UsingFixedFunction)
        Timer_audio_backup.TimerUdb = Timer_audio_ReadCounter();
        Timer_audio_backup.InterruptMaskValue = Timer_audio_STATUS_MASK;
        #if (Timer_audio_UsingHWCaptureCounter)
            Timer_audio_backup.TimerCaptureCounter = Timer_audio_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_audio_UDB_CONTROL_REG_REMOVED)
            Timer_audio_backup.TimerControlRegister = Timer_audio_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_audio_RestoreConfig
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
*  Timer_audio_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_audio_RestoreConfig(void) 
{   
    #if (!Timer_audio_UsingFixedFunction)

        Timer_audio_WriteCounter(Timer_audio_backup.TimerUdb);
        Timer_audio_STATUS_MASK =Timer_audio_backup.InterruptMaskValue;
        #if (Timer_audio_UsingHWCaptureCounter)
            Timer_audio_SetCaptureCount(Timer_audio_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_audio_UDB_CONTROL_REG_REMOVED)
            Timer_audio_WriteControlRegister(Timer_audio_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_audio_Sleep
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
*  Timer_audio_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_audio_Sleep(void) 
{
    #if(!Timer_audio_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_audio_CTRL_ENABLE == (Timer_audio_CONTROL & Timer_audio_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_audio_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_audio_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_audio_Stop();
    Timer_audio_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_audio_Wakeup
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
*  Timer_audio_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_audio_Wakeup(void) 
{
    Timer_audio_RestoreConfig();
    #if(!Timer_audio_UDB_CONTROL_REG_REMOVED)
        if(Timer_audio_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_audio_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
