/*
 * File:   newmain.c
 * Author: carol
 *
 * Created on 23 de Junho de 2023, 17:51
 */


#include <xc.h>
#define _XTAL_FREQ 4000000

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
void main(void) {
    TRISB = 0;
    configADC();
   
   while(1)
   { 
  
   
    
    //Colocar os valores no portb?
    
    PORTB = getValorADC();
   }
    return;
}
