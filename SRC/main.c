#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg.h"
#include "includes.h"
#include "lpc17xx.h"
#include "ecrypt-sync.h"
//#include "Xoodoo.h"
//extern volatile uint8_t XoodooState[48] __attribute__((aligned(4)));
#define IV_LENGTH   48 
#define TEXT_LENGTH 16
#define KEY_LENGTH 16
uint8_t cleartext[TEXT_LENGTH]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
uint8_t ciphertext[TEXT_LENGTH] = {0}; 
uint8_t key[KEY_LENGTH] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c} ;  // key:0123456789abcdef123456789abcdef0
uint8_t IV[IV_LENGTH] = {0}; // 1017e5241d0f02f5c6e5   //In Abby it was like 0xAE + Key + IV + Plaintext  
uint8_t plain_text[16] ={0};
/*********
 plain-text:
    6bc1bee22e409f96e93d7e117393172a
    ae2d8a571e03ac9c9eb76fac45af8e51
    30c81c46a35ce411e5fbc1191a0a52ef
    f69f2445df4f9b17ad2b417be66c3710

  key:
    2b7e151628aed2a6abf7158809cf4f3c

  resulting cipher
    3ad77bb40d7a3660a89ecaf32466ef97 
    f5d3d58503b9699de785895a96fdbaaf 
    43b1cd7f598ece23881b00e3ed030688 
    7b0c785e27e8ad3f8223207104725dd4 
****/////////////
void ActiveTracePins(void)
{
  
  LPC_PINCON->PINSEL10 = 0x08;
}


void ExternalClock_Configuration(void)
{
 LPC_SC-> SCS = 0x00000020; //External Clock source
 LPC_SC->PCLKSEL0 |= 0x40; //pclk = cclk
 while ((LPC_SC-> SCS & (1 << 6)) == 0);//The main oscillator is stable
 LPC_SC->CLKSRCSEL = 0x1;
 /* clkout of 10mhz on 1.27 */
LPC_PINCON->PINSEL3 |= (1<<22);
LPC_SC->CLKOUTCFG = 0x100; //enable and divide by 1
CLKPWR_SetPCLKDiv(CLKPWR_PCLKSEL_UART0,CLKPWR_PCLKSEL_CCLK_DIV_1);
LPC_SC->FLASHCFG  = 0x03A;  // one cpu clock for Flash access 
}


void main(void)
{

ExternalClock_Configuration();
init_peripherals();
//ActiveTracePins();
 uint8_t iv[48]={0};
 
 ECRYPT_keysetup(0,0,0,0);
  while(1)
  {
 
  receive_cleartext(cleartext, TEXT_LENGTH);
  ECRYPT_keysetup(0,0,0,0);
  uart_receive(IV, IV_LENGTH);
  ECRYPT_ivsetup(0,iv);
  
  set_trigger();
  asm (nop100);
  
  
  ECRYPT_encrypt_bytes(0,cleartext,ciphertext,16);
  
  asm (nop100);
  clear_trigger();
  send_ciphertext(ciphertext,TEXT_LENGTH);   
           
    }
  }

