#ifndef _DRIVER_I2C_SSD1306_H_
#define _DRIVER_I2C_SSD1306_H_

#include <stdint.h>



//--------------------------------- Register GPIO B
#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL (*(volatile uint32_t *)(GPIOB_BASE + 0x00))





//--------------------------------- Register RCC
#define RCC_BASE 0x40021000
// Define RCC register to enable i2c ports
#define RCC_APB2ENR (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define RCC_APB2ENR_IOPBEN (1U << 3)
// Define RCC register to enable i2c clock
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))
#define RCC_APB1ENR_I2C1EN (1U << 22)


//--------------------------------- Register I2C
#define I2C_BASE 0x40005400
// I2C1 register addresses with base address 0x40005400 and offsets for each register
#define I2C1_CR1 (*(volatile uint32_t*)(I2C_BASE + 0x00))
#define I2C1_CR2 (*(volatile uint32_t*)(I2C_BASE + 0x04))
#define I2C1_OAR1 (*(volatile uint32_t*)(I2C_BASE + 0x08))
#define I2C1_OAR2 (*(volatile uint32_t*)(I2C_BASE + 0x0C))
#define I2C1_DR (*(volatile uint32_t*)(I2C_BASE + 0x10))
#define I2C1_SR1 (*(volatile uint32_t*)(I2C_BASE + 0x14))
#define I2C1_SR2 (*(volatile uint32_t*)(I2C_BASE + 0x18))
#define I2C1_CCR (*(volatile uint32_t*)(I2C_BASE + 0x1C))
#define I2C1_TRISE (*(volatile uint32_t*)(I2C_BASE + 0x20))






#endif /* _DRIVER_I2C_SSD1306_H_ */