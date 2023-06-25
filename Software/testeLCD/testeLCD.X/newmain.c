/*
 * File:   newmain.c
 * Author: carol
 *
 * Created on 23 de Junho de 2023, 21:03
 */


#include <xc.h>
#define _XTAL_FREQ 4000000
//*** define pinos referentes a interface com LCD
#define RS PORTDbits.RD2
#define EN PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

#include "lcd.h"


void main(void) {
    TRISD = 0;
    Lcd_Init(); //incia o lcd
    //colocar a variavel
    char buffer[20];
    while(1)
    {
         //** mostra uma string e o conte?do de uma vari?vel
    Lcd_Clear();                          //limpa LCD
    Lcd_Set_Cursor(1,1);
                        
    Lcd_Write_String("luminosidade atual: i%", );             //Escreve o conte?do de buffer no LCD
    __delay_ms(100);
    }
    return;
}
