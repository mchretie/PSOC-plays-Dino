/*******************************************************************************
* File Name: DUCK.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "DUCK.h"

/* Error message for removed <resource> through optimization */
#ifdef DUCK_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* DUCK_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 DUCK_initVar = 0u;


/*******************************************************************************
* Function Name: DUCK_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  DUCK_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void DUCK_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(DUCK_initVar == 0u)
    {
        DUCK_Init();
        DUCK_initVar = 1u;
    }
    DUCK_Enable();

}


/*******************************************************************************
* Function Name: DUCK_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  DUCK_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void DUCK_Init(void) 
{
    #if (DUCK_UsingFixedFunction || DUCK_UseControl)
        uint8 ctrl;
    #endif /* (DUCK_UsingFixedFunction || DUCK_UseControl) */

    #if(!DUCK_UsingFixedFunction)
        #if(DUCK_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 DUCK_interruptState;
        #endif /* (DUCK_UseStatus) */
    #endif /* (!DUCK_UsingFixedFunction) */

    #if (DUCK_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        DUCK_CONTROL |= DUCK_CFG0_MODE;
        #if (DUCK_DeadBand2_4)
            DUCK_CONTROL |= DUCK_CFG0_DB;
        #endif /* (DUCK_DeadBand2_4) */

        ctrl = DUCK_CONTROL3 & ((uint8 )(~DUCK_CTRL_CMPMODE1_MASK));
        DUCK_CONTROL3 = ctrl | DUCK_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        DUCK_RT1 &= ((uint8)(~DUCK_RT1_MASK));
        DUCK_RT1 |= DUCK_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        DUCK_RT1 &= ((uint8)(~DUCK_SYNCDSI_MASK));
        DUCK_RT1 |= DUCK_SYNCDSI_EN;

    #elif (DUCK_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = DUCK_CONTROL & ((uint8)(~DUCK_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~DUCK_CTRL_CMPMODE1_MASK));
        DUCK_CONTROL = ctrl | DUCK_DEFAULT_COMPARE2_MODE |
                                   DUCK_DEFAULT_COMPARE1_MODE;
    #endif /* (DUCK_UsingFixedFunction) */

    #if (!DUCK_UsingFixedFunction)
        #if (DUCK_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            DUCK_AUX_CONTROLDP0 |= (DUCK_AUX_CTRL_FIFO0_CLR);
        #else /* (DUCK_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            DUCK_AUX_CONTROLDP0 |= (DUCK_AUX_CTRL_FIFO0_CLR);
            DUCK_AUX_CONTROLDP1 |= (DUCK_AUX_CTRL_FIFO0_CLR);
        #endif /* (DUCK_Resolution == 8) */

        DUCK_WriteCounter(DUCK_INIT_PERIOD_VALUE);
    #endif /* (!DUCK_UsingFixedFunction) */

    DUCK_WritePeriod(DUCK_INIT_PERIOD_VALUE);

        #if (DUCK_UseOneCompareMode)
            DUCK_WriteCompare(DUCK_INIT_COMPARE_VALUE1);
        #else
            DUCK_WriteCompare1(DUCK_INIT_COMPARE_VALUE1);
            DUCK_WriteCompare2(DUCK_INIT_COMPARE_VALUE2);
        #endif /* (DUCK_UseOneCompareMode) */

        #if (DUCK_KillModeMinTime)
            DUCK_WriteKillTime(DUCK_MinimumKillTime);
        #endif /* (DUCK_KillModeMinTime) */

        #if (DUCK_DeadBandUsed)
            DUCK_WriteDeadTime(DUCK_INIT_DEAD_TIME);
        #endif /* (DUCK_DeadBandUsed) */

    #if (DUCK_UseStatus || DUCK_UsingFixedFunction)
        DUCK_SetInterruptMode(DUCK_INIT_INTERRUPTS_MODE);
    #endif /* (DUCK_UseStatus || DUCK_UsingFixedFunction) */

    #if (DUCK_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        DUCK_GLOBAL_ENABLE |= DUCK_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        DUCK_CONTROL2 |= DUCK_CTRL2_IRQ_SEL;
    #else
        #if(DUCK_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            DUCK_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            DUCK_STATUS_AUX_CTRL |= DUCK_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(DUCK_interruptState);

            /* Clear the FIFO to enable the DUCK_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            DUCK_ClearFIFO();
        #endif /* (DUCK_UseStatus) */
    #endif /* (DUCK_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: DUCK_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void DUCK_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (DUCK_UsingFixedFunction)
        DUCK_GLOBAL_ENABLE |= DUCK_BLOCK_EN_MASK;
        DUCK_GLOBAL_STBY_ENABLE |= DUCK_BLOCK_STBY_EN_MASK;
    #endif /* (DUCK_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (DUCK_UseControl || DUCK_UsingFixedFunction)
        DUCK_CONTROL |= DUCK_CTRL_ENABLE;
    #endif /* (DUCK_UseControl || DUCK_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: DUCK_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void DUCK_Stop(void) 
{
    #if (DUCK_UseControl || DUCK_UsingFixedFunction)
        DUCK_CONTROL &= ((uint8)(~DUCK_CTRL_ENABLE));
    #endif /* (DUCK_UseControl || DUCK_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (DUCK_UsingFixedFunction)
        DUCK_GLOBAL_ENABLE &= ((uint8)(~DUCK_BLOCK_EN_MASK));
        DUCK_GLOBAL_STBY_ENABLE &= ((uint8)(~DUCK_BLOCK_STBY_EN_MASK));
    #endif /* (DUCK_UsingFixedFunction) */
}

#if (DUCK_UseOneCompareMode)
    #if (DUCK_CompareMode1SW)


        /*******************************************************************************
        * Function Name: DUCK_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DUCK_SetCompareMode(uint8 comparemode) 
        {
            #if(DUCK_UsingFixedFunction)

                #if(0 != DUCK_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << DUCK_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != DUCK_CTRL_CMPMODE1_SHIFT) */

                DUCK_CONTROL3 &= ((uint8)(~DUCK_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                DUCK_CONTROL3 |= comparemodemasked;

            #elif (DUCK_UseControl)

                #if(0 != DUCK_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << DUCK_CTRL_CMPMODE1_SHIFT)) &
                                                DUCK_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & DUCK_CTRL_CMPMODE1_MASK;
                #endif /* (0 != DUCK_CTRL_CMPMODE1_SHIFT) */

                #if(0 != DUCK_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << DUCK_CTRL_CMPMODE2_SHIFT)) &
                                               DUCK_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & DUCK_CTRL_CMPMODE2_MASK;
                #endif /* (0 != DUCK_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                DUCK_CONTROL &= ((uint8)(~(DUCK_CTRL_CMPMODE1_MASK |
                                            DUCK_CTRL_CMPMODE2_MASK)));
                DUCK_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (DUCK_UsingFixedFunction) */
        }
    #endif /* DUCK_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (DUCK_CompareMode1SW)


        /*******************************************************************************
        * Function Name: DUCK_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DUCK_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != DUCK_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << DUCK_CTRL_CMPMODE1_SHIFT)) &
                                           DUCK_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & DUCK_CTRL_CMPMODE1_MASK;
            #endif /* (0 != DUCK_CTRL_CMPMODE1_SHIFT) */

            #if (DUCK_UseControl)
                DUCK_CONTROL &= ((uint8)(~DUCK_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                DUCK_CONTROL |= comparemodemasked;
            #endif /* (DUCK_UseControl) */
        }
    #endif /* DUCK_CompareMode1SW */

#if (DUCK_CompareMode2SW)


    /*******************************************************************************
    * Function Name: DUCK_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != DUCK_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << DUCK_CTRL_CMPMODE2_SHIFT)) &
                                                 DUCK_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & DUCK_CTRL_CMPMODE2_MASK;
        #endif /* (0 != DUCK_CTRL_CMPMODE2_SHIFT) */

        #if (DUCK_UseControl)
            DUCK_CONTROL &= ((uint8)(~DUCK_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            DUCK_CONTROL |= comparemodemasked;
        #endif /* (DUCK_UseControl) */
    }
    #endif /*DUCK_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!DUCK_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: DUCK_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void DUCK_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(DUCK_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: DUCK_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 DUCK_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(DUCK_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(DUCK_CAPTURE_LSB_PTR));
    }

    #if (DUCK_UseStatus)


        /*******************************************************************************
        * Function Name: DUCK_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void DUCK_ClearFIFO(void) 
        {
            while(0u != (DUCK_ReadStatusRegister() & DUCK_STATUS_FIFONEMPTY))
            {
                (void)DUCK_ReadCapture();
            }
        }

    #endif /* DUCK_UseStatus */

#endif /* !DUCK_UsingFixedFunction */


/*******************************************************************************
* Function Name: DUCK_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void DUCK_WritePeriod(uint16 period) 
{
    #if(DUCK_UsingFixedFunction)
        CY_SET_REG16(DUCK_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(DUCK_PERIOD_LSB_PTR, period);
    #endif /* (DUCK_UsingFixedFunction) */
}

#if (DUCK_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: DUCK_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void DUCK_WriteCompare(uint16 compare) \
                                       
    {
        #if(DUCK_UsingFixedFunction)
            CY_SET_REG16(DUCK_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(DUCK_COMPARE1_LSB_PTR, compare);
        #endif /* (DUCK_UsingFixedFunction) */

        #if (DUCK_PWMMode == DUCK__B_PWM__DITHER)
            #if(DUCK_UsingFixedFunction)
                CY_SET_REG16(DUCK_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(DUCK_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (DUCK_UsingFixedFunction) */
        #endif /* (DUCK_PWMMode == DUCK__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: DUCK_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_WriteCompare1(uint16 compare) \
                                        
    {
        #if(DUCK_UsingFixedFunction)
            CY_SET_REG16(DUCK_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(DUCK_COMPARE1_LSB_PTR, compare);
        #endif /* (DUCK_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: DUCK_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_WriteCompare2(uint16 compare) \
                                        
    {
        #if(DUCK_UsingFixedFunction)
            CY_SET_REG16(DUCK_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(DUCK_COMPARE2_LSB_PTR, compare);
        #endif /* (DUCK_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (DUCK_DeadBandUsed)


    /*******************************************************************************
    * Function Name: DUCK_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!DUCK_DeadBand2_4)
            CY_SET_REG8(DUCK_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            DUCK_DEADBAND_COUNT &= ((uint8)(~DUCK_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(DUCK_DEADBAND_COUNT_SHIFT)
                DUCK_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << DUCK_DEADBAND_COUNT_SHIFT)) &
                                                    DUCK_DEADBAND_COUNT_MASK;
            #else
                DUCK_DEADBAND_COUNT |= deadtime & DUCK_DEADBAND_COUNT_MASK;
            #endif /* (DUCK_DEADBAND_COUNT_SHIFT) */

        #endif /* (!DUCK_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: DUCK_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 DUCK_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!DUCK_DeadBand2_4)
            return (CY_GET_REG8(DUCK_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(DUCK_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(DUCK_DEADBAND_COUNT & DUCK_DEADBAND_COUNT_MASK)) >>
                                                                           DUCK_DEADBAND_COUNT_SHIFT));
            #else
                return (DUCK_DEADBAND_COUNT & DUCK_DEADBAND_COUNT_MASK);
            #endif /* (DUCK_DEADBAND_COUNT_SHIFT) */
        #endif /* (!DUCK_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (DUCK_UseStatus || DUCK_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: DUCK_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(DUCK_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: DUCK_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 DUCK_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(DUCK_STATUS_PTR));
    }

#endif /* (DUCK_UseStatus || DUCK_UsingFixedFunction) */


#if (DUCK_UseControl)


    /*******************************************************************************
    * Function Name: DUCK_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 DUCK_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(DUCK_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: DUCK_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(DUCK_CONTROL_PTR, control);
    }

#endif /* (DUCK_UseControl) */


#if (!DUCK_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: DUCK_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 DUCK_ReadCapture(void) 
    {
        return (CY_GET_REG16(DUCK_CAPTURE_LSB_PTR));
    }

#endif /* (!DUCK_UsingFixedFunction) */


#if (DUCK_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: DUCK_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 DUCK_ReadCompare(void) 
    {
        #if(DUCK_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(DUCK_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(DUCK_COMPARE1_LSB_PTR));
        #endif /* (DUCK_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: DUCK_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 DUCK_ReadCompare1(void) 
    {
        return (CY_GET_REG16(DUCK_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: DUCK_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 DUCK_ReadCompare2(void) 
    {
        return (CY_GET_REG16(DUCK_COMPARE2_LSB_PTR));
    }

#endif /* (DUCK_UseOneCompareMode) */


/*******************************************************************************
* Function Name: DUCK_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 DUCK_ReadPeriod(void) 
{
    #if(DUCK_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(DUCK_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(DUCK_PERIOD_LSB_PTR));
    #endif /* (DUCK_UsingFixedFunction) */
}

#if ( DUCK_KillModeMinTime)


    /*******************************************************************************
    * Function Name: DUCK_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void DUCK_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(DUCK_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: DUCK_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 DUCK_ReadKillTime(void) 
    {
        return (CY_GET_REG8(DUCK_KILLMODEMINTIME_PTR));
    }

#endif /* ( DUCK_KillModeMinTime) */

/* [] END OF FILE */
