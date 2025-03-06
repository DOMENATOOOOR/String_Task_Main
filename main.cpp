#include <iostream>
#include "String.h"

int main() {
    String str1("Hello");
    String str2 = str1;
    String str3("World");
    str1 += "str987654321";
    String str4 = str1;
    std::cout<<str1.back()<<std::endl;
    std::cout<<str1.front()<<std::endl;
    str2 = "";
    str1.clear();
    str2.clear();
    str4.clear();
    str3.clear();
    return 0;
}