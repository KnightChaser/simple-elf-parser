#include "utils/elf_utils.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("[+] Analyzing ELF file: %s\n", argv[1]);
    Elf64_Ehdr ehdr;
    read_elf_header(fd, &ehdr);
    print_elf_header(&ehdr);

    close(fd);
    return 0;
}
