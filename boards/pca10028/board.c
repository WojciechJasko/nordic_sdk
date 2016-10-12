#include "board.h"
#include "board_config.h"
#include "nrf_core.h"

void nrf_board_init(void)
{
    NRF_GPIO->PIN_CNF[LED_RED] = (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)
                          | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                          | (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)
                          | (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos)
                          | (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos);
}

void nrf_board_led_on(uint32_t led_number)
{
    NRF_GPIO->OUTSET = (1<<LED_RED);
}

void nrf_board_led_off(uint32_t led_number)
{
    NRF_GPIO->OUTCLR = (1<<LED_RED);
}

void nrf_board_led_invert(uint32_t led_number)
{
    uint32_t gpio_state = NRF_GPIO->OUT;
    NRF_GPIO->OUTSET = ((1<<LED_RED) & ~gpio_state);
    NRF_GPIO->OUTCLR = ((1<<LED_RED) & gpio_state);
}
