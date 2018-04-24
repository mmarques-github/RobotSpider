#include "uart.h"
#define Baud_rate 9600

//***Initializing UART module for PIC16F877A***//
void Initialize_UART(void)
{
    //****Setting I/O pins for UART****//
    TRISC &= 0xDFFF; // TX Pin set as output
    TRISC |= 0x4000; ; // RX Pin set as input
    //________I/O pins set __________//
    
    /**Initialize SPBRG register for required 
    baud rate and set BRGH for fast baud_rate**/
    U1BRG = ((SYSCLK/16)/Baud_rate) - 1;
    //_________End of baud_rate setting_________//
    
    /*Enable Alternative I/O Ports*/
    U1MODEbits.ALTIO = 1; 
    
    /*Setting up the number of Data and Stop Bits*/
    U1MODEbits.PDSEL = 0x0;
    U1MODEbits.STSEL = 0x0;
    
    
    /*Enable UART*/
    U1MODEbits.UARTEN = 1;
    U1STAbits.UTXEN = 1;  
}
//________UART module Initialized__________//

 

//**Function to send one byte of date to UART**//
void UART_send_char(char bt)  
{
    while(!IFS0bits.U1TXIF);  // hold the program till TX buffer is free
    U1TXREG = bt; //Load the transmitter buffer with the received value
}
//_____________End of function________________//

 

//**Function to get one byte of date from UART**//
char UART_get_char()   
{
    if(U1STAbits.OERR) // check for Error 
    {
        U1STAbits.OERR = 0; //If error -> Reset 
    }
    
    while(!IFS0bits.U1RXIF);  // hold the program till RX buffer is free
    
    return U1RXREG; //receive the value and send it to main function
}
//_____________End of function________________//

 

//**Function to convert string to byte**//
void UART_send_string(char* st_pt)
{
    while(*st_pt) //if there is a char
        UART_send_char(*st_pt++); //process it as a byte data
}
//___________End of function______________//

void int2str(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}