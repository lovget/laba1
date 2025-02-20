// 1. Дана строка. Найти самое длинное слово  
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Функция для чтения строки с клавиатуры
void read_string(char** str) {
    int size = 1; //начальный размер выделенной памяти для строки
    int len = 0;
    char ch;
    char* temp;

    *str = (char*)malloc(size * sizeof(char)); // Выделение начальной памяти для строки

    if (*str == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    printf("Введите строку: ");
    while ((ch = getchar()) != '\n') {
        if (len >= size) {
            size *= 2; // Удвоение размера
            temp = (char*)malloc(size * sizeof(char)); // Выделение новой памяти
            if (temp == NULL) {
                printf("Ошибка выделения памяти\n");
                exit(1);
            }
            for (int i = 0; i < len; i++) {
                temp[i] = (*str)[i]; // Копирование старых данных в новый блок памяти
            }
            free(*str); 
            *str = temp; // освобождение старой памяти и присвоение нового адреса
        }
        (*str)[len++] = ch; //Добавляет символ и увеличивает длину.
    }
    (*str)[len] = '\0'; // Завершаем строку нулевым символом
}

// Функция для проверки, является ли символ пробелом
int is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

// Функция для поиска самого длинного слова
char* find_longest_word(const char* str) {
    int max_length = 0;
    int current_length = 0;
    const char* max_start = NULL;
    const char* current_start = NULL;
    char* longest_word = NULL;

    while (*str) {
        if (!is_space(*str) && current_start == NULL) {
            current_start = str; // Начало нового слова
            current_length = 0;
        }
        //Завершение слова и обновление максимальной длины.
        if (is_space(*str) || *(str + 1) == '\0') {
            if (!is_space(*str)) current_length++; // если не пробел, то +1 к длине слова
            if (current_start && current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
            }
            current_start = NULL; // Конец слова
        }
        else {
            current_length++; 
        }
        str++; //Переход к следующему символу
    }


    //копирование самого длинного слова
    if (max_start) {
        longest_word = (char*)malloc((max_length + 1) * sizeof(char));
        if (longest_word == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        for (int i = 0; i < max_length; i++) {
            longest_word[i] = max_start[i];
        }
        longest_word[max_length] = '\0'; // Завершаем строку нулевым символом
    }


    return longest_word;
}

int main() {
    // Установка локали для поддержки русского языка
    setlocale(LC_ALL, "Russian");

    char* str;
    read_string(&str);

    char* longest_word = find_longest_word(str);
    if (longest_word) {
        printf("Самое длинное слово: %s\n", longest_word);
        free(longest_word); // Освобождение памяти, выделенной для самого длинного слова
    }
    else {
        printf("В строке нет слов.\n");
    }

    free(str); // Освобождение памяти, выделенной для строки
    return 0;
}

//является ли следующий символ концом строки 
//max_length + 1: Добавляется 1, чтобы учесть нулевой символ \0, который обозначает конец строки.