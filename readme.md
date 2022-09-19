# Nios II example project

This is an example project based on the description found in the following 3 exercises:

https://fys4220.github.io/part-exercises/exercises_nios2_example.html

https://fys4220.github.io/part-exercises/exercises_nios2_interrupt.html


To test the code, clone this git repository, start the Nios II command shell en run the *create_and_compile_project.sh* script. This will create and compile the Quartus project, as well as the BSP and application software. Use *nios2-configure-sof* to program the FPGA, *nios2-download* to the application to the Nios II system, and the *nios2-termial* to connect to the system.

```
./create_and_compile_project.sh
nios2-configure-sof quartus/output_files/system_top.sof
nios2-download -g software/app/app.elf
nios2-terminal
```


## Basic system with JTAG UART 
The first development step demonstrates a minimal version including only the CPU, the on-chip memory, and a JTAR UART. A basic "Hello, World!" software application makes use of the JTARG UART to communicate with the host PC. This version of the example is tagged "minimal" and can be viewed here:
https://github.uio.no/FYS4220/fys4220_nios2_example/tree/minimal-v2


Description: https://pages.github.uio.no/fys4220/fys4220/embedded/embedded_nios2_system.html


## Adding PIO cores
To demonstrate reading and writing to memory mapped modules PIO cores were added. The software application was extended to allow the slide switches to turn on and off the LEDs. This part of the development is tagged with "minimal-pio":
https://github.uio.no/FYS4220/fys4220_nios2_example/tree/minimal-pio

Description: https://pages.github.uio.no/fys4220/fys4220/embedded/embedded_memory_mapped_sw.html

## Adding interrupt
Interrupt handling for the Nios II example is demonstrated with a PIO-module connected to one of the push buttons on the DE10-Lite board. The part is tagged with
https://github.uio.no/FYS4220/fys4220_nios2_example/tree/minimal-pio-with-interrupt

Description: https://pages.github.uio.no/fys4220/fys4220/embedded/embedded_interrupt.html
