#ifndef SAS_CLOCK_H
#define SAS_CLOCK_H

#include"sas_common.h"

typedef enum sas_clk_src {
    SAS_INT_OSC = 0,
    SAS_EXT_OSC,
    SAS_PLL
} sas_clk_src;

typedef enum sas_freq {
    SAS_FREQ_8MHZ = 0,
    SAS_FREQ_16MHZ,
    SAS_FREQ_32MHZ,
    SAS_FREQ_64MHZ,
    SAS_FREQ_72MHZ
}sas_freq;

typedef struct sas_clock {
    uint32_t sas_prediv1;
    uint32_t sas_prediv1scr;
    uint32_t sas_pllscr;
    uint32_t sas_pllmul;
    uint32_t sas_ahb_prescaler;
    uint32_t sas_apb1_prescaler;
    uint32_t sas_apb2_prescaler;
    uint32_t sas_adc_prescaler;
} sas_clock;

typedef enum {
    SAS_ADC_EN,
    SAS_CAN_EN,
    SAS_GPIOA_EN,
    SAS_GPIOB_EN,
    SAS_GPIOC_EN,
    SAS_GPIOD_EN,
    SAS_AFIO_EN,
} sas_periph_t;

sas_retype sas_clock_init();
sas_retype sas_clock_set(const sas_clock* );
sas_retype sas_peri_clock_enable(sas_periph_t );

#endif