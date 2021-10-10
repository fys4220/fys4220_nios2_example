#!/bin/bash
nios2-app-generate-makefile.exe --bsp-dir app_bsp --src-dir app --app-dir app
cd app 
make 
cd ..
