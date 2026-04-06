#include "i2c.h"
#include <stdio.h>


int main(void) {

    init_i2c() ;

    uint8_t data[] = {0x00, 0x01, 0x02} ;

    bool result = i2c_write(0x3C, data, sizeof(data)) ;
    
    printf("I2C write result: %s\n", result ? "Success" : "Failure") ;


    while (1) ;
}