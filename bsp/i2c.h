#ifndef _DRIVER_I2C_SSD1306_H_
#define _DRIVER_I2C_SSD1306_H_

#include <stdint.h>
#include <stdbool.h>

#define GOTO_ERROR_NON_SUCCESS(success) \
do {                                \
    if (!(success)) goto error ;    \
} while (0)


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

void i2c_init(void) ;
bool i2c_write(uint32_t addr, uint8_t* data, uint32_t len);
bool i2c_read(uint32_t addr, uint8_t* data, uint32_t size_data);
bool i2c_is_device_ready(uint32_t addr);
bool i2c_write_read(uint32_t addr, uint8_t* data_write, uint32_t size_write, uint8_t* data_read, uint32_t size_read);
bool i2c_wait_flag(volatile uint32_t* register_bit, uint32_t flag_mask);


typedef enum {
    I2C_OK = 0,
    I2C_ERROR_BUSY,
    I2C_ERROR_TIMEOUT,
    I2C_ERROR_NACK,
    I2C_ERROR_BUS,
    I2C_ERROR_UNKNOWN,
} i2c_status_t;

typedef enum{
    I2C_MASTER_TRANSMITTER,
    I2C_MASTER_RECIVER,
    I2C_SLAVE_TRANSMITTER,
    I2C_SLAVE_RECIVER,
} i2c_mode_t ;

#endif /* _DRIVER_I2C_SSD1306_H_ */