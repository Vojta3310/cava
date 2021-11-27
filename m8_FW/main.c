//**********************************************
//*****   PROGRAM FOR DRIVING BLDC MOTOR  ******
//**********************************************
// Controller:	ATmega8 (Clock: 16 Mhz-external)
// Author:		  Vojtěch Nydrle
// Date:		  	3-5 2020
// Fuses:			(E:FF, H:CF, L:FF)
//**********************************************

#include "uart.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//#include <stdbool.h>
#include <math.h>

void port_init(void) {
    PORTB = 0x00;
    DDRB = 0xFF;
    PORTC = 0x00;
    DDRC = 0xF8;
    PORTD = 0x00;
    DDRD = 0xF3;
}

// call this routine to initialize all peripherals
void init_devices(void) {
    port_init();
    uart_init();

    // TODO: somehow disable timer interrupt
    // TCCR0 |= (1 << CS01) | (1 << CS00);
    // TIMSK |= (1 << TOIE0);

    OCR1A = 0xff;
    OCR1B = 0xff;
    OCR2 = 0xff;

    // set none-inverting PWM mode
    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << COM1A0) | (1 << COM1B0);
    TCCR2 |= (1 << COM21) | (1 << COM20);

    // set 8bit Fast PWM Mode
    TCCR1B |= (1 << WGM12);
    TCCR1A |= (1 << WGM10);
    TCCR2 |= (1 << WGM21) | (1 << WGM20);

    // set prescaler to 1 and starts PWM
    TCCR1B |= (1 << CS10);
    TCCR2 |= (1 << CS20);

    sei();
}

volatile uint8_t cap = 0;
volatile int n = 0;
char str[5] = {0};
volatile char c;

uint8_t toi() {
    uint8_t num = 0;
    for (int i = 0; i < 3; ++i) {
        num *= 10;
        num += str[i] - '0';
    }
    return num;
}

ISR(USART_RXC_vect) {
    //cli();
    c = UDR;

    if (c >= '0' && c <= '9' && cap > 0) {
        str[n++] = c;
        if (n == 3) {
            if (cap == 1) {
                OCR1A = 255 - toi();
            } else if (cap == 2) {
                OCR1B = 255 - toi();
            } else if (cap == 3) {
                OCR2 = 255 - toi();
            }
            cap = 0;
            n = 0;
        }
    }

    if (c == 'r') {
        cap = 1;
    }
    if (c == 'g') {
        cap = 2;
    }
    if (c == 'b') {
        cap = 3;
    }

    if (c == 'f') {
        OCR2 = 255;
        OCR1A = 255;
        OCR1B = 255;
    }
    //sei();
}

// main program loop
int main(void) {
    init_devices();
    _delay_ms(80);
    char buf[128];
    sprintf(buf, "I am here ... and alive!\n\r");
    uart_puts(buf);

    while (1) {
    }
    return 0;
}

