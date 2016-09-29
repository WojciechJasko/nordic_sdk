#ifndef NRF_CORE_H__
#define NRF_CORE_H__

#include "mcu/compiler_abstraction.h"

#if defined(NRF51822)

    #include "mcu/nrf51.h"
    #include "mcu/nrf51_bitfields.h"
    #include "mcu/nrf51822_peripherals.h"
    #include "mcu/nrf51822_errata.h"

    #define NRF_IRQ_COUNT      41

#elif defined(NRF51422)

    #include "mcu/nrf51.h"
    #include "mcu/nrf51_bitfields.h"
    #include "mcu/nrf51422_peripherals.h"
    #include "mcu/nrf51422_errata.h"

    #define NRF_IRQ_COUNT      41

#elif defined(NRF51802)

    #include "mcu/nrf51.h"
    #include "mcu/nrf51_bitfields.h"
    #include "mcu/nrf51802_peripherals.h"
    #include "mcu/nrf51802_errata.h"

    #define NRF_IRQ_COUNT      41

#elif defined(NRF52832)

    #include "mcu/nrf52.h"
    #include "mcu/nrf52_bitfields.h"
    #include "mcu/nrf52832_peripherals.h"
    #include "mcu/nrf52832_errata.h"

    #define NRF_IRQ_COUNT      54

#else

#error "No platform defined"

#endif

#endif // NRF_CORE_H__
