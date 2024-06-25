#ifndef __FLASH_H
#define __FLASH_H


#include "main.h"
//写入的起始地址与结束地址
#define WRITE_START_ADDR  ((uint32_t)0x08008000)
#define WRITE_END_ADDR    ((uint32_t)0x08010000)

void FLASH_Write(uint32_t addr, uint32_t data);
uint32_t FLASH_Read(uint32_t addr);
#endif
