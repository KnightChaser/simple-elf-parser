#!/bin/bash

gcc -o elf_parser main.c utils/*.c
./elf_parser ./elf_parser