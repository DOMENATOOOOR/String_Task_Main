#include "String.h"

int main() {
    String str1("Hello");
    String str2("dddd");
    String str3("World");
    std::cout<<str3.at(1)<<std::endl;
    str3[2] = 'F';
    std::cout << str3.size() << std::endl;
    str3.erase(1, 3);
    str3.insert(2, str1);
    str1 += "str987654321";
    str1.replace(5,3,4,'d');
    std::cout<<str1.find(str3, 0)<<std::endl;;
    std::cout<<str1.find('s', 0)<<std::endl;
    std::cout<<str1.find("srew", 0)<<std::endl;;
    String str6 = str1;
    str6.at(1) = str1.at(3);
    str6.erase();
    str1.replace(5,3,4,'d');
    str1.swap(str2);
    std::cout<<str6.compare(str2)<< std::endl;
    String str4(str1);
    str4.reserve(1);
    str4 += str1;
    str4 += "fsss";
    std::cout << str4[2] << std::endl;
    String str5 = str4.substr(2, 2);
    std::cout<<str2.data()<< std::endl;
    str2.insert(2, "What the fox say?");
    str2.clear();
    std::cout<<str2.data()<< std::endl;
    str5.clear();
    str4.clear();
    return 0;
}
