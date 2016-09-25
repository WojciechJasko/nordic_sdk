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

#ifndef NRF_ERROR_H__
#define NRF_ERROR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup NRF_ERRORS_BASE Error Codes Base number definitions
 * @{ */
#define NRF_ERROR_BASE_NUM      (0x0)       ///< Global error base
#define NRF_ERROR_SDM_BASE_NUM  (0x1000)    ///< SDM error base
#define NRF_ERROR_SOC_BASE_NUM  (0x2000)    ///< SoC error base
#define NRF_ERROR_STK_BASE_NUM  (0x3000)    ///< STK error base
#define NRF_ERROR_ANT_BASE_NUM  (0x4000)    ///< ANT's Exception offset
/** @} */

#define NRF_SUCCESS                           (NRF_ERROR_BASE_NUM + 0)  ///< Successful command
#define NRF_ERROR_SVC_HANDLER_MISSING         (NRF_ERROR_BASE_NUM + 1)  ///< SVC handler is missing
#define NRF_ERROR_SOFTDEVICE_NOT_ENABLED      (NRF_ERROR_BASE_NUM + 2)  ///< SoftDevice has not been enabled
#define NRF_ERROR_INTERNAL                    (NRF_ERROR_BASE_NUM + 3)  ///< Internal Error
#define NRF_ERROR_NO_MEM                      (NRF_ERROR_BASE_NUM + 4)  ///< No Memory for operation
#define NRF_ERROR_NOT_FOUND                   (NRF_ERROR_BASE_NUM + 5)  ///< Not found
#define NRF_ERROR_NOT_SUPPORTED               (NRF_ERROR_BASE_NUM + 6)  ///< Not supported
#define NRF_ERROR_INVALID_PARAM               (NRF_ERROR_BASE_NUM + 7)  ///< Invalid Parameter
#define NRF_ERROR_INVALID_STATE               (NRF_ERROR_BASE_NUM + 8)  ///< Invalid state, operation disallowed in this state
#define NRF_ERROR_INVALID_LENGTH              (NRF_ERROR_BASE_NUM + 9)  ///< Invalid Length
#define NRF_ERROR_INVALID_FLAGS               (NRF_ERROR_BASE_NUM + 10) ///< Invalid Flags
#define NRF_ERROR_INVALID_DATA                (NRF_ERROR_BASE_NUM + 11) ///< Invalid Data
#define NRF_ERROR_DATA_SIZE                   (NRF_ERROR_BASE_NUM + 12) ///< Invalid Data size
#define NRF_ERROR_TIMEOUT                     (NRF_ERROR_BASE_NUM + 13) ///< Operation timed out
#define NRF_ERROR_NULL                        (NRF_ERROR_BASE_NUM + 14) ///< Null Pointer
#define NRF_ERROR_FORBIDDEN                   (NRF_ERROR_BASE_NUM + 15) ///< Forbidden Operation
#define NRF_ERROR_INVALID_ADDR                (NRF_ERROR_BASE_NUM + 16) ///< Bad Memory Address
#define NRF_ERROR_BUSY                        (NRF_ERROR_BASE_NUM + 17) ///< Busy
#define NRF_ERROR_CONN_COUNT                  (NRF_ERROR_BASE_NUM + 18) ///< Maximum connection count exceeded.
#define NRF_ERROR_RESOURCES                   (NRF_ERROR_BASE_NUM + 19) ///< Not enough resources for operation
#define NRF_ERROR_INVALID_LICENSE_KEY         (NRF_ERROR_BASE_NUM + 64) ///< Bad license key


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

#endif // NRF_ERROR_H__