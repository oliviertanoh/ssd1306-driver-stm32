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

bool i2c_write(uint32_t addr, uint8_t* data, uint32_t len){

    bool result = false ;
    bool check_result = false ;

    // Start data sending
    I2C1_CR1 |= (1U << 8) ;

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 0)) ;
    GOTO_ERROR_NON_SUCCESS(check_result) ;

    I2C1_DR = (addr << 1) ; // Write mode

    check_result = i2c_wait_flag(&I2C1_SR1, (1 << 1)) ;
    GOTO_ERROR_NON_SUCCESS(check_result);

    // Lire le registre SR2
    (void)I2C1_SR2 ;

    // Wait for the address to be sent
    check_result = i2c_wait_flag(&I2C1_SR1, 1U << 7) ;
    GOTO_ERROR_NON_SUCCESS(check_result) ;

    for (uint32_t i = 0; i < len; i++){

        I2C1_DR = data[i] ; // Command mode

        // Wait for the data to be transmitted
        check_result = i2c_wait_flag(&I2C1_SR1, (1U << 7)) ;
        GOTO_ERROR_NON_SUCCESS(check_result) ;
    }

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 2)); // attendre BTF=1
    GOTO_ERROR_NON_SUCCESS(check_result);

    // Stop data sending
    I2C1_CR1 |= (1U << 9) ;

    result = true ;
error :
    return result ;

}

bool i2c_wait_flag(volatile uint32_t* register_bit, uint32_t flag_mask){

    bool result = false ;
    uint32_t  timeout = 1000 ;

    while ( !(*register_bit & flag_mask)){

        timeout -- ;
        if (timeout == 0)  goto error ;
    }

    result = true ;

error :
    return result ;

}
