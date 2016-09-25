/*
 * BSD licence
 */

#ifndef NRF_NVIC_H__
#define NRF_NVIC_H__

#include <stdint.h>
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*nrf_nvic_irq_handler_t)(void);

void nrf_nvic_register(IRQn_Type irq, nrf_nvic_irq_handler_t p_function);

#ifdef __cplusplus
}
#endif

#endif // NRF_NVIC_H__
