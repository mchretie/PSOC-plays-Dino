/*******************************************************************************
* File Name: DUCK_PM.c
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

#include "DUCK.h"

static DUCK_backupStruct DUCK_backup;


/*******************************************************************************
* Function Name: DUCK_SaveConfig
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
*  DUCK_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void DUCK_SaveConfig(void) 
{

    #if(!DUCK_UsingFixedFunction)
        #if(!DUCK_PWMModeIsCenterAligned)
            DUCK_backup.PWMPeriod = DUCK_ReadPeriod();
        #endif /* (!DUCK_PWMModeIsCenterAligned) */
        DUCK_backup.PWMUdb = DUCK_ReadCounter();
        #if (DUCK_UseStatus)
            DUCK_backup.InterruptMaskValue = DUCK_STATUS_MASK;
        #endif /* (DUCK_UseStatus) */

        #if(DUCK_DeadBandMode == DUCK__B_PWM__DBM_256_CLOCKS || \
            DUCK_DeadBandMode == DUCK__B_PWM__DBM_2_4_CLOCKS)
            DUCK_backup.PWMdeadBandValue = DUCK_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(DUCK_KillModeMinTime)
             DUCK_backup.PWMKillCounterPeriod = DUCK_ReadKillTime();
        #endif /* (DUCK_KillModeMinTime) */

        #if(DUCK_UseControl)
            DUCK_backup.PWMControlRegister = DUCK_ReadControlRegister();
        #endif /* (DUCK_UseControl) */
    #endif  /* (!DUCK_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: DUCK_RestoreConfig
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
*  DUCK_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void DUCK_RestoreConfig(void) 
{
        #if(!DUCK_UsingFixedFunction)
            #if(!DUCK_PWMModeIsCenterAligned)
                DUCK_WritePeriod(DUCK_backup.PWMPeriod);
            #endif /* (!DUCK_PWMModeIsCenterAligned) */

            DUCK_WriteCounter(DUCK_backup.PWMUdb);

            #if (DUCK_UseStatus)
                DUCK_STATUS_MASK = DUCK_backup.InterruptMaskValue;
            #endif /* (DUCK_UseStatus) */

            #if(DUCK_DeadBandMode == DUCK__B_PWM__DBM_256_CLOCKS || \
                DUCK_DeadBandMode == DUCK__B_PWM__DBM_2_4_CLOCKS)
                DUCK_WriteDeadTime(DUCK_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(DUCK_KillModeMinTime)
                DUCK_WriteKillTime(DUCK_backup.PWMKillCounterPeriod);
            #endif /* (DUCK_KillModeMinTime) */

            #if(DUCK_UseControl)
                DUCK_WriteControlRegister(DUCK_backup.PWMControlRegister);
            #endif /* (DUCK_UseControl) */
        #endif  /* (!DUCK_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: DUCK_Sleep
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
*  DUCK_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void DUCK_Sleep(void) 
{
    #if(DUCK_UseControl)
        if(DUCK_CTRL_ENABLE == (DUCK_CONTROL & DUCK_CTRL_ENABLE))
        {
            /*Component is enabled */
            DUCK_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            DUCK_backup.PWMEnableState = 0u;
        }
    #endif /* (DUCK_UseControl) */

    /* Stop component */
    DUCK_Stop();

    /* Save registers configuration */
    DUCK_SaveConfig();
}


/*******************************************************************************
* Function Name: DUCK_Wakeup
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
*  DUCK_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void DUCK_Wakeup(void) 
{
     /* Restore registers values */
    DUCK_RestoreConfig();

    if(DUCK_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        DUCK_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
