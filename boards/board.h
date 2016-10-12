#ifndef NRF_BOARD_H__
#define NRF_BOARD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


void nrf_board_init(void);
void nrf_board_led_on(uint32_t led_number);
void nrf_board_led_off(uint32_t led_number);


#ifdef __cplusplus
}
#endif

#endif // NRF_BOARD_H__
