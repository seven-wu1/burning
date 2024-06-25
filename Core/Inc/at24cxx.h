#ifndef __AT24CXX_H__
#define __AT24CXX_H__

#include "main.h"


 
#ifdef __cplusplus
 extern "C" {
#endif
 
/*! -------------------------------------------------------------------------- */
/*! Include headers */
#include <stdint.h>
 
#define AT24CXX_TEST_ENABLE     0
 
/*! -------------------------------------------------------------------------- */
/*! Public functions prototype */
int AT24C02_write(uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
int AT24C02_read (uint8_t addr, uint8_t* dataPtr, uint16_t dataSize);
 
#if (1 == AT24CXX_TEST_ENABLE)
/*! -------------------------------------------------------------------------- */
/*! Public test functions prototype */
#define AT24CXX_TEST_ADDR       39
#define AT24CXX_TEST_BUFF_SIZE  255
#define AT24CXX_TEST_SIZE       90
 
int AT24C02_Test(void);
#endif
 
#ifdef __cplusplus
}
#endif
 
#endif
/*! end of the file */


