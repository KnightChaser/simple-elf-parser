/**
 * @file main.c
 * @brief Main source file for the ELF(Executable and Linkable Format) parser.
 *        Program entrypoint.
 * @author KnightChaser (https://github.com/knightchaser)
 */
//

#include "utils/elf_utils.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <elf-file-path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Failed to open the file\n");
        exit(EXIT_FAILURE);
    }

    printf("[+] Analyzing ELF file: %s\n", argv[1]);

    // File header (EHDR stands for ELF Header)
    Elf64_Ehdr ehdr;
    read_elf_header(fd, &ehdr);
    printf("[*] ELF header:\n");
    print_elf_header(&ehdr);

    // section header (SHDR stands for Section Header)
    Elf64_Shdr shdrs[ehdr.e_shnum];
    read_section_headers(fd, &ehdr, shdrs);
    printf("[*] Section headers:\n");

    char *shstrtab = read_section_header_string_table(fd, &ehdr, shdrs);
    print_section_headers(fd, &ehdr, shdrs, shstrtab);

    free(shstrtab);
    close(fd);
    return 0;
}