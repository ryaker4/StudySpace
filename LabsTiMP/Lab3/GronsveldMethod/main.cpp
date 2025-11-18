#include "modAlphaCipher.h"

#include <UnitTest++/UnitTest++.h>

#include <codecvt>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

// Проверка и установка локали
void init_locale()
{
    try {
        locale::global(locale("ru_RU.UTF-8"));
        wcout.imbue(locale("ru_RU.UTF-8"));
        wcin.imbue(locale("ru_RU.UTF-8"));
    } catch(const exception& e) {
        cerr << "Ошибка установки локали: " << e.what() << endl;
        locale::global(locale(""));
    }
}

// Конвертация wide → UTF-8 string
string to_utf8(const wstring& wstr)
{
    wstring_convert<codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

// Фикстура
struct KeyB_fixture {
    modAlphaCipher* p;
    KeyB_fixture()
    {
        init_locale();
        p = new modAlphaCipher(L"ПРИВЕТ");
    }
    ~KeyB_fixture() { delete p; }
};
SUITE(KeyTest)
{
    TEST(ValidKey) { 
        CHECK_EQUAL(to_utf8(L"БВГБВ"), to_utf8(modAlphaCipher(L"БВГ").encrypt(L"ААААА"))); 
        }
    TEST(LongKey) { 
        CHECK_EQUAL(to_utf8(L"БВГДЕ"), to_utf8(modAlphaCipher(L"БВГДЕЁЖЗИЙК").encrypt(L"ААААА"))); 
        }
    TEST(LowCaseKey) { 
        CHECK_EQUAL(to_utf8(L"БВГБВ"), to_utf8(modAlphaCipher(L"бвг").encrypt(L"ААААА"))); 
        }
    TEST(DigitsInKey) { 
        CHECK_THROW(modAlphaCipher(L"Б1"), cipher_error); 
        }
    TEST(PunctuationInKey) { 
        CHECK_THROW(modAlphaCipher(L"Б,В"), cipher_error); 
        }
    TEST(WhitespaceInKey) { 
        CHECK_THROW(modAlphaCipher(L"Б В"), cipher_error); 
    }
    TEST(EmptyKey) { 
        CHECK_THROW(modAlphaCipher(L""), cipher_error); 
        }
    TEST(WeakKey) { 
        CHECK_THROW(modAlphaCipher(L"ААА"), cipher_error); 
        }
}

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) { CHECK_EQUAL(to_utf8(L"ЯБСДЙЕЬЩЩ"), to_utf8(p->encrypt(L"ПРИВЕТМИР"))); }

    TEST_FIXTURE(KeyB_fixture, LowCaseString) { CHECK_EQUAL(to_utf8(L"ЯБСДЙЕЬЩЩ"), to_utf8(p->encrypt(L"приветмир"))); }

    TEST_FIXTURE(KeyB_fixture, StringWithWhitespaceAndPunct)
    {
        CHECK_EQUAL(to_utf8(L"ЯБСДЙЕЬЩЩ"), to_utf8(p->encrypt(L"Привет, мир!")));
    }

    TEST_FIXTURE(KeyB_fixture, EmptyString) { CHECK_THROW(p->encrypt(L""), cipher_error); }

    TEST_FIXTURE(KeyB_fixture, NoAlphaString) { CHECK_THROW(p->encrypt(L"1234+8765=9999"), cipher_error); }
}

SUITE(DecryptTest)
{
    TEST_FIXTURE(KeyB_fixture, DecryptText) { CHECK_EQUAL(to_utf8(L"ПРИВЕТМИР"), to_utf8(p->decrypt(L"ЯБСДЙЕЬЩЩ"))); }

    TEST_FIXTURE(KeyB_fixture, EmptyDecrypt) { CHECK_THROW(p->decrypt(L""), cipher_error); }
}

int main(int argc, char** argv)
{
    init_locale();
    return UnitTest::RunAllTests();
}
