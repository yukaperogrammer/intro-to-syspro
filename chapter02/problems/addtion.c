#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define BASE 10

long convert_to_long(char *);

int main(int argc, char *argv[])
{
    long num1 = 0;
    long num2 = 0;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: adtion.out <number1> <number2>\n");
        exit(1);
    }

    num1 = convert_to_long(argv[1]);
    num2 = convert_to_long(argv[2]);

    printf("%ld + %ld = %ld\n", num1, num2, num1 + num2);

    return 0;
}

long convert_to_long(char *c)
{
    long num;
    char *ptr;

    num = strtol(c, &ptr, BASE);
    errno = 0;

    /* 通常エラー処理 */
    if (errno == EINVAL || errno == ERANGE)
    {
        perror("ERROR(addtion.out)");
        exit(1);
    }
    else if (errno != 0)
    {
        perror("Unexpected ERROR(addtion.out)");
        exit(1);
    }

    /* 10進数変換できない文字があればエラーにする */
    if (ptr == c || *ptr != '\0')
    {
        fprintf(stderr, "%s is not convert to long\n", c);
        exit(1);
    }

    return num;
}

