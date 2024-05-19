/**
 * @file utils/elf_utils.c
 * @brief A source file for the ELF(Executable and Linkable Format) parser.
 */

#include "elf_utils.h"

void read_elf_header(int fd, Elf64_Ehdr *ehdr) {
    
    // Read the ELF header, then verify that the read was successful
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    if (read(fd, ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // ELF file magic number verification (0x7F followed by ELF(45 4c 46))
    if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
        ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
        ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
        ehdr->e_ident[EI_MAG3] != ELFMAG3) {
        fprintf(stderr, "Not an ELF file\n");
        exit(EXIT_FAILURE);
    }
}

// Specification
// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_layout
void print_elf_header(const Elf64_Ehdr *ehdr) {
    printf("ELF Header specification:\n");
    printf("  Magic:   ");

    for (int index = 0; index < EI_NIDENT; index++)
        printf("%02x ", ehdr->e_ident[index]);

    printf("\n");
    printf("  Class:                             %d\n", ehdr->e_ident[EI_CLASS]);
    printf("  Data:                              %d\n", ehdr->e_ident[EI_DATA]);
    printf("  Version:                           %d\n", ehdr->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %d\n", ehdr->e_ident[EI_OSABI]);
    printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %d\n", ehdr->e_type);
    printf("  Machine:                           %d\n", ehdr->e_machine);
    printf("  Version:                           0x%x\n", ehdr->e_version);
    printf("  Entry point address:               0x%lx\n", ehdr->e_entry);
    printf("  Start of program headers:          %ld (bytes into file)\n", ehdr->e_phoff);
    printf("  Start of section headers:          %ld (bytes into file)\n", ehdr->e_shoff);
    printf("  Flags:                             0x%x\n", ehdr->e_flags);
    printf("  Size of this header:               %d (bytes)\n", ehdr->e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", ehdr->e_phentsize);
    printf("  Number of program headers:         %d\n", ehdr->e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", ehdr->e_shentsize);
    printf("  Number of section headers:         %d\n", ehdr->e_shnum);
    printf("  Section header string table index: %d\n", ehdr->e_shstrndx);
}
