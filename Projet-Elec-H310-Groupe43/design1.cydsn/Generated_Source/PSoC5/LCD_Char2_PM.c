/*******************************************************************************
* File Name: LCD_Char2_PM.c
* Version 2.20
*
* Description:
*  This file provides the API source code for the Static Segment LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "LCD_Char2.h"


static LCD_Char2_BACKUP_STRUCT LCD_Char2_backup;


/*******************************************************************************
* Function Name: LCD_Char2_SaveConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Char2_SaveConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Char2_RestoreConfig
********************************************************************************
*
* Summary:
*  Does nothing, provided for consistency.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void LCD_Char2_RestoreConfig(void) 
{
}


/*******************************************************************************
* Function Name: LCD_Char2_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Char2_Sleep(void) 
{
    LCD_Char2_backup.enableState = LCD_Char2_enableState;
    LCD_Char2_SaveConfig();
    LCD_Char2_Stop();
}


/*******************************************************************************
* Function Name: LCD_Char2_Wakeup
********************************************************************************
*
* Summary:
*  Wakes the component from sleep mode. Configures DMA and enables the component
*  for normal operation.
*
* Parameters:
*  LCD_Char2_enableState - Global variable.
*
* Return:
*  Status one of standard status for PSoC3 Component
*       CYRET_SUCCESS - Function completed successfully.
*       CYRET_LOCKED - The object was locked, already in use. Some of TDs or
*                      a channel already in use.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LCD_Char2_Wakeup(void) 
{
    LCD_Char2_RestoreConfig();

    if(LCD_Char2_backup.enableState == 1u)
    {
        LCD_Char2_Enable();
    }
}


/* [] END OF FILE */
