/* ECOP14 - JOGO DO REFLEXO
 * 
 * André Casadei Marques 201901640
 * Gabriel Akio Vieira Onohara 2019009078
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "pic18f4520.h"
#include "teclado.h"
#include "rtc.h"


//ARRUMAR RAND

void cronometro5s(){
    int values7seg[5] = {0x06, 0x5B, 0x4F, 0x66, 0x6D};
    int indice;
    
    BitClr(INTCON2, 7); //liga pull up 
    ADCON1 = 0x0E; //config AD 
    TRISA = 0x00; //config a porta A como Saída
    TRISD = 0x00; //config a porta D como Saída
    PORTD = 0x00;
    for (indice = 4; indice >= 0; indice--) {
        PORTD = values7seg[indice];
        BitSet(PORTA, 2); //liga o 4o display 
        atraso_ms(1000);
    }
    lcd_cmd(L_CLR);
    BitClr(PORTA, 2); //desliga o 4o display
    atraso_ms(500);
}

void pisca3vezes(){
    TRISB = 0x00;   //config da porta B como Saída
    PORTB = 0b00000000;    //apaga os LEDs no PORTB
    atraso_ms(400);   
    PORTB = 0b11111111;    //acende os LEDs no PORTB
    atraso_ms(400);
    PORTB = 0b00000000;    //apaga os LEDs no PORTB
    atraso_ms(400);   
    PORTB = 0b11111111;    //acende os LEDs no PORTB
    atraso_ms(400);
    PORTB = 0b00000000;    //apaga os LEDs no PORTB
    atraso_ms(400);   
    PORTB = 0b11111111;    //acende os LEDs no PORTB
    atraso_ms(400);
}

void print1(){
    lcd_init(); //Config LCD
    lcd_cmd(L_CLR);
    lcd_cmd(L_L2);
    lcd_str("   Loading...");
    atraso_ms(1000);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("   Bem vindo!");
    lcd_cmd(L_L2);
    lcd_str("vc esta jogando:");
    lcd_cmd(L_L3);
    lcd_str("JOGO DO REFLEXO");
    atraso_ms(2200);
   
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("   Pressione");
    lcd_cmd(L_L2);
    lcd_str("    a tecla");
    lcd_cmd(L_L3);
    lcd_str(" correspondente");
    lcd_cmd(L_L4);
    lcd_str("  ao LED aceso");
    atraso_ms(2200);
    
    lcd_cmd(L_CLR);
    lcd_cmd(L_L1);
    lcd_str("    ATENCAO!");
    lcd_cmd(L_L2);
    lcd_str("     o jogo");
    lcd_cmd(L_L3);
    lcd_str("  Comecara em:");
    lcd_cmd(L_L4);
    lcd_str("      ****");
    atraso_ms(2000);
    
    
}

unsigned char leTeclado(){
    int  aux4;
    unsigned char aux3, valorT = 255;
    for (aux4 = 0; aux4 < 80; aux4++){
        aux3 = tc_tecla(); //lê o teclado
        if(aux3!=255){
            valorT = aux3;
        }
    }
    return valorT;
}

void print2(unsigned char pontuacaoUn, unsigned char pontuacaoDz){
    ADCON1 = 0x06;
    TRISB = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;
    TRISB = 0x00;
    
    
    if(pontuacaoUn == '0' && pontuacaoDz == '0'){
        lcd_cmd(L_CLR);
        lcd_cmd(L_L2);
        lcd_str("      GAME");
        lcd_cmd(L_L3);
        lcd_str("      OVER");
        atraso_ms(1500);
    }
    else{
        lcd_cmd(L_CLR);
        lcd_cmd(L_L2);
        lcd_str("    Parabens!");
        lcd_cmd(L_L3);
        lcd_str("Fez um bom jogo!");
        atraso_ms(1500);
    }
        lcd_cmd(L_CLR);
        lcd_cmd(L_L2);
        lcd_str(" Sua pontuacao");
        lcd_cmd(L_L3);
        lcd_str(" e de ");
        lcd_dat(pontuacaoDz);
        lcd_dat(pontuacaoUn);
        lcd_str(" pontos");

}

void main(void) {
    ADCON1 = 0x06; //config AD            
    TRISB = 0x01; //config a porta B
    TRISD = 0x00; //config a porta D como Saída
    TRISE = 0x00; //config a porta E como Saída
    
    
    print1();
    cronometro5s();
    pisca3vezes();
    
    
    int cont1, cont2;
    unsigned char valorLed, segundosRtc = 0;
    unsigned char valorTeclado = 255;
    unsigned char pontuacaoUn = '0', pontuacaoDz = '0';
    int values7seg2[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
    int aux, aux2;
    
    //rtc_r()
    //srand((const char *)tempo);
    srand(time(NULL));
    
    int valuesLED[8] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};
    
    for (cont1 = 5; cont1 >= 0; cont1--) {     //conta dezenas de segundos 
        for (cont2 = 9; cont2 >= 0; cont2--) { //conta segundos 

            for (aux = 0; aux < 5; aux++) { //exibe os segundos no display de 7 segmentos
                PORTD = values7seg2[cont2];
                BitSet(PORTA, 5);
                atraso_ms(10);
                BitClr(PORTA, 5);

                PORTD = values7seg2[cont1];
                BitSet(PORTA, 4);
                atraso_ms(10);
                BitClr(PORTA, 4);
            }

            valorLed = rand() % 7 + 1;
            TRISB = 0x00;   //config da porta B como Saída
            PORTB = 0b00000000;    //apaga os LEDs no PORTB
            atraso_ms(100);    //tempo que os LEDs ficam apagados
            PORTB = valuesLED[valorLed]; //porta B recebe valor do LED aleatório
            atraso_ms(300);    //tempo que o LED fica aceso
            PORTB = 0b00000000;    //apaga os LEDs no PORTB
            TRISB = 0xF8;   //config a porta B como entrada
            TRISD = 0x0F;   //config a porta D como entrada
            
            valorTeclado = leTeclado(); //Lê o teclado
            
            if (7 - valorTeclado == valorLed) { //compara o valor recebido do teclado com o valor do LED que acendeu
                if (pontuacaoUn < '9'){
                    pontuacaoUn++;   //incrementa o contador de pontos da unidade
                }
                else{
                    pontuacaoUn = '0';
                    pontuacaoDz++;
                }
            }
            TRISD = 0x00; //config porta D como Saída
        }
    }
    
    print2(pontuacaoUn, pontuacaoDz); //imprime a pontuação

    while (1); //loop infinito
    return;
}