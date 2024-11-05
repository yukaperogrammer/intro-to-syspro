#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;

    /*書き込むデータ用の変数*/
    char name[] = "Takako Toyota";
    int age = 25;
    float height = 163.42;

    /* ファイルをバイナリモードで開く */
    if ((fp = fopen("profile_binary.bin", "wb")) == NULL)
    {
        perror("profile_binary.bin");
        exit(1);
    }

    fwrite(name, sizeof(char), 14, fp);
    fwrite(&age, sizeof(int), 1, fp);
    fwrite(&height, sizeof(float), 1, fp);

    /* ファイルを閉じる */
    if (fclose(fp) == EOF)
    {
        perror("profile_binary.bin");
        exit(1);
    }

    return 0;
}

