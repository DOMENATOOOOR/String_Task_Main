#include "../String.h"
#include <gtest/gtest.h>

TEST(StringTest, DefaultConstructor) {
    String str;
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(str.capacity(), 0);
    EXPECT_EQ(str.data(), nullptr);
}

// Тестирование конструктора с C-строкой
TEST(StringTest, ConstructorWithCString) {
    String str("Hello");
    EXPECT_EQ(str.size(), 5);
    EXPECT_EQ(str.capacity(), 6); // +1 для '0'
    EXPECT_STREQ(str.data(), "Hello");
}

// Тестирование конструктора с C-строкой и длиной
TEST(StringTest, ConstructorWithCStringAndLength) {
    String str("Hello, World!", 5);
    EXPECT_EQ(str.size(), 5);
    EXPECT_STREQ(str.data(), "Hello");
}

// Тестирование конструктора с символом
TEST(StringTest, ConstructorWithChar) {
    String str(5, 'A');
    EXPECT_EQ(str.size(), 5);
    EXPECT_STREQ(str.data(), "AAAAA");
}

// Тестирование конструктора копирования
TEST(StringTest, CopyConstructor) {
    String original("Copy me");
    String copy(original);
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_STREQ(copy.data(), original.data());
}

// Тестирование метода front()
TEST(StringTest, FrontMethod) {
    String str("Hello");
    EXPECT_EQ(str.front(), 'H');
}

// Тестирование оператора += с другим объектом String
TEST(StringTest, OperatorPlusEqualsString) {
    String str1("Hello");
    String str2(" World");
    str1 += str2;
    EXPECT_STREQ(str1.data(), "Hello World");
}

// Тестирование оператора += с C-строкой
TEST(StringTest, OperatorPlusEqualsCString) {
    String str("Hello");
    str += " World";
    EXPECT_STREQ(str.data(), "Hello World");
}

// Тестирование оператора += с символом
TEST(StringTest, OperatorPlusEqualsChar) {
    String str("Hello");
    str += '!';
    EXPECT_STREQ(str.data(), "Hello!");
}

// Тестирование деструктора
TEST(StringTest, Destructor) {
    {
        String str("Temporary");
        EXPECT_EQ(str.size(), 9);
    } // Здесь объект str выходит из области видимости и должен быть уничтожен.
    /*
        [       OK ] StringTest.Destructor (0 ms)
        Вызвался деструктор (для объекта, который не ссылается на другие объекты)
     */
}

// Тестирование размера
TEST(StringTest, Size) {
    String str("Hello");
    EXPECT_EQ(str.size(), 5);
}

// Тестирование размера с учетом нуль-терминатора
TEST(StringTest, Capacity) {
    String str("Hello");
    EXPECT_EQ(str.capacity(), 6);
}

// Тестирование данных в data
TEST(StringTest, Data) {
    String str("Hello");
    EXPECT_STREQ(str.data(), "Hello");
}

// Тестирование числа ссылок
TEST(StringTest, RefCount) {
    String str("Hello");
    String str2(str);
    EXPECT_EQ(str2.countRef(), 2);
    EXPECT_EQ(str.countRef(), 2);
}

// Тестирование резерва
TEST(StringTest, Reserve) {
    String str("Hello");
    str.reserve(10);
    EXPECT_EQ(str.size(), 10);
}

// Тестирование очистки объекта
TEST(StringTest, Clear) {
    String str("Hello");
    str.clear();
    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(str.capacity(), 0);
    EXPECT_EQ(str.data(), nullptr);
    EXPECT_EQ(str.countRef(), 1);
}

// Тестирование пустоты
TEST(StringTest, Empty) {
    String str;
    EXPECT_EQ(str.empty(), true);
}

// Тестирование метода at() для неконстантного объекта
TEST(StringTest, AtMethodNonConst) {
    String str("Hello");
    EXPECT_EQ(str.at(0), 'H');
    EXPECT_EQ(str.at(4), 'o');
}

// Тестирование метода at() для константного объекта
TEST(StringTest, AtMethodConst) {
    const String str("World");
    EXPECT_EQ(str.at(0), 'W');
    EXPECT_EQ(str.at(3), 'l');
}

// Тестирование метода at() с выходом за пределы
TEST(StringTest, AtMethodOutOfRange) {
    String str("Test");
    EXPECT_THROW(str.at(4), std::out_of_range);
}

// Тестирование оператора [] для неконстантного объекта
TEST(StringTest, OperatorSquareBracketsNonConst) {
    String str("Hello");
    EXPECT_EQ(str[1], 'e');
    str[1] = 'a';
    EXPECT_EQ(str[1], 'a');
}

// Тестирование оператора [] для константного объекта
TEST(StringTest, OperatorSquareBracketsConst) {
    const String str("World");
    EXPECT_EQ(str[2], 'r');
}

// Тестирование оператора [] с выходом за пределы
TEST(StringTest, OperatorSquareBracketsOutOfRange) {
    String str("Test");
    EXPECT_THROW(str[4], std::out_of_range);
}

// Тестирование оператора присваивания для строки
TEST(StringTest, AssignmentOperatorString) {
    String str1("Hello");
    String str2;
    str2 = str1;
    EXPECT_STREQ(str2.data(), "Hello");
}

// Тестирование оператора присваивания для C-style строки
TEST(StringTest, AssignmentOperatorCString) {
    String str;
    str = "Goodbye";
    EXPECT_STREQ(str.data(), "Goodbye");
}

// Тестирование самоприсваивания
TEST(StringTest, AssignmentOperatorSelfAssignment) {
    String str("Hello");
    str = str;
    EXPECT_STREQ(str.data(), "Hello");
}

// Тестирование метода insert с объектом String
TEST(StringTest, InsertString) {
    String str("Hello");
    String toInsert(" World");
    str.insert(5, toInsert);
    EXPECT_STREQ(str.data(), "Hello World");
}

// Тестирование метода insert с C-style строкой
TEST(StringTest, InsertCString) {
    String str("Hello");
    str.insert(5, " World");
    EXPECT_STREQ(str.data(), "Hello World");
}

// Тестирование метода insert с выходом за пределы
TEST(StringTest, InsertOutOfRange) {
    String str("Hello");
    EXPECT_THROW(str.insert(6, " World"), std::out_of_range);
}

// Тестирование метода insert с нулевым указателем
TEST(StringTest, InsertNullPointer) {
    String str("Hello");
    EXPECT_THROW(str.insert(5, nullptr), std::logic_error);
}

// Тестирование метода erase с корректными параметрами
TEST(StringTest, EraseValidParameters) {
    String str("Hello, World!");
    str.erase(5, 7);
    EXPECT_STREQ(str.data(), "Hello!");
}

// Тестирование метода erase с выходом за пределы
TEST(StringTest, EraseOutOfRange) {
    String str("Hello");
    EXPECT_THROW(str.erase(10, 1), std::out_of_range);
}

// Тестирование метода erase с len равным npos
TEST(StringTest, EraseLenIsNpos) {
    String str("Hello, World!");
    str.erase(5, String::npos);
    EXPECT_STREQ(str.data(), "Hello");
}

// Тестирование метода erase с len равным 0
TEST(StringTest, EraseLenIsZero) {
    String str("Hello");
    str.erase(2, 0);
    EXPECT_STREQ(str.data(), "Hello");
}

// Тестирование метода find для поиска символа
TEST(StringTest, FindCharacter) {
    String str("Hello, World!");
    EXPECT_EQ(str.find('W', 0), 7);
    EXPECT_EQ(str.find('o', 5), 8);
}

// Тестирование метода find для отсутствующего символа
TEST(StringTest, FindCharacterNotFound) {
    String str("Hello");
    EXPECT_EQ(str.find('z', 0), 18446744073709551615);
}


// Тестирование метода substr с корректными параметрами
TEST(StringTest, SubstrValidParameters) {
    String str("Hello, World!");
    String sub = str.substr(7, 5);
    EXPECT_STREQ(sub.data(), "World");
}

// Тестирование метода substr с выходом за пределы
TEST(StringTest, SubstrOutOfRange) {
    String str("Hello");
    EXPECT_THROW(str.substr(10, 1), std::out_of_range);
}

// Тестирование метода substr с len равным npos
TEST(StringTest, SubstrLenIsNpos) {
    String str("Hello, World!");
    String sub = str.substr(7, String::npos);
    EXPECT_STREQ(sub.data(), "World!");
}

// Тестирование метода substr с len равным 0
TEST(StringTest, SubstrLenIsZero) {
    String str("Hello");
    String sub = str.substr(2, 0);
    EXPECT_STREQ(sub.data(), "");
}

// Тестирование метода compare для равных строк
TEST(StringTest, CompareEqualStrings) {
    String str1("Hello");
    String str2("Hello");
    EXPECT_EQ(str1.compare(str2), 0);
}

// Тестирование метода compare для разных строк
TEST(StringTest, CompareDifferentStrings) {
    String str1("Hello");
    String str2("World");
    EXPECT_LT(str1.compare(str2), 0);
}

// Тестирование метода compare для строк разной длины
TEST(StringTest, CompareDifferentLengthStrings) {
    String str1("Hello");
    String str2("Hello!");
    EXPECT_LT(str1.compare(str2), 0);
}

// Тестирование метода replace с заменой подстроки на другую строку
TEST(StringTest, ReplaceSubstringWithString) {
    String str("Hello, World!");
    String replacement("Beautiful");
    str.replace(7, 5, replacement);
    EXPECT_STREQ(str.data(), "Hello, Beautiful!");
}

// Тестирование метода replace с заменой подстроки на C-строку
TEST(StringTest, ReplaceSubstringWithCString) {
    String str("Hello, World!");
    str.replace(7, 5, "Universe");
    EXPECT_STREQ(str.data(), "Hello, Universe!");
}

// Тестирование метода replace с заменой символов
TEST(StringTest, ReplaceSubstringWithChar) {
    String str("Hello");
    str.replace(2, 3, 2, 'x');
    EXPECT_STREQ(str.data(), "Hexx");
}

// Тестирование метода replace с выходом за пределы
TEST(StringTest, ReplaceOutOfRange) {
    String str("Hello");
    EXPECT_THROW(str.replace(10, 1, "Test"), std::out_of_range);
}

// Тестирование метода replace с нулевой длиной замены
TEST(StringTest, ReplaceWithZeroLength) {
    String str("Hello, World!");
    str.replace(5, 0, " Beautiful");
    EXPECT_STREQ(str.data(), "Hello Beautiful, World!");
}

// Тестирование метода swap
TEST(StringTest, SwapStrings) {
    String str1("Hello");
    String str2("World");
    str1.swap(str2);
    EXPECT_STREQ(str1.data(), "World");
    EXPECT_STREQ(str2.data(), "Hello");
}

// Тестирование метода swap с пустыми строками
TEST(StringTest, SwapWithEmptyString) {
    String str1("Hello");
    String str2("");
    str1.swap(str2);
    EXPECT_STREQ(str1.data(), "");
    EXPECT_STREQ(str2.data(), "Hello");
}

// Тестирование метода find для поиска существующей подстроки
TEST(StringTest, FindExistingSubstring) {
    String str("Hello, World!");
    EXPECT_EQ(str.find("World"), 7); // "World" начинается с 7-го символа
}

// Тестирование метода find для поиска несуществующей подстроки
TEST(StringTest, FindNonExistingSubstring) {
    String str("Hello, World!");
    EXPECT_EQ(str.find("Universe"), 18446744073709551615);
}

// Тестирование метода find с начальной позицией
TEST(StringTest, FindWithPosition) {
    String str("Hello, Hello!");
    EXPECT_EQ(str.find("Hello", 5), 7);
}

// Тестирование метода find с выходом за пределы
TEST(StringTest, FindOutOfRange) {
    String str("Hello");
    EXPECT_EQ(str.find("o", 10), 18446744073709551615);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}