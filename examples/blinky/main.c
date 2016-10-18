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

/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_core.h"

#define LED_RED 21

void nrf_board_init(void)
{
    NRF_GPIO->PIN_CNF[LED_RED] = (GPIO_PIN_CNF_DIR_Output   << GPIO_PIN_CNF_DIR_Pos)
                          | (GPIO_PIN_CNF_INPUT_Disconnect  << GPIO_PIN_CNF_INPUT_Pos)
                          | (GPIO_PIN_CNF_PULL_Disabled     << GPIO_PIN_CNF_PULL_Pos)
                          | (GPIO_PIN_CNF_DRIVE_S0S1        << GPIO_PIN_CNF_DRIVE_Pos)
                          | (GPIO_PIN_CNF_SENSE_Disabled    << GPIO_PIN_CNF_SENSE_Pos);
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

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    uint32_t i;
    /* Configure LED-pins as outputs. */
    nrf_board_init();

    /* Toggle LEDs. */
    while (true)
    {
        nrf_board_led_invert(0);
        i=1000000;
        while(i-- != 0);
    }
}

/**
 *@}
 **/
