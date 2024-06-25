#include "flash.h"


void FLASH_Write(uint32_t addr, uint32_t data)
{
  uint32_t PageError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;
  
  HAL_FLASH_Unlock();     //����
  
  EraseInitStruct.Banks = FLASH_BANK_1;
  EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES; // ����������Ϊ����
  EraseInitStruct.NbPages = 1; //һ��ֻ����һ������
  EraseInitStruct.PageAddress = addr;// �����ĵ�ַ
  
  if (HAL_FLASHEx_Erase(&EraseInitStruct,&PageError) == HAL_OK) //����ṹ���е���ʼ��ַ0x0801FC00����һҳ�����ݲ����ɹ�������OK
  {
      printf("Erase OK\r\n");
  }
  
  HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,addr, data); //��FLASH��д��
  
  HAL_FLASH_Lock();  // ����
  
//  printf("at address:0x%x, write value:%d\r\n", addr, *(__IO uint32_t*)addr);
}
/**
  * @brief  �����洢��ַ�е�����
  * @param  ��STM32��FLASH�洢�ռ�ģ��EEPROM�Ķ�д
  * @retval ����ֵ����FLASH�ж�������
  */
uint32_t FLASH_Read(uint32_t addr)
{
    return *(__IO uint32_t*)addr;
}
