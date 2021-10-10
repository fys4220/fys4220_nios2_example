#!/bin/bash
nios2-bsp hal app_bsp ../quartus/nios2_system.sopcinfo
cd app_bsp
make 
cd ..
