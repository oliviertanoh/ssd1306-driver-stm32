#include "i2c.h"

void i2c_init(void){

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

    // Send the slave address with the write bit (0)
    I2C1_DR = (addr << 1) ;

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

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 2)); // wait for the byte transfer to be finished
    GOTO_ERROR_NON_SUCCESS(check_result);

    // Stop data sending
    I2C1_CR1 |= (1U << 9) ;

    result = true ;
error :
    return result ;
}


i2c_status_t i2c_is_device_ready(uint32_t addr){

    i2c_status_t result = I2C_ERROR_UNKNOWN ;
    bool check_result = false ;

    I2C1_CR1 |= (1U << 8) ; // Start condition

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 0)) ;
    GOTO_ERROR_NON_SUCCESS(check_result);

    I2C1_DR = (addr << 1) | 0;  // send address with write bit (0)

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 1) | (1U << 10));

    if (!check_result) {
        result = I2C_ERROR_TIMEOUT;  // timeout occurred
        goto error ;
    }

    if (I2C1_SR1 & (1U << 1)) {
        (void)I2C1_SR2;    // device present
    } else {
        I2C1_SR1 &= ~(1U << 10);
        result = I2C_ERROR_NACK;  // device absent
        goto error ;
    }

    I2C1_CR1 |= (1U << 9) ; // Stop data sending

    result = I2C_OK ;
error :
    return result ;
}


bool i2c_read(uint32_t addr, uint8_t* data, uint32_t size_data){

    bool result = false ;
    bool check_result = false ;

    I2C1_CR1 |= (1U << 8) ; // Start condition

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 0)) ;
    GOTO_ERROR_NON_SUCCESS(check_result) ;

    I2C1_DR = (addr << 1) | 1 ;

    check_result = i2c_wait_flag(&I2C1_SR1, (1U << 1)) ;
    GOTO_ERROR_NON_SUCCESS(check_result) ;

    (void)I2C1_SR2;

    I2C1_CR1 |= (1U << 10) ; // Set ACK bit to 1

    for (uint32_t i = 0 ; i < size_data ; i++){

        check_result = i2c_wait_flag(&I2C1_SR1, (1U << 6));
        GOTO_ERROR_NON_SUCCESS(check_result);

        // Set ACK bit to 1 to acknowledge before receiving the last byte
        if (i == size_data - 1) {
            I2C1_CR1 &= ~(1U << 10) ; // Clear ACK bit
            I2C1_CR1 |= (1U << 9) ; // Stop data sending
        }

        //Read data
        data[i] = I2C1_DR ;

    }

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

bool delay (volatile uint32_t count){
    while (count --);
    return true ;
}