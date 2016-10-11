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

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    uint32_t i;
    /* Configure LED-pins as outputs. */
    NRF_GPIO->PIN_CNF[19] = (GPIO_PIN_CNF_DIR_Output       << GPIO_PIN_CNF_DIR_Pos)
                          | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos)
                          | (GPIO_PIN_CNF_PULL_Disabled    << GPIO_PIN_CNF_PULL_Pos)
                          | (GPIO_PIN_CNF_DRIVE_S0S1       << GPIO_PIN_CNF_DRIVE_Pos)
                          | (GPIO_PIN_CNF_SENSE_Disabled   << GPIO_PIN_CNF_SENSE_Pos);

    /* Toggle LEDs. */
    while (true)
    {
        uint32_t gpio_state = NRF_GPIO->OUT;      \
        NRF_GPIO->OUTSET = ((1<<19) & ~gpio_state); \
        NRF_GPIO->OUTCLR = ((1<<19) & gpio_state);
        i=1000000;
        while(i-- != 0);
    }
}

/**
 *@}
 **/
