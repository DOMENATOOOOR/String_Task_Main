#include "String.h"
String::String(): data_(nullptr), size_(0), capacity_(0), refCount_(new size_t(1)) {};


String::String(const char* str): String() {
    if (str)
    {
        size_ = std::strlen(str);
        capacity_ = size_ + 1;
        refCount_ = new size_t(1);
        data_ = new char[capacity_];
        strcpy(data_, str);
    }

};
String::String(const char* str, size_t n): String()
{
    if (str) {
        size_ = n;
        capacity_ = size_ + 1;
        refCount_ = new size_t(1);
        data_ = new char[capacity_];
        std::strncpy(data_, str, size_);
        data_[size_] = '\0';
    }
};
String::String(size_t n, char c): String()
    {
    if (c) {
        size_ = n;
        capacity_ = size_ + 1;
        refCount_ = new size_t(1);
        data_ = new char[capacity_];
        std::memset(data_, c, size_);
        data_[size_] = '\0';
    }
    };
String::String(const String& str): size_(0), capacity_(0)//копирование
    {
    if (str.data_) {
        size_ = str.size_;
        capacity_ = str.capacity_;
        data_ = str.data_;
        refCount_ = str.refCount_;
        ++(*refCount_);
    }
    else {
        refCount_ = new size_t(1);
        data_ = nullptr;
        }
    };
String::String(const String& str, size_t pos, size_t len): String()//копирование начиная с какой-то позиции до конца либо до определенного конца
    {
    if (str.data_)
    {
        if (pos > str.size_)
        {
            throw std::out_of_range("Выход за границы массива");
        }
        if (len == npos || len > str.size_)
        {
            len = str.size_ - pos;
        }
        size_ = len;
        capacity_ = size_ + 1;
        data_ = new char[capacity_];
        std::strncpy(data_, str.data_ + pos, len);
        data_[len] = '\0';
    }
};
String::~String() {
    if (refCount_) {
        (*refCount_)--;
        if ((*refCount_) == 0) {
            delete refCount_;
            delete[] data_;
        }
    }
};

size_t String::size() const
    {
    return size_;
    };

size_t String::capacity() const
    {
    return capacity_;
    };

void String::reserve(size_t n)
    {
    if (n >= size_)
    {
        size_ = n;
        capacity_ = n + 1;
        if (data_)
        {
            char* new_data_ = new char[size_];
            std::strcpy(new_data_, data_);
            if (*refCount_ == 1)
            {
                delete[] data_;
            }
            data_ = new_data_;
            data_[size_] = '\0';
        }
    }
    };
void String::clear()
    {
    size_ = 0;
    capacity_ = 0;
        if (--(*refCount_) == 0)
        {
            data_[0] = '\0';
        }
        else
        {
            refCount_ = new size_t(1);
            data_ = new char[0];
        }
    };
bool String::empty() const
    {
    return !size_;
    };

char& String::at(size_t pos)
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
    return data_[pos];
    };
const char& String::at(size_t pos) const
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
    return data_[pos];
    };

char& String::operator[](size_t pos)
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");

    return data_[pos];
    };
const char& String::operator[](size_t pos) const
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");

    return data_[pos];
    };

char& String::back()
    {
    if (empty()) {
        throw std::out_of_range("Attempt to access front of an empty string");
    }

    return at(size_ - 1);
    };
const char& String::back() const
    {
    if (empty()) {
        throw std::out_of_range("Attempt to access front of an empty string");
    }

    return at(size_ - 1);
    };

char& String::front()
    {
    if (empty()) {
        throw std::out_of_range("Attempt to access front of an empty string");
    }

    return at(0);
    };
const char& String::front() const
    {
    if (empty()) {
        throw std::out_of_range("Attempt to access front of an empty string");
    }

    return at(0);
    };

String& String::operator+=(const String& str)
    {
    detach();

    reserve(size_ + str.size_);
    std::strcat(data_, str.data_);
    return *this;
    };
String& String::operator+=(const char* str)
    {
    detach();

    reserve(size_ + std::strlen(str));
    std::strcat(data_, str);
    return *this;
    };
String& String::operator+=(char c)
    {
    detach();

    reserve(size_ + 1);
    data_[size_-1] = c;
    data_[size_] = '\0';
    return *this;
    };

String& String::operator=(const String& str) {
        if (this != &str && str.data_)
        {
            size_ = str.size_;
            capacity_ = str.capacity_;
            if((*refCount_) == 1)
            {
                delete refCount_;
                delete data_;
                data_ = str.data_;
                refCount_ = str.refCount_;
                ++(*refCount_);
            }
            else
            {
                --(*refCount_);
                data_ = str.data_;
                refCount_ = str.refCount_;
                ++(*refCount_);
            }
        }

        return *this;
    };
String& String::operator=(const char* str)
    {
        if (str)
        {
            size_ = std::strlen(str);
            capacity_ = size_ + 1;
            if((*refCount_) == 1)
            {
                delete[] data_;
                data_ = new char[size_];
                std::strcpy(data_, str);
            }
            else
            {
                --(*refCount_);
                data_ = new char[size_];
                std::strcpy(data_, str);
                refCount_ = new size_t(1);
            }
        }
        else throw std::logic_error("Пустая строка");

        return *this;
    };

String& String::insert(size_t pos, const String&  str)
    {
    if (pos > size_) throw std::out_of_range("Выход за пределы строки");

    detach();

    reserve(size_ + str.size_);
    std::memmove(data_ + pos + str.size_, data_ + pos, size_ - str.size_ - pos + 1);
    std::memcpy(data_ + pos, str.data_, str.size_);
    return *this;

    };
String& String::insert(size_t pos, const char* str)
    {
    if (!str) throw std::logic_error("Null pointer подается в функцию");
    if (pos > size_) throw std::out_of_range("Выход за пределы строки");
    size_t str_size_ = std::strlen(str);

    detach();

    reserve(size_ + str_size_);
    std::memmove(data_ + pos + str_size_, data_ + pos, size_ - str_size_ - pos + 1);
    std::memcpy(data_ + pos, str, str_size_);
    return *this;
    };

String& String::erase(size_t pos, size_t len)
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
    if (len == npos || pos + len > size_) len = size_ - pos;

    detach();

    std::memmove(data_ + pos, data_ + pos + len, size_ - len - pos + 1);
    size_ -= len;
    capacity_ = size_ + 1;
    return *this;
    };

String& String::replace(size_t pos, size_t len, const String& str)
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
    if (len == npos || pos + len > size_) len = size_ - pos;

    size_t new_size_ = size_ - len + str.size_;

    char* newData = new char[new_size_];
    std::strncpy(newData, data_, pos);
    std::strcpy(newData + pos, str.data_);
    std::strcpy(newData + pos + str.size_, data_ + pos + len);

    detach();

    data_ = newData;
    size_ = new_size_;
    capacity_ = size_ + 1;

    return *this;
    };
String& String::replace(size_t pos, size_t len, const char* str)
    {
    if (!str) throw std::logic_error("Null pointer подается в функцию");
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
    if (len == npos || pos + len > size_) len = size_ - pos;

    size_t newStrLen = std::strlen(str);
    size_t new_size_ = size_ - len + newStrLen;

    char* newData = new char[new_size_];
    std::strncpy(newData, data_, pos);
    std::strcpy(newData + pos, str);
    std::strcpy(newData + pos + newStrLen, data_ + pos + len);

    detach();

    data_ = newData;
    size_ = new_size_;
    capacity_ = size_ + 1;

    return *this;
    };
String& String::replace(size_t pos, size_t len, size_t n, char c)
    {
    if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
    if (len == npos || pos + len > size_) len = size_ - pos;
    size_t new_size_ = size_ - len + n;

    char* newData = new char[new_size_];
    std::strncpy(newData, data_, pos);
    std::memset(newData + pos, c, n);
    std::strcpy(newData + pos + n, data_ + pos + len);

    detach();

    data_ = newData;
    size_ = new_size_;
    capacity_ = size_ + 1;

    return *this;
    };

void String::swap(String& str)
    {
    std::swap(data_, str.data_);
    std::swap(size_, str.size_);
    std::swap(capacity_, str.capacity_);
    std::swap(refCount_, str.refCount_);
    };
const char* String::data() const{
    if (!data_) {
        throw std::runtime_error("Data pointer is null");
    }
    return data_;
    };

size_t String::find(const String& str, size_t pos) const
    {
    if (pos >= size_) return npos;
    const char* result = std::strstr(data_ + pos, str.data_);
    return result ? result - data_ : npos;
    };
size_t String::find(const char* str, size_t pos) const
    {
    if (!str) throw std::logic_error("Null pointer подается в функцию");

    if (pos >= size_) return npos;
    const char* result = std::strstr(data_ + pos, str);
    return result ? result - data_ : npos;
    };
size_t String::find(char c, size_t pos) const
    {
    if (pos >= size_) return npos;

    for (size_t i = pos; i < size_; i++) {
        if (data_[i] == c) return i;
        }
    return npos;
    };

String String::substr(size_t pos, size_t len)
    {
    if (pos > size_) throw std::out_of_range("Выход за пределы строки");

    if (len == npos || pos + len > size_) len = size_ - pos;
    return {data_ + pos, len};
    };

int String::compare(const String& str) const
    {
    if (!str.data_) {
        throw std::runtime_error("Cannot compare with a null string");
    }
    return strcmp(data_, str.data_);
    };

size_t String::countRef() const
    {
    if (!refCount_) {
        throw std::logic_error("Cannot get the reference count of a null string");
    }
    return *refCount_;
    };


void String::detach() {
    if((*refCount_) != 1) {
        --(*refCount_);
        refCount_ = new size_t(1);
        char* new_data_ = new char[size_];
        std::strcpy(new_data_, data_);
        data_ = new_data_;
        std::cout<< "Адрес new_data_:" << static_cast<void*>(new_data_) << std::endl;
    }
}
