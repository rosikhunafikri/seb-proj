#!/bin/bash

g++ ./prototype_v2.cpp -o prototype_v2 -static-libgcc -static-libstdc++


./prototype_v2.exe


python display.py
