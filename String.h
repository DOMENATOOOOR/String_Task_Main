#pragma once
#include <cstring>
#include <stdexcept>
class String {

private:
    char* data_;
    size_t size_;
    size_t capacity_;
    size_t *refCount_;
public:
    String()
    {
        refCount_ = new size_t(1);
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;

    };
    String(const char* str) {
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
            data_ = nullptr;
            capacity_ = 0;
        }

    };
    String(const char* str, size_t n)
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
    String(size_t n, char c)
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
    String(const String& str)//копирование
    {
        refCount_ = str.refCount_;
        size_ = str.size_;
        capacity_ = str.capacity_;
        data_ = new char[capacity_];
        std::strcpy(data_, str.data_);
        ++(*refCount_);
    };
    String(const String& str, size_t pos, size_t len = npos)//копирование начиная с какой-то позиции до конца либо до определенного конца
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
    ~String() {
        if ((*refCount_) - 1 == 0) {
            std::cout<<"Вызвался диструктор"<<std::endl;
            delete[] data_;
            delete refCount_;
        }
    };

    size_t size()
    {
        return size_;
    };

    size_t capacity()
    {
        return capacity_;
    };

    void reserve(size_t n = 0)
    {
        if (n >= size_)
        {
            char* new_data_ = new char[n+1];
            if (data_)
            {
                std::strcpy(new_data_, data_);
                delete[] data_;
            }
            data_ = new_data_;
            size_ = n;
            capacity_ = size_ + 1;
            data_[size_] = '\0';
        }
    };
    void clear()
    {
        if ((*refCount_) - 1 == 0)
        {
            delete[] data_;
            delete refCount_;
            size_ = 0;
            capacity_ = 0;
            data_ = nullptr;
            refCount_ = new size_t(1);
        }
        else
        {
            size_ = 0;
            capacity_ = 0;
            delete[] data_;
            data_ = nullptr;
            --(*refCount_);
            refCount_ = new size_t(1);
        }
    };
    bool empty()
    {
        return size_ == 0;
    };

    char& at(size_t pos)
    {
        if (pos >= size_)
        {
            throw std::out_of_range("Выход за пределы строки");
        }
        return data_[pos];
    };
    const char& at(size_t pos) const
    {
        if (pos >= size_)
        {
            throw std::out_of_range("Выход за пределы строки");
        }
        return data_[pos];
    };


    char& operator[](size_t pos)
    {
        if (pos >= size_)
        {
            throw std::out_of_range("Выход за пределы строки");
        }
        return data_[pos];
    };
    const char& operator[](size_t pos) const
    {
        if (pos >= size_)
        {
            throw std::out_of_range("Выход за пределы строки");
        }
        return data_[pos];
    };

    char& back()
    {
        return at(size_ - 1);
    };
    const char& back() const
    {
        return at(size_ - 1);
    };

    char& front()
    {
        return at(0);
    };
    const char& front() const
    {
        return at(0);
    };

    String& operator+=(const String& str)
    {
        reserve(size_ + str.size_);
        if((*refCount_)-1 == 0)
        {
            std::strcat(data_, str.data_);
        }
        else
        {
            --(*refCount_);
            char* new_data_ = new char[size_ + str.size_ + 1];
            std::strcpy(new_data_, data_);
            std::strcat(new_data_, str.data_);
            delete[] data_;
            data_ = new_data_;
            refCount_ = new size_t(1);
        }
        return *this;
        };

    String& operator+=(const char* str)
    {
        reserve(size_ + std::strlen(str));
        if((*refCount_)-1 == 0)
        {
            std::strcat(data_, str);
        }
        else
        {
            --(*refCount_);
            char* new_data_ = new char[size_ + std::strlen(str) + 1];
            std::strcpy(new_data_, data_);
            std::strcat(new_data_, str);
            delete[] data_;
            data_ = new_data_;
            refCount_ = new size_t(1);
        }
        return *this;
    };
    String& operator+=(char c)
    {
        reserve(size_ + 1);
        if((*refCount_)-1 == 0)
        {
            data_[size_-1] = c;
            data_[size_] = '\0';
        }
        else {
            --(*refCount_);
            data_[size_-1] = c;
            data_[size_] = '\0';
            refCount_ = new size_t(1);
        }
        return *this;
    };

    String& operator=(const String& str) {
        if (this != &str)
        {
            size_ = str.size_;
            capacity_ = str.capacity_;
            delete[] data_;
            data_ = new char[str.capacity_];
            if((*refCount_)-1 == 0)
            {
                delete refCount_;
                std::strcpy(data_, str.data_);
                refCount_ = str.refCount_;
                ++(*refCount_);
            }
            else
            {
                --(*refCount_);
                std::strcpy(data_, str.data_);
                refCount_ = str.refCount_;
                ++(*refCount_);
            }
        }

        return *this;
    };
    String& operator=(const char* str)
    {
        if (str)
        {
            size_ = std::strlen(str);
            capacity_ = size_ + 1;
            delete[] data_;
            data_ = new char[capacity_];
            if((*refCount_)-1 == 0)
            {
                std::strcpy(data_, str);
            }
            else
            {
                --(*refCount_);
                std::strcpy(data_, str);
                refCount_ = new size_t(1);
            }
        }
        else
        {
            throw std::out_of_range("Пустая строка");
        }
        return *this;
    };

    //выполняет вставку строки str в позицию pos.
    //Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");.
    String& insert(size_t pos, const String&  str);
    String& insert(size_t pos, const char* str);

    //выполняет удаление подстроки в строке начиная с позиции pos и охватывая len символов.
    //Если len равняется npos, то удаление происходит с позиции pos до конца строки. Если pos больше размера строки, то выбрасывается исключение throw    .
    //std::out_of_range("message");.
    String& erase(size_t pos = 0, size_t len = npos);

    //выполняет замену подстроки в строке начиная с позиции pos и охватывая len символов.
    //Если len равняется npos, то удаление происходит с позиции pos до конца строки.
    //Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");.
    String& replace(size_t pos, size_t len, const String& str);
    String& replace(size_t pos, size_t len, const char* str);
    String& replace(size_t pos, size_t len, size_t n, char c);

    void swap(String& str);
    const char* data();

    //возвращает индекс подстроки str (или символа c) в строке. pos - задает позицию с которой начинать поиск.
    //Если подстроку не нашли или pos больше размера строки, метод возращает npos.
    size_t find(const String& str, size_t pos = 0);
    size_t find(const char* str, size_t pos = 0);
    size_t find(char c, size_t pos = 0);

    String substr(size_t pos = 0, size_t len = npos);

    int compare(const String& str);
  //статическая константа с максимальным значением size_t.
  // Это значением может быть использовано в методах для параметра len, что означает "до конца строки".
  //Также эта константа может быть использована в качестве возвращаемого значения для указания отсутствия совпадений.
    static const size_t npos = -1;

    size_t countRef();
};
