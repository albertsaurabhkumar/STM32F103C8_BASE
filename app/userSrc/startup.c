/*
**  Processor: STM32F103
**  Author: Saurabh Kumar
**  GCC Version: 12.3
**  
**  Startup file for the GCC Compiler
**  Execution starts from here after the reset.
**  Startup Code Initialize the RAM and required peripherals
**  And then Jumps to the main() function
*/

#include "startup.h"

void Reset_Handler(){

    initDataNbss();
    main();
    /* Never returns back to here */
}

void initDataNbss() {

    /* Variable for copy data section */

    uint32_t* endTextAdd   = (uint32_t*) &_etext;
    uint32_t* startDataAdd = (uint32_t*) &_sdata_ram;
    uint32_t* endDataAdd   = (uint32_t*) &_edata_ram;

    /* Variable for copy bss section */

    uint32_t* startBss  = (uint32_t*) &_bss_start_;
    uint32_t* endBss    = (uint32_t*) &_bss_end_;

    /*copy data section */

    while(startDataAdd != endDataAdd)
    {
       *(startDataAdd++) = *(endTextAdd++);
    }

    /*copy bss section */

    while(startBss != endBss)
    {
        *(startBss++) = 0;
    }
}