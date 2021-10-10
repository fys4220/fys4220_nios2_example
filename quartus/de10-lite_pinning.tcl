# de10-lite_pinning.tcl

# Dedicated FPGA clock pin for 50 MHz clock
set_location_assignment PIN_P11 -to clk

# key0 - used as reset
set_location_assignment PIN_B8 -to arst_n

#To avoid that the FPGA is driving an unintended value on pins that are not in use:
set_global_assignment -name RESERVE_ALL_UNUSED_PINS "AS INPUT TRI-STATED"