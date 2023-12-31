/*******************************************************************************
* File Name: ROW0.h  
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

#if !defined(CY_PINS_ROW0_H) /* Pins ROW0_H */
#define CY_PINS_ROW0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ROW0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ROW0__PORT == 15 && ((ROW0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ROW0_Write(uint8 value);
void    ROW0_SetDriveMode(uint8 mode);
uint8   ROW0_ReadDataReg(void);
uint8   ROW0_Read(void);
void    ROW0_SetInterruptMode(uint16 position, uint16 mode);
uint8   ROW0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ROW0_SetDriveMode() function.
     *  @{
     */
        #define ROW0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ROW0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ROW0_DM_RES_UP          PIN_DM_RES_UP
        #define ROW0_DM_RES_DWN         PIN_DM_RES_DWN
        #define ROW0_DM_OD_LO           PIN_DM_OD_LO
        #define ROW0_DM_OD_HI           PIN_DM_OD_HI
        #define ROW0_DM_STRONG          PIN_DM_STRONG
        #define ROW0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ROW0_MASK               ROW0__MASK
#define ROW0_SHIFT              ROW0__SHIFT
#define ROW0_WIDTH              1u

/* Interrupt constants */
#if defined(ROW0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ROW0_SetInterruptMode() function.
     *  @{
     */
        #define ROW0_INTR_NONE      (uint16)(0x0000u)
        #define ROW0_INTR_RISING    (uint16)(0x0001u)
        #define ROW0_INTR_FALLING   (uint16)(0x0002u)
        #define ROW0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ROW0_INTR_MASK      (0x01u) 
#endif /* (ROW0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ROW0_PS                     (* (reg8 *) ROW0__PS)
/* Data Register */
#define ROW0_DR                     (* (reg8 *) ROW0__DR)
/* Port Number */
#define ROW0_PRT_NUM                (* (reg8 *) ROW0__PRT) 
/* Connect to Analog Globals */                                                  
#define ROW0_AG                     (* (reg8 *) ROW0__AG)                       
/* Analog MUX bux enable */
#define ROW0_AMUX                   (* (reg8 *) ROW0__AMUX) 
/* Bidirectional Enable */                                                        
#define ROW0_BIE                    (* (reg8 *) ROW0__BIE)
/* Bit-mask for Aliased Register Access */
#define ROW0_BIT_MASK               (* (reg8 *) ROW0__BIT_MASK)
/* Bypass Enable */
#define ROW0_BYP                    (* (reg8 *) ROW0__BYP)
/* Port wide control signals */                                                   
#define ROW0_CTL                    (* (reg8 *) ROW0__CTL)
/* Drive Modes */
#define ROW0_DM0                    (* (reg8 *) ROW0__DM0) 
#define ROW0_DM1                    (* (reg8 *) ROW0__DM1)
#define ROW0_DM2                    (* (reg8 *) ROW0__DM2) 
/* Input Buffer Disable Override */
#define ROW0_INP_DIS                (* (reg8 *) ROW0__INP_DIS)
/* LCD Common or Segment Drive */
#define ROW0_LCD_COM_SEG            (* (reg8 *) ROW0__LCD_COM_SEG)
/* Enable Segment LCD */
#define ROW0_LCD_EN                 (* (reg8 *) ROW0__LCD_EN)
/* Slew Rate Control */
#define ROW0_SLW                    (* (reg8 *) ROW0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ROW0_PRTDSI__CAPS_SEL       (* (reg8 *) ROW0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ROW0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ROW0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ROW0_PRTDSI__OE_SEL0        (* (reg8 *) ROW0__PRTDSI__OE_SEL0) 
#define ROW0_PRTDSI__OE_SEL1        (* (reg8 *) ROW0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ROW0_PRTDSI__OUT_SEL0       (* (reg8 *) ROW0__PRTDSI__OUT_SEL0) 
#define ROW0_PRTDSI__OUT_SEL1       (* (reg8 *) ROW0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ROW0_PRTDSI__SYNC_OUT       (* (reg8 *) ROW0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ROW0__SIO_CFG)
    #define ROW0_SIO_HYST_EN        (* (reg8 *) ROW0__SIO_HYST_EN)
    #define ROW0_SIO_REG_HIFREQ     (* (reg8 *) ROW0__SIO_REG_HIFREQ)
    #define ROW0_SIO_CFG            (* (reg8 *) ROW0__SIO_CFG)
    #define ROW0_SIO_DIFF           (* (reg8 *) ROW0__SIO_DIFF)
#endif /* (ROW0__SIO_CFG) */

/* Interrupt Registers */
#if defined(ROW0__INTSTAT)
    #define ROW0_INTSTAT            (* (reg8 *) ROW0__INTSTAT)
    #define ROW0_SNAP               (* (reg8 *) ROW0__SNAP)
    
	#define ROW0_0_INTTYPE_REG 		(* (reg8 *) ROW0__0__INTTYPE)
#endif /* (ROW0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ROW0_H */


/* [] END OF FILE */
