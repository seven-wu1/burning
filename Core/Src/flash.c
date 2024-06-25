#include "flash.h"


void FLASH_Write(uint32_t addr, uint32_t data)
{
  uint32_t PageError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;
  
  HAL_FLASH_Unlock();     //解锁
  
  EraseInitStruct.Banks = FLASH_BANK_1;
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // 擦除的类型为扇区
  EraseInitStruct.NbPages = 1; //一次只擦除一个扇区
  EraseInitStruct.PageAddress = addr;// 擦除的地址
  
  if (HAL_FLASHEx_Erase(&EraseInitStruct,&PageError) == HAL_OK) //如果结构体中的起始地址0x0801FC00，这一页的数据擦除成功，返回OK
  {
      printf("Erase OK\r\n");
  }
  
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,addr, data); //向FLASH中写入
  
  HAL_FLASH_Lock();  // 上锁
  
//  printf("at address:0x%x, write value:%d\r\n", addr, *(__IO uint32_t*)addr);
}
/**
  * @brief  读出存储地址中的内容
  * @param  用STM32中FLASH存储空间模拟EEPROM的读写
  * @retval 返回值：从FLASH中读出数据
  */
uint32_t FLASH_Read(uint32_t addr)
{
    return *(__IO uint32_t*)addr;
}
