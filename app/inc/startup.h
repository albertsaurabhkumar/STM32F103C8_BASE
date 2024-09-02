#include "main.h"

extern uint32_t _intvec_start_;
extern uint32_t _intvec_end_;
extern uint32_t _bss_start_;
extern uint32_t _bss_end_;
extern uint32_t _edata_ram;
extern uint32_t _etext;
extern uint32_t _sdata_ram;

void initDataNbss();
void Reset_Handler();