#!/bin/bash
g++ -std=c++11 code/main.cpp code/automato.cpp code/determinimiza.cpp code/lexica.cpp code/utilidades.cpp -Wall -O2
time ./a.out
