#include "modAlphaCipher.h"
#include <locale>
#include <string>
#include <iostream>
using namespace std;
void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        
        if (destructCipherText) // надо "портить"?
            cipherText.front() = tolower(cipherText.front()); // "портим"
        
        decryptedText = cipher.decrypt(cipherText);
        wcout<<"key="<<key<<endl;
        wcout<<Text<<endl;
        wcout<<cipherText<<endl;
        wcout<<decryptedText<<endl;
        } catch (const cipher_error & e) {
            cerr<<"Error: "<<e.what()<<endl;
        }
    }
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    check(L"СОБАКАКОТПОПУГАЙ", L"ЭХО");
    check(L"СОБАКАКОТПОПУГАЙ", L"ВОДА");
    check(L"КОРИЧНЕВАЯЛИСАИЛЕНИВАЯСОБАКА",L"Простой");
    check(L"КОРИЧНЕВАЯЛИСАИЛЕНИВАЯСОБАКА",L"");
    check(L"КОРИЧНЕВАЯЛИСАИЛЕНИВАЯСОБАКА",L"АБВГ123");
    check(L"КОРИЧНЕВАЯЛИСАИЛЕНИВАЯСОБАКА",L"ТОПСЕКРЕТ",true);
    
    return 0;
}