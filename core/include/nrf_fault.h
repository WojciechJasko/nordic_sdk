/* Copyright (c) 2013 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 */

#ifndef NRF_FAULT_H__
#define NRF_FAULT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@defgroup NRF_FAULT_ID_RANGES Fault ID ranges
 * @{ */
#define NRF_FAULT_ID_SD_RANGE_START     (0x0)           /**< SoftDevice ID range start. */
#define NRF_FAULT_ID_APP_RANGE_START    (0x1000)        /**< Application ID range start. */
#define NRF_FAULT_ID_SDK_RANGE_START    (0x2000)        
/**@} */

#define NRF_FAULT_ID_SDK_ERROR      (NRF_FAULT_ID_SDK_RANGE_START + 1)
#define NRF_FAULT_ID_SDK_ASSERT     (NRF_FAULT_ID_SDK_RANGE_START + 2)


void nrf_fault_handler(uint32_t id, uint32_t pc, uint32_t info);


#ifdef __cplusplus
}
#endif

#endif // NRF_FAULT_H__