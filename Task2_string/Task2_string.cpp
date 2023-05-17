#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <locale.h>
//Напишите две функции foo, bar, выполняющие одинаковые действия (в соответствии с указанным
//вариантом):
//использующую только строки в стиле С
//использующую строки типа string


char* foo(char* destination, const char* source1, const char* source2) {
    bool used[256] = { false }; // массив для отметки использованных символов
    int dest_index = 0;
    int len1 = std::strlen(source1);
    int len2 = std::strlen(source2);

    for (int i = 0; i < len1; i++) {
        if (!used[source1[i]]) {
            used[source1[i]] = true;
            destination[dest_index++] = source1[i];
        }
    }

    for (int i = 0; i < len2; i++) {
        if (!used[source2[i]]) {
            used[source2[i]] = true;
            destination[dest_index++] = source2[i];
        }
    }

    destination[dest_index] = '\0';
    return destination;
}

std::string bar(const std::string& source1, const std::string& source2) {
    bool used[256] = { false }; // массив для отметки использованных символов
    std::string result;

    for (char c : source1) {
        if (!used[c]) {
            used[c] = true;
            result.push_back(c);
        }
    }

    for (char c : source2) {
        if (!used[c]) {
            used[c] = true;
            result.push_back(c);
        }
    }

    return result;
}

int main() {
    setlocale(LC_ALL, "Russia");
    // Считываем данные из файла
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        int length = std::stoi(line);
        char* str1 = new char[length + 1];
        file.getline(str1, length + 1);
        std::getline(file, line);
        length = std::stoi(line);
        char* str2 = new char[length + 1];
        file.getline(str2, length + 1);

        // Применяем функцию foo
        char* result_foo = new char[length * 2 + 1];
        foo(result_foo, str1, str2);
        std::cout << "foo: " << result_foo << std::endl;
        delete[] result_foo;

        // Применяем функцию bar
        std::string s1(str1), s2(str2);
        std::string result_bar = bar(s1, s2);
        std::cout << "bar: " << result_bar << std::endl;

        // Освобождаем выделенную память
        delete[] str1;
        delete[] str2;
    }

    return 0;
}
