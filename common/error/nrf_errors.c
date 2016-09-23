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

#include <stdio.h>

#include <nrf_errors.h>
#include <nrf.h>
#include <nrf_assert.h>

void nrf_error_handler(nrf_ret_t err_code, uint32_t line_num, const uint8_t * p_file_name)
{
    nrf_error_info_t error_info =
    {
        .line_num    = line_num,
        .p_file_name = p_file_name,
        .err_code    = err_code,
    };

    nrf_error_fault_handler(NRF_FAULT_ID_SDK_ERROR, 0, (uint32_t)(&error_info));
}

void nrf_error_handler_bare(nrf_ret_t err_code)
{
    nrf_error_info_t error_info =
    {
        .line_num    = 0,
        .p_file_name = NULL,
        .err_code    = err_code,
    };

    nrf_error_fault_handler(NRF_FAULT_ID_SDK_ERROR, 0, (uint32_t)(&error_info));
}


__WEAK void nrf_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
#ifdef NRF_DEBUG
    static volatile struct
    {
        uint32_t                fault_id;
        uint32_t                pc;
        union {
            nrf_assert_info_t * p_assert;
            nrf_error_info_t  * p_error;
        } info;
    } m_error_data = {0};

    m_error_data.fault_id   = id;
    m_error_data.pc         = pc;

    switch (id)
    {
        case NRF_FAULT_ID_SDK_ASSERT:
            m_error_data.info.p_error = (nrf_assert_info_t *)info;
            break;

        case NRF_FAULT_ID_SDK_ERROR:
            m_error_data.info.p_error = (nrf_error_info_t *)info;
            break;
    }

    UNUSED_VARIABLE(m_error_data);

    volatile bool loop = true;

    __disable_irq();
    while (loop);
    __enable_irq();
#else
    NVIC_SystemReset();
#endif // NRF_DEBUG
}
