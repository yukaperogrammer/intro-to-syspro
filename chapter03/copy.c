#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 512

int main(int argc, char *argv[])
{
    FILE *fpin = NULL;
    FILE *fpout = NULL;
    char buf[BUFSIZE];

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <origin filename> <new filename>\n", argv[0]);
        exit(1);
    }

    /* コピー元ファイルを開く */
    if ((fpin = fopen(argv[1], "r")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }

    /* コピー先ファイルを開く */
    if ((fpout = fopen(argv[2], "w")) == NULL)
    {
        perror(argv[2]);
        if (fclose(fpin) == EOF)
        {
            perror(argv[1]);
        };
        exit(1);
    }

    /* ファイルの内容をコピー */
    while (fgets(buf, BUFSIZE - 1, fpin) != NULL)
    {
        fputs(buf, fpout);
    }

    /* コピー元ファイルを閉じる */
    if (fclose(fpin) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    /* コピー先ファイルを閉じる */
    if (fclose(fpout) == EOF)
    {
        perror(argv[2]);
        exit(1);
    }

    return 0;
}

