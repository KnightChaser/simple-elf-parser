/**
 * @file utils/elf_header_const.h
 * @brief A header file of constants(numerical value - stringified meaningful constant) for the ELF header.
 */
//

#ifndef ELF_HEADER_CONST_H
#define ELF_HEADER_CONST_H

#include <stdio.h>
#include <elf.h>

char* get_const_str_EI_CLASS(int value);             // EI_CLASS (File class)
char* get_const_str_EI_DATA(int value);              // EI_DATA (Data encoding)
char* get_const_str_EI_VERSION(int value);           // EI_VERSION (File version)
char* get_const_str_EI_OSABI(int value);             // EI_OSABI (Operating system/ABI)
char* get_const_str_E_TYPE(int value);               // e_type (Object file type)
char* get_const_str_E_MACHINE(int value);            // e_machine (Architecture)

#endif // ELF_HEADER_CONST_H