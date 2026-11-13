#include "TableCipher.h"
#include <iostream>
#include <limits>
#include <locale>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int key;
    wstring text;
    unsigned op;

    try {
        wcout << L"Введите ключ: ";
        if (!(wcin >> key)) {
            cerr << "Ошибка: неверный ввод ключа (ожидается число)" << endl;
            return 1;
        }
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        TableCipher cipher(key);
        wcout << L"Ключ загружен\n";

        do {
            wcout << L"Шифр готов. Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать, 3-сменить ключ): ";
            if (!(wcin >> op)) {
                wcout << L"Неверный ввод операции. Попробуйте снова.\n";
                wcin.clear();
                wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
                continue;
            }
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');

            if(op > 3) {
                wcout << L"Неправильная операция\n";
            } else if(op == 3) {
                wcout << L"Введите новый ключ: ";
                if (wcin >> key) {
                    wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
                    try {
                        cipher = TableCipher(key);
                        wcout << L"Ключ успешно изменён\n";
                    } catch(const cipher_error& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                } else {
                    wcout << L"Неверный ввод ключа.\n";
                    wcin.clear();
                    wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
                }
            } else if(op > 0) {
                wcout << L"Введите текст: ";
                getline(wcin, text);
                try {
                    if(op == 1) {
                        wcout << L"Зашифрованный текст: " << endl;
                        wcout << cipher.encrypt(text) << endl;
                    } else {
                        wcout << L"Расшифрованный текст: " << endl;
                        wcout << cipher.decrypt(text) << endl;
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