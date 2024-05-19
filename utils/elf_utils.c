/**
 * @file utils/elf_utils.c
 * @brief A source file for the ELF(Executable and Linkable Format) parser.
 */
//

#include "elf_utils.h"
#include "elf_header_const.h"
#include <elf.h>
#include <stdio.h>

// Read and validate the ELF header
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

// Print the ELF header according to the official ELF header specification
// Specification
// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_layout
void print_elf_header(const Elf64_Ehdr *ehdr) {
    // Read and verify the ELF header first
    printf("ELF Header specification:\n");
    printf("  Magic:   ");

    for (unsigned int index = 0; index < EI_NIDENT; index++)
        printf("%02x ", ehdr->e_ident[index]);

    printf("\n");
    printf("  Class:                             %d (%s)\n", ehdr->e_ident[EI_CLASS], get_const_str_EI_CLASS(ehdr->e_ident[EI_CLASS]));
    printf("  Data:                              %d (%s)\n", ehdr->e_ident[EI_DATA], get_const_str_EI_DATA(ehdr->e_ident[EI_DATA]));
    printf("  Version:                           %d (%s)\n", ehdr->e_ident[EI_VERSION], get_const_str_EI_VERSION(ehdr->e_ident[EI_VERSION]));
    printf("  OS/ABI:                            %d (%s)\n", ehdr->e_ident[EI_OSABI], get_const_str_EI_OSABI(ehdr->e_ident[EI_OSABI]));
    printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);
    printf("  Type:                              %d (%s)\n", ehdr->e_type, get_const_str_E_TYPE(ehdr->e_type));
    printf("  Machine:                           %d (%s)\n", ehdr->e_machine, get_const_str_E_MACHINE(ehdr->e_machine));
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

// Read the section headers
void read_section_headers(int fd, const Elf64_Ehdr *ehdr, Elf64_Shdr *shdrs) {
    // Find(Seek) the section headers and read them
    if (lseek(fd, ehdr->e_shoff, SEEK_SET) < 0) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    size_t shdrs_size = ehdr->e_shnum * sizeof(Elf64_Shdr);             // Section header size is the number of section headers * size of each section header

    // Read the section headers
    if (read(fd, shdrs, shdrs_size) != shdrs_size) {
        perror("read");
        exit(EXIT_FAILURE);
    }
}

// Read the section header string table
char* read_section_header_string_table(int fd, const Elf64_Ehdr *ehdr, const Elf64_Shdr *shdrs) {
    // ehdr     = ELF header
    // shdrs    = section headers
    // shstrtab = section header string table
    // shstrndx = section header string table index (naming sense is so confusing haha)
    char *shstrtab = malloc(shdrs[ehdr->e_shstrndx].sh_size);
    if (!shstrtab) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Find(Seek) the section header string table and read it
    if (lseek(fd, shdrs[ehdr->e_shstrndx].sh_offset, SEEK_SET) < 0) {
        perror("lseek");
        free(shstrtab);
        exit(EXIT_FAILURE);
    }

    // Read the section header string table
    if (read(fd, shstrtab, shdrs[ehdr->e_shstrndx].sh_size) != shdrs[ehdr->e_shstrndx].sh_size) {
        perror("read");
        free(shstrtab);
        exit(EXIT_FAILURE);
    }
    return shstrtab;
}

// Print the section headers according to the specificcation
// Specification
// https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Section_header
void print_section_headers(int fd, const Elf64_Ehdr *ehdr, const Elf64_Shdr *shdrs, const char *shstrtab) {
    printf("Section Headers:\n");
    printf("   Nr | Name                     | size(Bytes) | V.ADDR.      | offset\n");
    printf("===========================================================================\n");
    for (unsigned int index = 0; index < ehdr->e_shnum; index++) {
        char* sh_name = calloc(shdrs[index].sh_size, sizeof(char)); // Section name
        strcpy(sh_name, &shstrtab[shdrs[index].sh_name]);           // Section name
        int sh_type = shdrs[index].sh_type;                         // Section type
        unsigned long sh_flags = shdrs[index].sh_flags;             // Section flags
        unsigned long sh_addr = shdrs[index].sh_addr;               // Section virtual address
        unsigned long sh_offset = shdrs[index].sh_offset;           // Section file offset
        unsigned long sh_size = shdrs[index].sh_size;               // Section size
        unsigned long sh_link = shdrs[index].sh_link;               // Link to another section
        unsigned long sh_info = shdrs[index].sh_info;               // Additional section information
        unsigned long sh_addralign = shdrs[index].sh_addralign;     // Section alignment
        unsigned long sh_entsize = shdrs[index].sh_entsize;         // Entry size if section holds table
        printf("   %2d | %-24s |  %10lu | 0x%010lx | 0x%08lx\n", index, sh_name, sh_size, sh_addr, sh_offset);
    }
}