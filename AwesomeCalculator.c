/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Advanced
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 1/9/2021
Author  : www.Eca.ir *** www.Webkade.ir
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 40.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/
#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

//Variables
int keys[] = {0x28, 0x14, 0x24, 0x44, 0x12, 0x22, 0x42, 0x11, 0x21, 0x41, 0x81,  0x82, 0x84, 0x18, 0x48, 0x88};;
 
char decoded_keys[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '/', '*', '-', 'c', '=', '+'};
   
unsigned char currenct_selected_button = '';

unsigned char currenct_operator = 'c';

int index = 0, row, col, colRow;

int number = 0;

int oprand = 0;

char printable_number[16];

int is_selecting = 0;

void read_key(void){

    DDRD=0x0F;
    PORTD=0x0F;
    row=PIND;
    
    delay_ms(1);
    
    DDRD=0xF0;
    PORTD=0xF0;
    col=PIND;
    
    colRow=row&col;
    
    if (colRow==0x00){
        is_selecting = 0;
    }
}

int sum(int first, int second){
    return first + second;
}

int div(int first, int second){
    return first / second;
}

int min(int first, int second){
    return first - second;
}

int mul(int first, int second){
    return first * second;
}


void update(void){
    index = 0;
    
    while(index < 16){ 

        if (colRow==keys[index]){
            if (is_selecting == 1){
                break; //means user has not pulled up his filgers from the key.
            }
            
            is_selecting = 1; 
            currenct_selected_button = decoded_keys[index];
            
            if (number > 10000){
                break;
            }
            
            if (currenct_selected_button == 'c'){
                currenct_operator = 'c';
                oprand = 0;
                number = 0;
                lcd_clear();
                break;
            }
    
            if (currenct_selected_button == '/' || currenct_selected_button == '*' || currenct_selected_button == '+' || currenct_selected_button == '-'){
    
                currenct_operator = currenct_selected_button;
                oprand = number;
                number = 0;
                lcd_clear();
                break;
            }
            
            if (currenct_selected_button == '='){
                if (currenct_operator == '/'){
                   number = div(oprand, number);
                   break;
                }
                if (currenct_operator == '*'){
                   number = mul(oprand, number);
                   break;
                }
                if (currenct_operator == '-'){
                   number = min(oprand, number);
                   break;
                }
                if (currenct_operator == '+'){
                   number = sum(oprand, number);
                   break;
                } 
                 
            }
            if (index < 10){
                number = (number * 10) + index; //as we sorted the keys 0-9, now if the index is below 10 its the number actually.
            }
        }
        index++;
    }
}

void update_lcd(void){   
    sprintf(printable_number, "%d", number);

}

void main(void)
{

PORTA=0x00;
DDRA=0x00;

PORTB=0x00;
DDRB=0x00;
 
PORTC=0x00;
DDRC=0xFF;

PORTD=0x00;
DDRD=0x00;


TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

MCUCR=0x00;
MCUCSR=0x00;

TIMSK=0x00;

UCSRB=0x00;

ACSR=0x80;
SFIOR=0x00;
ADCSRA=0x00;

SPCR=0x00;

TWCR=0x00;

lcd_init(16);


while (1)
      {

        read_key();
        update();
        
        update_lcd();
                
        lcd_gotoxy(0,0);
        
        lcd_puts(printable_number);
      }
}

