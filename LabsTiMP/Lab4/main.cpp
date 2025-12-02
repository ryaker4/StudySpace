/**
 * @file main.cpp
 * @brief Главный модуль программы для шифрования методом табличной маршрутной перестановки
 * @author Рябов Кирилл
 * @version 1.0
 * @date 02.12.2025г.
 * @copyright ИБСТ ПГУ
 * @brief Программа предоставляет пользовательский интерфейс для работы с шифром
 *        табличной маршрутной перестановки.
 * 
 * Программа позволяет:
 * 1. Зашифровать текст с использованием заданного ключа (количество столбцов)
 * 2. Расшифровать ранее зашифрованный текст
 * 3. Выйти из программы
 */

#include <iostream>
#include <string>
#include <locale>
#include "route_cipher.h"

using namespace std;

/**
 * @brief Главная функция программы
 * @details Предоставляет пользовательский интерфейс в виде меню для работы с шифром.
 *          Обрабатывает пользовательский ввод, вызывает соответствующие методы
 *          класса RouteCipher и обрабатывает исключения.
 * @return Код завершения программы (0 - успешное завершение)
 */
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    
    int choice;
    int key;
    wstring text, result;
    
    do {
        wcout << L"\n=== ШИФР ТАБЛИЧНОЙ ПЕРЕСТАНОВКИ ===" << endl;
        wcout << L"1. Зашифровать текст" << endl;
        wcout << L"2. Расшифровать текст" << endl;
        wcout << L"3. Выход" << endl;
        wcout << L"Выберите действие: ";
        wcin >> choice;
        wcin.ignore(); ///< Игнорируем оставшийся символ новой строки
        
        if (choice == 1 || choice == 2) {
            wcout << L"Введите ключ (количество столбцов): ";
            wcin >> key;
            wcin.ignore();
            
            if (choice == 1) {
                wcout << L"Введите текст для шифрования: ";
            } else {
                wcout << L"Введите текст для расшифрования: ";
            }
            
            getline(wcin, text);
            
            try {
                RouteCipher cipher(key);
                
                if (choice == 1) {
                    result = cipher.encrypt(text);
                    wcout << L"Зашифрованный текст: " << result << endl;
                } else {
                    result = cipher.decrypt(text);
                    wcout << L"Расшифрованный текст: " << result << endl;
                }
            } catch (const exception& e) {
                wcout << L"Ошибка: " << e.what() << endl;
            }
        } else if (choice == 3) {
            wcout << L"Выход из программы." << endl;
        } else {
            wcout << L"Неверный выбор! Попробуйте снова." << endl;
        }
        
    } while (choice != 3);
    
    return 0;
}