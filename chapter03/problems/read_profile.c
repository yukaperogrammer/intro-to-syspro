#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSIZE 64
#define LISTSIZE 20

typedef struct profile
{
    char name[24];
    int age;
} profile;

void do_print(int, profile *);

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[BUFSIZE];
    char *ptr;
    char *endptr;
    int no;
    int char_at;
    long age;
    profile list[LISTSIZE];

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <csv filename>\n", argv[0]);
        exit(1);
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        perror(argv[1]);
        exit(1);
    }

    no = 0;
    while (fgets(buf, BUFSIZE - 1, fp) != NULL)
    {
        /* 改行は飛ばす */
        if (buf[0] == '\n')
        {
            continue;
        }

        /* 名前を代入する */
        ptr = buf;
        char_at = 0;
        while (*ptr != ',')
        {
            list[no].name[char_at] = *ptr;
            char_at++;
            ptr++;
        }
        list[no].name[char_at] = '\0'; // 末尾にナル文字を追加
        ptr++; // この操作でptrは数字の先頭アドレスを指している

        /* 年齢を代入する */
        age = strtol(ptr, &endptr, 10);
        if (errno == EINVAL || errno == ERANGE)
        {
            fprintf(stderr, "ERROR(strtol)\n");
            fclose(fp);
            exit(1);
        }
        else if (errno != 0)
        {
            fprintf(stderr, "Unexpected ERROR(strtol)\n");
            fclose(fp);
            exit(1);
        }
        list[no].age = (int)age;

        /* 初期化&更新 */
        age = 0;
        no++;
    }

    do_print(no, list);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void do_print(int no, profile *list)
{
    int i;

    for (i = 0; i < no; i++)
    {
        printf("[NO.%d]\n", i);
        printf("\tname=%s\n", list[i].name);
        printf("\tage=%d\n", list[i].age);
    }
}

