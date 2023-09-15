/*******************************************************************************
* File Name: JUMP_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "JUMP.h"

static JUMP_backupStruct JUMP_backup;


/*******************************************************************************
* Function Name: JUMP_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  JUMP_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void JUMP_SaveConfig(void) 
{

    #if(!JUMP_UsingFixedFunction)
        #if(!JUMP_PWMModeIsCenterAligned)
            JUMP_backup.PWMPeriod = JUMP_ReadPeriod();
        #endif /* (!JUMP_PWMModeIsCenterAligned) */
        JUMP_backup.PWMUdb = JUMP_ReadCounter();
        #if (JUMP_UseStatus)
            JUMP_backup.InterruptMaskValue = JUMP_STATUS_MASK;
        #endif /* (JUMP_UseStatus) */

        #if(JUMP_DeadBandMode == JUMP__B_PWM__DBM_256_CLOCKS || \
            JUMP_DeadBandMode == JUMP__B_PWM__DBM_2_4_CLOCKS)
            JUMP_backup.PWMdeadBandValue = JUMP_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(JUMP_KillModeMinTime)
             JUMP_backup.PWMKillCounterPeriod = JUMP_ReadKillTime();
        #endif /* (JUMP_KillModeMinTime) */

        #if(JUMP_UseControl)
            JUMP_backup.PWMControlRegister = JUMP_ReadControlRegister();
        #endif /* (JUMP_UseControl) */
    #endif  /* (!JUMP_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: JUMP_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  JUMP_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void JUMP_RestoreConfig(void) 
{
        #if(!JUMP_UsingFixedFunction)
            #if(!JUMP_PWMModeIsCenterAligned)
                JUMP_WritePeriod(JUMP_backup.PWMPeriod);
            #endif /* (!JUMP_PWMModeIsCenterAligned) */

            JUMP_WriteCounter(JUMP_backup.PWMUdb);

            #if (JUMP_UseStatus)
                JUMP_STATUS_MASK = JUMP_backup.InterruptMaskValue;
            #endif /* (JUMP_UseStatus) */

            #if(JUMP_DeadBandMode == JUMP__B_PWM__DBM_256_CLOCKS || \
                JUMP_DeadBandMode == JUMP__B_PWM__DBM_2_4_CLOCKS)
                JUMP_WriteDeadTime(JUMP_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(JUMP_KillModeMinTime)
                JUMP_WriteKillTime(JUMP_backup.PWMKillCounterPeriod);
            #endif /* (JUMP_KillModeMinTime) */

            #if(JUMP_UseControl)
                JUMP_WriteControlRegister(JUMP_backup.PWMControlRegister);
            #endif /* (JUMP_UseControl) */
        #endif  /* (!JUMP_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: JUMP_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  JUMP_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void JUMP_Sleep(void) 
{
    #if(JUMP_UseControl)
        if(JUMP_CTRL_ENABLE == (JUMP_CONTROL & JUMP_CTRL_ENABLE))
        {
            /*Component is enabled */
            JUMP_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            JUMP_backup.PWMEnableState = 0u;
        }
    #endif /* (JUMP_UseControl) */

    /* Stop component */
    JUMP_Stop();

    /* Save registers configuration */
    JUMP_SaveConfig();
}


/*******************************************************************************
* Function Name: JUMP_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  JUMP_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void JUMP_Wakeup(void) 
{
     /* Restore registers values */
    JUMP_RestoreConfig();

    if(JUMP_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        JUMP_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
