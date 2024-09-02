#include "startup.h"
/**************************************************/
/*             System Interrupt Handling          */
/**************************************************/
void DefaultHandler(void) {
    while(1); /* Never returns from here */
}
void NMI_Handler(void) {
    while(1); /* Never returns from here */
}

void HardFault_Handler(void) {
    while(1); /* Never returns from here */
}
void MemManage_Handler(void) {
    while(1); /* Never returns from here */
}
void BusFault_Handler(void) {
    while(1); /* Never returns from here */
}
void UsageFault_Handler(void) {
    while(1); /* Never returns from here */
}
void SVC_Handler(void) {
    while(1); /* Never returns from here */
}  

void DebugMon_Handler(void) {
    while(1); /* Never returns from here */
}  
void PendSV_Handler(void) {
    while(1); /* Never returns from here */
}
void SysTick_Handler(void) {
    while(1); /* Never returns from here */
}

void  WWDG_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  PVD_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TAMPER_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  RTC_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  FLASH_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  RCC_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI0_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI1_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI2_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI3_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI4_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel1_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel2_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel3_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel4_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel5_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel6_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  DMA1_Channel7_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  ADC1_2_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  USB_HP_CAN1_TX_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  USB_LP_CAN1_RX0_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  CAN1_RX1_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  CAN1_SCE_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI9_5_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TIM1_BRK_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TIM1_UP_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TIM1_TRG_COM_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TIM1_CC_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TIM2_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  TIM3_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  I2C1_EV_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  I2C1_ER_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  SPI1_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  USART1_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  USART2_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  EXTI15_10_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  RTC_Alarm_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
void  USBWakeUp_IRQHandler(void) __attribute__ ((weak, alias("DefaultHandler")));   
   
             

uint32_t vectorTable[] __attribute__ ((section (".intvec"))) = {
     (uint32_t) 0x20002800,                                           /* Top of Stack */
     (uint32_t) Reset_Handler,                                        /* Reset Handler */
     (uint32_t) NMI_Handler,                                          /* NMI Handler*/
     (uint32_t) HardFault_Handler,                                    /* Hard Fault Handler*/
     (uint32_t) MemManage_Handler,                                    /* MPU Fault Handler*/
     (uint32_t) BusFault_Handler,                                     /* Bus Fault Handler*/
     (uint32_t) UsageFault_Handler,                                   /* Usage Fault Handler*/
     (uint32_t) 0 ,                                                                 /* Reserved*/
     (uint32_t) 0 ,                                                                 /* Reserved*/
     (uint32_t) 0 ,                                                                 /* Reserved*/
     (uint32_t) 0 ,                                                                 /* Reserved*/
     (uint32_t) SVC_Handler,                                          /* SVCall Handler*/
     (uint32_t) DebugMon_Handler,                                     /* Debug Monitor Handler*/
     (uint32_t) 0 ,                                                       /* Reserved*/
     (uint32_t) PendSV_Handler,                                       /* PendSV Handler*/
     (uint32_t) SysTick_Handler,                                      /* SysTick Handler*/
                                          /* External Interrupts*/

     (uint32_t) WWDG_IRQHandler,
     (uint32_t) PVD_IRQHandler,
     (uint32_t) TAMPER_IRQHandler,
     (uint32_t) RTC_IRQHandler,
     (uint32_t) FLASH_IRQHandler,
     (uint32_t) RCC_IRQHandler,
     (uint32_t) EXTI0_IRQHandler,
     (uint32_t) EXTI1_IRQHandler,
     (uint32_t) EXTI2_IRQHandler,
     (uint32_t) EXTI3_IRQHandler,
     (uint32_t) EXTI4_IRQHandler,
     (uint32_t) DMA1_Channel1_IRQHandler,
     (uint32_t) DMA1_Channel2_IRQHandler,
     (uint32_t) DMA1_Channel3_IRQHandler,
     (uint32_t) DMA1_Channel4_IRQHandler,
     (uint32_t) DMA1_Channel5_IRQHandler,
     (uint32_t) DMA1_Channel6_IRQHandler,
     (uint32_t) DMA1_Channel7_IRQHandler,
     (uint32_t) ADC1_2_IRQHandler,
     (uint32_t) USB_HP_CAN1_TX_IRQHandler,
     (uint32_t) USB_LP_CAN1_RX0_IRQHandler,
     (uint32_t) CAN1_RX1_IRQHandler,
     (uint32_t) CAN1_SCE_IRQHandler,
     (uint32_t) EXTI9_5_IRQHandler,
     (uint32_t) TIM1_BRK_IRQHandler,
     (uint32_t) TIM1_UP_IRQHandler,
     (uint32_t) TIM1_TRG_COM_IRQHandler,
     (uint32_t) TIM1_CC_IRQHandler,
     (uint32_t) TIM2_IRQHandler,
     (uint32_t) TIM3_IRQHandler,
     (uint32_t) 0,
     (uint32_t) I2C1_EV_IRQHandler,
     (uint32_t) I2C1_ER_IRQHandler,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) SPI1_IRQHandler,
     (uint32_t) 0,
     (uint32_t) USART1_IRQHandler,
     (uint32_t) USART2_IRQHandler,
     (uint32_t) 0,
     (uint32_t) EXTI15_10_IRQHandler,
     (uint32_t) RTC_Alarm_IRQHandler,
     (uint32_t) USBWakeUp_IRQHandler,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) 0,
     (uint32_t) 0xF108F85F,                                       /* SCG bus interrupt request*/
};