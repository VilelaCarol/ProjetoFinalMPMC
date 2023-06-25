/*
 * File:   newmain.c
 * Author: carol
 *
 * Created on 25 de Junho de 2023, 11:05
 */


#include <xc.h>
#include <pic16f877a.h>
#include <stdio.h>
#include <stdlib.h>

#define _XTAL_FREQ 4000000
#define ENTER PORTBbits.RB0
#define PWM_REG CCPR1L        //PINO RC2
#define BTN_MAIS PORTBbits.RB2
#define BTN_MENOS PORTBbits.RB3

//*** define pinos referentes a interface com LCD
#define RS PORTDbits.RD2
#define EN PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

#include "lcd.h"

// FLAGS BOTÕES
int btn_mais_aux = 0;
int btn_menos_aux = 0;
int porcentagem_PWM = 50;
int menu_ativo = 0;


void intToASCIIinCustomBase(int numero, char* resultado, int base) {
    int indice = 0;
    int resto;
    if (numero == 0) {
        resultado[indice++] = '0';
        resultado[indice] = '\0';
        return;
    }
    while (numero != 0) {
        resto = numero % base;
        resultado[indice++] = (resto > 9) ? (resto - 10) + 'A' : resto + '0';
        numero /= base;
    }
    resultado[indice] = '\0';

    // Inverte a string
    int i, j;
    for (i = 0, j = indice - 1; i < j; i++, j--) {
        char temp = resultado[i];
        resultado[i] = resultado[j];
        resultado[j] = temp;
    }
}

void configPWMRegs(){
    CCP1CON = 0x0F; 
    PR2 = 100;      
    PWM_REG = porcentagem_PWM;    
    TMR2ON = 1;     
    
    
}

void verificaBtnMais(){
    
    //verificando botão mais 
    if(!btn_mais_aux && !BTN_MAIS){
        btn_mais_aux = 1;
        if(porcentagem_PWM<100){
            porcentagem_PWM+=10;
        }
        else{
            porcentagem_PWM = 100;
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
        if(porcentagem_PWM>0){
            porcentagem_PWM-=10;
        }
        else{
            porcentagem_PWM = 0;
        }
   }
    else{
        if(BTN_MENOS){
            btn_menos_aux = 0;
        }
    }
}


void __interrupt() interrupcao(void) 
{
    if(INTF){
        if(menu_ativo){
            menu_ativo = 0;
        }
        else{
        menu_ativo = 1;
        }
        
        INTCONbits.INTF = 0;
    }
     
   
}


void escreveLCD(char* linha1, char* linha2)
{
                   //** mostra uma string e o conteudo de uma variavel
    Lcd_Clear();                          //limpa LCD
    Lcd_Set_Cursor(1,1);                        
    Lcd_Write_String(linha1);             //Escreve o conte?do de buffer no LCD
    
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String(linha2);
    
    __delay_ms(100);
        
     
}

void handleSetupMenu ()
{
    while (menu_ativo)                          // Se o botao for acionado
    {

     
        verificaBtnMais();
        verificaBtnMenos();
        escreveLCD("MENU - OBJETIVO", "500 LUX");
       
    }
}

void configIntExterns()
{
    OPTION_REGbits.INTEDG   = 0;
    INTCONbits.GIE          = 1;
    INTCONbits.INTE         = 1;
    INTCONbits.INTF         = 0;
    return;
}


void main(void) {
  
    TRISC = 0x00;   // Configure PORTC as output(RC2-PWM1, RC1-PWM2)
    
    OPTION_REGbits.INTEDG = 1;
    TRISB = 1;
    
    
    configPWMRegs();
    
    
    TRISD = 0;
    Lcd_Init(); //incia o lcd
    //colocar a variavel
    char* texto_menu;
   
    texto_menu = "LAMPADA EM :";
   

    configIntExterns();
    while(1)
    { 
        handleSetupMenu();
        PWM_REG = porcentagem_PWM;
        char texto_porcentagem [16];
        intToASCIIinCustomBase (porcentagem_PWM, texto_porcentagem, 10);
        texto_porcentagem [14] = '%';
        
        escreveLCD(texto_menu, texto_porcentagem);
                
    
    }
    return;
}