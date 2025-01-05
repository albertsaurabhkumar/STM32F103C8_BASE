#include "sas_spi.h"
#include "sas_common.h"

void sas_spiInit() {
    sas_peri_clock_enable(SAS_SPI_EN);

    SPI1->CR2 =  SPI_CR2_SSOE;
    SPI1->CR1 =  SPI_CR1_BR_2|SPI_CR1_CPOL|SPI_CR1_CPHA|/* SPI_CR1_DFF */SPI_CR1_MSTR;
}

void sas_SpiEnable() {

    SPI1->CR1 |=  SPI_CR1_SPE;
}

void sas_SpiDisable() {

    SPI1->CR1 &=  ~SPI_CR1_SPE;
}

void sas_spiTxRxByte(uint8_t address,uint8_t txdata, uint8_t rxdata) {
    sas_SpiEnable();
    if(!(SPI1->SR & SPI_SR_BSY)) {
        SPI1->DR = address;
    }
    while(!(SPI1->SR & SPI_SR_RXNE));
    rxdata = SPI1->DR;
    
    sas_SpiDisable();
}

uint8_t spi_readByte(){
    uint8_t rxdata;
    while(!(SPI1->SR & SPI_SR_RXNE)); 
    
    rxdata = SPI1->DR;
    sas_SpiDisable();
    return rxdata;
}

void spi_writeByte(uint8_t data){
    sas_SpiEnable();
    if(!(SPI1->SR & SPI_SR_BSY)) {
        SPI1->DR = data;
    }
}