/*******************************************************************************
* File Name: LCD_Char2.h
* Version 2.20
*
* Description:
*  This header file contains registers and constants associated with the
*  Character LCD component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CHARLCD_LCD_Char2_H)
#define CY_CHARLCD_LCD_Char2_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define LCD_Char2_CONVERSION_ROUTINES     (1u)
#define LCD_Char2_CUSTOM_CHAR_SET         (0u)

/* Custom character set types */
#define LCD_Char2_NONE                     (0u)    /* No Custom Fonts      */
#define LCD_Char2_HORIZONTAL_BG            (1u)    /* Horizontal Bar Graph */
#define LCD_Char2_VERTICAL_BG              (2u)    /* Vertical Bar Graph   */
#define LCD_Char2_USER_DEFINED             (3u)    /* User Defined Fonts   */


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} LCD_Char2_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void LCD_Char2_Init(void) ;
void LCD_Char2_Enable(void) ;
void LCD_Char2_Start(void) ;
void LCD_Char2_Stop(void) ;
void LCD_Char2_WriteControl(uint8 cByte) ;
void LCD_Char2_WriteData(uint8 dByte) ;
void LCD_Char2_PrintString(char8 const string[]) ;
void LCD_Char2_Position(uint8 row, uint8 column) ;
void LCD_Char2_PutChar(char8 character) ;
void LCD_Char2_IsReady(void) ;
void LCD_Char2_SaveConfig(void) ;
void LCD_Char2_RestoreConfig(void) ;
void LCD_Char2_Sleep(void) ;
void LCD_Char2_Wakeup(void) ;

#if((LCD_Char2_CUSTOM_CHAR_SET == LCD_Char2_VERTICAL_BG) || \
                (LCD_Char2_CUSTOM_CHAR_SET == LCD_Char2_HORIZONTAL_BG))

    void  LCD_Char2_LoadCustomFonts(uint8 const customData[])
                        ;

    void  LCD_Char2_DrawHorizontalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                         ;

    void LCD_Char2_DrawVerticalBG(uint8 row, uint8 column, uint8 maxCharacters, uint8 value)
                        ;

#endif /* ((LCD_Char2_CUSTOM_CHAR_SET == LCD_Char2_VERTICAL_BG) */

#if(LCD_Char2_CUSTOM_CHAR_SET == LCD_Char2_USER_DEFINED)

    void LCD_Char2_LoadCustomFonts(uint8 const customData[])
                            ;

#endif /* ((LCD_Char2_CUSTOM_CHAR_SET == LCD_Char2_USER_DEFINED) */

#if(LCD_Char2_CONVERSION_ROUTINES == 1u)

    /* ASCII Conversion Routines */
    void LCD_Char2_PrintInt8(uint8 value) ;
    void LCD_Char2_PrintInt16(uint16 value) ;
    void LCD_Char2_PrintInt32(uint32 value) ;
    void LCD_Char2_PrintNumber(uint16 value) ; 
    void LCD_Char2_PrintU32Number(uint32 value) ;
    
#endif /* LCD_Char2_CONVERSION_ROUTINES == 1u */

/* Clear Macro */
#define LCD_Char2_ClearDisplay() LCD_Char2_WriteControl(LCD_Char2_CLEAR_DISPLAY)

/* Off Macro */
#define LCD_Char2_DisplayOff() LCD_Char2_WriteControl(LCD_Char2_DISPLAY_CURSOR_OFF)

/* On Macro */
#define LCD_Char2_DisplayOn() LCD_Char2_WriteControl(LCD_Char2_DISPLAY_ON_CURSOR_OFF)

#define LCD_Char2_PrintNumber(value) LCD_Char2_PrintU32Number((uint16) (value))


/***************************************
*           Global Variables
***************************************/

extern uint8 LCD_Char2_initVar;
extern uint8 LCD_Char2_enableState;
extern uint8 const CYCODE LCD_Char2_customFonts[64u];


/***************************************
*           API Constants
***************************************/

/* Full Byte Commands Sent as Two Nibbles */
#define LCD_Char2_DISPLAY_8_BIT_INIT       (0x03u)
#define LCD_Char2_DISPLAY_4_BIT_INIT       (0x02u)
#define LCD_Char2_DISPLAY_CURSOR_OFF       (0x08u)
#define LCD_Char2_CLEAR_DISPLAY            (0x01u)
#define LCD_Char2_CURSOR_AUTO_INCR_ON      (0x06u)
#define LCD_Char2_DISPLAY_CURSOR_ON        (0x0Eu)
#define LCD_Char2_DISPLAY_2_LINES_5x10     (0x2Cu)
#define LCD_Char2_DISPLAY_ON_CURSOR_OFF    (0x0Cu)

#define LCD_Char2_RESET_CURSOR_POSITION    (0x03u)
#define LCD_Char2_CURSOR_WINK              (0x0Du)
#define LCD_Char2_CURSOR_BLINK             (0x0Fu)
#define LCD_Char2_CURSOR_SH_LEFT           (0x10u)
#define LCD_Char2_CURSOR_SH_RIGHT          (0x14u)
#define LCD_Char2_DISPLAY_SCRL_LEFT        (0x18u)
#define LCD_Char2_DISPLAY_SCRL_RIGHT       (0x1Eu)
#define LCD_Char2_CURSOR_HOME              (0x02u)
#define LCD_Char2_CURSOR_LEFT              (0x04u)
#define LCD_Char2_CURSOR_RIGHT             (0x06u)

/* Point to Character Generator Ram 0 */
#define LCD_Char2_CGRAM_0                  (0x40u)

/* Point to Display Data Ram 0 */
#define LCD_Char2_DDRAM_0                  (0x80u)

/* LCD Characteristics */
#define LCD_Char2_CHARACTER_WIDTH          (0x05u)
#define LCD_Char2_CHARACTER_HEIGHT         (0x08u)

#if(LCD_Char2_CONVERSION_ROUTINES == 1u)
    #define LCD_Char2_NUMBER_OF_REMAINDERS_U32 (0x0Au)
    #define LCD_Char2_TEN                      (0x0Au)
    #define LCD_Char2_8_BIT_SHIFT              (8u)
    #define LCD_Char2_32_BIT_SHIFT             (32u)
    #define LCD_Char2_ZERO_CHAR_ASCII          (48u)
#endif /* LCD_Char2_CONVERSION_ROUTINES == 1u */

/* Nibble Offset and Mask */
#define LCD_Char2_NIBBLE_SHIFT             (0x04u)
#define LCD_Char2_NIBBLE_MASK              (0x0Fu)

/* LCD Module Address Constants */
#define LCD_Char2_ROW_0_START              (0x80u)
#define LCD_Char2_ROW_1_START              (0xC0u)
#define LCD_Char2_ROW_2_START              (0x94u)
#define LCD_Char2_ROW_3_START              (0xD4u)

/* Custom Character References */
#define LCD_Char2_CUSTOM_0                 (0x00u)
#define LCD_Char2_CUSTOM_1                 (0x01u)
#define LCD_Char2_CUSTOM_2                 (0x02u)
#define LCD_Char2_CUSTOM_3                 (0x03u)
#define LCD_Char2_CUSTOM_4                 (0x04u)
#define LCD_Char2_CUSTOM_5                 (0x05u)
#define LCD_Char2_CUSTOM_6                 (0x06u)
#define LCD_Char2_CUSTOM_7                 (0x07u)

/* Other constants */
#define LCD_Char2_BYTE_UPPER_NIBBLE_SHIFT  (0x04u)
#define LCD_Char2_BYTE_LOWER_NIBBLE_MASK   (0x0Fu)
#define LCD_Char2_U16_UPPER_BYTE_SHIFT     (0x08u)
#define LCD_Char2_U16_LOWER_BYTE_MASK      (0xFFu)
#define LCD_Char2_CUSTOM_CHAR_SET_LEN      (0x40u)

#define LCD_Char2_LONGEST_CMD_US           (0x651u)
#define LCD_Char2_WAIT_CYCLE               (0x10u)
#define LCD_Char2_READY_DELAY              ((LCD_Char2_LONGEST_CMD_US * 4u)/(LCD_Char2_WAIT_CYCLE))


/***************************************
*             Registers
***************************************/

/* Device specific registers */
#if (CY_PSOC4)

    #define LCD_Char2_PORT_DR_REG           (*(reg32 *) LCD_Char2_LCDPort__DR)  /* Data Output Register */
    #define LCD_Char2_PORT_DR_PTR           ( (reg32 *) LCD_Char2_LCDPort__DR)
    #define LCD_Char2_PORT_PS_REG           (*(reg32 *) LCD_Char2_LCDPort__PS)  /* Pin State Register */
    #define LCD_Char2_PORT_PS_PTR           ( (reg32 *) LCD_Char2_LCDPort__PS)
    
    #define LCD_Char2_PORT_PC_REG           (*(reg32 *) LCD_Char2_LCDPort__PC)
    #define LCD_Char2_PORT_PC_PTR           (*(reg32 *) LCD_Char2_LCDPort__PC)
    
#else

    #define LCD_Char2_PORT_DR_REG           (*(reg8 *) LCD_Char2_LCDPort__DR)  /* Data Output Register */
    #define LCD_Char2_PORT_DR_PTR           ( (reg8 *) LCD_Char2_LCDPort__DR)
    #define LCD_Char2_PORT_PS_REG           (*(reg8 *) LCD_Char2_LCDPort__PS)  /* Pin State Register */
    #define LCD_Char2_PORT_PS_PTR           ( (reg8 *) LCD_Char2_LCDPort__PS)

    #define LCD_Char2_PORT_DM0_REG          (*(reg8 *) LCD_Char2_LCDPort__DM0) /* Port Drive Mode 0 */
    #define LCD_Char2_PORT_DM0_PTR          ( (reg8 *) LCD_Char2_LCDPort__DM0)
    #define LCD_Char2_PORT_DM1_REG          (*(reg8 *) LCD_Char2_LCDPort__DM1) /* Port Drive Mode 1 */
    #define LCD_Char2_PORT_DM1_PTR          ( (reg8 *) LCD_Char2_LCDPort__DM1)
    #define LCD_Char2_PORT_DM2_REG          (*(reg8 *) LCD_Char2_LCDPort__DM2) /* Port Drive Mode 2 */
    #define LCD_Char2_PORT_DM2_PTR          ( (reg8 *) LCD_Char2_LCDPort__DM2)

#endif /* CY_PSOC4 */


/***************************************
*       Register Constants
***************************************/

/* SHIFT must be 1 or 0 */
#if (0 == LCD_Char2_LCDPort__SHIFT)
    #define LCD_Char2_PORT_SHIFT               (0x00u)
#else
    #define LCD_Char2_PORT_SHIFT               (0x01u)
#endif /* (0 == LCD_Char2_LCDPort__SHIFT) */

#define LCD_Char2_PORT_MASK                ((uint8) (LCD_Char2_LCDPort__MASK))

#if (CY_PSOC4)

    #define LCD_Char2_DM_PIN_STEP              (3u)
    /* Hi-Z Digital is defined by the value of "001b" and this should be set for
    * four data pins, in this way we get - 0x00000249. A similar Strong drive
    * is defined with "110b" so we get 0x00000DB6.
    */
    #define LCD_Char2_HIGH_Z_DATA_DM           ((0x00000249ul) << (LCD_Char2_PORT_SHIFT *\
                                                                          LCD_Char2_DM_PIN_STEP))
    #define LCD_Char2_STRONG_DATA_DM           ((0x00000DB6ul) << (LCD_Char2_PORT_SHIFT *\
                                                                          LCD_Char2_DM_PIN_STEP))
    #define LCD_Char2_DATA_PINS_MASK           (0x00000FFFul)
    #define LCD_Char2_DM_DATA_MASK             ((uint32) (LCD_Char2_DATA_PINS_MASK << \
                                                      (LCD_Char2_PORT_SHIFT * LCD_Char2_DM_PIN_STEP)))

#else

    /* Drive Mode register values for High Z */
    #define LCD_Char2_HIGH_Z_DM0               (0xFFu)
    #define LCD_Char2_HIGH_Z_DM1               (0x00u)
    #define LCD_Char2_HIGH_Z_DM2               (0x00u)

    /* Drive Mode register values for High Z Analog */
    #define LCD_Char2_HIGH_Z_A_DM0             (0x00u)
    #define LCD_Char2_HIGH_Z_A_DM1             (0x00u)
    #define LCD_Char2_HIGH_Z_A_DM2             (0x00u)

    /* Drive Mode register values for Strong */
    #define LCD_Char2_STRONG_DM0               (0x00u)
    #define LCD_Char2_STRONG_DM1               (0xFFu)
    #define LCD_Char2_STRONG_DM2               (0xFFu)

#endif /* CY_PSOC4 */

/* Pin Masks */
#define LCD_Char2_RS                     ((uint8) \
                                                (((uint8) 0x20u) << LCD_Char2_LCDPort__SHIFT))
#define LCD_Char2_RW                     ((uint8) \
                                                (((uint8) 0x40u) << LCD_Char2_LCDPort__SHIFT))
#define LCD_Char2_E                      ((uint8) \
                                                (((uint8) 0x10u) << LCD_Char2_LCDPort__SHIFT))
#define LCD_Char2_READY_BIT              ((uint8) \
                                                (((uint8) 0x08u) << LCD_Char2_LCDPort__SHIFT))
#define LCD_Char2_DATA_MASK              ((uint8) \
                                                (((uint8) 0x0Fu) << LCD_Char2_LCDPort__SHIFT))

/* These names are obsolete and will be removed in future revisions */
#define LCD_Char2_PORT_DR                  LCD_Char2_PORT_DR_REG
#define LCD_Char2_PORT_PS                  LCD_Char2_PORT_PS_REG
#define LCD_Char2_PORT_DM0                 LCD_Char2_PORT_DM0_REG
#define LCD_Char2_PORT_DM1                 LCD_Char2_PORT_DM1_REG
#define LCD_Char2_PORT_DM2                 LCD_Char2_PORT_DM2_REG


/***************************************
*       Obsolete function names
***************************************/
#if(LCD_Char2_CONVERSION_ROUTINES == 1u)
    /* This function names are obsolete and will be removed in future 
    * revisions of the component.
    */
    #define LCD_Char2_PrintDecUint16(x)   LCD_Char2_PrintNumber(x)  
    #define LCD_Char2_PrintHexUint8(x)    LCD_Char2_PrintInt8(x)
    #define LCD_Char2_PrintHexUint16(x)   LCD_Char2_PrintInt16(x)        

#endif /* LCD_Char2_CONVERSION_ROUTINES == 1u */

#endif /* CY_CHARLCD_LCD_Char2_H */


/* [] END OF FILE */
