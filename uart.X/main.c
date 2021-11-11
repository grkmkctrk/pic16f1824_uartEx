

#include "mcc_generated_files/mcc.h"
#include <string.h>

void uartw(uint8_t data){
    while(0 == PIR1bits.TXIF);
    TXREG = data;
}

void uartW(uint8_t* data){
    size_t size = strlen((char*) data);
    if(size > 1){
        for (
                int i = 0; 
                i < size; 
                uartw(*data++), TXREG = *data, i++
            );
    }else{
        while(0 == PIR1bits.TXIF);
        TXREG = *data;
    }
}

void uartWln(uint8_t* data){
    uartW(data);
    uartW("\n\r");
}

void main(void)
{
    volatile uint8_t rxData;
    // Initialize the device
    SYSTEM_Initialize();

    uartWln("Hi!"); // initial
    while(1)
    {
        if(EUSART_is_rx_ready()) // ready to receive
        {
            rxData = EUSART_Read(); // read data
            if(EUSART_is_tx_ready()) // ready to transmit
            {   
                uartW("Your choice is : (3 to light led)"); uartWln(&rxData);
                if(rxData == '3') uartLed_SetHigh();
                else uartLed_SetLow();
            }
        }
    }
}
/**
 End of File
*/