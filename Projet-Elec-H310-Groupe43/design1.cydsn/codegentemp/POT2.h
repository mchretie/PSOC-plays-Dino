/*******************************************************************************
* File Name: POT2.h  
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

#if !defined(CY_PINS_POT2_H) /* Pins POT2_H */
#define CY_PINS_POT2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "POT2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 POT2__PORT == 15 && ((POT2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    POT2_Write(uint8 value);
void    POT2_SetDriveMode(uint8 mode);
uint8   POT2_ReadDataReg(void);
uint8   POT2_Read(void);
void    POT2_SetInterruptMode(uint16 position, uint16 mode);
uint8   POT2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the POT2_SetDriveMode() function.
     *  @{
     */
        #define POT2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define POT2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define POT2_DM_RES_UP          PIN_DM_RES_UP
        #define POT2_DM_RES_DWN         PIN_DM_RES_DWN
        #define POT2_DM_OD_LO           PIN_DM_OD_LO
        #define POT2_DM_OD_HI           PIN_DM_OD_HI
        #define POT2_DM_STRONG          PIN_DM_STRONG
        #define POT2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define POT2_MASK               POT2__MASK
#define POT2_SHIFT              POT2__SHIFT
#define POT2_WIDTH              1u

/* Interrupt constants */
#if defined(POT2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in POT2_SetInterruptMode() function.
     *  @{
     */
        #define POT2_INTR_NONE      (uint16)(0x0000u)
        #define POT2_INTR_RISING    (uint16)(0x0001u)
        #define POT2_INTR_FALLING   (uint16)(0x0002u)
        #define POT2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define POT2_INTR_MASK      (0x01u) 
#endif /* (POT2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define POT2_PS                     (* (reg8 *) POT2__PS)
/* Data Register */
#define POT2_DR                     (* (reg8 *) POT2__DR)
/* Port Number */
#define POT2_PRT_NUM                (* (reg8 *) POT2__PRT) 
/* Connect to Analog Globals */                                                  
#define POT2_AG                     (* (reg8 *) POT2__AG)                       
/* Analog MUX bux enable */
#define POT2_AMUX                   (* (reg8 *) POT2__AMUX) 
/* Bidirectional Enable */                                                        
#define POT2_BIE                    (* (reg8 *) POT2__BIE)
/* Bit-mask for Aliased Register Access */
#define POT2_BIT_MASK               (* (reg8 *) POT2__BIT_MASK)
/* Bypass Enable */
#define POT2_BYP                    (* (reg8 *) POT2__BYP)
/* Port wide control signals */                                                   
#define POT2_CTL                    (* (reg8 *) POT2__CTL)
/* Drive Modes */
#define POT2_DM0                    (* (reg8 *) POT2__DM0) 
#define POT2_DM1                    (* (reg8 *) POT2__DM1)
#define POT2_DM2                    (* (reg8 *) POT2__DM2) 
/* Input Buffer Disable Override */
#define POT2_INP_DIS                (* (reg8 *) POT2__INP_DIS)
/* LCD Common or Segment Drive */
#define POT2_LCD_COM_SEG            (* (reg8 *) POT2__LCD_COM_SEG)
/* Enable Segment LCD */
#define POT2_LCD_EN                 (* (reg8 *) POT2__LCD_EN)
/* Slew Rate Control */
#define POT2_SLW                    (* (reg8 *) POT2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define POT2_PRTDSI__CAPS_SEL       (* (reg8 *) POT2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define POT2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) POT2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define POT2_PRTDSI__OE_SEL0        (* (reg8 *) POT2__PRTDSI__OE_SEL0) 
#define POT2_PRTDSI__OE_SEL1        (* (reg8 *) POT2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define POT2_PRTDSI__OUT_SEL0       (* (reg8 *) POT2__PRTDSI__OUT_SEL0) 
#define POT2_PRTDSI__OUT_SEL1       (* (reg8 *) POT2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define POT2_PRTDSI__SYNC_OUT       (* (reg8 *) POT2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(POT2__SIO_CFG)
    #define POT2_SIO_HYST_EN        (* (reg8 *) POT2__SIO_HYST_EN)
    #define POT2_SIO_REG_HIFREQ     (* (reg8 *) POT2__SIO_REG_HIFREQ)
    #define POT2_SIO_CFG            (* (reg8 *) POT2__SIO_CFG)
    #define POT2_SIO_DIFF           (* (reg8 *) POT2__SIO_DIFF)
#endif /* (POT2__SIO_CFG) */

/* Interrupt Registers */
#if defined(POT2__INTSTAT)
    #define POT2_INTSTAT            (* (reg8 *) POT2__INTSTAT)
    #define POT2_SNAP               (* (reg8 *) POT2__SNAP)
    
	#define POT2_0_INTTYPE_REG 		(* (reg8 *) POT2__0__INTTYPE)
#endif /* (POT2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_POT2_H */


/* [] END OF FILE */
