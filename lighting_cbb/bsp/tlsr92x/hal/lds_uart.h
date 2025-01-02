#ifndef _LDS_UART_H_
#define _LDS_UART_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "lds_device_config.h"
#include "tl_common.h"

#if defined(LDS_UART_ENABLE)
void ldsUartPacketRecvTask(void);

void ldsUartTxPacketSent(const uint8_t *buff, uint32_t len);

#endif

#ifdef __cplusplus
}
#endif
#endif
