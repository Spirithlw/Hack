#!/bin/bash

g++ -c keygen.cpp
g++ keygen.o -o keygen-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio