//	Author: Gabriel Rodgers
//	Date: 8/1/2024
//	Purpose: To get the LD2 on the Nucleo-L476RG to turn on. 

#include <stdint.h>

#define GPIOA 0x48000000
#define RCC 0x40021000

#define GPIOA_ODR (*((volatile uint32_t *) GPIOA + 0x14))
#define GPIOA_MODER (*((volatile uint32_t *) GPIOA))
#define GPIOA_OTYPER (*((volatile uint32_t *) GPIOA + 0x04))
#define GPIOA_OSPEEDR (*((volatile uint32_t *) GPIOA + 0x08))
#define GPIOA_PUPDR (*((volatile uint32_t *) GPIOA + 0x0C))
#define GPIOA_BSRR (*((volatile uint32_t *) GPIOA + 0x18))

//define the first register in the RCC memory section
//this method directly dereferences the memory itself to access the registers
#define RCC_CR (*((volatile uint32_t *) RCC)) 	//sysclk config
#define RCC_CFGR (*((volatile uint32_t *) RCC + 0x08))	//clk config
#define RCC_AHB1ENR (*((volatile uint32_t *) RCC + 0x48))	//clk enable for peripherals
#define RCC_AHB2ENR (*((volatile uint32_t *) RCC + 0x4C))	//clk enable for peripherals
#define RCC_APB1ENR1 (*((volatile uint32_t *) RCC + 0x58))	//clk enable for peripherals
#define RCC_CCIPR (*((volatile uint32_t *) RCC + 0x88))		//clk config for peripherals


void led_on(void){

	//set LED pin (GPIOA pin 5) to be general purpose output mode
	GPIOA_MODER |= (1 << 10);
	GPIOA_MODER &= ~(1 << 11);

	//set LED pin to be Z (floating) so that led stays on
	//GPIOA_PUPDR &= ~(1 << 11);
	//GPIOA_PUPDR &= ~(1 << 10);

	GPIOA_OTYPER &= ~(1 << 5); // set PA5 to be push-pull
				   
	GPIOA_ODR |= (1 << 5); // set led ON
	//GPIOA_BSRR |= (1 << 5);

	//const uint32_t second = 1; 
}

int main(void) {
	
	const uint32_t first = 100; 

	//enable clk for peripherals (GPIO Port A)
	RCC_AHB2ENR |= (1 << 0);	

	for(uint32_t i=0; i < 100; i++); 

	led_on();

//	volatile uint32_t val;
//	val = 0;

	while (1) {
		
//		if (val == 1000000) {

//			GPIOA_ODR ^= (1 << 5); // set led ON
//			val = 0;
//		}

//		val++;
	}

	return 0;
}
