#!/bin/bash

echo "Enter quartus folder to create and compile Quartus project"
cd Quartus
# Create project
quartus_sh -t create_project.tcl
# Compile project
quartus_sh --flow compile system_top
cd ..
echo "Enter software folder to generate and compile BSP and application"
cd software
bash create_bsp.sh
bash create_app.sh 
cd ..


