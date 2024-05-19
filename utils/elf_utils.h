/**
 * @file utils/elf_utils.h
 * @brief A header file for the ELF(Executable and Linkable Format) parser.
 */
//

#ifndef ELF_UTILS_H
#define ELF_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void read_elf_header(int fd, Elf64_Ehdr *ehdr);
void print_elf_header(const Elf64_Ehdr *ehdr);

#endif // ELF_UTILS_H