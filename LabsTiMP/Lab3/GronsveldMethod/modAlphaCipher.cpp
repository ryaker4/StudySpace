#include "modAlphaCipher.h"
#include <locale>
#include <cwctype>
#include <algorithm>
#include <stdexcept>

using namespace std;

static const locale loc("ru_RU.UTF-8");

modAlphaCipher::modAlphaCipher(const std::wstring& skey)
{
    numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; // без Ё 
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(skey));
}

wstring modAlphaCipher::encrypt(const wstring& open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for (size_t i = 0; i < work.size(); i++) {
        work[i] = (work[i] + numAlpha.size() - key[i % key.size()]) % numAlpha.size();
    }
    return convert(work);
}

vector<int> modAlphaCipher::convert(const wstring& s)
{
    vector<int> result;
    for (auto c : s) {
        auto it = alphaNum.find(c);
        if (it == alphaNum.end())
            throw cipher_error("Недопустимый символ в тексте");
        result.push_back(it->second);
    }
    return result;
}

wstring modAlphaCipher::convert(const vector<int>& v)
{
    wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

wstring modAlphaCipher::getValidKey(const wstring& s)
{
    if (s.empty())
        throw cipher_error("Пустой ключ");
    // Исправления
    for (auto c : s) {
        if (!iswalpha(c)) {
            throw cipher_error("Недопустимый символ в ключе");
        }
    }
        

    wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            tmp.push_back(towupper(c));
        }
    }

    if (tmp.empty())
        throw cipher_error("Ключ не содержит букв");
    // Дополнительные исправления    
    int countA = 0;
    for (auto c : tmp) {
        if (c == L'А')
            countA++;
    }

    double ratio = static_cast<double>(countA) / tmp.size();
    if (ratio > 0.5) {
        throw cipher_error("Слабый ключ: более 50% букв А");
    }

    return tmp;
}

wstring modAlphaCipher::getValidOpenText(const wstring& s)
{
    wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            tmp.push_back(towupper(c));
        }
    }

    if (tmp.empty())
        throw cipher_error("Пустой открытый текст");

    return tmp;
}

wstring modAlphaCipher::getValidCipherText(const wstring& s)
{
    if (s.empty())
        throw cipher_error("Пустой шифртекст");

    for (auto c : s) {
        if (!iswalpha(c)) {
            throw cipher_error("Недопустимый символ в шифртексте");
        }
    }

    return s;
}
