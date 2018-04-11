#include "adc.h"

#define _XTAL_FREQ 16000000 

void ADC_Init()
{
  TRISA1 = 1;
  ANSELAbits.ANSA1 = 0;         //Set RA1 as Analog Input
  ADCON0 = 0x5;                 //Turn ON ADC and Clock Selection
  
  ADCON1 = 0x00;                //All pins as Analog Input and setting Reference Voltages
}

int ADC_Read()
{
  ADCON0 |= 0x4;               //Setting channel selection bits
  __delay_ms(2);               //Acquisition time to charge hold capacitor
  GO_nDONE = 1;                //Initializes A/D conversion
  while(GO_nDONE);             //Waiting for conversion to complete
  return ((ADRESH<<8)+ADRESL); //Return result
}
