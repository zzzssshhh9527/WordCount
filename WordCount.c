#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int count_characters(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("文件不存在\n");
        return -1;
    }

    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

int count_words(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("文件不存在\n");
        return -1;
    }

    int count = 0;
    char buffer[100];
    char c;
    int start = 0; // 表示当前是否处于一个单词中

    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            buffer[start++] = c;
        } else {
            // 如果不是字母、逗号，则表示一个单词的结束
            if (start > 0) {
                buffer[start] = '\0'; // 添加字符串结束符
                count++; // 单词计数加一
                start = 0; // 重置单词标志
            }
        }
    }
    //加入文本末尾是字母，则单词数应加1
    if (isalpha(buffer[start])) {
        count++;
    }

    fclose(file);
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [parameter] [input_file_name]\n", argv[0]);
        return 1;
    }
    char *option = argv[1];
    char *file_name = argv[2];
    
    if (strcmp(option, "-c") == 0) {
        printf("字符数: %d\n", count_characters(file_name));
    } else if (strcmp(option, "-w") == 0) {
        printf("单词数: %d\n", count_words(file_name));
    } else {
        printf("无效的参数\n");
        return 1;
    }

    return 0;
}
