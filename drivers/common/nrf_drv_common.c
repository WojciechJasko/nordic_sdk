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

#include <nrf_drv_common.h>


void nrf_drv_common_irq_enable(IRQn_Type IRQn, uint8_t priority)
{
    NVIC_SetPriority(IRQn, priority);
    NVIC_ClearPendingIRQ(IRQn);
    NVIC_EnableIRQ(IRQn);
}

void nrf_drv_common_irq_disable(IRQn_Type IRQn)
{
    NVIC_DisableIRQ(IRQn);
}
