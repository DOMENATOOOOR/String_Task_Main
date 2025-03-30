#include "String.h"
#include <cstring>
String::String()
{
    refCount_ = new size_t(1);
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
    void detach(char*& data);
    void detach_1();
};


String::String(const char* str) {
    if (str)
    {
        size_ = std::strlen(str);
        capacity_ = size_ + 1;
        refCount_ = new size_t(1);
        data_ = new char[capacity_];
        strcpy(data_, str);
    }
    else
    {
        refCount_ = new size_t(1);
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

};
String::String(const char* str, size_t n)
{
    if (str) {
        size_ = n;
        capacity_ = size_ + 1;
        refCount_ = new size_t(1);
        data_ = new char[capacity_];
        std::strncpy(data_, str, size_);
        data_[size_] = '\0';
    }
    else
    {
        size_ = 0;
        data_ = nullptr;
        capacity_ = 0;
    }
};
String::String(size_t n, char c)
    {
        if (c) {
            size_ = n;
            capacity_ = size_ + 1;
            refCount_ = new size_t(1);
            data_ = new char[capacity_];
            std::memset(data_, c, size_);
            data_[size_] = '\0';
        }
        else {
            size_ = 0;
            capacity_ = 0;
            data_ = nullptr;
        }

    };
String::String(const String& str)//копирование
    {
        refCount_ = str.refCount_;
        size_ = str.size_;
        capacity_ = str.capacity_;
        data_ = str.data_;
        ++(*refCount_);
    };
String::String(const String& str, size_t pos, size_t len)//копирование начиная с какой-то позиции до конца либо до определенного конца
    {
        refCount_ = new size_t(1);
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
    };
String::~String() {
        if ((*refCount_) == 1) {
            if (data_ != nullptr)
            {
                delete[] data_;
                data_ = nullptr;
            }
            delete refCount_;
        }
        else
        {
            --(*refCount_);
            refCount_ = new size_t(1);
            delete refCount_;
            data_ = new char[1];
            delete[] data_;
            data_ = nullptr;
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
            char* new_data_ = new char[n+1];
            size_ = n;
            capacity_ = n + 1;
            if (data_)
            {
                if (*refCount_ == 1)
                {
                    std::strcpy(new_data_, data_);
                    delete[] data_;
                    data_ = new_data_;
                    data_[size_] = '\0';
                }
                else
                {
                    std::strcpy(new_data_, data_);
                    data_ = new char[n+1];
                    data_ = new_data_;
                    data_[size_] = '\0';
                }
            }
            detach(new_data_);
        }
    };
void String::clear()
    {
        if ((*refCount_) == 1)
        {
            delete[] data_;
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }
        else
        {
            --(*refCount_);
            refCount_ = new size_t(1);
            size_ = 0;
            capacity_ = 0;
            data_ = new char[0];
            delete[] data_;
            data_ = nullptr;
        }
    };
bool String::empty() const
    {
        return size_ == 0;
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
        return at(size_ - 1);
    };
const char& String::back() const
    {
        return at(size_ - 1);
    };

char& String::front()
    {
        return at(0);
    };
const char& String::front() const
    {
        return at(0);
    };

String& String::operator+=(const String& str)
    {
        if((*refCount_) == 1)
        {
            this->reserve(size_ + str.size_);
            std::strcat(data_, str.data_);
        }
        else
        {
            detach_1();
            this->reserve(size_ + str.size_);
            std::strcat(data_, str.data_);
        }
        return *this;
        };
String& String::operator+=(const char* str)
    {
        if((*refCount_) == 1)
        {
            this->reserve(size_ + std::strlen(str));
            std::strcat(data_, str);
        }
        else
        {
            detach_1();
            this->reserve(size_ + std::strlen(str));
            std::strcat(data_, str);
        }
        return *this;
    };
String& String::operator+=(char c)
    {
        if((*refCount_) == 1)
        {
            this->reserve(size_ + 1);
            data_[size_-1] = c;
            data_[size_] = '\0';
        }
        else {
            detach_1();
            this->reserve(size_ + 1);
            data_[size_-1] = c;
            data_[size_] = '\0';
        }
        return *this;
    };

String& String::operator=(const String& str) {
        if (this != &str)
        {
            size_ = str.size_;
            capacity_ = str.capacity_;
            if((*refCount_) == 1)
            {
                delete refCount_;
                refCount_ = nullptr;
                data_ = str.data_;
                refCount_ = str.refCount_;
                ++(*refCount_);
            }
            else
            {
                --(*refCount_);
                data_ = new char[str.capacity_];
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
                std::strcpy(data_, str);
            }
            else
            {
                --(*refCount_);
                data_ = new char[capacity_];
                std::strcpy(data_, str);
                refCount_ = new size_t(1);
            }
        }
        else throw std::logic_error("Пустая строка");

        return *this;
    };

String& String::insert(size_t pos, const String&  str)
    {
        if (pos > this->size_) throw std::out_of_range("Выход за пределы строки");

        if ((*refCount_) - 1 == 0)
        {
            this->reserve(size_ + str.size_);
            std::memmove(data_ + pos + str.size_, data_ + pos, size_ - str.size_ - pos + 1);
            std::memcpy(data_ + pos, str.data_, str.size_);
        }
        else
        {
            detach_1();
            this->reserve(size_ + str.size_);
            std::memmove(data_ + pos + str.size_, data_ + pos, size_ - str.size_ - pos + 1);
            std::memcpy(data_ + pos, str.data_, str.size_);
        }
        return *this;

    };
String& String::insert(size_t pos, const char* str)
    {
        if (!str) throw std::logic_error("Null pointer подается в функцию");
        if (pos > size_) throw std::out_of_range("Выход за пределы строки");
        size_t str_size_ = std::strlen(str);
        if ((*refCount_) - 1 == 0)
        {
            this->reserve(size_ + str_size_);
            std::memmove(data_ + pos + str_size_, data_ + pos, size_ - str_size_ - pos + 1);
            std::memcpy(data_ + pos, str, str_size_);
        }
        else
        {
            detach_1();
            this->reserve(size_ + str_size_);
            std::memmove(data_ + pos + str_size_, data_ + pos, size_ - str_size_ - pos + 1);
            std::memcpy(data_ + pos, str, str_size_);
        }
        return *this;
    };

String& String::erase(size_t pos, size_t len)
    {
        if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
        if (len == npos || pos + len > size_) len = size_ - pos;
        if ((*refCount_) == 1)
        {
            std::memmove(data_ + pos, data_ + pos + len, size_ - len - pos + 1);
            size_t new_size_ = size_ - len;
            char* new_data_ = new char[new_size_ + 1];
            std::strncpy(new_data_, data_, new_size_);
            new_data_[new_size_] = '\0';
            delete [] data_;
            data_ = new char[new_size_ + 1];
            std::strcpy(data_, new_data_);
            detach(new_data_);
            size_ -= len;
            capacity_ = size_ + 1;
        }
        else
        {
            detach_1();
            std::memmove(data_ + pos, data_ + pos + len, size_ - len - pos + 1);
            size_t new_size_ = size_ - len;
            char* new_data_ = new char[new_size_ + 1];
            std::strncpy(new_data_, data_, new_size_);
            new_data_[new_size_] = '\0';
            delete [] data_;
            data_ = new char[new_size_ + 1];
            std::strcpy(data_, new_data_);
            detach(new_data_);
            size_ -= len;
            capacity_ = size_ + 1;
        }

        return *this;
    };

String& String::replace(size_t pos, size_t len, const String& str)
    {
        if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
        if (len == npos || pos + len > size_) len = size_ - pos;
        size_t new_size_ = size_ - len + str.size_;
            if ((*refCount_) - 1 == 0)
            {
                char* newData = new char[new_size_ + 1];
                std::strncpy(newData, data_, pos);
                std::strcpy(newData + pos, str.data_);
                std::strcpy(newData + pos + str.size_, data_ + pos + len);
                data_ = newData;
                size_ = new_size_;
                capacity_ = size_ + 1;
                detach(newData);
            }
            else
            {
                detach_1();
                char* newData = new char[new_size_ + 1];
                std::strncpy(newData, data_, pos);
                std::strcpy(newData + pos, str.data_);
                std::strcpy(newData + pos + str.size_, data_ + pos + len);
                data_ = newData;
                size_ = new_size_;
                capacity_ = size_ + 1;
                detach(newData);
            }
        return *this;
    };
String& String::replace(size_t pos, size_t len, const char* str)
    {
        if (!str) throw std::logic_error("Null pointer подается в функцию");
        if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
        if (len == npos || pos + len > size_) len = size_ - pos;
        size_t newStrLen = std::strlen(str);
        size_t new_size_ = size_ - len + newStrLen;
        if ((*refCount_) - 1 == 0)
        {
            char* newData = new char[new_size_ + 1];
            std::strncpy(newData, data_, pos);
            std::strcpy(newData + pos, str);
            std::strcpy(newData + pos + newStrLen, data_ + pos + len);
            data_ = newData;
            size_ = new_size_;
            capacity_ = size_ + 1;
            detach(newData);
        }
        else
        {
            detach_1();
            char* newData = new char[new_size_ + 1];
            std::strncpy(newData, data_, pos);
            std::strcpy(newData + pos, str);
            std::strcpy(newData + pos + newStrLen, data_ + pos + len);
            data_ = newData;
            size_ = new_size_;
            capacity_ = size_ + 1;
            detach(newData);
        }
        return *this;
    };
String& String::replace(size_t pos, size_t len, size_t n, char c)
    {
        if (pos >= size_) throw std::out_of_range("Выход за пределы строки");
        if (len == npos || pos + len > size_) len = size_ - pos;
        size_t new_size_ = size_ - len + n;
        if ((*refCount_) - 1 == 0)
        {
            char* newData = new char[new_size_ + 1];
            std::strncpy(newData, data_, pos);
            std::memset(newData + pos, c, n);
            std::strcpy(newData + pos + n, data_ + pos + len);
            data_ = newData;
            size_ = new_size_;
            capacity_ = size_ + 1;
            detach(newData);
        }
        else
        {
            detach_1();
            char* newData = new char[new_size_ + 1];
            std::strncpy(newData, data_, pos);
            std::memset(newData + pos, c, n);
            std::strcpy(newData + pos + n, data_ + pos + len);
            data_ = newData;
            size_ = new_size_;
            capacity_ = size_ + 1;
            detach(newData);
        }
        return *this;
    };

void String::swap(String& str)
    {
        std::swap(data_, str.data_);
        std::swap(size_, str.size_);
        std::swap(capacity_, str.capacity_);
        std::swap(refCount_, str.refCount_);
    };
const char* String::data() {
        return data_;
    };

size_t String::find(const String& str, size_t pos)
    {
        if (pos >= size_) return npos;
        const char* result = std::strstr(data_ + pos, str.data_);
        return result ? result - data_ : npos;
    };
size_t String::find(const char* str, size_t pos)
    {
        if (!str) throw std::logic_error("Null pointer подается в функцию");

        if (pos >= size_) return npos;
        const char* result = std::strstr(data_ + pos, str);
        return result ? result - data_ : npos;
    };
size_t String::find(char c, size_t pos)
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
        return strcmp(data_, str.data_);
    };

size_t String::countRef()
    {
        return *refCount_;
    };

void String::detach(char*& data) {
    data = new char[0];
    delete[] data;
    data = nullptr;
}

void String::detach_1() {
    --(*refCount_);
    refCount_ = new size_t(1);
    char* new_data_ = data_;
    data_ = new char[capacity_];
    std::strcpy(data_, new_data_);
    detach(new_data_);
}
