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
#include "board.h"

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
