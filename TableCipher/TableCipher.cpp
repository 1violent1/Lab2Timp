#include "TableCipher.h"
#include <iostream>
#include <locale>
#include <string>

using namespace std;

TableCipher::TableCipher(int key)
    : key(getValidKey(key))
{
}

std::wstring TableCipher::encrypt(const std::wstring& text)
{
    std::wstring valid_text = getValidOpenText(text);
    int rows;
    if(valid_text.length() % key != 0) {
        rows = valid_text.length() / key + 1;
    } else {
        rows = valid_text.length() / key;
    }
    wchar_t table[rows][key];
    int index = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < key; j++) {
            if(index < valid_text.length()) {
                table[i][j] = valid_text[index];
                index++;
            } else {
                table[i][j] = L' ';
            }
        }
    }
    std::wstring encrypted_text;
    for(int i = key - 1; i >= 0; i--) {
        for(int j = 0; j < rows; j++) {
            encrypted_text += table[j][i];
        }
    }
    return encrypted_text;
}

std::wstring TableCipher::decrypt(const std::wstring& encrypted_text)
{
    std::wstring valid_text = getValidCipherText(encrypted_text);
    int rows;
    if(valid_text.length() % key != 0) {
        rows = valid_text.length() / key + 1;
    } else {
        rows = valid_text.length() / key;
    }
    wchar_t table[rows][key];
    int index = 0;
    for(int i = key - 1; i >= 0; i--) {
        for(int j = 0; j < rows; ++j) {
            if(index < valid_text.length()) {
                table[j][i] = valid_text[index];
                index++;
            } else {
                table[j][i] = L' ';
            }
        }
    }
    wstring decrypted_text;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < key; j++) {
            decrypted_text += table[i][j];
        }
    }
    return decrypted_text;
}

inline int TableCipher::getValidKey(int key)
{
    if (key <= 0)
        throw cipher_error("Invalid key: key must be greater than 0");
    return key;
}

inline std::wstring TableCipher::getValidOpenText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty open text");
    bool all_spaces = true;
    for (auto c : s) {
        if (c != L' ' && c != L'\t') {
            all_spaces = false;
            break;
        }
    }
    if (all_spaces)
        throw cipher_error("Empty open text");
    if (key > (int)s.length())
        throw cipher_error("Invalid key: key is greater than text length");
    return s;
}

inline std::wstring TableCipher::getValidCipherText(const std::wstring& s)
{
    if (s.empty())
        throw cipher_error("Empty cipher text");
    if (s.length() % key != 0)
        throw cipher_error("Invalid cipher text: length must be a multiple of key");
    return s;
}