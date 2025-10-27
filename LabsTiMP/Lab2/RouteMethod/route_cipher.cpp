#include "route_cipher.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cwctype>
#include <stdexcept>
#include <locale>

bool isRussianLetter(wchar_t c) {
    c = std::towupper(c);
    return (c >= L'А' && c <= L'Я') || c == L'Ё';
}

RouteCipher::RouteCipher(int cols) : columns(cols) {
    if (cols <= 0) {
        throw cipher_error("Columns must be positive");
    }
}

std::wstring RouteCipher::encrypt(const std::wstring& text) {
    if (text.empty()) {
        return L"";
    }
    
    std::wstring processedText;
    for (wchar_t c : text) {
        if (c != L' ') {
            wchar_t upperChar = std::towupper(c);
            if (!isRussianLetter(upperChar)) {
                throw cipher_error("Text must contain only Russian letters and spaces");
            }
            processedText += upperChar;
        }
    }
    
    if (processedText.empty()) {
        throw cipher_error("Text must contain at least one letter");
    }
    
    int textLength = processedText.length();
    int rows = (textLength + columns - 1) / columns;
    
    if (rows <= 0) {
        throw cipher_error("Invalid table dimensions");
    }
    
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L' '));
    int index = 0;
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (index < textLength) {
                table[i][j] = processedText[index++];
            }
        }
    }
    
    std::wstring result;
    
    int top = 0, bottom = rows - 1;
    int left = 0, right = columns - 1;
    
    while (top <= bottom && left <= right) {
        
        for (int i = top; i <= bottom; ++i) {
            if (table[i][right] != L' ') {
                result += table[i][right];
            }
        }
        right--;
        
        
        if (top <= bottom) {
            for (int j = right; j >= left; --j) {
                if (table[bottom][j] != L' ') {
                    result += table[bottom][j];
                }
            }
            bottom--;
        }
        
        
        if (left <= right) {
            for (int i = bottom; i >= top; --i) {
                if (table[i][left] != L' ') {
                    result += table[i][left];
                }
            }
            left++;
        }
    }
    
    return result;
}

std::wstring RouteCipher::decrypt(const std::wstring& cipherText) {
    if (cipherText.empty()) {
        return L"";
    }
    
    // Проверяем, что зашифрованный текст содержит только русские буквы
    for (wchar_t c : cipherText) {
        wchar_t upperChar = std::towupper(c);
        if (!isRussianLetter(upperChar)) {
            throw cipher_error("Cipher text must contain only Russian letters");
        }
    }
    
    int textLength = cipherText.length();
    int rows = (textLength + columns - 1) / columns;
    
    if (rows <= 0) {
        throw cipher_error("Invalid table dimensions for decryption");
    }
    
    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(columns, L' '));
    
    int top = 0, bottom = rows - 1;
    int left = 0, right = columns - 1;
    int index = 0;
    
    while (top <= bottom && left <= right && index < textLength) {
        
        for (int i = top; i <= bottom && index < textLength; ++i) {
            table[i][right] = cipherText[index++];
        }
        right--;
        
        if (top <= bottom) {
            for (int j = right; j >= left && index < textLength; --j) {
                table[bottom][j] = cipherText[index++];
            }
            bottom--;
        }
        
        if (left <= right) {
            for (int i = bottom; i >= top && index < textLength; --i) {
                table[i][left] = cipherText[index++];
            }
            left++;
        }
    }
    
    // Проверяем, что все символы были использованы
    if (index != textLength) {
        throw cipher_error("Decryption error: not all characters were placed in table");
    }
    
    std::wstring result;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (table[i][j] != L' ') {
                result += table[i][j];
            }
        }
    }
    
    return result;
}