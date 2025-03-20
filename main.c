#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Функция для обмена двух элементов в файле
void swap_in_file(FILE* file, int pos1, int pos2) {
    int num1, num2;

    // Читаем первый элемент
    fseek(file, pos1 * sizeof(int), SEEK_SET);
    fread(&num1, sizeof(int), 1, file);

    // Читаем второй элемент
    fseek(file, pos2 * sizeof(int), SEEK_SET);
    fread(&num2, sizeof(int), 1, file);

    // Меняем их местами
    fseek(file, pos1 * sizeof(int), SEEK_SET);
    fwrite(&num2, sizeof(int), 1, file);
    fseek(file, pos2 * sizeof(int), SEEK_SET);
    fwrite(&num1, sizeof(int), 1, file);
}

// Функция для сортировки элементов в файле (пузырьковая сортировка)
void sort_file(FILE* file, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int num1, num2;

            // Считываем два соседних элемента
            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&num1, sizeof(int), 1, file);
            fread(&num2, sizeof(int), 1, file);

            // Если элементы в неправильном порядке, меняем их местами
            if (num1 > num2) {
                fseek(file, j * sizeof(int), SEEK_SET);
                fwrite(&num2, sizeof(int), 1, file);
                fwrite(&num1, sizeof(int), 1, file);
            }
        }
    }
}

// Функция для подсчёта количества чисел, кратных заданному числу
int count_multiples(FILE* file, int count, int divisor) {
    int multiple_count = 0;

    rewind(file); // Переход в начало файла
    for (int i = 0; i < count; i++) {
        int num;

        // Считываем число и проверяем кратность
        fread(&num, sizeof(int), 1, file);
        if (num % divisor == 0) {
            multiple_count++;
        }
    }
    return multiple_count;
}

// Функция для циклического сдвига элементов на k позиций вправо
void rotate_file(FILE* file, int count, int k) {
    k %= count; // Убедимся, что k меньше длины

    // Выполняем сдвиг k раз
    for (int i = 0; i < k; i++) {
        int last;

        // Считываем последний элемент
        fseek(file, (count - 1) * sizeof(int), SEEK_SET);
        fread(&last, sizeof(int), 1, file);

        // Сдвигаем элементы вправо
        for (int j = count - 1; j > 0; j--) {
            int current;

            fseek(file, (j - 1) * sizeof(int), SEEK_SET);
            fread(&current, sizeof(int), 1, file);

            fseek(file, j * sizeof(int), SEEK_SET);
            fwrite(&current, sizeof(int), 1, file);
        }

        // Помещаем последний элемент в начало
        fseek(file, 0, SEEK_SET);
        fwrite(&last, sizeof(int), 1, file);
    }
}

// Функция для замены всех повторяющихся элементов на 0
void replace_duplicates_with_zero(FILE* file, int count) {
    rewind(file); // Переход в начало файла
    for (int i = 0; i < count; i++) {
        int num1;

        // Считываем текущий элемент
        fseek(file, i * sizeof(int), SEEK_SET);
        fread(&num1, sizeof(int), 1, file);

        // Проверяем на повторы среди следующих элементов
        for (int j = i + 1; j < count; j++) {
            int num2;

            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&num2, sizeof(int), 1, file);

            if (num1 == num2 && num1 != 0) {
                // Если найден дубликат, заменяем его на 0
                fseek(file, j * sizeof(int), SEEK_SET);
                int zero = 0;
                fwrite(&zero, sizeof(int), 1, file);
            }
        }
    }
}

// Главная функция программы
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "rus"); // Установка локали для поддержки русского языка

    // Проверяем наличие имени файла в аргументах командной строки
    if (argc < 2) {
        printf("Укажите имя файла как первый аргумент командной строки.\n");
        return 1;
    }

    FILE* file;
    // Открываем файл для записи и чтения
    fopen_s(&file, argv[1], "wb+");
    if (!file) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    printf("Введите количество чисел: ");
    int n;
    scanf_s("%d", &n);

    // Запись чисел в файл
    printf("Введите натуральные числа:\n");
    for (int i = 0; i < n; i++) {
        int num;
        scanf_s("%d", &num);
        fwrite(&num, sizeof(int), 1, file);
    }

    // Чтение и вывод чисел из файла
    printf("Числа из файла:\n");
    rewind(file);
    for (int i = 0; i < n; i++) {
        int num;
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    // Обмен элементов по указанным позициям
    printf("Введите позиции для обмена (от 0 до %d):\n", n - 1);
    int pos1, pos2;
    scanf_s("%d %d", &pos1, &pos2);
    swap_in_file(file, pos1, pos2);

    // Вывод после обмена
    printf("Файл после обмена элементов:\n");
    rewind(file);
    for (int i = 0; i < n; i++) {
        int num;
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    // Сортировка файла
    sort_file(file, n);
    printf("Файл после сортировки:\n");
    rewind(file);
    for (int i = 0; i < n; i++) {
        int num;
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    // Подсчёт кратных чисел
    printf("Введите число для подсчёта кратных ему:\n");
    int divisor;
    scanf_s("%d", &divisor);
    int multiples = count_multiples(file, n, divisor);
    printf("Количество чисел, кратных %d: %d\n", divisor, multiples);

    // Выполнение циклического сдвига
    printf("Введите количество позиций для циклического сдвига вправо: ");
    int k;
    scanf_s("%d", &k);
    rotate_file(file, n, k);

    // Вывод после сдвига
    printf("Файл после циклического сдвига на %d позиции:\n", k);
    rewind(file);
    for (int i = 0; i < n; i++) {
        int num;
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    // Замена повторяющихся чисел на 0
    replace_duplicates_with_zero(file, n);
    printf("Файл после замены повторов на 0:\n");
    rewind(file);
    for (int i = 0; i < n; i++) {
        int num;
        fread(&num, sizeof(int), 1, file);
        printf("%d ", num);
    }
    printf("\n");

    fclose(file); // Закрытие файла
    return 0;
}
