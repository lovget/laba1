// 1. ���� ������. ����� ����� ������� �����  
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ������� ��� ������ ������ � ����������
void read_string(char** str) {
    int size = 1; //��������� ������ ���������� ������ ��� ������
    int len = 0;
    char ch;
    char* temp;

    *str = (char*)malloc(size * sizeof(char)); // ��������� ��������� ������ ��� ������

    if (*str == NULL) {
        printf("������ ��������� ������\n");
        exit(1);
    }

    printf("������� ������: ");
    while ((ch = getchar()) != '\n') {
        if (len >= size) {
            size *= 2; // �������� �������
            temp = (char*)malloc(size * sizeof(char)); // ��������� ����� ������
            if (temp == NULL) {
                printf("������ ��������� ������\n");
                exit(1);
            }
            for (int i = 0; i < len; i++) {
                temp[i] = (*str)[i]; // ����������� ������ ������ � ����� ���� ������
            }
            free(*str); 
            *str = temp; // ������������ ������ ������ � ���������� ������ ������
        }
        (*str)[len++] = ch; //��������� ������ � ����������� �����.
    }
    (*str)[len] = '\0'; // ��������� ������ ������� ��������
}

// ������� ��� ��������, �������� �� ������ ��������
int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// ������� ��� ������ ������ �������� �����
char* find_longest_word(const char* str) {
    int max_length = 0;
    int current_length = 0;
    const char* max_start = NULL;
    const char* current_start = NULL;
    char* longest_word = NULL;

    while (*str) {
        if (!is_space(*str) && current_start == NULL) {
            current_start = str; // ������ ������ �����
            current_length = 0;
        }
        //���������� ����� � ���������� ������������ �����.
        if (is_space(*str) || *(str + 1) == '\0') {
            if (!is_space(*str)) current_length++; // ���� �� ������, �� +1 � ����� �����
            if (current_start && current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
            }
            current_start = NULL; // ����� �����
        }
        else {
            current_length++; 
        }
        str++; //������� � ���������� �������
    }


    //����������� ������ �������� �����
    if (max_start) {
        longest_word = (char*)malloc((max_length + 1) * sizeof(char));
        if (longest_word == NULL) {
            printf("������ ��������� ������\n");
            exit(1);
        }
        for (int i = 0; i < max_length; i++) {
            longest_word[i] = max_start[i];
        }
        longest_word[max_length] = '\0'; // ��������� ������ ������� ��������
    }


    return longest_word;
}

int main() {
    // ��������� ������ ��� ��������� �������� �����
    setlocale(LC_ALL, "Russian");

    char* str;
    read_string(&str);

    char* longest_word = find_longest_word(str);
    if (longest_word) {
        printf("����� ������� �����: %s\n", longest_word);
        free(longest_word); // ������������ ������, ���������� ��� ������ �������� �����
    }
    else {
        printf("� ������ ��� ����.\n");
    }

    free(str); // ������������ ������, ���������� ��� ������
    return 0;
}

//�������� �� ��������� ������ ������ ������ 
//max_length + 1: ����������� 1, ����� ������ ������� ������ \0, ������� ���������� ����� ������.