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

#include <nrf_errors.h>
#include <nrf_fault.h>
#include <device/compiler_abstraction.h>

__WEAK void nrf_error_handler(nrf_ret_t err_code, uint32_t line_num, const uint8_t * p_file_name)
{
    nrf_error_info_t error_info =
    {
        .line_num    = line_num,
        .p_file_name = p_file_name,
        .err_code    = err_code,
    };

    nrf_fault_handler(NRF_FAULT_ID_SDK_ERROR, 0, (uint32_t)(&error_info));
}
