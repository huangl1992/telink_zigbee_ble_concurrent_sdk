#ifndef _LDS_FLASH_REMEMBER_H_
#define _LDS_FLASH_REMEMBER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lds_error_codes.h"

bool LdsFlashMemoryRead(uint32_t addr, uint8_t *data, uint16_t len);

/**
 * @brief function for write flash memory data
 *
 * @param [in]  addr: user flash address
 * @param [in] data: user data
 * @param [in]  len:  user data length
 * @return

 */
bool LdsFlashMemoryWrite(uint32_t addr, uint8_t *data, uint16_t len);

/**
 * @brief function for earse flash memory data
 *
 * @param [in]  addr: user flash address
 * @param [in] data: user data
 * @param [in]  len:  user data length
 * @return

 */
bool LdsFlashMemoryErase(uint32_t addr);

//#endif
#ifdef __cplusplus
}
#endif

#endif // _LDS_DRIVER_I2C_H_
