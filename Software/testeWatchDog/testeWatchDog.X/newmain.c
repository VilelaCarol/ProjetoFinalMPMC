/*
 * File:   newmain.c
 * Author: carol
 *
 * Created on 23 de Junho de 2023, 16:26
 */


#include <xc.h>
#pragma config WDTE = ON           //habilita o uso do watchdog
#pragma config FOSC = HS           //define uso do clock externo em 4 ou 20mHZ
#pragma CONFIG PWRTE = ON          // habilita o reset ao ligar. obs: posso ligar apenas um resistor no vcc no pino 1 com esse pragma
#pragma BOREN = ON                 // habilita o reset por Brown-out


void main(void) {
    
    OPTION_REGbits.PSA = 1;         //indica a utiliza��o do timer0 para Watchdog
    
    //Configura��o da taxa de temporiza��o do watch dog 1:2 36ms
    
    OPTION_REGbits.ps0 = 1;
    OPTION_REGbits.ps1 = 0;
    OPTION_REGbits.ps2 = 0;
    
    
    CLRWDT();
    return;
}
