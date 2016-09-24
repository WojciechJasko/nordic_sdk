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

#include <nrf_drv_rtc.h>
#include <nrf_assert.h>


void nrf_drv_rtc_init(nrf_drv_rtc_t        const * const  p_instance,
                      nrf_drv_rtc_config_t const *        p_config,
                      nrf_drv_rtc_handler_t               handler)
{
    NRF_ASSERT(handler);
    NRF_ASSERT(p_config);
    NRF_ASSERT(p_instance);
    NRF_ASSERT(p_instance->p_cb->state == NRF_DRV_STATE_UNINITIALIZED);

    nrf_drv_common_irq_enable(p_instance->irq,   p_config->irq_priority);
    nrf_hal_rtc_prescaler_set(p_instance->p_reg, p_config->prescaler);

    p_instance->p_cb->state         = NRF_DRV_STATE_INITIALIZED;
    p_instance->p_cb->handler       = handler;
    p_instance->p_cb->reliable      = p_config->reliable;
    p_instance->p_cb->tick_latency  = p_config->tick_latency;
}

void nrf_drv_rtc_uninit(nrf_drv_rtc_t const * const p_instance)
{
    NRF_ASSERT(p_instance->p_cb->state != NRF_DRV_STATE_UNINITIALIZED);

    uint32_t mask = NRF_HAL_RTC_INT_TICK_MASK     |
                    NRF_HAL_RTC_INT_OVERFLOW_MASK |
                    NRF_HAL_RTC_INT_COMPARE0_MASK |
                    NRF_HAL_RTC_INT_COMPARE1_MASK |
                    NRF_HAL_RTC_INT_COMPARE2_MASK |
                    NRF_HAL_RTC_INT_COMPARE3_MASK;

    nrf_drv_common_irq_disable(p_instance->irq);

    nrf_hal_rtc_task_trigger(p_instance->p_reg,     NRF_HAL_RTC_TASK_STOP);
    nrf_hal_rtc_event_disable(p_instance->p_reg,    mask);
    nrf_hal_rtc_int_disable(p_instance->p_reg,      mask);

    p_instance->p_cb->state = NRF_DRV_STATE_UNINITIALIZED;
}

void nrf_drv_rtc_enable(nrf_drv_rtc_t const * const p_instance)
{
    NRF_ASSERT(p_instance->p_cb->state == NRF_DRV_STATE_INITIALIZED);

    nrf_hal_rtc_task_trigger(p_instance->p_reg, NRF_HAL_RTC_TASK_START);
    p_instance->p_cb->state = NRF_DRV_STATE_POWERED_ON;
}

void nrf_drv_rtc_disable(nrf_drv_rtc_t const * const p_instance)
{
    NRF_ASSERT(m_cb[p_instance->instance_id].state != NRF_DRV_STATE_UNINITIALIZED);

    nrf_hal_rtc_task_trigger(p_instance->p_reg, NRF_HAL_RTC_TASK_STOP);
    p_instance->p_cb->state = NRF_DRV_STATE_INITIALIZED;
}

nrf_ret_t nrf_drv_rtc_cc_disable(nrf_drv_rtc_t const * const p_instance, uint32_t channel)
{
    NRF_ASSERT(p_instance->p_cb->state != NRF_DRV_STATE_UNINITIALIZED);
    NRF_ASSERT(channel < p_instance->cc_channel_count);

    nrf_hal_rtc_event_t event    = NRF_HAL_RTC_CHANNEL_EVENT_ADDR(channel);
    uint32_t            int_mask = NRF_HAL_RTC_CHANNEL_INT_MASK(channel);

    nrf_hal_rtc_event_disable(p_instance->p_reg, int_mask);
    if (nrf_hal_rtc_int_is_enabled(p_instance->p_reg, int_mask))
    {
        nrf_hal_rtc_int_disable(p_instance->p_reg, int_mask);
        if (nrf_hal_rtc_event_pending(p_instance->p_reg, event))
        {
            nrf_hal_rtc_event_clear(p_instance->p_reg, event);
            return NRF_ERROR_TIMEOUT;
        }
    }
    return NRF_SUCCESS;
}

nrf_ret_t nrf_drv_rtc_cc_set(nrf_drv_rtc_t const * const p_instance,
                             uint32_t                    channel,
                             uint32_t                    val,
                             bool                        enable_irq)
{
    NRF_ASSERT(p_instance->p_cb->state != NRF_DRV_STATE_UNINITIALIZED);
    NRF_ASSERT(channel < p_instance->cc_channel_count);

    nrf_hal_rtc_event_t event    = NRF_HAL_RTC_CHANNEL_EVENT_ADDR(channel);
    uint32_t            int_mask = NRF_HAL_RTC_CHANNEL_INT_MASK(channel);

    nrf_hal_rtc_event_disable(p_instance->p_reg,    int_mask);
    nrf_hal_rtc_int_disable(p_instance->p_reg,      int_mask);

    val = NRF_HAL_RTC_WRAP(val);
    if (p_instance->p_cb->reliable)
    {
        nrf_hal_rtc_cc_set(p_instance->p_reg, channel, val);
        uint32_t cnt = nrf_hal_rtc_counter_get(p_instance->p_reg);
        int32_t diff = cnt - val;
        if (cnt < val)
        {
            diff += RTC_COUNTER_COUNTER_Msk;
        }
        if (diff < p_instance->p_cb->tick_latency)
        {
            return NRF_ERROR_TIMEOUT;
        }
    }
    else
    {
        nrf_hal_rtc_cc_set(p_instance->p_reg, channel, val);
    }

    if (enable_irq)
    {
        nrf_hal_rtc_event_clear(p_instance->p_reg,  event);
        nrf_hal_rtc_int_enable(p_instance->p_reg,   int_mask);
    }
    nrf_hal_rtc_event_enable(p_instance->p_reg, int_mask);

    return NRF_SUCCESS;
}

void nrf_drv_rtc_tick_enable(nrf_drv_rtc_t const * const p_instance, bool enable_irq)
{
    nrf_hal_rtc_event_t event = NRF_HAL_RTC_EVT_TICK;
    uint32_t            mask  = NRF_HAL_RTC_INT_TICK_MASK;

    nrf_hal_rtc_event_clear(p_instance->p_reg,  event);
    nrf_hal_rtc_event_enable(p_instance->p_reg, mask);
    if (enable_irq)
    {
        nrf_hal_rtc_int_enable(p_instance->p_reg, mask);
    }
}

void nrf_drv_rtc_tick_disable(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t mask = NRF_HAL_RTC_INT_TICK_MASK;

    nrf_hal_rtc_event_disable(p_instance->p_reg, mask);
    nrf_hal_rtc_int_disable(p_instance->p_reg,   mask);
}

void nrf_drv_rtc_overflow_enable(nrf_drv_rtc_t const * const p_instance, bool enable_irq)
{
    nrf_hal_rtc_event_t event = NRF_HAL_RTC_EVT_OVERFLOW;
    uint32_t            mask  = NRF_HAL_RTC_INT_OVERFLOW_MASK;

    nrf_hal_rtc_event_clear(p_instance->p_reg,  event);
    nrf_hal_rtc_event_enable(p_instance->p_reg, mask);
    if (enable_irq)
    {
        nrf_hal_rtc_int_enable(p_instance->p_reg, mask);
    }
}

void nrf_drv_rtc_overflow_disable(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t mask = NRF_HAL_RTC_INT_OVERFLOW_MASK;
    nrf_hal_rtc_event_disable(p_instance->p_reg, mask);
    nrf_hal_rtc_int_disable(p_instance->p_reg,   mask);
}

uint32_t nrf_drv_rtc_max_ticks_get(nrf_drv_rtc_t const * const p_instance)
{
    uint32_t ticks;
    if (p_instance->p_cb->reliable)
    {
        ticks = NRF_HAL_RTC_COUNTER_MAX - p_instance->p_cb->tick_latency;
    }
    else
    {
        ticks = NRF_HAL_RTC_COUNTER_MAX;
    }
    return ticks;
}


void nrf_drv_rtc_int_handler(nrf_drv_rtc_t const * const p_instance)
{
    nrf_hal_rtc_event_t event       = NRF_HAL_RTC_EVT_COMPARE_0;
    uint32_t            int_mask    = (uint32_t)NRF_HAL_RTC_INT_COMPARE0_MASK;

    for (uint32_t i = 0; i < p_instance->cc_channel_count; i++)
    {
        if (nrf_hal_rtc_int_is_enabled(p_instance->p_reg, int_mask) &&
            nrf_hal_rtc_event_pending(p_instance->p_reg, event))
        {
            nrf_hal_rtc_event_disable(p_instance->p_reg, int_mask);
            nrf_hal_rtc_int_disable(p_instance->p_reg, int_mask);
            nrf_hal_rtc_event_clear(p_instance->p_reg, event);
            p_instance->p_cb->handler((nrf_drv_rtc_evt_t)i);
        }
        int_mask <<= 1;
        event = (nrf_hal_rtc_event_t)((uint32_t)event + sizeof(uint32_t));
    }

    event = NRF_HAL_RTC_EVT_TICK;
    if (nrf_hal_rtc_int_is_enabled(p_instance->p_reg, NRF_HAL_RTC_INT_TICK_MASK) &&
        nrf_hal_rtc_event_pending(p_instance->p_reg, event))
    {
        nrf_hal_rtc_event_clear(p_instance->p_reg, event);
        p_instance->p_cb->handler(NRF_DRV_RTC_EVT_TICK);
    }

    event = NRF_HAL_RTC_EVT_OVERFLOW;
    if (nrf_hal_rtc_int_is_enabled(p_instance->p_reg, NRF_HAL_RTC_INT_OVERFLOW_MASK) &&
        nrf_hal_rtc_event_pending(p_instance->p_reg, event))
    {
        nrf_hal_rtc_event_clear(p_instance->p_reg, event);
        p_instance->p_cb->handler(NRF_DRV_RTC_EVT_OVERFLOW);
    }
}
