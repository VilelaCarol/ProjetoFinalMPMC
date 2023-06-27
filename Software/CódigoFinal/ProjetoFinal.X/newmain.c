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
#include <math.h>

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
#define LED1 PORTDbits.RD1
#define LED2 PORTDbits.RD0
#define LED3 PORTCbits.RC7
#define LED4 PORTCbits.RC6
#define LED5 PORTCbits.RC5
#define LED6 PORTCbits.RC4
#define LED7 PORTCbits.RC3
#define LED8 PORTCbits.RC1


#include "lcd.h"

// FLAGS BOTÕES
int btn_mais_aux = 0;
int btn_menos_aux = 0;
int porcentagem_PWM = 50;
int menu_ativo = 0;
int luminosidade_desejada = 400;

void configADC(){
    //configura quais pinos serão entrada analógica...neste caso estou colocando todos como entrada analógica
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG3 = 1;
    
    //configura clock para conversão, sample rate de Fosc/2
    
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 0;
    ADCON1bits.ADCS2 = 0;
    
    //define s evai ser 8 ou 10 bits... no meu caso são 8 bits ... 0= 8 BITS   1= 10 BITS
    
    ADCON1bits.ADFM = 0;
  
    //incializa registradores do AD
    ADRESL = 0x00;
    ADRESH = 0X00;
           
    //Liga o conversor ad
    
    ADCON0bits.ADON = 1;
    
    //Seleciona canal da entrada 0 como entrada analógica 
    ADCON0bits.CHS0 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
      
}
void atualizarLeds(int porcentagem){
    int numLEDsAcesos = (porcentagem * 8)/100;
    LED1= 0;
    LED2= 0;
    LED3= 0;
    LED4= 0;
    LED5= 0;
    LED6= 0;
    LED7= 0;
    LED8= 0;
    if(numLEDsAcesos > 0){
        LED1 = 1;
    }
    if(numLEDsAcesos > 1){
        LED2 = 1;
    }
    if(numLEDsAcesos > 2){
        LED3 = 1;
    }
    if(numLEDsAcesos > 3){
        LED4 = 1;
    }
    if(numLEDsAcesos > 4){
        LED5 = 1;
    }
    if(numLEDsAcesos > 5){
        LED6 = 1;
    }
    if(numLEDsAcesos > 6){
        LED7 = 1;
    }
    if(numLEDsAcesos > 7){
        LED8 = 1;
    }

    
}

int getValorADC(){
    int valor;
     //CONVERTE
    
    ADCON0bits.GO = 1;
    
    
    //tempo de conversão
    __delay_us(10);
            
    //passa o valor convertido para o reg para a variavel
            
    valor = ADRESH;     // ou = 256;
    return valor;
}

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
        if(luminosidade_desejada<1000){
            luminosidade_desejada+=10;
        }
        else{
            luminosidade_desejada = 1000;
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
        if(luminosidade_desejada>10){
            luminosidade_desejada-=10;
        }
        else{
            luminosidade_desejada = 10;
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
        char texto_luminosidade_desejada [16];
        intToASCIIinCustomBase (luminosidade_desejada , texto_luminosidade_desejada, 10);
        escreveLCD("MENU - OBJETIVO", texto_luminosidade_desejada);
       
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

float converteLeituraAnParaVolts(float leitura)
{
    return leitura * 5/255;
}

int converteVoltsParaLux(float v_ldr){
    int r_ldr = (10000*v_ldr)/(5-v_ldr);
    float b = ((log10(4) - log10(9)) - 1)/990;
    float  l_ldr = 
    (
        log10(r_ldr) 
        - 
        log10(400) 
        + 
        1000 * b
    ) 
    * 
    (
        1/b
    );
    return l_ldr;
}
float v_ldr;
int leitura;
int luminosidade_atual;

void main(void) {
  
    TRISC = 0x00;   // Configure PORTC as output(RC2-PWM1, RC1-PWM2)
    
    OPTION_REGbits.INTEDG = 1;
    TRISB = 1;
    
    configADC();
    configPWMRegs();
    
    
    TRISD = 0;
    Lcd_Init(); //incia o lcd
    //colocar a variavel
    char* texto_menu;
   
    texto_menu = "LUMINOSIDADE ATUAL:";
   

    configIntExterns();
    int margem_erro_lux = 10;
    while(1)
    { 
        leitura = getValorADC();
        v_ldr = converteLeituraAnParaVolts(leitura);
        luminosidade_atual = converteVoltsParaLux(v_ldr);
        handleSetupMenu();
        
        char texto_luminosidade [16];
        intToASCIIinCustomBase (luminosidade_atual , texto_luminosidade, 10);
        
        escreveLCD(texto_menu, texto_luminosidade);
        
        if(luminosidade_atual < luminosidade_desejada - margem_erro_lux)
        {
            if(porcentagem_PWM < 100)   //aumenta pwm
                porcentagem_PWM++;    
        }       
        else if (luminosidade_atual > luminosidade_desejada + margem_erro_lux)
        {
            if(porcentagem_PWM > 0)    //diminiu o pwm
                porcentagem_PWM--;
        }
        PWM_REG = porcentagem_PWM;
        atualizarLeds(porcentagem_PWM);
    }
    return;
}