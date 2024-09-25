/**
  ******************************************************************************
  * @file    main.c
  * @author  Saurabh K
  * @brief   Description: main function source file
  *
  *          This file contains:
  *           - Data structures and functions for main
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Sanguine Auto Software.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/************************ Include Header Files **************************/
#include "main.h"

/************************ Start the Global Variables **************************/
#define APP_ADD 0x08006004
#define VectorAdd 0x08006000
#define NEW_MSP 0x20002800

typedef void (*voidFunc)(void);
volatile uint32_t BootAppFlag __attribute__ ((section (".BootAppFlags")));
volatile uint32_t dlyCnt;
volatile uint32_t counter;
uint32_t timeoutVar;
uint16_t count=0;
uint16_t pendingData;

bool validAppAvailble;
uint32_t i=0;
state_machin_t currstate;

/************************ End the Global Variables **************************/


void delay(uint32_t a) {
  while(a>0){
    a--;
    dlyCnt=a;
  }
}

void JumpToApp() {
  uint32_t* jumpAddress = (uint32_t*)(APP_ADD);
  uint32_t* jumpAdd = (uint32_t*)(*jumpAddress);
  voidFunc jmpFn = (voidFunc)jumpAdd;
  BootAppFlag = 0xA5A5A5A5;
  //SCB_VTOR = (uint32_t)(VectorAdd);
  __set_MSP(NEW_MSP);
  jmpFn();
}

// void canInit() {
//   rcc_periph_clock_enable(RCC_GPIOA);
//   rcc_periph_clock_enable(RCC_AFIO);
//   rcc_periph_clock_enable(RCC_CAN);
  
//   gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_CAN_TX);   /* Set the mode as output of above GPIO */
//   gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_CAN_RX);   /* Set the mode as output of above GPIO */
  
//   while(can_init(CAN1,false,false,false,false,false,false,1,CAN_BTR_TS1_7TQ,CAN_BTR_TS2_8TQ,1,false,false)==1);
//   GPIO_ODR(GPIOA) = GPIO_ODR(GPIOA)|GPIO_CAN_RX;

//   can_filter_init(0,true,false,0,0,0,1);
// }

// void uartSetup(){
//   rcc_periph_clock_enable(RCC_USART1);
//   gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO_USART1_TX);
//   gpio_set_mode(GPIOA, GPIO_MODE_INPUT,GPIO_CNF_INPUT_PULL_UPDOWN, GPIO_USART1_RX);
//   GPIO_ODR(GPIOA) = GPIO_ODR(GPIOA)|GPIO_USART1_RX;

//   usart_set_baudrate(USART1_BASE , 9600);
//   usart_set_databits(USART1_BASE , 8);
//   usart_set_mode(USART1_BASE , USART_MODE_TX_RX);
//   //usart_enable_rx_interrupt(USART1_BASE);
//   usart_enable(USART1_BASE);
//   //nvic_enable_irq(37);

// }

// void erase_application(uint32_t appAddress) {
//   for(uint32_t i=appAddress;i<0x8008000;i+=0x400){
//     flash_unlock();
//     flash_erase_page(i);
//     flash_lock();
//   }
// }

int main(void) {
  sas_canFrame* canRcvdFrame;
  // __asm__ volatile ("CPSIE I\n"); /* Enable the GLOBAL interrupts */
  // DwReqPkt_t DrequestPkt;
  // ReqRespPkt_t tempPkt;
  // DataPkt_t tempDataPkt;
  // //canTxStruct_t canTxPckt;
  // //canRxStruct_t canRxPckt;
  // currstate = init;
  // validAppAvailble = (*(uint32_t*)APP_ADD) != 0xFFFFFFFF;
  // //uint8_t data[8]={1,2,3,4,5,6,7,8};

  // // rcc_periph_clock_enable(RCC_GPIOC);                                       /* intialize the clock for the gpio PC13 */ 
	// // rcc_periph_clock_enable(RCC_GPIOA);
  // // uartSetup();
  // // gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);   /* Set the mode as output of above GPIO */

  // /* Erasing Application because expecting a application flashing */
  // /* Erase from 24 -> 08006000 sector to 31 */

  // if((BootAppFlag == 0xDEADDEAD) | ((*(uint32_t*)VectorAdd) != 0x20002800)) {
  //   erase_application(APP_ADD);
  //   BootAppFlag = 0xA5A5A5A5;
  // }
  sysinit();
  sas_peri_clock_enable(SAS_GPIOC_EN);
  config_gpio_pin(SAS_PORTC, SAS_PIN13, OUT_PUPL);

  while(1)
  {
    if(read_pin(SAS_PORTC, SAS_PIN13) == HIGH) {
      write_pin(SAS_PORTC, SAS_PIN13,LOW);
    } else {
      write_pin(SAS_PORTC, SAS_PIN13,HIGH);
    }
  
    canRcvdFrame = sas_canRead();
    sas_canWrite(canRcvdFrame);
    
    for(uint32_t i=0;i<30000;i++);
  }

    return 0;
}


//if((CAN_RF0R(CAN1)&CAN_RF0R_FMP0_MASK)||(CAN_RF1R(CAN1)&CAN_RF0R_FMP0_MASK)) 
//{        
//canReceive(&canRxPckt,1);        
//}
//initCanPck(&canTxPckt, 0x470, 0, &data, 8);
//canTransmit(&canTxPckt);
