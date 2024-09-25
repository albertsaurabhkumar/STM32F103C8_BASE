#ifndef SAS_CAN_H
#define SAS_CAN_H
#include "sas_common.h"
#include "sas_clock.h"
#include "sas_gpio.h"

typedef enum {
  SAS_CAN_NOERR      ,                         /*          000: No Error */
  SAS_CAN_STUFFERR   ,                         /*      001: Stuff Error */
  SAS_CAN_FORMERR    ,                         /*     010: Form Error */
  SAS_CAN_ACKERR     ,                         /*    011: Acknowledgment Error */
  SAS_CAN_RECESIVERR ,                         /*        100: Bit recessive Error */
  SAS_CAN_DOMINANTERR,                         /*         101: Bit dominant Error */
  SAS_CAN_CRCERR     ,                         /*    110: CRC Error */
  SAS_CAN_USER       ,                         /*  111: Set by software */
} sas_can_err_t;

typedef enum {
  BAUD_250Kbps,
  BAUD_500Kbps
} CAN_Baud_t;

typedef enum {
 TQ_1 =1,
 TQ_2,
 TQ_3,
 TQ_4,
 TQ_5,
 TQ_6,
 TQ_7,
 TQ_8,
 TQ_9,
 TQ_10,
 TQ_11,
 TQ_12,
 TQ_13,
 TQ_14,
 TQ_15,
 TQ_16,
} timeQuanta;

typedef enum {
  SAS_CAN_SILENT,
  SAS_CAN_LBK,
  SAS_CAN_NORMAL
} sas_can_mode;

typedef enum {
  SAS_STOP,
  SAS_START,
  SAS_RESET
} sas_cmd;

typedef struct {
  uint8_t rec;
  uint8_t tec;
  uint8_t reservedByte;
  uint8_t reserved7:1;
  sas_can_err_t error:3;
  uint8_t reserved3:1;
  uint8_t busofflag:1;
  uint8_t errwarningflag:1;
  uint8_t errpassiveflag:1;
}sas_can_status;

typedef struct sas_can
{
  /* data */
}sas_can_configuration;


typedef struct sas_canFrame {
    uint32_t canid;
    uint8_t ext;
    uint8_t rtr;
    uint8_t dlc;
    uint8_t data[8]; 
} sas_canFrame;

sas_retype sas_can_init(void);
sas_retype sas_can_fiter_conf();
sas_retype sas_can_startStop(sas_cmd);
sas_retype sas_set_can_mode(sas_can_mode);
sas_retype sas_get_can_status(sas_can_status* );
sas_retype sas_canWrite(sas_canFrame* );
sas_canFrame* sas_canRead();

#endif
