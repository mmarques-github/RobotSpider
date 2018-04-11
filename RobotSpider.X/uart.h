/* 
 * File:   UARTconfig.h
 * Author: Marcelo
 *
 * Created on March 29, 2018, 11:54 PM
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>
#include "i2c.h"

void Initialize_UART(void);

char UART_get_char();
void UART_send_char(char);
void UART_send_string(char *);

#endif /*HC_HEADER_TEMPLATE_H*/