#include "peripherals.h"

/**
 * Init board peripherals
 */
void init_peripherals(void)
{
   

  CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO,ENABLE);
  GPIO_SetDir(2, 0x00000002, 1);
  GPIO_ClearValue(2, 0x00000002);
  
  PINSEL_CFG_Type PinCfg;

  /*
	 * Initialize UART0 pin connect
	 */
PinCfg.Funcnum = 1;
PinCfg.OpenDrain = 0;
PinCfg.Pinmode = 0;
PinCfg.Pinnum = 2;   //TXD
PinCfg.Portnum = 0;
PINSEL_ConfigPin(&PinCfg);
PinCfg.Pinnum = 3; //RXD
PINSEL_ConfigPin(&PinCfg);

// LPC_PINCON->PINSEL0 &= ~0x000000F0;
// LPC_PINCON->PINSEL0 |= 0x00000050;            // Enable TxD0 P0.2 and p0.3 
//  
  // UART Configuration structure variable
UART_CFG_Type UARTConfigStruct;
UARTConfigStruct.Baud_rate = 9600;
UARTConfigStruct.Databits = UART_DATABIT_8;
UARTConfigStruct.Parity = UART_PARITY_NONE;
UARTConfigStruct.Stopbits = UART_STOPBIT_1;

UART_Init(LPC_UART0,&UARTConfigStruct);


UART_FIFO_CFG_Type UARTCfgFIFO;
UARTCfgFIFO.FIFO_Level = UART_FIFO_TRGLEV0;
UARTCfgFIFO.FIFO_ResetRxBuf = ENABLE;
UARTCfgFIFO.FIFO_ResetTxBuf = ENABLE;
UARTCfgFIFO.FIFO_DMAMode = DISABLE;

UART_FIFOConfig(LPC_UART0, &UARTCfgFIFO);
//LPC_PINCON->PINSEL0 |= (1<<4) | (1<<6);
//LPC_UART0->FCR =0x7; 
}
void receive_cleartext(unsigned char *cleartext, unsigned int n)
{
 
   while (!(LPC_UART0->LSR & UART_LSR_RDR));
   UART_ReceiveByte(LPC_UART0);
    for (uint8_t i = 0; i < n; i++)
    {
        while (!(LPC_UART0->LSR & UART_LSR_RDR));
        cleartext[i] = UART_ReceiveByte(LPC_UART0);
    }
}
//
//
//
///**
// * Receive Registers value
// */
uint8_t receive_registers_value(void)
{
 
  while (!(LPC_UART0->LSR & UART_LSR_RDR));
  return UART_ReceiveByte(LPC_UART0);
  
}


void uart_receive(unsigned char *iv, unsigned int n)
{
  
    for (uint8_t i = 0; i < n; i++)
    {
        while (!(LPC_UART0->LSR & UART_LSR_RDR));
        iv[i] = UART_ReceiveByte(LPC_UART0);
    }
}



//
//
///**
// * Send ciphertext
 //*/
void send_ciphertext(unsigned char *ciphertext, unsigned int n)
{
  
   for (uint8_t i = 0; i < n; i++)
   {
       while(!(LPC_UART0->LSR & 0x20));
//       
     LPC_UART0->THR = ciphertext[i];
        //usart_send_blocking(USART1, ciphertext[i]);
       
      //while (!(LPC_UART0->LSR & UART_LSR_THRE));
       
            
    }
}

/**
 * Set trigger
 */
void set_trigger(void)
{
   
   GPIO_SetValue(2, 0x00000002);
}

/**
 * Clear trigger
 */
void clear_trigger(void)
{
   GPIO_ClearValue(2, 0x00000002);
}
