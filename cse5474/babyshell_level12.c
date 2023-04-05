#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

void *shellcode_mem;
size_t shellcode_size;

int main(int argc, char **argv, char **envp)
{
    assert(argc > 0);

    printf("###\n");
    printf("### Welcome to %s!\n", argv[0]);
    printf("###\n");
    printf("\n");
    printf("This challenge reads in some bytes, modifies them (depending on the specific\n");
    printf("challenge configuration, and executes them as code! This is a common exploitation\n");
    printf("scenario, called \"code injection\". Through this series of challenges, you will\n");
    printf("practice your shellcode writing skills under various constraints!\n");
    printf("\n");

    for (int i = 3; i < 10000; i++) close(i);
    for (char **a = argv; *a != NULL; a++) memset(*a, 0, strlen(*a));
    for (char **a = envp; *a != NULL; a++) memset(*a, 0, strlen(*a));

    shellcode_mem = mmap((void *) 0x1337000, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, 0, 0);
    printf("Mapping shellcode memory at %p.\n", shellcode_mem);
    assert(shellcode_mem == (void *) 0x1337000);

    printf("Reading %#x bytes from stdin into %p.\n", 0x12, shellcode_mem);
    shellcode_size = read(0, shellcode_mem, 0x12);
    assert(shellcode_size > 0);

    printf("Removing write permissions from first %d bytes of shellcode.\n", 4096);
    assert(mprotect(shellcode_mem, 4096, PROT_READ|PROT_EXEC) == 0);

    puts("Executing shellcode!\n");
    ((void(*)())shellcode_mem)();

}