/*
 * BSD licence
 */

#include <stdint.h>
#include "nrf_nvic.h"
#include "compiler_abstraction.h"

void nrf_nvic_default_handler(void);

__STATIC nrf_nvic_irq_handler_t m_irq_handlers[NRF_NVIC_IRQHandler_MAX] = {nrf_nvic_default_handler};

void nrf_nvic_default_handler(void)
{
    return;
}

void POWER_CLOCK_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_POWER_CLOCK_IRQHandler]();
}

void RADIO_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_RADIO_IRQHandler]();
}

void GPIOTE_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_GPIOTE_IRQHandler]();
}

void TIMER0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_TIMER0_IRQHandler]();
}

void TIMER1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_TIMER1_IRQHandler]();
}

void TIMER2_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_TIMER2_IRQHandler]();
}

void RTC0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_RTC0_IRQHandler]();
}

void TEMP_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_TEMP_IRQHandler]();
}

void RNG_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_RNG_IRQHandler]();
}

void ECB_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_ECB_IRQHandler]();
}

void CCM_AAR_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_CCM_AAR_IRQHandler]();
}

void WDT_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_WDT_IRQHandler]();
}

void RTC1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_RTC1_IRQHandler]();
}

void QDEC_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_QDEC_IRQHandler]();
}

#if ((NRF_MCU == NRF51822) || (NRF_MCU == NRF51422) || (NRF_MCU == NRF51802))
void UART0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_UART0_IRQHandler]();
}

void SPI0_TWI0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SPI0_TWI0_IRQHandler]();
}

void SPI1_TWI1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SPI1_TWI1_IRQHandler]();
}

void ADC_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_ADC_IRQHandler]();
}

void LPCOMP_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_LPCOMP_IRQHandler]();
}

void SWI0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI0_IRQHandler]();
}

void SWI1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI1_IRQHandler]();
}

void SWI2_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI2_IRQHandler]();
}

void SWI3_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI3_IRQHandler]();
}

void SWI4_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI4_IRQHandler]();
}

void SWI5_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI5_IRQHandler]();
}

#elif (NRF_MCU == NRF52832)
void UARTE0_UART0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_UARTE0_UART0_IRQHandler]();
}

void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler]();
}

void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler]();
}

void NFCT_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_NFCT_IRQHandler]();
}

void SAADC_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SAADC_IRQHandler]();
}

void COMP_LPCOMP_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_COMP_LPCOMP_IRQHandler]();
}

void SWI0_EGU0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI0_EGU0_IRQHandler]();
}

void SWI1_EGU1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI1_EGU1_IRQHandler]();
}

void SWI2_EGU2_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI2_EGU2_IRQHandler]();
}

void SWI3_EGU3_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI3_EGU3_IRQHandler]();
}

void SWI4_EGU4_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI4_EGU4_IRQHandler]();
}

void SWI5_EGU5_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SWI5_EGU5_IRQHandler]();
}

void TIMER3_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_TIMER3_IRQHandler]();
}

void TIMER4_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_TIMER4_IRQHandler]();
}

void PWM0_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_PWM0_IRQHandler]();
}

void PDM_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_PDM_IRQHandler]();
}

void MWU_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_MWU_IRQHandler]();
}

void PWM1_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_PWM1_IRQHandler]();
}

void PWM2_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_PWM2_IRQHandler]();
}

void SPIM2_SPIS2_SPI2_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_SPIM2_SPIS2_SPI2_IRQHandler]();
}

void RTC2_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_RTC2_IRQHandler]();
}

void I2S_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_I2S_IRQHandler]();
}

void FPU_IRQHandler(void)
{
    m_irq_handlers[NRF_NVIC_FPU_IRQHandler]();
}

#endif

__STATIC_INLINE void nrf_nvic_register(nrf_nvic_irq_t irq, nrf_nvic_irq_handler_t p_function)
{
    m_irq_handlers[irq] = p_function;
}
