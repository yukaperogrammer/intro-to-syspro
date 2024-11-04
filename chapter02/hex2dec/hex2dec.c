#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *ptr;
    long ret;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: hex2dec <hex-number>\n");
        exit(1);
    }

    ret = strtol(argv[1], &ptr, 16);
    if (errno == EINVAL || errno == ERANGE)
    {
        perror("ERROR(hex2dec)");
        exit(1);
    }
    else if (errno != 0)
    {
        perror("Unexpected ERROR(hex2dec)");
        exit(1);
    }
    else if (ptr == argv[1])
    {
        fprintf(stderr, "No hex number is found.");
        exit(1);
    }

    printf("%s(hex) is %ld(dec)\n", argv[1], ret);
    if (*ptr != '\0')
    {
        printf("Futher characters after number: %s\n", ptr);
    }

    return 0;
}

