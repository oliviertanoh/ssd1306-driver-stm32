#include "i2c.h"



void init_i2c(void){

    // Enable clock for GPIOB and I2C1
    RCC_APB2ENR |= RCC_APB2ENR_IOPBEN ;
    RCC_APB1ENR |= RCC_APB1ENR_I2C1EN ;

    // Configure PB6  mode alternative function mode and drain-open mode (50 Mhz)
    GPIOB_CRL &= ~(0xF << 24) ;
    GPIOB_CRL |= (0xF << 24) ;
    // Configure PB7  mode alternative function mode and drain-open mode (50 Mhz)
    GPIOB_CRL &= ~(0xF << 28) ;
    GPIOB_CRL |= (0xF << 28) ;

    // Disable the I2C peripheral before configuring it
    I2C1_CR1 &= ~(1U << 0) ;

    // Set the peripheral clock frequency in MHz (assuming APB1 clock is 36 MHz)
    I2C1_CR2 &= ~(0x3F) ;
    I2C1_CR2 |= (36U) ;

    // Configure standard mode
    I2C1_CCR &= ~(1U << 15);
    // Set 100 Khz for standard mode
    I2C1_CCR &= ~(0xFFF);
    I2C1_CCR |= (180U);
    I2C1_TRISE &= ~(0x3F);
    I2C1_TRISE |= (37U);

    // Enable the I2C peripheral
    I2C1_CR1 |= (1U << 0) ;

}
