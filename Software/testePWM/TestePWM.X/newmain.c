/*
 * File:   newmain.c
 * Author: carol
 *
 * Created on 18 de Junho de 2023, 22:31
 */


#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>

#define _XTAL_FREQ 4000000

#define PWM_REG CCPR1L        //PINO RC2
#define BTN_MAIS PORTBbits.RB2
#define BTN_MENOS PORTBbits.RB3

// FLAGS BOTÕES
int btn_mais_aux = 0;
int btn_menos_aux = 0;

void configPWMRegs(){
    CCP1CON = 0x0F; // Select the PWM mode.
    PR2 = 100;      // Set the Cycle time to 100 for varying the duty cycle from 0-100
    PWM_REG = 0;    // By default set the dutyCycle to 50
    TMR2ON = 1;     //Start the Timer for PWM generation
    
    
}

void verificaBtnMais(){
    
    //verificando botão mais 
    if(!btn_mais_aux && !BTN_MAIS){
        btn_mais_aux = 1;
        if(PWM_REG<=100){
            PWM_REG+=10;
        }
    }
    else{
        if(BTN_MAIS){
            btn_mais_aux = 0;
        }
    }

}

void verificaBtnMenos(){

    if(!btn_menos_aux && !BTN_MENOS){
        btn_menos_aux = 1;
        if(PWM_REG>=0){
            PWM_REG-=10;
        }
   }
    else{
        if(BTN_MENOS){
            btn_menos_aux = 0;
        }
    }
}

void main(void) {
  
    TRISC = 0x00;   // Configure PORTC as output(RC2-PWM1, RC1-PWM2)
    
    OPTION_REGbits.INTEDG = 1;
    TRISB = 1;
    
    configPWMRegs();
   
    

    
    while(1)
    { 
        verificaBtnMais();
        verificaBtnMenos();
        
         
    }
    return;
}
