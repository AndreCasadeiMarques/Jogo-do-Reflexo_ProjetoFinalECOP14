#include "pic18f4520.h"
#include "teclado.h"
#include "delay.h"

// TC0 PORTDbits.RD3 BitTst(PORTD,3)
// TC1 PORTDbits.RD2 BitTst(PORTD,2)
// TC2 PORTDbits.RD1 BitTst(PORTD,1)
// TC3 PORTDbits.RD0 BitTst(PORTD,0)

const unsigned char colunaTeclado[3] = {0x1, 0x2, 0x4};
unsigned int atrasoMin = 5;
unsigned int atrasoMax = 15;


unsigned char tc_tecla() {
    unsigned char i;
    unsigned char ret = 0;
    unsigned char aux = PORTB;
    
    for (i = 0; i < 3; i++) {
        PORTB = ~colunaTeclado[i];
        atraso_ms(atrasoMin);
        if (!BitTst(PORTD, 3)) { //TC1
            atraso_ms(atrasoMax);
            if (!BitTst(PORTD, 3)) {
                while (!BitTst(PORTD, 3));
                ret = 1 + i;
                break;
            }
        };
        if (!BitTst(PORTD, 2)) {
            atraso_ms(atrasoMax);
            if (!BitTst(PORTD, 2)) {
                while (!BitTst(PORTD, 2));
                ret = 4 + i;
                break;
            }
        };
        if (!BitTst(PORTD, 1)) {
            atraso_ms(atrasoMax);
            if (!BitTst(PORTD, 1)) {
                while (!BitTst(PORTD, 1));
                ret = 7 + i;
                break;
            }
        };
        if (!BitTst(PORTD, 0)) {
            atraso_ms(atrasoMax);
            if (!BitTst(PORTD, 0)) {
                while (!BitTst(PORTD, 0));
                ret = 10 + i;
                break;
            }
        };
        PORTB = 0x00;
    };

    if (!ret)ret = 255;
    if (ret == 11)ret = 0;
    PORTB = aux;
    return ret;
}