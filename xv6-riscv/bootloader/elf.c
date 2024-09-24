#include "types.h"
#include "param.h"
#include "layout.h"
#include "riscv.h"
#include "defs.h"
#include "buf.h"
#include "elf.h"

#include <stdbool.h>

struct elfhdr* kernel_elfhdr;
struct proghdr* kernel_phdr;

uint64 find_kernel_load_addr(enum kernel ktype) {
    /* CSE 536: Get kernel load address from headers */
    if(ktype==NORMAL){
        kernel_elfhdr = (struct elfhdr*) RAMDISK;
        uint64 ph_offset = kernel_elfhdr->phoff;
        uint64 ph_size = kernel_elfhdr->phentsize;
    
        kernel_phdr = (struct proghdr*)(RAMDISK + ph_offset + ph_size);
    }
    else {
        kernel_elfhdr = (struct elfhdr*) RECOVERYDISK;
        uint64 ph_offset = kernel_elfhdr->phoff;
        uint64 ph_size = kernel_elfhdr->phentsize;
    
        kernel_phdr = (struct proghdr*)(RECOVERYDISK + ph_offset + ph_size);
    }
    return kernel_phdr->vaddr;
}

uint64 find_kernel_size(enum kernel ktype) {
    /* CSE 536: Get kernel binary size from headers */
    if(ktype == NORMAL){
        kernel_elfhdr = (struct elfhdr*) RAMDISK;
    }
    else {
        kernel_elfhdr = (struct elfhdr*) RECOVERYDISK;
    }
    return kernel_elfhdr->shoff + (kernel_elfhdr->shentsize)*(kernel_elfhdr->shnum);
}

uint64 find_kernel_entry_addr(enum kernel ktype) {
    /* CSE 536: Get kernel entry point from headers */
    if(ktype == NORMAL){
        kernel_elfhdr = (struct elfhdr*) RAMDISK;
    }
    else {
        kernel_elfhdr = (struct elfhdr*) RECOVERYDISK;
    }
    return kernel_elfhdr->entry;
}
