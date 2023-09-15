/*******************************************************************************
* File Name: isr_Keypad.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_Keypad_H)
#define CY_ISR_isr_Keypad_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Keypad_Start(void);
void isr_Keypad_StartEx(cyisraddress address);
void isr_Keypad_Stop(void);

CY_ISR_PROTO(isr_Keypad_Interrupt);

void isr_Keypad_SetVector(cyisraddress address);
cyisraddress isr_Keypad_GetVector(void);

void isr_Keypad_SetPriority(uint8 priority);
uint8 isr_Keypad_GetPriority(void);

void isr_Keypad_Enable(void);
uint8 isr_Keypad_GetState(void);
void isr_Keypad_Disable(void);

void isr_Keypad_SetPending(void);
void isr_Keypad_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Keypad ISR. */
#define isr_Keypad_INTC_VECTOR            ((reg32 *) isr_Keypad__INTC_VECT)

/* Address of the isr_Keypad ISR priority. */
#define isr_Keypad_INTC_PRIOR             ((reg8 *) isr_Keypad__INTC_PRIOR_REG)

/* Priority of the isr_Keypad interrupt. */
#define isr_Keypad_INTC_PRIOR_NUMBER      isr_Keypad__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Keypad interrupt. */
#define isr_Keypad_INTC_SET_EN            ((reg32 *) isr_Keypad__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Keypad interrupt. */
#define isr_Keypad_INTC_CLR_EN            ((reg32 *) isr_Keypad__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Keypad interrupt state to pending. */
#define isr_Keypad_INTC_SET_PD            ((reg32 *) isr_Keypad__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Keypad interrupt. */
#define isr_Keypad_INTC_CLR_PD            ((reg32 *) isr_Keypad__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Keypad_H */


/* [] END OF FILE */
