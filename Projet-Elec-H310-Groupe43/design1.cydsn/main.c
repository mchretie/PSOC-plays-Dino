/* ========================================
 *
 *
 *
 * Groupe 43
 * Projet Digital Electronics
 * Elec-H310
 * youssef TALHAOUI 503861 /  Marcus Chretien 498327 
 * ========================================
*/
#include "project.h"
#include "keypad.h"
#include <stdio.h>
#include <math.h>
#define PI 3.14


float jmp; 
uint16_t i = 0;
uint8_t value;
uint16 ms_count;
int score= 0 ;

// Array to contain the values of the sin wave 
double wave[100];

void jump() ; 
void duck() ; 

CY_ISR(sw1){ // interruption for jump button 
    jump();}
    
CY_ISR(sw2){ // interruption for duck button  
    duck();}

CY_ISR (InterruptionRX) { // interruption for UART 
    
    uint8_t status = 0;
    do{
        // Checks if no UART Rx errors
        status = UART_ReadRxStatus () ;
        if (( status & UART_RX_STS_PAR_ERROR ) |
            ( status & UART_RX_STS_STOP_ERROR ) |
            ( status & UART_RX_STS_BREAK ) |
            ( status & UART_RX_STS_OVERRUN ) ) {
        // Parity , framing , break or overrun error
        //LCD_Position (1 ,0) ;
        //LCD_PrintString (" UART err");
        }
    
        // Check that rx buffer is not empty and get rx data
        if ( ( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0) {
            uint8 Receiver = UART_ReadRxData () ;
        
            if (Receiver == 'J' || Receiver == 'j' ){ 
            // if we receive a j then jump
                jump();
            }
            else if(Receiver == 'D' || Receiver == 'd' ){ 
            //if we receive a d then duck 
                duck();
            }
        }
    } while (( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0) ;
}

// interruption for reset button 
CY_ISR(sw3){
if (SW3_Read()){
    Timer_Stop();
    score=0;
    LCD_Char_ClearDisplay();
    LCD_Char_Position(0,0);
    LCD_Char_PrintString("READY");
}}

// interruption for the score counting on LCD screen
// 10pts incrementation every second
CY_ISR(MY_ISR) {
    score+=10;
    LCD_Char_Position(1,0);
    LCD_Char_PrintNumber(score);
}

//duck function
void duck(){
    LCD_Char_Position(0,0);  
    LCD_Char_PrintString("Duck ");
    LED3_Write(1); //turn the led on 
    LED4_Write(1);
    // Updates servo motor to "push-down" position 
    DUCK_WriteCompare(2100); 
    int j=0;
    
    // Loop generating ducking sound for 0.5s 
    for(int i=0;i<500000;i++) { 
        if(0x80 & Timer_audio_ReadStatusRegister()){
            VDAC_SetValue(wave[j]); 
            if (j>99) j=0;
            j++;
       }
    }
    // Updates servo motor to "up" position 
    DUCK_WriteCompare(2500);
    LED3_Write(0); //turn off the led
    LED4_Write(0);
    char string[1024];
    sprintf(string,"DUCK \n");
    //Writes "DUCK" in the UART 
    UART_PutString(string);
    //if the game didn't start , start  the score  
    if ( score == 0 ){
        Timer_Start(); // Configure and enable timer
        isr_1_StartEx(MY_ISR);
    }
}


// Jump function
void jump(){
    LCD_Char_Position(0,0);  // displays "Jump" on the LCD screen
    LCD_Char_PrintString("Jump ");
    LED1_Write(1); // LEDs switch on 
    LED2_Write(1);
    // Updates servo motor to "push-down" position 
    JUMP_WriteCompare(2100);
    int j =0;
    
    // Loop generating jumping sound for 0.5s 
     for(int i=0;i<500000;i++){ 
        if(0x80 & Timer_audio_ReadStatusRegister()){
            VDAC_SetValue(wave[j]);
            if (j>99) j=0;
            // increment twice to get a higher pitch
            j++;
            j++;
        }
    }
    // Updates servo motor to "up" position 
    JUMP_WriteCompare(2600);
    LED1_Write(0); // turn off the LEDs
    LED2_Write(0);
    char string[1024];
    //Writes "JUMP" in the UART 
    sprintf(string,"JUMP \n");
    UART_PutString(string); //print in the UART JUMP
    //if the game didn't start , start the score  
    if ( score == 0 ){
        Timer_Start(); // Configure and enable timer
        isr_1_StartEx(MY_ISR);
    }
}



int main(void)
{
    /* Enable global interrupts. */
    CyGlobalIntEnable;
    
    //start the interruption for the 3 buttons 
    isr_sw3_StartEx(sw3);
    isr_sw2_StartEx(sw2);
    isr_sw1_StartEx(sw1);
    
    //start the interruption to read UART 
    isr_RX_StartEx(InterruptionRX);
    ADC_Start(); 
    AMUX_Start();// switch between the photoresistors
    LCD_Char_Start();
    LCD_Char_ClearDisplay();
    Timer_audio_Start();
    VDAC_Start();
    UART_Start();
    JUMP_Start();
    DUCK_Start();
    LCD_Char_Init();
    LCD_Char_Start();
    LCD_Char_PrintString("READY");
    keypadInit();
    ADC_StartConvert();
    
    char key;

    //initialising the sin wave for the sound 
    for (int i =0 ;i<100;i++){ 
        wave[i]= 128*sin( (i/25)* 2 * M_PI)+80;
    }
    for(;;){
        key=keypadScan();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT); //to read the value of the resistors
        
        AMUX_Select(0); //switch to the jump resistor 
        int32 tmp_pot1=ADC_GetResult32(); 
        int16 potjump=ADC_CountsTo_mVolts(tmp_pot1);
        
        CyDelay(10); // Delay needed for the AMUX
        
        AMUX_Select(1); //switch to the duck resistor
        int32 tmp_pot2=ADC_GetResult32();
        int16 potduck=ADC_CountsTo_mVolts(tmp_pot2);

         if ( (potjump> 3200) || key=='2' ){ // if object detected or key pressed
            jump();
        }
        else if ( (potduck>3550 ) || key=='5'  ) {// if object detected or key pressed
                duck();
        }  
        //For calibration and DEBUG, allows us to show values on our computer
        //sprintf(string,"pot1 %d  pot2 %d \r\n",potjump,potduck);
        //UART_PutString(string);
        
    }
}
/* [] END OF FILE */

