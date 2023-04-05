#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/sendfile.h>

__attribute__((constructor))
void init(void)
{
    // disable buffering
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

void win(void)
{
    puts("You win! Here is your flag:");
    sendfile(1, open("/flag", 0), 0, 0x400);
    exit(0);
}

struct layout
{
    char padding[0x40];
    char buf[0x400];
};

void func(void)
{
    struct layout layout;
    char *buf = layout.buf;
    int ret = 0;
    int lead_len = 0;

    puts("In this challenge, you can perform format string attack for infinite times");
    puts("You can use the the attack to leak information and prepare your payload");
    puts("After your payload is ready, send \"END\" to exit from the while loop");
    puts("And hopefully your payload can be triggered :)\n");

    memset(buf, 0, sizeof(layout.buf));
    
    // protection info
    puts("You can use `checksec` command to check the protection of the binary.");
    while(1)
    {
        // intro
        puts("\nNow, the program is waiting for your input.");
        puts("If your input contains \"END\", the program exits from the while loop before triggering the vulnerability:");

        // clear buffer and read input from user
        memset(buf, 0, sizeof(layout.buf)-lead_len);
        // clear buffer if necessary
        memset(buf, 0, sizeof(layout.buf)-lead_len);
        // read user input
        ret = read(0, buf, sizeof(layout.buf)-lead_len-1);
        // you use pwntools? that's a biiiiig NO.
        if(ret <= 0 || strstr(buf, "END")) break;
        // oh no, A Wild Vulnerability Appears!
        puts("Show me what you got :P");
        printf(layout.buf);
    }
}

int main(int argc, char **argv, char **envp)
{
    assert(argc > 0);
    printf("###\n### Welcome to %s!\n###\n\n", argv[0]);

    // challenge introduction
    puts("In this challenge, you will be performing attack against the old and famous vulnerability:\n"
         "\"format string vulnerability\". This challenge reads in some bytes and print the\n"
         "input as the format using `printf` in different ways(depending on the specific challenge\n"
         "configuration). Different challenges have different protections on. ROP may be needed in\n"
         "some challenges. Have fun!\n");

    printf("To ensure that you are preforming stack operations, rather than doing other tricks, this\n");
    printf("will sanitize all environment variables and arguments and close all file\ndescriptors > 2,\n");

    for (int i = 3; i < 10000; i++) close(i);
    for (char **a = argv; *a != NULL; a++) memset(*a, 0, strlen(*a));
    for (char **a = envp; *a != NULL; a++) memset(*a, 0, strlen(*a));
    func();
}
