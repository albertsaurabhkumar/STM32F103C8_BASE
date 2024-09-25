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


sas_retype sas_setCANBaud(CAN_Baud_t baudrate) {
  sas_retype ret = SAS_OK;
  /* Verify the CAN initialization Mode */
  if(!(CAN_MSR_INAK & CAN1->MSR)) {
    return SAS_ERR;
  }
  /* Set the BTR Register */

  CAN1->BTR &= ~(0x37F03FF);

  CAN1->BTR |=  ((CAN_BTR_BRP_Msk & (baudrate==BAUD_250Kbps? TQ_7:TQ_3) )|(CAN_BTR_TS1 & (TQ_8 << CAN_BTR_TS1_Pos))
  |(CAN_BTR_TS2 & (TQ_7 << CAN_BTR_TS2_Pos))|(CAN_BTR_SJW & (TQ_1 << CAN_BTR_SJW_Pos)));  /* Setting Baud Rete to 500Kbps and 0x37F03FF masking for BTR bits */
 
 return ret;
}

sas_retype sas_can_initMode() {
  /* Set the INRQ Bit in CAN_MCR register */
  sas_retype ret = SAS_ERR;
  /* Exit from Sleep */
  CAN1->MCR &= ~CAN_MCR_SLEEP;

  /* Enter to Initialization Mode */
  CAN1->MCR |= CAN_MCR_INRQ;

  if(CAN_MSR_INAK & CAN1->MSR) {
    ret = SAS_OK;
  }

  return ret;

}

sas_retype sas_can_init(void) {
    sas_retype status = SAS_ERR;

    /* clock enable for CAN */
    status = sas_peri_clock_enable(SAS_GPIOA_EN);                  /* Enable the clock for GPIOA */
    status = sas_peri_clock_enable(SAS_AFIO_EN);                   /* Enable the clock for the Alternate functions */
    status = sas_peri_clock_enable(SAS_CAN_EN);                    /* Enabel the clock for the CAN peripheral */
    
    /* Enable GPIO for CAN */
    config_gpio_pin(SAS_PORTA, SAS_PIN11, IN_FLT);                 /* Set the CAN RX gpio pin */
    config_gpio_pin(SAS_PORTA, SAS_PIN12, AF_OD);                  /* Set the CAN TX gpio pin  */

    status = sas_can_initMode();                                   /* Set CAN to initialize mode */
    status = sas_setCANBaud(BAUD_500Kbps);                         /* Configure the CAN BaudRate: Now fixed to 500kbps */
    status = sas_can_fiter_conf();                                 /* 7 filters to FIFO0 and 7 to FIFO1 Configure the filters  */
    status = sas_can_startStop(SAS_START);                         /* Enable the can peripheral to normal mode */

    return status;
}

sas_retype sas_can_startStop(sas_cmd cmd){
  sas_retype ret = SAS_ERR;
  switch (cmd)
  {
  case SAS_STOP:
    /* Enter to Sleep */
    CAN1->MCR |= CAN_MCR_SLEEP;

    if(CAN_MSR_SLAK & CAN1->MSR) {
      ret = SAS_OK;
    }
    break;
  case SAS_START:
    /* Exit from Initialization */
    CAN1->MCR &= ~CAN_MCR_INRQ;

    if(CAN_MSR_INAK & CAN1->MSR) {
      ret = SAS_OK;
    }
    break;
  case SAS_RESET:
    /* Reset the CAN Settings */
    CAN1->MCR |= CAN_MCR_RESET;
    break;
  
  default:
    break;
  }
  return ret;
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

sas_retype sas_get_can_status(sas_can_status* status) {
  /* TODO: Copy the can_IER register to this variable and return it back */
  return SAS_OK;
}

sas_retype sas_can_fiter_conf() {
  /* Mask and filter to select the can id to recieive and reject */
  /* Without this can does not work */
  /* Enter the Filter Initialization Mode by setting the FINIT bit in CAN_FMR */
  uint16_t NoOfFilters = 14;
  CAN1->FMR |= CAN_FMR_FINIT;

  /* Set the ID mask mode or ID list mode for 0-28 filters, 0 = Mask Mode and 1 = List Mode (Default Mask Mode)*/
  CAN1->FM1R = 0;

  /* Scaling of the Filter ie 2 - 16 bit mode or single 32 bit mode (Default is 0x00000000) */
  CAN1->FS1R = 0x3FFF;

  /* Assign the Filter to FIFO 0,1 respectively */
  CAN1->FFA1R = 0xFF;                                                                       /* Assigning the 0-7 ie 8 filters to FIFO 1 rest to FIFO 0 */

  /* Reset the content of Filters Before Activation */

  for(int i=0;i<NoOfFilters;i++) {
    CAN1->sFilterRegister[i].FR1 =0;
    CAN1->sFilterRegister[i].FR2 =0;
  }
  /* Active the filters */
  CAN1->FA1R = 0x3FFF;

  CAN1->FMR &= ~CAN_FMR_FINIT;
    
  return SAS_OK;
}

sas_retype sas_canWrite(sas_canFrame* canFrame ){
  /* Write the message to the can bus */
  /* Will keep it in pooling mode for now */
  /* TODO: Make a FIFO buffer so that tx msg can be stored */

  if(CAN1->TSR & CAN_TSR_TME0) {
    CAN1->sTxMailBox->TDTR = (canFrame->dlc << CAN_TDT0R_DLC_Pos) & CAN_TDT0R_DLC;
    CAN1->sTxMailBox->TDHR = (canFrame->data[4] << CAN_TDH0R_DATA4_Pos)|(canFrame->data[5] << CAN_TDH0R_DATA5_Pos)|(canFrame->data[6] << CAN_TDH0R_DATA6_Pos)|(canFrame->data[7] << CAN_TDH0R_DATA7_Pos);
    CAN1->sTxMailBox->TDLR = (canFrame->data[0] << CAN_TDL0R_DATA0_Pos)|(canFrame->data[1] << CAN_TDL0R_DATA1_Pos)|(canFrame->data[2] << CAN_TDL0R_DATA2_Pos)|(canFrame->data[3] << CAN_TDL0R_DATA3_Pos);
    CAN1->sTxMailBox->TIR = (canFrame->canid << CAN_TI0R_STID_Pos) & CAN_TI0R_STID;
    CAN1->sTxMailBox->TIR |= CAN_TI0R_TXRQ;                                                     /* Send Request */
    return SAS_OK;
  } else {
    return SAS_ERR;
  }

}

sas_canFrame canRxFrame;
sas_canFrame* sas_canRead(){
  /* Read the message to the can bus */
  /* Will keep it in interrupt mode for now */
  /* TODO: Make a FIFO buffer so that rx msg can be stored */
union can_data
{
  uint8_t data8[4];
  uint32_t data32;
} dataRXL, dataRXH;


  if((CAN1->RF0R & CAN_RF0R_FMP0) ||(CAN1->RF1R & CAN_RF1R_FMP1)) {
    if(CAN1->RF0R & CAN_RF0R_FMP0){
      canRxFrame.ext = (CAN1->sFIFOMailBox[0].RIR & CAN_RI0R_IDE) >> CAN_RI0R_IDE_Pos;
      canRxFrame.rtr = (CAN1->sFIFOMailBox[0].RIR & CAN_RI0R_RTR) >> CAN_RI0R_RTR_Pos;
      canRxFrame.dlc = (CAN1->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC);
      dataRXL.data32 = (CAN1->sFIFOMailBox[0].RDLR);
      dataRXH.data32 = (CAN1->sFIFOMailBox[0].RDHR);
      canRxFrame.canid = (CAN1->sFIFOMailBox[0].RIR);

      CAN1->RF0R|=CAN_RF0R_RFOM0; /* Release FIFO 0 */
    } else {
      canRxFrame.ext = (CAN1->sFIFOMailBox[1].RIR & CAN_RI1R_IDE) >> CAN_RI1R_IDE_Pos;
      canRxFrame.rtr = (CAN1->sFIFOMailBox[1].RIR & CAN_RI1R_RTR) >> CAN_RI1R_RTR_Pos;
      canRxFrame.dlc = (CAN1->sFIFOMailBox[1].RDTR & CAN_RDT1R_DLC);
      dataRXL.data32 = (CAN1->sFIFOMailBox[1].RDLR);
      dataRXH.data32 = (CAN1->sFIFOMailBox[1].RDHR);
      canRxFrame.canid = (CAN1->sFIFOMailBox[1].RIR);

      CAN1->RF1R|=CAN_RF1R_RFOM1; /* Release FIFO 0 */
    }
  }

  if(canRxFrame.ext == 1) {
    canRxFrame.canid = (canRxFrame.canid & CAN_RI0R_EXID) >> CAN_RI0R_EXID_Pos ;
  } else {
    canRxFrame.canid = (canRxFrame.canid & CAN_RI0R_STID) >> CAN_RI0R_STID_Pos;
  }

  canRxFrame.data[0] = dataRXL.data8[0]; 
  canRxFrame.data[1] = dataRXL.data8[1]; 
  canRxFrame.data[2] = dataRXL.data8[2]; 
  canRxFrame.data[3] = dataRXL.data8[3]; 
  canRxFrame.data[4] = dataRXH.data8[0]; 
  canRxFrame.data[5] = dataRXH.data8[1]; 
  canRxFrame.data[6] = dataRXH.data8[2]; 
  canRxFrame.data[7] = dataRXH.data8[3]; 
  
return &canRxFrame;
}
