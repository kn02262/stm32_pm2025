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


int __attribute((noreturn)) main(void) {

rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
rcc_periph_clock_enable(RCC_GPIOC);
gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
while (1) {
		 delay(10000000); // Эту функцию мы писали ранее (utils) 
		gpio_toggle(GPIOC, GPIO13);
   }

}
