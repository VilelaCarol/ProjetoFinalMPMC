/*
 * File:   newmain.c
 * Author: carol
 *
 * Created on 23 de Junho de 2023, 21:03
 */


#include <xc.h>
#include "lcd.h"

//*** define pinos referentes a interface com LCD
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7


void main(void) {
    //colocar a variavel
    char buffer[20];
    while(1)
    {
         //** mostra uma string e o conte?do de uma vari?vel
    Lcd_Clear();                          //limpa LCD
    sprintf(buffer, "Float = %0.2f", f);  //Armazena em buffer o conte?do da vari?vel f formatado com duas casas
    Lcd_Set_Cursor(1,1);                  
    Lcd_Write_String(buffer);             //Escreve o conte?do de buffer no LCD
    __delay_ms(2000);
    }
    return;
}
