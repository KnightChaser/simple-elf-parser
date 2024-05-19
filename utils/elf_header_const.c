/**
 * @file utils/elf_header_const.c
 * @brief Convert numerical values to stringified meaningful constants for the ELF header.
 */
//

#include "elf_header_const.h"

// EI_CLASS is set to 1 for 32-bit objects and 2 for 64-bit objects.
char* get_const_str_EI_CLASS(int value) {
    switch (value) {
        case ELFCLASSNONE:
            return "ELFCLASSNONE";
        case ELFCLASS32:
            return "32-bit objects";
        case ELFCLASS64:
            return "64-bit objects";
        default:
            return "Unknown";
    }
}

// EI_DATA specifies the data encoding of the processor-specific data in the object file.
// Set to 1 for little-endian and 2 for big-endian.
char* get_const_str_EI_DATA(int value) {
    switch (value) {
        case ELFDATANONE:
            return "ELFDATANONE";
        case ELFDATA2LSB:
            return "2's complement, little-endian";
        case ELFDATA2MSB:
            return "2's complement, big-endian";
        default:
            return "Unknown";
    }
}

// EI_VERSION is set to 1 for the original version of ELF.
char* get_const_str_EI_VERSION(int value) {
    switch (value) {
        case EV_NONE:
            return "EV_NONE";
        case EV_CURRENT:
            return "Current version";
        default:
            return "Unknown";
    }
}

// EI_OSABI identifies the operating system and/or ABI for which the object is prepared.
char* get_const_str_EI_OSABI(int value) {
    switch (value) {
        case ELFOSABI_NONE:
            return "ELFOSABI_NONE";
        case ELFOSABI_HPUX:
            return "HP-UX";
        case ELFOSABI_NETBSD:
            return "NetBSD";
        case ELFOSABI_LINUX:
            return "Linux";
        case ELFOSABI_SOLARIS:
            return "Sun Solaris";
        case ELFOSABI_AIX:
            return "AIX";
        case ELFOSABI_IRIX:
            return "IRIX";
        case ELFOSABI_FREEBSD:
            return "FreeBSD";
        case ELFOSABI_TRU64:
            return "TRU64 UNIX";
        case ELFOSABI_MODESTO:
            return "Novell Modesto";
        case ELFOSABI_OPENBSD:
            return "OpenBSD";
        case ELFOSABI_ARM:
            return "ARM";
        case ELFOSABI_STANDALONE:
            return "Standalone (embedded) application";
        default:
            return "Unknown";
    }
}

// e_type specifies the object file type.
char* get_const_str_E_TYPE(int value) {
    switch (value) {
        case ET_NONE:
            return "ET_NONE";
        case ET_REL:
            return "Relocatable file";
        case ET_EXEC:
            return "Executable file";
        case ET_DYN:
            return "Shared object file";
        case ET_CORE:
            return "Core file";
        default:
            return "Unknown";
    }
}

// e_machine specifies the architecture for which the object is prepared.
// It specifies the target ISA(Instruction Set Architecture).
char* get_const_str_E_MACHINE(int value) {
    switch (value) {
        case EM_NONE:
            return "EM_NONE";
        case EM_M32:
            return "AT&T WE 32100";
        case EM_SPARC:
            return "SPARC";
        case EM_386:
            return "Intel 80386";
        case EM_68K:
            return "Motorola 68000";
        case EM_88K:
            return "Motorola 88000";
        case EM_860:
            return "Intel 80860";
        case EM_MIPS:
            return "MIPS R3000";
        case EM_PARISC:
            return "HP/PA";
        case EM_SPARC32PLUS:
            return "SPARC with enhanced instruction set";
        case EM_PPC:
            return "PowerPC";
        case EM_PPC64:
            return "PowerPC 64-bit";
        case EM_S390:
            return "IBM S/390";
        case EM_ARM:
            return "ARM";
        case EM_SH:
            return "Renesas SuperH";
        case EM_SPARCV9:
            return "SPARC v9 64-bit";
        case EM_IA_64:
            return "Intel Itanium";
        case EM_X86_64:
            return "AMD x86-64";
        case EM_VAX:
            return "DEC Vax";
        default:
            return "Unknown";
    }
}