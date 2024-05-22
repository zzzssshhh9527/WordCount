#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    char *option = argv[1];
    char *file_name = argv[2];
    char buffer[256];
    int word_count = 0;
    int char_count = 0;
    int start = 0; // 表示当前是否处于一个单词中
    char c;

    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("文件不存在\n");
        return -1;
    }

    // 先进行字符统计
    while ((c = fgetc(file)) != EOF)
    {
        char_count++;
    }
    // 重置文件指针
    rewind(file);

    // 然后进行单词统计
    while ((c = fgetc(file)) != EOF)
    {
        if (isalpha(c))
        {
            buffer[start++] = c;
        }
        else // 如果不是字母则表示一个单词的结束
        {
            // 排除"  as"这种情况
            if (start > 0)
            {
                buffer[start] = '\0'; // 添加字符串结束符
                word_count++;         // 单词计数加一
                start = 0;            // 重置单词标志
            }
        }
    }
    // 假如文本末尾是字母，则单词数应加1
    if (isalpha(buffer[start]))
    {
        word_count++;
    }

    fclose(file);

    if (strcmp(option, "-c") == 0)
    {
        printf("char_count: %d\n", char_count);
    }
    else if (strcmp(option, "-w") == 0)
    {
        printf("word_count: %d\n", word_count);
    }
    else
    {
        printf("无效的参数\n");
        return 1;
    }

    return 0;
}