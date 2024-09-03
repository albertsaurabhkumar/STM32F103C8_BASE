/**
  ******************************************************************************
  * @file    sas_common.h
  * @author  Saurabh K
  * @brief   Description: common abstraction layer header file which is common
  *          to all the peripherals
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

#ifndef SAS_COMMON_H
#define SAS_COMMON_H

#include "stm32f103x6.h"
#include "stdbool.h"

#define MMIO(x) (*(uint32_t*)(x))

/// @brief SAS return type return the status of call SAS_ERR, SAS_OK, SAS_INVALID
typedef enum {
    SAS_ERR = 0,
    SAS_OK,
    SAS_INVALID
} sas_retype;

#endif