#pragma once
#include <cstring>
#include <stdexcept>
#include <iostream>
class String {

private:
    char* data_;
    size_t size_;
    size_t capacity_;
    size_t *refCount_;
    void detach(char*& data);
    void detach_1();

public:
    String();
    String(const char* str);
    String(const char* str, size_t n);
    String(size_t n, char c);
    String(const String& str);
    String(const String& str, size_t pos, size_t len = npos);
    ~String();

    [[nodiscard]] size_t size() const;

    [[nodiscard]] size_t capacity() const;

    void reserve(size_t n = 0);
    void clear();
    [[nodiscard]] bool empty() const;

    char& at(size_t pos);
    [[nodiscard]] const char& at(size_t pos) const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    char& back();
    [[nodiscard]] const char& back() const;

    char& front();
    [[nodiscard]] const char& front() const;

    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String& operator+=(char c);

    String& operator=(const String& str);
    String& operator=(const char* str);

    String& insert(size_t pos, const String&  str);
    String& insert(size_t pos, const char* str);

    String& erase(size_t pos = 0, size_t len = npos);

    String& replace(size_t pos, size_t len, const String& str);
    String& replace(size_t pos, size_t len, const char* str);
    String& replace(size_t pos, size_t len, size_t n, char c);

    void swap(String& str);
    const char* data();

    size_t find(const String& str, size_t pos = 0);
    size_t find(const char* str, size_t pos = 0);
    size_t find(char c, size_t pos = 0);

    String substr(size_t pos = 0, size_t len = npos);

    [[nodiscard]] int compare(const String& str) const;

    size_t countRef();

    static const size_t npos = -1;
};
