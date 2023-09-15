/*******************************************************************************
* File Name: LCD4.h  
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

#if !defined(CY_PINS_LCD4_H) /* Pins LCD4_H */
#define CY_PINS_LCD4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LCD4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LCD4__PORT == 15 && ((LCD4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LCD4_Write(uint8 value);
void    LCD4_SetDriveMode(uint8 mode);
uint8   LCD4_ReadDataReg(void);
uint8   LCD4_Read(void);
void    LCD4_SetInterruptMode(uint16 position, uint16 mode);
uint8   LCD4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LCD4_SetDriveMode() function.
     *  @{
     */
        #define LCD4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LCD4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LCD4_DM_RES_UP          PIN_DM_RES_UP
        #define LCD4_DM_RES_DWN         PIN_DM_RES_DWN
        #define LCD4_DM_OD_LO           PIN_DM_OD_LO
        #define LCD4_DM_OD_HI           PIN_DM_OD_HI
        #define LCD4_DM_STRONG          PIN_DM_STRONG
        #define LCD4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LCD4_MASK               LCD4__MASK
#define LCD4_SHIFT              LCD4__SHIFT
#define LCD4_WIDTH              1u

/* Interrupt constants */
#if defined(LCD4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LCD4_SetInterruptMode() function.
     *  @{
     */
        #define LCD4_INTR_NONE      (uint16)(0x0000u)
        #define LCD4_INTR_RISING    (uint16)(0x0001u)
        #define LCD4_INTR_FALLING   (uint16)(0x0002u)
        #define LCD4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LCD4_INTR_MASK      (0x01u) 
#endif /* (LCD4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LCD4_PS                     (* (reg8 *) LCD4__PS)
/* Data Register */
#define LCD4_DR                     (* (reg8 *) LCD4__DR)
/* Port Number */
#define LCD4_PRT_NUM                (* (reg8 *) LCD4__PRT) 
/* Connect to Analog Globals */                                                  
#define LCD4_AG                     (* (reg8 *) LCD4__AG)                       
/* Analog MUX bux enable */
#define LCD4_AMUX                   (* (reg8 *) LCD4__AMUX) 
/* Bidirectional Enable */                                                        
#define LCD4_BIE                    (* (reg8 *) LCD4__BIE)
/* Bit-mask for Aliased Register Access */
#define LCD4_BIT_MASK               (* (reg8 *) LCD4__BIT_MASK)
/* Bypass Enable */
#define LCD4_BYP                    (* (reg8 *) LCD4__BYP)
/* Port wide control signals */                                                   
#define LCD4_CTL                    (* (reg8 *) LCD4__CTL)
/* Drive Modes */
#define LCD4_DM0                    (* (reg8 *) LCD4__DM0) 
#define LCD4_DM1                    (* (reg8 *) LCD4__DM1)
#define LCD4_DM2                    (* (reg8 *) LCD4__DM2) 
/* Input Buffer Disable Override */
#define LCD4_INP_DIS                (* (reg8 *) LCD4__INP_DIS)
/* LCD Common or Segment Drive */
#define LCD4_LCD_COM_SEG            (* (reg8 *) LCD4__LCD_COM_SEG)
/* Enable Segment LCD */
#define LCD4_LCD_EN                 (* (reg8 *) LCD4__LCD_EN)
/* Slew Rate Control */
#define LCD4_SLW                    (* (reg8 *) LCD4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LCD4_PRTDSI__CAPS_SEL       (* (reg8 *) LCD4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LCD4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LCD4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LCD4_PRTDSI__OE_SEL0        (* (reg8 *) LCD4__PRTDSI__OE_SEL0) 
#define LCD4_PRTDSI__OE_SEL1        (* (reg8 *) LCD4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LCD4_PRTDSI__OUT_SEL0       (* (reg8 *) LCD4__PRTDSI__OUT_SEL0) 
#define LCD4_PRTDSI__OUT_SEL1       (* (reg8 *) LCD4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LCD4_PRTDSI__SYNC_OUT       (* (reg8 *) LCD4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LCD4__SIO_CFG)
    #define LCD4_SIO_HYST_EN        (* (reg8 *) LCD4__SIO_HYST_EN)
    #define LCD4_SIO_REG_HIFREQ     (* (reg8 *) LCD4__SIO_REG_HIFREQ)
    #define LCD4_SIO_CFG            (* (reg8 *) LCD4__SIO_CFG)
    #define LCD4_SIO_DIFF           (* (reg8 *) LCD4__SIO_DIFF)
#endif /* (LCD4__SIO_CFG) */

/* Interrupt Registers */
#if defined(LCD4__INTSTAT)
    #define LCD4_INTSTAT            (* (reg8 *) LCD4__INTSTAT)
    #define LCD4_SNAP               (* (reg8 *) LCD4__SNAP)
    
	#define LCD4_0_INTTYPE_REG 		(* (reg8 *) LCD4__0__INTTYPE)
#endif /* (LCD4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LCD4_H */


/* [] END OF FILE */
