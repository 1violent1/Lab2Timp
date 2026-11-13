#pragma once
#include <string>
#include <stdexcept>

class cipher_error: public std::invalid_argument {
public:
    explicit cipher_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};

class TableCipher
{
private:
    int key;
    int getValidKey(int key);
    std::wstring getValidOpenText(const std::wstring& s);
    std::wstring getValidCipherText(const std::wstring& s);
public:
    TableCipher() = delete; 
    TableCipher(int key);
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& encrypted_text);
};