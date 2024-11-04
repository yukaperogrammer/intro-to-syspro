#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void close_files(FILE *, FILE *);

int main(int argc, char *argv[])
{
    FILE *fpin;
    FILE *fpout;
    int c;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <origin filename> <new filename>\n", argv[0]);
        exit(1);
    }

    errno = 0; // errno初期化
    if ((fpin = fopen(argv[1], "r")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }

    if ((fpout = fopen(argv[2], "w")) == NULL)
    {
        perror(argv[2]);
        /* fpinは開いているので閉じる */
        if (fclose(fpin) == EOF)
        {
            perror(argv[1]);
        }
        exit(1);
    }

    while ((c = fgetc(fpin)) != EOF)
    {
        /* ファイルの書き込みでエラーがあればファイルを2つとも閉じる */
        if (fputc(c, fpout) == EOF)
        {
            close_files(fpin, fpout);
        }
    }

    /* fgetcでエラーが起きていないか確認 */
    if (ferror(fpin))
    {
        fprintf(stderr, "ERROR read file\n");
        close_files(fpin, fpout);
    }

    /* すべてのプロセスが正常に終了,ファイルを閉じてプログラム終了 */
    close_files(fpin, fpout);

    return 0;
}

/* 2つのファイルを閉じる  */
void close_files(FILE *fpin, FILE *fpout)
{
    if (fclose(fpin) == EOF || fclose(fpout) == EOF)
    {
        fprintf(stderr, "ERROR close file\n");
        exit(1);
    }
}

