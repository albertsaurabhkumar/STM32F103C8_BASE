/*
**  Processor: S32K144
**  Author: Saurabh Kumar
**  GCC Version: 12.3
**  
**  Main program file for the GCC Compiler
*/

#include "main.h"
volatile uint32_t dlyCnt;
volatile uint32_t counter;

void delay(uint32_t a) {
  while(a>0){
    a--;
    dlyCnt=a;
  }
}

int main(void) {
  while(1)
  {
    gpio_toggle(GPIOC, GPIO13);    /* Toggle the gpio */
    delay(100000);
  }
  return 0;
}
