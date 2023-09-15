/*******************************************************************************
* File Name: POT1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_POT1_H) /* Pins POT1_H */
#define CY_PINS_POT1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "POT1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 POT1__PORT == 15 && ((POT1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    POT1_Write(uint8 value);
void    POT1_SetDriveMode(uint8 mode);
uint8   POT1_ReadDataReg(void);
uint8   POT1_Read(void);
void    POT1_SetInterruptMode(uint16 position, uint16 mode);
uint8   POT1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the POT1_SetDriveMode() function.
     *  @{
     */
        #define POT1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define POT1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define POT1_DM_RES_UP          PIN_DM_RES_UP
        #define POT1_DM_RES_DWN         PIN_DM_RES_DWN
        #define POT1_DM_OD_LO           PIN_DM_OD_LO
        #define POT1_DM_OD_HI           PIN_DM_OD_HI
        #define POT1_DM_STRONG          PIN_DM_STRONG
        #define POT1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define POT1_MASK               POT1__MASK
#define POT1_SHIFT              POT1__SHIFT
#define POT1_WIDTH              1u

/* Interrupt constants */
#if defined(POT1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in POT1_SetInterruptMode() function.
     *  @{
     */
        #define POT1_INTR_NONE      (uint16)(0x0000u)
        #define POT1_INTR_RISING    (uint16)(0x0001u)
        #define POT1_INTR_FALLING   (uint16)(0x0002u)
        #define POT1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define POT1_INTR_MASK      (0x01u) 
#endif /* (POT1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define POT1_PS                     (* (reg8 *) POT1__PS)
/* Data Register */
#define POT1_DR                     (* (reg8 *) POT1__DR)
/* Port Number */
#define POT1_PRT_NUM                (* (reg8 *) POT1__PRT) 
/* Connect to Analog Globals */                                                  
#define POT1_AG                     (* (reg8 *) POT1__AG)                       
/* Analog MUX bux enable */
#define POT1_AMUX                   (* (reg8 *) POT1__AMUX) 
/* Bidirectional Enable */                                                        
#define POT1_BIE                    (* (reg8 *) POT1__BIE)
/* Bit-mask for Aliased Register Access */
#define POT1_BIT_MASK               (* (reg8 *) POT1__BIT_MASK)
/* Bypass Enable */
#define POT1_BYP                    (* (reg8 *) POT1__BYP)
/* Port wide control signals */                                                   
#define POT1_CTL                    (* (reg8 *) POT1__CTL)
/* Drive Modes */
#define POT1_DM0                    (* (reg8 *) POT1__DM0) 
#define POT1_DM1                    (* (reg8 *) POT1__DM1)
#define POT1_DM2                    (* (reg8 *) POT1__DM2) 
/* Input Buffer Disable Override */
#define POT1_INP_DIS                (* (reg8 *) POT1__INP_DIS)
/* LCD Common or Segment Drive */
#define POT1_LCD_COM_SEG            (* (reg8 *) POT1__LCD_COM_SEG)
/* Enable Segment LCD */
#define POT1_LCD_EN                 (* (reg8 *) POT1__LCD_EN)
/* Slew Rate Control */
#define POT1_SLW                    (* (reg8 *) POT1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define POT1_PRTDSI__CAPS_SEL       (* (reg8 *) POT1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define POT1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) POT1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define POT1_PRTDSI__OE_SEL0        (* (reg8 *) POT1__PRTDSI__OE_SEL0) 
#define POT1_PRTDSI__OE_SEL1        (* (reg8 *) POT1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define POT1_PRTDSI__OUT_SEL0       (* (reg8 *) POT1__PRTDSI__OUT_SEL0) 
#define POT1_PRTDSI__OUT_SEL1       (* (reg8 *) POT1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define POT1_PRTDSI__SYNC_OUT       (* (reg8 *) POT1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(POT1__SIO_CFG)
    #define POT1_SIO_HYST_EN        (* (reg8 *) POT1__SIO_HYST_EN)
    #define POT1_SIO_REG_HIFREQ     (* (reg8 *) POT1__SIO_REG_HIFREQ)
    #define POT1_SIO_CFG            (* (reg8 *) POT1__SIO_CFG)
    #define POT1_SIO_DIFF           (* (reg8 *) POT1__SIO_DIFF)
#endif /* (POT1__SIO_CFG) */

/* Interrupt Registers */
#if defined(POT1__INTSTAT)
    #define POT1_INTSTAT            (* (reg8 *) POT1__INTSTAT)
    #define POT1_SNAP               (* (reg8 *) POT1__SNAP)
    
	#define POT1_0_INTTYPE_REG 		(* (reg8 *) POT1__0__INTTYPE)
#endif /* (POT1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_POT1_H */


/* [] END OF FILE */
