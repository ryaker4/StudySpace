#pragma once
#include <string>
#include <stdexcept>


class RouteCipher {
private:
    int columns;
public:
    RouteCipher(int cols);
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& cipherText);
};

class cipher_error : public std::invalid_argument {
public:
    explicit cipher_error(const std::string& message) 
        : std::invalid_argument(message) {}
};