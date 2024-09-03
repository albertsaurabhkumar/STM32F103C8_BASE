#include "stdint.h"
#include "stdbool.h"

typedef enum {
  dataPkt = 0x31,
  retransPkt = 0x32,
  ackPkt = 0x55,
  dwReqPkt = 0x56
} Pktype_t;

typedef struct {
  Pktype_t pktype;
  uint16_t totalSize;
} DwReqPkt_t;

typedef struct {
  Pktype_t pktype;
  uint8_t dlc;
  uint8_t data[8];
  uint8_t crc;
} DataPkt_t;

typedef struct {
  Pktype_t pktype;
  uint8_t dlc;
  uint8_t crc;
} ReqRespPkt_t;

DataPkt_t ReadDataPkt();
ReqRespPkt_t ReadReqRespPkt();
DwReqPkt_t ReadDwReqPkt();
bool writeDataPkt(DataPkt_t *pkt);
bool writeReqRespPkt(ReqRespPkt_t *pkt);

