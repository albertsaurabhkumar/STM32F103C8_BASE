#ifndef SAS_SPI_H
#define SAS_SPI_H

#include "sas_clock.h"

void sas_spiInit();
void sas_SpiEnable();
void sas_SpiDisable();
void spi_writeByte(uint8_t);
uint8_t spi_readByte();
void sas_spiTxRxByte(uint8_t ,uint8_t , uint8_t );

#endif