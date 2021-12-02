#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>

const short TLETTER_SIZE = 17; // Размер слова

struct TLetter {
    char letter[TLETTER_SIZE] {'\0'};
    unsigned int strIndex;
    unsigned int textIndex;

    TLetter() = default;

    TLetter(std::string* s, unsigned int si, unsigned int ti): strIndex(si), textIndex(ti) {
        for (unsigned int i = 0; i < s->size(); ++i) {
            letter[i] = (*s)[i];
        }
    };

    TLetter(std::string s, unsigned int si, unsigned int ti): strIndex(si), textIndex(ti) {
        for (unsigned int i = 0; i < s.size(); ++i) {
            letter[i] = s[i];
        }
    };

    ~TLetter() = default;

    const bool operator==(const TLetter &rval) const {
        for (unsigned int i = 0; i < TLETTER_SIZE; ++i) {
            if (letter[i] != rval.letter[i]) {
                return false;
            }
        }
        return true;
    } 
};


unsigned int* LowZFunction(const std::vector<TLetter> pattern, unsigned int par_size) {
    unsigned int patternSize = pattern.size();
    unsigned int* result = new unsigned int[patternSize] {0};

    for (unsigned int i = 1; i < patternSize; ++i) { 
        while (i + result[i] < patternSize and pattern[result[i]] == pattern[i + result[i]]) {
            ++result[i];
        }
    }
    return result;
}

unsigned int* ZFunction(const std::vector<TLetter> pattern, unsigned int par_size) {
    unsigned int patternSize = pattern.size();
    unsigned int* result = new unsigned int[patternSize] {0};
    unsigned int left = 0;
    unsigned int right = 0;
    for (unsigned int i = 1; i < patternSize; ++i) { // Проходимся по каждому терму
        if (i <= right) { // Индекс с которого можно начать сравнивать
            result[i] = std::min(right - i, result[i - left]);
        }
        while (i + result[i] < patternSize and pattern[result[i]] == pattern[i + result[i]]) { // Наивный подсчет, если result[i] == 0
            ++result[i];
        }
        if (i + result[i] > right) { // Смещение границы самого правого вхождения
            left = i;
            right = i + result[i];
        }
    }
    return result;
}

void ToLower(char* str) { // Перевод в нижний регистр символа
    if (*str>='A' and *str<='Z') {
        *str -= 'A'-'a';
    }
}

int main() {

    std::vector<TLetter> text; // Массив термов вида: pattern + "#" + text

    unsigned int strNumber = 0;
    unsigned int textNumber = 0;
    unsigned int patternSize = 0;

    std::string letter = "";
    char c;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (letter != "") {
                text.push_back(TLetter(&letter, strNumber, textNumber));
                ++textNumber;
                ++patternSize;
                letter = "";
            }
        } else if (c == '\n') {
            if (letter != "") {
                text.push_back(TLetter(&letter, strNumber, textNumber));
                ++textNumber;
                ++patternSize;
                letter = "";
            }
            break;
        } else {
            ToLower(&c);
            letter += c;
        }
    }

    if (!text.size()) { // Если паттерн пустой
        return 0;
    }

    text.push_back(TLetter(std::string("#"), strNumber, 0)); // Дополняем разделяющим термом
    strNumber = 1;
    textNumber = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            if (letter != "") {
                text.push_back(TLetter(&letter, strNumber, textNumber));
                ++textNumber;
                letter = "";
            }
        } else if (c == '\n') {
            if (letter != "") {
                text.push_back(TLetter(&letter, strNumber, textNumber));
                letter = "";
            }
            textNumber = 0;
            ++strNumber;
        } else {
            ToLower(&c);
            letter += c;
        }
    }

    if (letter != "") {
        text.push_back(TLetter(&letter, strNumber, textNumber));
    }

    std::chrono::time_point<std::chrono::system_clock> start1 = std::chrono::system_clock::now();
    unsigned int* zf1 = ZFunction(text, patternSize);
    std::chrono::time_point<std::chrono::system_clock> end1 = std::chrono::system_clock::now();

    std::chrono::time_point<std::chrono::system_clock> start2 = std::chrono::system_clock::now();
    unsigned int* zf2 = LowZFunction(text, patternSize); // Расчет Z - функции для массива вида: pattern + "#" + text
    std::chrono::time_point<std::chrono::system_clock> end2 = std::chrono::system_clock::now();

    if (zf1) {
        std::cout << "Вхождение есть\n"; 
    } else {
        std::cout << "Вхождения нет\n";
    }

    if (zf2) {
        std::cout << "Вхождение есть\n"; 
    } else {
        std::cout << "Вхождения нет\n";
    }

    // std::chrono::time_point<std::chrono::system_clock> start1 = std::chrono::system_clock::now();
    // std::chrono::time_point<std::chrono::system_clock> end1 = std::chrono::system_clock::now();
    std::ofstream fout("time_log1.txt", std::ios_base::app);
    fout << (text.size() - patternSize) << " ";
    fout << std::chrono::duration<double>(end1-start1).count() << " ";
    fout << std::chrono::duration<double>(end2-start2).count() << "\n";
    fout.close();

    // std::ofstream fout("time_log1.txt", std::ios_base::out);
    // if (!fout.is_open()) std::cout << "Файл не открылся\n";
    // for (unsigned int i = 0; i < text.size(); ++i) { // Вывод ответа
    //     if (zf1[i] == patternSize) { // Если значение z - функции равно длине паттерна, то это вхождение
    //        // printf("%d, %d\n", text[i].strIndex, text[i].textIndex+1);
    //         fout << text[i].strIndex << ", " << text[i].textIndex+1 << "\n";
    //     }
    // }
    // fout.close();

    // std::ofstream fout2("time_log2.txt", std::ios_base::out);
    // for (unsigned int i = 0; i < text.size(); ++i) { // Вывод ответа
    //     if (zf2[i] == patternSize) { // Если значение z - функции равно длине паттерна, то это вхождение
    //        // printf("%d, %d\n", text[i].strIndex, text[i].textIndex+1);
    //         fout2 << text[i].strIndex << ", " << text[i].textIndex+1 << "\n";
    //     }
    // }
    // fout2.close();

    delete []zf1;
    delete []zf2;

    return 0;
}