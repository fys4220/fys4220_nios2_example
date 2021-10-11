#include <stdio.h>
#include "system.h" //access Nios II system info
#include "io.h" //access to IORD and IORW
#include "unistd.h" //access to usleep
#include "altera_avalon_pio_regs.h" //access to PIO macros

int main(){
    printf("Hello, World!\n");
    int sw_data = 1;
    while(1){
        //Access registers using IORD and IOWR from io.h
        sw_data = IORD(PIO_SW_BASE,0);
        IOWR(PIO_LED_BASE,0,sw_data);
        
        //Alternative solution using PIO macros
        //sw_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_SW_BASE);
        //IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,sw_data);

        usleep(100000); //sleep 100 us

    }
    return 0;
}