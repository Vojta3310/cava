#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

#include <avr/io.h>

/******************************************************
    inicializacia
    - nastavenie baudRate - ako vstupna premenna
    - zapne vysielac a prijimac
    - 8 datovych a 1 stop bity
******************************************************/

void uart_init();

/******************************************************
    odosle bajt (znak)
******************************************************/

void uart_putc(unsigned char data);

/******************************************************
    odosle retazec bajtov (znakov)
******************************************************/

void uart_puts(char *s);

/******************************************************
    prijem bajt-u (znak)
******************************************************/

unsigned char uart_getc(void);

/******************************************************
    prijem bajt-u (znak) not pooling
******************************************************/

unsigned char uart_getcNP(void);

/******************************************************
    prijem retazca znakov
******************************************************/


unsigned char uart_gets(char *pole);

/******************************************************
    vycistenie buffer-a
******************************************************/

extern void uart_flush(void);

#endif // UART_H_INCLUDED
