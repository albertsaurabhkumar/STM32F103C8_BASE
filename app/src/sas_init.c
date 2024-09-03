/**
  ******************************************************************************
  * @file    sas_init.c
  * @author  Saurabh K
  * @brief   Description: System Initialization source file
  *
  *          This file contains:
  *           - Data structures and functions for system peripherals init
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

#include "sas_init.h"

sas_retype sysinit(void) {
    if(SAS_OK != sas_clock_init()){
        return SAS_ERR;
    }

    if(SAS_OK != sas_wdg_init()){
        return SAS_ERR;
    }

    if(SAS_OK != sas_can_init()){
        return SAS_ERR;
    }
    return SAS_OK;
}