#define _GNU_SOURCE 1
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

char EXPECTED_RESULT[] = "\x75\x64\x67\x67\x77\x63\x62\x66";

int main(int argc, char **argv, char **envp)
{
    printf("###\n");
    printf("### Welcome to %s!\n", argv[0]);
    printf("###\n");
    printf("\n");

    puts("This license verifier software will allow you to read the flag.");
    puts("However, before you can do so, you must verify that you are licensed to read flag files!");
    puts("This program consumes a license key over some communication channel that you must figure out.");
    puts("You must also figure out (by reverse engineering this program) what that license key is.");
    puts("Providing the correct license key will net you the flag!");

    unsigned char input[9] = { 0 };

    puts("Ready to receive your license key!");

    char *input_envp = NULL;
    for (int i = 0; envp[i]; i++)
    {
        if (strncmp(envp[i], "wblui", strlen("wblui")) == 0)
        {
            input_envp = envp[i];
            break;
        }
    }
    assert(input_envp != 0);
    memcpy(input, input_envp + sizeof("wblui") + 2, 8);

    for (int i = 0; i < 8 / 2; i++)
    {
        unsigned char x = input[i];
        unsigned char y = input[8 - i - 1];
        input[i] = y;
        input[8 - i - 1] = x;
    }

    puts("Checking the received license key!");

    if (strncmp(input, EXPECTED_RESULT, 8) == 0)
    {
        puts("Correct! Here is your flag:");
        sendfile(1, open("/flag", 0), 0, 1024);
        exit(0);
    }
    else
    {
        puts("Wrong! No flag for you!");
        exit(1);
    }
}