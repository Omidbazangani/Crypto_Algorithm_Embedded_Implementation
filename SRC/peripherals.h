/**
 * Peripherals manage triggers and text input/output with outside world.
 * When compiling with ELMO flag, we use ELMO library to trigger and and send and receive text.
 * When compiling for a board, we use GPIO and UART.
 */

#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include "includes.h"
#include <stdint.h>

//#define USART_BAUDRATE 115200
//#define USART_DATABITS 8
#define Trigger_Pin GPIO_Pin_0
#define Trigger_GPIO_Port GPIOA
   
void init_peripherals(void);
void program_end(void);
void receive_cleartext(unsigned char *cleartext, unsigned int n);
void send_ciphertext(unsigned char *ciphertext, unsigned int n);
void set_trigger(void);
void clear_trigger(void);
uint8_t receive_registers_value(void);
void uart_receive(unsigned char *iv, unsigned int n);
#endif
