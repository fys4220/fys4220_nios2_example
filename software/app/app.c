#include <stdio.h>
#include "system.h" //access Nios II system info
#include "io.h" //access to IORD and IORW
#include "unistd.h" //access to usleep
#include "altera_avalon_pio_regs.h" //access to PIO macros
#include <sys/alt_irq.h> // access to the IRQ routines

/* Declare a global variable to holds the edge capture value
Declaring a variable as volatile tells the compiler that
the value of the variable may change at any time without
any action being taken by the code the compiler finds nearby.
This variable will be connected to the interrupt register which
is controlled from HW and not SW. The compile will therefor not
find any code that controls this variable, and if not declared as
volatile, the compile may decided to optimize and remove this variable. */
volatile int edge_capture;

/* This is the ISR which will be called when the system signals an interrupt. */
static void handle_interrupts(void* context)
{   
    //Cast context to edge_capture's type
	//Volatile to avoid compiler optimization
    //this will point to the edge_capture variable.
	volatile int* edge_capture_ptr = (volatile int*) context;

	//Read the edge capture register on the PIO and store the value
    //The value will be stored in the edge_capture variable and accessible
    //from other parts of the code.
	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_IRQ_BASE);

	//Write to edge capture register to reset it
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_IRQ_BASE,0);

}

/* This function is used to initializes and registers the interrupt handler. */
static void init_interrupt_pio()
{
	//Recast the edge_capture point to match the
	//alt_irq_register() function prototypo
	void* edge_capture_ptr = (void*)&edge_capture;

	//Enable a single interrupt input by writing a one to the corresponding interruptmask bit locations
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_IRQ_BASE,0x1);

	//Reset the edge capture register
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_IRQ_BASE,0);

	//Register the interrupt handler in the system
    //The ID and PIO_IRQ number is available from the system.h file.
	alt_ic_isr_register(PIO_IRQ_IRQ_INTERRUPT_CONTROLLER_ID,
			PIO_IRQ_IRQ, handle_interrupts, edge_capture_ptr, 0x0);

    /* In order to keep the impact of interrupts on the execution of the main program to a minimum,
    it is important to keep interrupt routines short. If additional processing is necessary for a
    particular interrupt, it is better to do this outside of the ISR. E.g., checking the value
    of the edge_capture variable.*/

}


int main(){
    printf("Hello, World!\n");
    int sw_data = 1;

    // Initialize the interrupt
    init_interrupt_pio();
    
    while(1){
        //Access registers using IORD and IOWR from io.h
        sw_data = IORD(PIO_SW_BASE,0);
        IOWR(PIO_LED_BASE,0,sw_data);
        
        //Alternative solution using PIO macros
        //sw_data = IORD_ALTERA_AVALON_PIO_DATA(PIO_SW_BASE);
        //IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,sw_data);

        // When an interrupt event has occurred, the edge_capture variable has been updated
        // Poll the edge capture variable check for interrupt
	     if (edge_capture == 0x1) //bit position 0 corresponds to button press
	    {
		    printf("Interrupt detected, Key1 was pressed!\n");
		    edge_capture = 0; // reset variable to "unregister" event
	    }
        
        usleep(100000); //sleep 100 us

    }
    return 0;
}