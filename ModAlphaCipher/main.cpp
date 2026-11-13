#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    wstring key;
    wstring text;
    unsigned op;

    try {
        wcout << L"Введите ключ: ";
        wcin >> key;
        modAlphaCipher cipher(key);
        wcout << L"Ключ загружен\n";

        do {
            wcout << L"Шифр готов. Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать): ";
            wcin >> op;
            if(op > 2) {
                wcout << L"Неправильная операция\n";
            } else if(op > 0) {
                wcout << L"Введите текст: ";
                wcin >> text;
                try {
                    if(op == 1) {
                        wstring res = cipher.encrypt(text);
                        wcout << L"Зашифрованный текст: " << res << endl;
                    } else {
                        wstring res = cipher.decrypt(text);
                        wcout << L"Расшифрованный текст: " << res << endl;
                    }
                } catch(const cipher_error& e) {
                    cerr << "Ошибка: " << e.what() << endl;
                }
            }
        } while(op != 0);
    } catch(const cipher_error& e) {
        cerr << "Ошибка (ключ): " << e.what() << endl;
        return 1;
    } catch(const std::exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}