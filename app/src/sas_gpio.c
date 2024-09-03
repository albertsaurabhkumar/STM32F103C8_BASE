/**
  ******************************************************************************
  * @file    sas_gpio.c
  * @author  Saurabh K
  * @brief   Description: GPIO driver file with read and write functions
  *
  *          This file contains:
  *           - Data structures for all sas library peripherals
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

#include "sas_gpio.h"

GPIO_t gpio;

void config_gpio_pin(sas_port port,sas_pin pin, sas_config config) {
    
    gpio.port = port;
    gpio.pin = pin;
    gpio.config = config;
    gpio.level = LOW;
    sas_configure_pin(&gpio);
}

sas_level read_pin(sas_port port,sas_pin pin) {
    
    gpio.port = port;
    gpio.pin = pin;
    if(SAS_OK == sas_read_pin(&gpio)) {
        return gpio.level;
    } else {
        return UNKNOWN;
    }
}

void write_pin(sas_port port, sas_pin pin,sas_level level) {
    gpio.port = port;
    gpio.pin = pin;
    gpio.level = level;
    sas_write_pin(&gpio);
}

/// @brief Read the level of input/output pin
/// @return sas_retype

sas_retype sas_read_pin(GPIO_t * gpioPtr) {
    sas_retype ret = SAS_OK;
    if (gpioPtr->port == SAS_PORTC) {
    uint32_t temp = GPIOC->IDR;
    gpioPtr->level = (temp & (1 << gpioPtr->pin))>>gpioPtr->pin;
    } else {

    }

    return ret;
}

/// @brief Write the level of input/output pin
/// @return sas_retype

sas_retype sas_write_pin(GPIO_t * gpioPtr) {
    sas_retype ret = SAS_ERR;
    switch (gpioPtr->port)
    {
    case SAS_PORTC:
        GPIOC->BSRR = 1 << (gpioPtr->pin + (16 * (~gpioPtr->level & 0x1)));
        break;
    default:
        break;
    }

    return ret; 
}

/// @brief Read the level of input/output port
/// @return sas_retype

sas_retype sas_read_port(GPIO_t * gpioPtr ) {
    sas_retype ret = SAS_ERR;
    return ret;
}

/// @brief Write the level of input/output port
/// @return sas_retype

sas_retype sas_write_port(GPIO_t * gpioPtr) {
    sas_retype ret = SAS_ERR;
    return ret;
}

/// @brief Configure the GPIO port pin as input or output
/// @return sas_retype

sas_retype sas_configure_pin(GPIO_t * gpioPtr) {
    sas_retype ret = SAS_ERR;
    uint8_t shift = 0;
    bool crh=0;
    if(gpioPtr->pin > 7) {
        crh = 1;
        shift = (gpioPtr->pin - 8) * 4;
    } else {
        shift = (gpioPtr->pin) * 4;
    }

    switch (gpioPtr->port)
    {
    case SAS_PORTA: /* For PORT A */
        if (crh) {
            GPIOA->CRH = (gpioPtr->config << shift) | ( (~(0xF << shift)) & GPIOA->CRH);
        } else {
            GPIOA->CRL = (gpioPtr->config << shift) | ( (~(0xF << shift)) & GPIOA->CRL);
        }
        break;
    case SAS_PORTB: /* For PORT B */
        if (crh) {
            GPIOB->CRH = (gpioPtr->config << shift) | ( (~(0xF << shift)) & GPIOB->CRH);
        } else {
            GPIOB->CRL = (gpioPtr->config << shift) | ( (~(0xF << shift)) & GPIOB->CRL);
        }
        break;
    case SAS_PORTC: /* For PORT C */
        if (crh) {
            GPIOC->CRH = (gpioPtr->config << shift) | ( (~(0xF << shift)) & GPIOC->CRH);
        } else {
            GPIOC->CRL = (gpioPtr->config << shift) | ( (~(0xF << shift)) & GPIOC->CRL);
        }
        break;
    
    default:
        break;
    }   
    return ret;
}

/// @brief Configure the GPIO port as input or output
/// @return sas_retype

sas_retype sas_configure_port(GPIO_t * gpioPtr) {
    sas_retype ret = SAS_ERR;
    return ret;
}

