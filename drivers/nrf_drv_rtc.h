/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
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

#ifndef NRF_DRV_RTC_H__
#define NRF_DRV_RTC_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <nrf_hal_rtc.h>
#include <nrf_macros.h>
#include <nrf_errors.h>
#include <nrf_drv_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/**@brief RTC driver instance configuration structure. */
typedef struct
{
    uint16_t prescaler;
    uint8_t  irq_priority;
    uint8_t  tick_latency;
    bool     reliable;
} nrf_drv_rtc_config_t;

typedef enum
{
    NRF_DRV_RTC_EVT_COMPARE0 = 0,
    NRF_DRV_RTC_EVT_COMPARE1 = 1,
    NRF_DRV_RTC_EVT_COMPARE2 = 2,
    NRF_DRV_RTC_EVT_COMPARE3 = 3,
    NRF_DRV_RTC_EVT_TICK     = 4,
    NRF_DRV_RTC_EVT_OVERFLOW = 5
} nrf_drv_rtc_evt_t;

/**@brief RTC driver instance handler type. */
typedef void (*nrf_drv_rtc_handler_t)(nrf_drv_rtc_evt_t int_type);

typedef struct
{
    nrf_drv_state_t         state;
    nrf_drv_rtc_handler_t   handler;
    bool                    reliable;
    uint8_t                 tick_latency;
} nrf_drv_rtc_cb_t;

typedef struct
{
    nrf_drv_rtc_cb_t * p_cb;
    NRF_RTC_Type     * p_reg;
    IRQn_Type          irq;
    uint8_t            cc_channel_count;
} nrf_drv_rtc_t;


#define NRF_DRV_RTC_DEF(id)                                 \
static nrf_drv_rtc_cb_t     CONCAT_3(nrf_drv_rtc, id, cb);  \
static const nrf_drv_rtc_t  CONCAT_2(nrf_drv_rtc, id) =     \
{                                                           \
    .p_cb             = CONCAT_3(nrf_drv_rtc, id, cb),      \
    .p_reg            = CONCAT_2(NRF_RTC, id),              \
    .irq              = CONCAT_3(RTC, id, _IRQn),           \
    .cc_channel_count = CONCAT_3(RTC, id, _CC_NUM),         \
}

void nrf_drv_rtc_init(nrf_drv_rtc_t        const * const  p_instance,
                      nrf_drv_rtc_config_t const *        p_config,
                      nrf_drv_rtc_handler_t               handler);

void nrf_drv_rtc_uninit(nrf_drv_rtc_t const * const p_instance);

void nrf_drv_rtc_enable(nrf_drv_rtc_t const * const p_instance);

void nrf_drv_rtc_disable(nrf_drv_rtc_t const * const p_instance);

nrf_ret_t nrf_drv_rtc_cc_set(nrf_drv_rtc_t const * const p_instance,
                             uint32_t                    channel,
                             uint32_t                    val,
                             bool                        enable_irq);

nrf_ret_t nrf_drv_rtc_cc_disable(nrf_drv_rtc_t const * const p_instance, uint32_t channel);

void nrf_drv_rtc_tick_enable(nrf_drv_rtc_t const * const p_instance, bool enable_irq);

void nrf_drv_rtc_tick_disable(nrf_drv_rtc_t const * const p_instance);

void nrf_drv_rtc_overflow_enable(nrf_drv_rtc_t const * const p_instance, bool enable_irq);

void nrf_drv_rtc_overflow_disable(nrf_drv_rtc_t const * const p_instance);

uint32_t nrf_drv_rtc_max_ticks_get(nrf_drv_rtc_t const * const p_instance);


#ifdef __cplusplus
}
#endif

#endif // NRF_DRV_RTC_H__
