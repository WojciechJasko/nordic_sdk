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

#ifndef NRF_ERRORS_H__
#define NRF_ERRORS_H__

#include <stdint.h>
#include <nrf_error.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_FAULT_ID_SDK_RANGE_START 0x00004000

#define NRF_FAULT_ID_SDK_ERROR       NRF_FAULT_ID_SDK_RANGE_START + 1
#define NRF_FAULT_ID_SDK_ASSERT      NRF_FAULT_ID_SDK_RANGE_START + 2


typedef uint32_t nrf_ret_t;

typedef struct
{
    uint16_t        line_num;
    uint8_t const * p_file_name;
    nrf_ret_t       err_code;
} nrf_error_info_t;


void nrf_error_handler(nrf_ret_t err_code, uint32_t line_num, const uint8_t * p_file_name);

#ifdef NRF_DEBUG
#define NRF_ERROR_HANDLER(err_code)                                    \
    do                                                                 \
    {                                                                  \
        nrf_error_handler((err_code), __LINE__, (uint8_t*) __FILE__);  \
    } while (0)
#else
#define NRF_ERROR_HANDLER(err_code)                                    \
    do                                                                 \
    {                                                                  \
        nrf_error_handler((err_code), 0, NULL);                        \
    } while (0)
#endif

#define NRF_ERROR_CHECK(err_code)                           \
    do                                                      \
    {                                                       \
        const uint32_t local_err_code = (err_code);         \
        if (local_err_code != NRF_SUCCESS)                  \
        {                                                   \
            NRF_ERROR_HANDLER(local_err_code);              \
        }                                                   \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif // NRF_ERRORS_H__