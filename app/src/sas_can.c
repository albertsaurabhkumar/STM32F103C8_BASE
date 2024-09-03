/**
  ******************************************************************************
  * @file    sas_can.c
  * @author  Saurabh K
  * @brief   Description: CAN peripheral abstraction layer source file
  *
  *          This file contains:
  *           - Data structures and functions for CAN peripherals
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

#include "sas_can.h"

sas_retype sas_can_init(void) {
    sas_retype status;
    GPIO_t gpio;
    /* clock enable for can */
    status = sas_peri_clock_enable(SAS_GPIOA_EN);  /* Enable the clock for GPIOA */
    status = sas_peri_clock_enable(SAS_AFIO_EN);   /* Enable the clock for the Alternate functions */
    status = sas_peri_clock_enable(SAS_CAN_EN);    /* Enabel the clock for the CAN peripheral */

    gpio.port = SAS_PORTA;

    gpio.config = IN_FLT;
    gpio.pin = SAS_PIN11;
    status = sas_configure_pin(&gpio);                  /* Set the CAN RX gpio pin */

    gpio.config = AF_OD;
    gpio.pin = SAS_PIN12;
    status = sas_configure_pin(&gpio);                  /* Set the CAN TX gpio pin  */

    status = sas_can_config();                      /* Configure the CAN BaudRate: Now fixed to 500kbps */
    status = sas_can_fiter_conf();                  /* 7 filters to FIFO0 and 7 to FIFO1 Configure the filters  */
    status = sas_can_startStop(1);                  /* Enable the can peripheral to normal mode */

    return status;
}

sas_retype sas_can_startStop(){
  if(1) {
    /* start the can communication */
  }else {
    /* Stop the can communication */
  }
  return SAS_OK;
}

sas_retype sas_set_can_mode(sas_can_mode mode) {
  switch (mode) 
  {
    case SAS_CAN_SILENT:
    {
      break;
    }
    case SAS_CAN_LBK:
    {
      break;
    }
    case SAS_CAN_NORMAL:
    {
      break;
    }
  /* Set the mode of the can */
  return SAS_OK;
  }
return SAS_OK;
}

sas_retype sas_can_config() {
  uint32_t temp = 0;
  temp|= CAN_BTR_SJW;
  temp|= CAN_BTR_BRP;
  temp|= CAN_BTR_TS1;
  temp|= CAN_BTR_TS2;
  
  CAN1->BTR = temp;
  return SAS_OK;
}  

sas_retype sas_get_can_status(sas_can_status* status) {
  /* TODO: Copy the can_IER register to this variable and return it back */
  return SAS_OK;
}

sas_retype sas_can_fiter_conf() {
  /* Mask and filter to select the can id to recieive and reject */
  /* Without this can does not work */
    return SAS_OK;
}

sas_retype sas_canWrite(sas_canFrame* canFrame ){
  /* Write the message to the can bus */
  /* Will keep it in pooling mode for now */
  /* TODO: Make a FIFO buffer so that tx msg can be stored */
  return SAS_OK;
}

sas_retype sas_canRead(sas_canFrame* canFrame ){
  /* Read the message to the can bus */
  /* Will keep it in interrupt mode for now */
  /* TODO: Make a FIFO buffer so that rx msg can be stored */
return SAS_OK;
}
