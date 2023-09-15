/*******************************************************************************
* File Name: Timer_DAC_PM.c
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

#include "Timer_DAC.h"

static Timer_DAC_backupStruct Timer_DAC_backup;


/*******************************************************************************
* Function Name: Timer_DAC_SaveConfig
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
*  Timer_DAC_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_DAC_SaveConfig(void) 
{
    #if (!Timer_DAC_UsingFixedFunction)
        Timer_DAC_backup.TimerUdb = Timer_DAC_ReadCounter();
        Timer_DAC_backup.InterruptMaskValue = Timer_DAC_STATUS_MASK;
        #if (Timer_DAC_UsingHWCaptureCounter)
            Timer_DAC_backup.TimerCaptureCounter = Timer_DAC_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_DAC_UDB_CONTROL_REG_REMOVED)
            Timer_DAC_backup.TimerControlRegister = Timer_DAC_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_DAC_RestoreConfig
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
*  Timer_DAC_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_DAC_RestoreConfig(void) 
{   
    #if (!Timer_DAC_UsingFixedFunction)

        Timer_DAC_WriteCounter(Timer_DAC_backup.TimerUdb);
        Timer_DAC_STATUS_MASK =Timer_DAC_backup.InterruptMaskValue;
        #if (Timer_DAC_UsingHWCaptureCounter)
            Timer_DAC_SetCaptureCount(Timer_DAC_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_DAC_UDB_CONTROL_REG_REMOVED)
            Timer_DAC_WriteControlRegister(Timer_DAC_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_DAC_Sleep
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
*  Timer_DAC_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_DAC_Sleep(void) 
{
    #if(!Timer_DAC_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_DAC_CTRL_ENABLE == (Timer_DAC_CONTROL & Timer_DAC_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_DAC_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_DAC_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_DAC_Stop();
    Timer_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_DAC_Wakeup
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
*  Timer_DAC_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_DAC_Wakeup(void) 
{
    Timer_DAC_RestoreConfig();
    #if(!Timer_DAC_UDB_CONTROL_REG_REMOVED)
        if(Timer_DAC_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_DAC_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
