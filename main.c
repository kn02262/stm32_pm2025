#include <stdint.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencmsis/core_cm3.h>

void delay(uint32_t ticks) {
	for (int i=0; i<ticks; i++) {
		__asm("nop");
	}
}

void TIM2_IRQHandler(void) {
//void tim2_isr(void) {
   gpio_toggle(GPIOC, GPIO13);
   timer_clear_flag(TIM2, TIM_SR_UIF);
}

int __attribute((noreturn)) main(void) {
rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
rcc_periph_clock_enable(RCC_GPIOC);
gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

rcc_periph_clock_enable(RCC_TIM2);
rcc_periph_reset_pulse(RST_TIM2);
timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
timer_set_prescaler(TIM2, 719);
timer_disable_preload(TIM2);
timer_set_period(TIM2, 50000);
timer_enable_irq(TIM2, TIM_DIER_UIE);

nvic_enable_irq(NVIC_TIM2_IRQ);
nvic_clear_pending_irq(NVIC_TIM2_IRQ);
timer_enable_counter(TIM2);

while (1) {__asm volatile ("nop");}

}
