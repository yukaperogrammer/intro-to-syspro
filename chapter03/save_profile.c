#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct profile
{
    char name[24];
    int age;
} profile;

int main(int argc, char*argv[])
{
    FILE *fp;
    int i;
    profile list[] = {
        {"Tomoko Tanaka", 19},
        {"Miya Sakai", 21},
        {"Ayane Yamamoto", 20}
    };

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    if ((fp = fopen(argv[1], "w")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }

    fprintf(fp, "name, age\n");
    for (i = 0; i < 3; i++)
    {
        if (fprintf(fp, "%s, %d\n", list[i].name, list[i].age) < 0)
        {
            perror(argv[1]);
            fclose(fp);
            exit(1);
        }
    }

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

