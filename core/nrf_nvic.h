/*
 * BSD licence
 */

#ifndef NRF_NVIC_H__
#define NRF_NVIC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NRF_NVIC_POWER_CLOCK_IRQHandler,
    NRF_NVIC_RADIO_IRQHandler,
    NRF_NVIC_GPIOTE_IRQHandler,
    NRF_NVIC_TIMER0_IRQHandler,
    NRF_NVIC_TIMER1_IRQHandler,
    NRF_NVIC_TIMER2_IRQHandler,
    NRF_NVIC_RTC0_IRQHandler,
    NRF_NVIC_TEMP_IRQHandler,
    NRF_NVIC_RNG_IRQHandler,
    NRF_NVIC_ECB_IRQHandler,
    NRF_NVIC_CCM_AAR_IRQHandler,
    NRF_NVIC_WDT_IRQHandler,
    NRF_NVIC_RTC1_IRQHandler,
    NRF_NVIC_QDEC_IRQHandler,

#if ((NRF_MCU == NRF51822) || (NRF_MCU == NRF51422) || (NRF_MCU == NRF51802))
    NRF_NVIC_UART0_IRQHandler,
    NRF_NVIC_SPI0_TWI0_IRQHandler,
    NRF_NVIC_SPI1_TWI1_IRQHandler,
    NRF_NVIC_ADC_IRQHandler,
    NRF_NVIC_LPCOMP_IRQHandler,
    NRF_NVIC_SWI0_IRQHandler,
    NRF_NVIC_SWI1_IRQHandler,
    NRF_NVIC_SWI2_IRQHandler,
    NRF_NVIC_SWI3_IRQHandler,
    NRF_NVIC_SWI4_IRQHandler,
    NRF_NVIC_SWI5_IRQHandler,

#elif (NRF_MCU == NRF52832)
    NRF_NVIC_UARTE0_UART0_IRQHandler,
    NRF_NVIC_SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler,
    NRF_NVIC_SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler,
    NRF_NVIC_NFCT_IRQHandler,
    NRF_NVIC_SAADC_IRQHandler,
    NRF_NVIC_COMP_LPCOMP_IRQHandler,
    NRF_NVIC_SWI0_EGU0_IRQHandler,
    NRF_NVIC_SWI1_EGU1_IRQHandler,
    NRF_NVIC_SWI2_EGU2_IRQHandler,
    NRF_NVIC_SWI3_EGU3_IRQHandler,
    NRF_NVIC_SWI4_EGU4_IRQHandler,
    NRF_NVIC_SWI5_EGU5_IRQHandler,
    NRF_NVIC_TIMER3_IRQHandler,
    NRF_NVIC_TIMER4_IRQHandler,
    NRF_NVIC_PWM0_IRQHandler,
    NRF_NVIC_PDM_IRQHandler,
    NRF_NVIC_MWU_IRQHandler,
    NRF_NVIC_PWM1_IRQHandler,
    NRF_NVIC_PWM2_IRQHandler,
    NRF_NVIC_SPIM2_SPIS2_SPI2_IRQHandler,
    NRF_NVIC_RTC2_IRQHandler,
    NRF_NVIC_I2S_IRQHandler,
    NRF_NVIC_FPU_IRQHandler,

#endif
    NRF_NVIC_IRQHandler_MAX
} nrf_nvic_irq_t;

typedef void (*nrf_nvic_irq_handler_t)(void);

void nrf_nvic_register(nrf_nvic_irq_t irq, nrf_nvic_irq_handler_t p_function);

#ifdef __cplusplus
}
#endif

#endif // NRF_NVIC_H__
