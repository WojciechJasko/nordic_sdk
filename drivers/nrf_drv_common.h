/* Copyright (c) 2015 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#ifndef NRF_DRV_COMMON_H__
#define NRF_DRV_COMMON_H__

#include <stdint.h>
#include <nrf.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Driver state.
 */
typedef enum
{
    NRF_DRV_STATE_UNINITIALIZED, /**< Uninitialized. */
    NRF_DRV_STATE_INITIALIZED, /**< Initialized but powered off. */
    NRF_DRV_STATE_POWERED_ON
} nrf_drv_state_t;



#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_COMMON_H__
