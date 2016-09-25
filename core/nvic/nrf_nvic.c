/*
 * BSD licence
 */

#include <stdint.h>
#include "nrf_nvic.h"
#include "compiler_abstraction.h"

/**
  * @brief Macro for counting offset in IRQ array. -15 is reset handler and is casting to zero in
  * array in this module.
  */
#define IRQ_ARRAY_OFFSET_GET(irq) (irq + 15)

void nrf_nvic_default_handler(void);

__STATIC nrf_nvic_irq_handler_t m_irq_handlers[NRF_IRQ_COUNT] = {nrf_nvic_default_handler};

void nrf_nvic_default_handler(void)
{
    return;
}

void POWER_CLOCK_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(POWER_CLOCK_IRQn)]();
}

void RADIO_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(RADIO_IRQHandler]();
}

void GPIOTE_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(GPIOTE_IRQHandler)]();
}

void TIMER0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(TIMER0_IRQHandler)]();
}

void TIMER1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(TIMER1_IRQHandler)]();
}

void TIMER2_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(TIMER2_IRQHandler)]();
}

void RTC0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(RTC0_IRQHandler)]();
}

void TEMP_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(TEMP_IRQHandler)]();
}

void RNG_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(RNG_IRQHandler)]();
}

void ECB_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(ECB_IRQHandler)]();
}

void CCM_AAR_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(CCM_AAR_IRQHandler)]();
}

void WDT_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(WDT_IRQHandler)]();
}

void RTC1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(RTC1_IRQHandler)]();
}

void QDEC_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(QDEC_IRQHandler)]();
}

#if ((NRF_MCU == NRF51822) || (NRF_MCU == NRF51422) || (NRF_MCU == NRF51802))
void UART0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(UART0_IRQHandler)]();
}

void SPI0_TWI0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SPI0_TWI0_IRQHandler)]();
}

void SPI1_TWI1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SPI1_TWI1_IRQHandler)]();
}

void ADC_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(ADC_IRQHandler)]();
}

void LPCOMP_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(LPCOMP_IRQHandler)]();
}

void SWI0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI0_IRQHandler)]();
}

void SWI1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI1_IRQHandler)]();
}

void SWI2_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI2_IRQHandler)]();
}

void SWI3_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI3_IRQHandler)]();
}

void SWI4_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI4_IRQHandler)]();
}

void SWI5_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI5_IRQHandler)]();
}

#elif (NRF_MCU == NRF52832)
void UARTE0_UART0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(UARTE0_UART0_IRQHandler)]();
}

void SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQHandler)]();
}

void SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQHandler)]();
}

void NFCT_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(NFCT_IRQHandler)]();
}

void SAADC_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SAADC_IRQHandler)]();
}

void COMP_LPCOMP_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(COMP_LPCOMP_IRQHandler)]();
}

void SWI0_EGU0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI0_EGU0_IRQHandler)]();
}

void SWI1_EGU1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI1_EGU1_IRQHandler)]();
}

void SWI2_EGU2_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI2_EGU2_IRQHandler)]();
}

void SWI3_EGU3_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI3_EGU3_IRQHandler)]();
}

void SWI4_EGU4_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI4_EGU4_IRQHandler)]();
}

void SWI5_EGU5_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SWI5_EGU5_IRQHandler)]();
}

void TIMER3_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(TIMER3_IRQHandler)]();
}

void TIMER4_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(TIMER4_IRQHandler)]();
}

void PWM0_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(PWM0_IRQHandler)]();
}

void PDM_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(PDM_IRQHandler)]();
}

void MWU_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(MWU_IRQHandler)]();
}

void PWM1_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(PWM1_IRQHandler)]();
}

void PWM2_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(PWM2_IRQHandler)]();
}

void SPIM2_SPIS2_SPI2_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(SPIM2_SPIS2_SPI2_IRQHandler)]();
}

void RTC2_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(RTC2_IRQHandler)]();
}

void I2S_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(I2S_IRQHandler)]();
}

void FPU_IRQHandler(void)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(FPU_IRQHandler)]();
}

#endif

__WEAK void nrf_nvic_register(IRQn_Type irq, nrf_nvic_irq_handler_t p_function)
{
    m_irq_handlers[IRQ_ARRAY_OFFSET_GET(irq)] = p_function;
}
