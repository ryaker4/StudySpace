#include <UnitTest++/UnitTest++.h>
#include <iostream>
#include <string>
#include <locale>
#include "route_cipher.h"

SUITE(RouteCipherTests) {
    // Тесты конструктора
    TEST(ValidColumns) {
        RouteCipher cipher(5);
    }
    
    TEST(InvalidColumnsZero) {
        CHECK_THROW(RouteCipher cipher(0), cipher_error);
    }
    
    TEST(InvalidColumnsNegative) {
        CHECK_THROW(RouteCipher cipher(-3), cipher_error);
    }
    
    // Тесты шифрования
    TEST(EncryptBasic) {
        RouteCipher cipher(3);
        std::wstring result = cipher.encrypt(L"ПРИВЕТ МИР");
        CHECK(result == L"ИТРИМВПРЕ");
    }
    
    TEST(EncryptEmptyString) {
        RouteCipher cipher(2);
        std::wstring result = cipher.encrypt(L"");
        CHECK(result == L"");
    }
    
    TEST(EncryptOnlySpaces) {
        RouteCipher cipher(2);
        CHECK_THROW(cipher.encrypt(L"   "), cipher_error);
    }
    
    TEST(EncryptInvalidCharacters) {
        RouteCipher cipher(2);
        CHECK_THROW(cipher.encrypt(L"Hello World"), cipher_error);
    }
    
    TEST(EncryptMixedCase) {
        RouteCipher cipher(3);
        std::wstring result = cipher.encrypt(L"привет мир");
        CHECK(result == L"ИТРИМВПРЕ");
    }
    
    // Тесты дешифрования
    TEST(DecryptBasic) {
        RouteCipher cipher(3);
        std::wstring result = cipher.decrypt(L"ИТРИМВПРЕ");
        CHECK(result == L"ПРИВЕТМИР");
    }
    
    TEST(DecryptEmptyString) {
        RouteCipher cipher(2);
        std::wstring result = cipher.decrypt(L"");
        CHECK(result == L"");
    }
    
    TEST(DecryptInvalidCharacters) {
        RouteCipher cipher(2);
        CHECK_THROW(cipher.decrypt(L"Hello"), cipher_error);
    }
    
    // Интеграционные тесты (шифрование + дешифрование)
    TEST(EncryptDecryptRoundTrip) {
        RouteCipher cipher(4);
        std::wstring original = L"КОДИРОВАНИЕТЕКСТА";
        std::wstring encrypted = cipher.encrypt(original);
        std::wstring decrypted = cipher.decrypt(encrypted);
        CHECK(original == decrypted);
    }
    
    TEST(EncryptDecryptRoundTripWithSpaces) {
        RouteCipher cipher(3);
        std::wstring original = L"ПРИВЕТ МИР КАК ДЕЛА";
        std::wstring encrypted = cipher.encrypt(original);
        std::wstring decrypted = cipher.decrypt(encrypted);
        // После дешифрования пробелы не сохраняются
        CHECK(decrypted == L"ПРИВЕТМИРКАКДЕЛА");
    }
    
    TEST(EncryptDecryptDifferentColumnSizes) {
        std::wstring original = L"ТЕСТОВОЕСООБЩЕНИЕ";
        
        RouteCipher cipher1(2);
        std::wstring encrypted1 = cipher1.encrypt(original);
        std::wstring decrypted1 = cipher1.decrypt(encrypted1);
        CHECK(original == decrypted1);
        
        RouteCipher cipher2(5);
        std::wstring encrypted2 = cipher2.encrypt(original);
        std::wstring decrypted2 = cipher2.decrypt(encrypted2);
        CHECK(original == decrypted2);
    }
}

int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}


