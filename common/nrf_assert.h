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

#ifndef NRF_ASSERT_H__
#define NRF_ASSERT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint16_t        line_num;
    uint8_t const * p_file_name;
} nrf_assert_info_t;

void nrf_assert_handler(uint16_t line_num, const uint8_t * p_file_name);

#ifdef NRF_DEBUG
#define NRF_ASSERT(EXPR)                                            \
if (!EXPR)                                                          \
{                                                                   \
    nrf_assert_handler((uint16_t)__LINE__, (uint8_t *)__FILE__);    \
}
#else
#define NRF_ASSERT(EXPR)
#endif // NRF_DEBUG


#ifdef __cplusplus
}
#endif

#endif /* NRF_ASSERT_H_ */
