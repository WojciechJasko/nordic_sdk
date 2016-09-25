#ifndef NRF_CORE_H__
#define NRF_CORE_H__

#define NRF51822    51822
#define NRF51422    51422
#define NRF51802    51802
#define NRF52832    52832

#include "mcu/compiler_abstraction.h"

#if (NRF_MCU == NRF51822)

    #include "mcu/nrf51.h"
    #include "mcu/nrf51_bitfields.h"
    #include "mcu/nrf51822_peripherals.h"
    #include "mcu/nrf51822_errata.h"

#elif (NRF_MCU == NRF51422)

    #include "mcu/nrf51.h"
    #include "mcu/nrf51_bitfields.h"
    #include "mcu/nrf51422_peripherals.h"
    #include "mcu/nrf51422_errata.h"

#elif (NRF_MCU == NRF51802)

    #include "mcu/nrf51.h"
    #include "mcu/nrf51_bitfields.h"
    #include "mcu/nrf51802_peripherals.h"
    #include "mcu/nrf51802_errata.h"

#elif (NRF_MCU == NRF52832)

    #include "mcu/nrf52.h"
    #include "mcu/nrf52_bitfields.h"
    #include "mcu/nrf52832_peripherals.h"
    #include "mcu/nrf52832_errata.h"

#endif

#endif // NRF_CORE_H__
