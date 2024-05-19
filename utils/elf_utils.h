/**
 * @file utils/elf_utils.h
 * @brief A header file for the ELF(Executable and Linkable Format) parser.
 */
//

#ifndef ELF_UTILS_H
#define ELF_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void    read_elf_header(int fd, Elf64_Ehdr *ehdr);                                                                     // Read & validate the ELF header
void    print_elf_header(const Elf64_Ehdr *ehdr);                                                                      // Print the ELF header
void    read_section_headers(int fd, const Elf64_Ehdr *ehdr, Elf64_Shdr *shdrs);                                       // Read the section headers
char*   read_section_header_string_table(int fd, const Elf64_Ehdr *ehdr, const Elf64_Shdr *shdrs);                     // Read the section header string table
void    print_section_headers(int fd, const Elf64_Ehdr *ehdr, const Elf64_Shdr *shdr, const char* shstrtab);           // Print the section header (shstrtab = section header string table)

#endif // ELF_UTILS_H