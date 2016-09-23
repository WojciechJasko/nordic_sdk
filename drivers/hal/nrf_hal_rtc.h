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

#ifndef NRF_HAL_RTC_H__
#define NRF_HAL_RTC_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <nrf.h>
#include <nrf_peripherals.h>
#include <nrf_assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_HAL_RTC_COUNTER_MAX             RTC_COUNTER_COUNTER_Msk
#define NRF_HAL_RTC_WRAP(val)               ((val) & NRF_HAL_RTC_COUNTER_MAX)
#define NRF_HAL_RTC_CHANNEL_INT_MASK(ch)    ((uint32_t)NRF_HAL_RTC_INT_COMPARE0_MASK << (ch))
#define NRF_HAL_RTC_CHANNEL_EVENT_ADDR(ch)  ((nrf_hal_rtc_event_t)(NRF_HAL_RTC_EVT_COMPARE_0 + (ch) * sizeof(uint32_t)))

typedef enum
{
    /*lint -save -e30*/
    NRF_HAL_RTC_TASK_START            = offsetof(NRF_RTC_Type,TASKS_START),     /**< Start. */
    NRF_HAL_RTC_TASK_STOP             = offsetof(NRF_RTC_Type,TASKS_STOP),      /**< Stop. */
    NRF_HAL_RTC_TASK_CLEAR            = offsetof(NRF_RTC_Type,TASKS_CLEAR),     /**< Clear. */
    NRF_HAL_RTC_TASK_TRIGGER_OVERFLOW = offsetof(NRF_RTC_Type,TASKS_TRIGOVRFLW),/**< Trigger overflow. */
    /*lint -restore*/
} nrf_hal_rtc_task_t;

typedef enum
{
    /*lint -save -e30*/
    NRF_HAL_RTC_EVT_TICK        = offsetof(NRF_RTC_Type,EVENTS_TICK),       /**< Tick event. */
    NRF_HAL_RTC_EVT_OVERFLOW    = offsetof(NRF_RTC_Type,EVENTS_OVRFLW),     /**< Overflow event. */
    NRF_HAL_RTC_EVT_COMPARE_0   = offsetof(NRF_RTC_Type,EVENTS_COMPARE[0]), /**< Compare 0 event. */
    NRF_HAL_RTC_EVT_COMPARE_1   = offsetof(NRF_RTC_Type,EVENTS_COMPARE[1]), /**< Compare 1 event. */
    NRF_HAL_RTC_EVT_COMPARE_2   = offsetof(NRF_RTC_Type,EVENTS_COMPARE[2]), /**< Compare 2 event. */
    NRF_HAL_RTC_EVT_COMPARE_3   = offsetof(NRF_RTC_Type,EVENTS_COMPARE[3])  /**< Compare 3 event. */
    /*lint -restore*/
} nrf_hal_rtc_event_t;

typedef enum
{
    NRF_HAL_RTC_INT_TICK_MASK     = RTC_INTENSET_TICK_Msk,     /**< RTC interrupt from tick event. */
    NRF_HAL_RTC_INT_OVERFLOW_MASK = RTC_INTENSET_OVRFLW_Msk,   /**< RTC interrupt from overflow event. */
    NRF_HAL_RTC_INT_COMPARE0_MASK = RTC_INTENSET_COMPARE0_Msk, /**< RTC interrupt from compare event on channel 0. */
    NRF_HAL_RTC_INT_COMPARE1_MASK = RTC_INTENSET_COMPARE1_Msk, /**< RTC interrupt from compare event on channel 1. */
    NRF_HAL_RTC_INT_COMPARE2_MASK = RTC_INTENSET_COMPARE2_Msk, /**< RTC interrupt from compare event on channel 2. */
    NRF_HAL_RTC_INT_COMPARE3_MASK = RTC_INTENSET_COMPARE3_Msk  /**< RTC interrupt from compare event on channel 3. */
} nrf_hal_rtc_int_t;

/**@brief Function for setting a compare value for a channel.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  ch            Channel.
 * @param[in]  cc_val        Compare value to set.
 */
__STATIC_INLINE void nrf_hal_rtc_cc_set(NRF_RTC_Type * p_rtc, uint32_t ch, uint32_t cc_val)
{
    p_rtc->CC[ch] = cc_val;
}

/**@brief Function for returning the compare value for a channel.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  ch            Channel.
 *
 * @return                   COMPARE[ch] value.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_cc_get(NRF_RTC_Type * p_rtc, uint32_t ch)
{
    return p_rtc->CC[ch];
}

/**@brief Function for enabling interrupts.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  mask          Interrupt mask to be enabled.
 */
__STATIC_INLINE void nrf_hal_rtc_int_enable(NRF_RTC_Type * p_rtc, uint32_t mask)
{
    p_rtc->INTENSET = mask;
}

/**@brief Function for disabling interrupts.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  mask          Interrupt mask to be disabled.
 */
__STATIC_INLINE void nrf_hal_rtc_int_disable(NRF_RTC_Type * p_rtc, uint32_t mask)
{
    p_rtc->INTENCLR = mask;
}

/**@brief Function for checking if interrupts are enabled.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  mask          Mask of interrupt flags to check.
 *
 * @return                   Mask with enabled interrupts.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_int_is_enabled(NRF_RTC_Type * p_rtc, uint32_t mask)
{
    return (p_rtc->INTENSET & mask);
}

/**@brief Function for returning the status of currently enabled interrupts.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 *
 * @return                   Value in INTEN register.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_int_get(NRF_RTC_Type * p_rtc)
{
    return p_rtc->INTENSET;
}

/**@brief Function for checking if an event is pending.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  event         Address of the event.
 *
 * @return                   Mask of pending events.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_event_pending(NRF_RTC_Type * p_rtc, nrf_hal_rtc_event_t event)
{
    return *(volatile uint32_t *)((uint8_t *)p_rtc + (uint32_t)event);
}

/**@brief Function for clearing an event.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  event         Event to clear.
 */
__STATIC_INLINE void nrf_hal_rtc_event_clear(NRF_RTC_Type * p_rtc, nrf_hal_rtc_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)p_rtc + (uint32_t)event)) = 0;
#if __CORTEX_M == 0x04
    volatile uint32_t dummy = *((volatile uint32_t *)((uint8_t *)p_rtc + (uint32_t)event));
    (void)dummy;
#endif
}

/**@brief Function for returning a counter value.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 *
 * @return                   Counter value.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_counter_get(NRF_RTC_Type * p_rtc)
{
     return p_rtc->COUNTER;
}

/**@brief Function for setting a prescaler value.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  val           Value to set the prescaler to.
 */
__STATIC_INLINE void nrf_hal_rtc_prescaler_set(NRF_RTC_Type * p_rtc, uint32_t val)
{
    NRF_ASSERT(val <= NRF_HAL_RTC_COUNTER_MAX);
    p_rtc->PRESCALER = val;
}

__STATIC_INLINE uint32_t nrf_hal_rtc_prescaler_get(NRF_RTC_Type * p_rtc)
{
    return p_rtc->PRESCALER;
}

/**@brief Function for returning the address of an event.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  event         Requested event.
 *
 * @return     Address of the requested event register.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_event_address_get(NRF_RTC_Type * p_rtc, nrf_hal_rtc_event_t event)
{
    return (uint32_t)p_rtc + event;
}

/**@brief Function for returning the address of a task.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  task          Requested task.
 *
 * @return     Address of the requested task register.
 */
__STATIC_INLINE uint32_t nrf_hal_rtc_task_address_get(NRF_RTC_Type * p_rtc, nrf_hal_rtc_task_t task)
{
    return (uint32_t)p_rtc + task;
}

/**@brief Function for starting a task.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  task          Requested task.
 */
__STATIC_INLINE void nrf_hal_rtc_task_trigger(NRF_RTC_Type * p_rtc, nrf_hal_rtc_task_t task)
{
    *(volatile uint32_t *)((uint32_t)p_rtc + task) = 1;
}

/**@brief Function for enabling events.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  mask          Mask of event flags to enable.
 */
__STATIC_INLINE void nrf_hal_rtc_event_enable(NRF_RTC_Type * p_rtc, uint32_t mask)
{
    p_rtc->EVTENSET = mask;
}

/**@brief Function for disabling an event.
 *
 * @param[in]  p_rtc         Pointer to the peripheral registers structure.
 * @param[in]  event         Requested event.
 */
__STATIC_INLINE void nrf_hal_rtc_event_disable(NRF_RTC_Type * p_rtc, uint32_t mask)
{
    p_rtc->EVTENCLR = mask;
}

#ifdef __cplusplus
}
#endif

#endif // NRF_HAL_RTC_H__
