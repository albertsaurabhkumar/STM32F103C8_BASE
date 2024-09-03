#include "sas_clock.h"

const sas_clock sas_clock_config[2] = {
    /* Internal osc to 72MHz */
    {
    .sas_prediv1 = 1,
    .sas_prediv1scr = 1,
    .sas_pllscr = 1,
    .sas_pllmul = 1,
    .sas_ahb_prescaler = 1,
    .sas_apb1_prescaler = 1,
    .sas_apb2_prescaler = 1,
    .sas_adc_prescaler = 1
    },

    /* External osc to 72MHz */
    {
    .sas_prediv1 = 0,                                       /* No Div */
    .sas_prediv1scr =0,                                     /* 0 - Direct HSE else Divided HSE */
    .sas_pllscr = RCC_CFGR_PLLSRC,                          /* 0 - HSI and 1 - HSE */
    .sas_pllmul = RCC_CFGR_PLLMULL9,                        /* Multiply by 9 */
    .sas_ahb_prescaler =RCC_CFGR_HPRE_DIV1,                 /* No Div */
    .sas_apb1_prescaler =RCC_CFGR_PPRE1_DIV2,               /* Div by 2 Max Freq 36MHz*/
    .sas_apb2_prescaler =RCC_CFGR_PPRE2_DIV1,               /* No Div Max Freq 72MHz*/
    .sas_adc_prescaler =RCC_CFGR_ADCPRE_DIV8,               /* Div by 6 Max Freq 14MHz */
    }
};

sas_retype sas_clock_init() {

    /* Check for HSE and ON if it not on */
    if(!(RCC->CR & RCC_CR_HSEON)) {
        RCC->CR = RCC->CR | RCC_CR_HSEON;
    }
    /* Check HSE is ready or not */
    while(!(RCC->CR & RCC_CR_HSERDY));
    sas_clock_set(&sas_clock_config[SAS_EXT_OSC]);

    return SAS_OK;
}

sas_retype sas_clock_set(const sas_clock* clock) {
    uint32_t Temp_Reg = 0;

    /* Filling and setting the configuration register for RCC */
    
    Temp_Reg = (clock->sas_ahb_prescaler)|(~clock->sas_ahb_prescaler & Temp_Reg);

    Temp_Reg = (clock->sas_apb1_prescaler)|(~clock->sas_apb1_prescaler & Temp_Reg);

    Temp_Reg = (clock->sas_apb2_prescaler)|(~clock->sas_apb2_prescaler & Temp_Reg);
    
    Temp_Reg = (clock->sas_adc_prescaler)|(~clock->sas_adc_prescaler & Temp_Reg);

    Temp_Reg = (clock->sas_pllmul)|(~clock->sas_pllmul & Temp_Reg);

    Temp_Reg = (clock->sas_pllscr)|(~clock->sas_pllscr & Temp_Reg);

    RCC->CFGR = (Temp_Reg)|(~Temp_Reg & RCC->CFGR);

    if(!(RCC->CR & RCC_CR_PLLON)) {
        RCC->CR = RCC->CR | RCC_CR_PLLON;
    }

    /* Check PLL is ready or not */
    while(!(RCC->CR & RCC_CR_PLLRDY));

    // /* Filling and setting the configuration register 2 for RCC */

    // Temp_Reg = (clock->sas_prediv1)|(~clock->sas_pllscr & Temp_Reg);

    // Temp_Reg = (clock->sas_prediv1scr)|(~clock->sas_pllscr & Temp_Reg);

    // RCC->CFGR = (Temp_Reg)|(~Temp_Reg & RCC->CFGR);
    
    // RCC->CFGR = (RCC_CFGR_SW_PLL)|(~RCC_CFGR_SW_PLL & RCC->CFGR);
    
    return SAS_OK;
}


sas_retype sas_peri_clock_enable(sas_periph_t peri) {
    /* Get the peripheral to enable PPRE1 or PPRE2 */
    if(peri == SAS_CAN_EN){
        RCC->APB1ENR =  (RCC_APB1ENR_CAN1EN) |(~ RCC_APB1ENR_CAN1EN & RCC->APB1ENR);
    } else if(peri == SAS_AFIO_EN){
        RCC->APB2ENR =  (RCC_APB2ENR_AFIOEN) |(~ RCC_APB2ENR_AFIOEN & RCC->APB2ENR);
    } else if(peri == SAS_GPIOA_EN){
        RCC->APB2ENR =  (RCC_APB2ENR_IOPAEN) |(~ RCC_APB2ENR_IOPAEN & RCC->APB2ENR);
    } else if(peri == SAS_GPIOC_EN){
        RCC->APB2ENR =  (RCC_APB2ENR_IOPCEN) |(~ RCC_APB2ENR_IOPCEN & RCC->APB2ENR);
    } else {
        /* TODO: Implement the other Peripherals */
    }
    return SAS_OK;
}
