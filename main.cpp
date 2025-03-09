#include "String.h"

int main() {
    String str1("Hello");
    String str2("dddd");
    String str3("World");
    str3[2] = 'F';
    str3.erase(1, 3);
    str3.insert(2, str1);
    str1 += "str987654321";
    str1.replace(5,3,4,'d');
    size_t n1 = str1.find(str3, 0);
    size_t n2 = str1.find('s', 0);
    size_t n3 = str1.find("srew", 0);
    str1.swap(str2);
    String str4 = str1;
    std::cout << str4[2] << std::endl;
    String str5;
    str5 = str4.substr(2, 2);
    std::cout<<str2.data()<< std::endl;
    str2.insert(2, "I am sexy and I know it!");
    str1.clear();
    str2.clear();
    str3.clear();
    str4.clear();
    return 0;
}
