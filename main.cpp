#include "set.h"

//преобразование в инт
int toInt(const char *str, int *resI){
    char *e;
    int res;

    errno = 0;
    res = strtol(str, &e, 10);
    if(!errno && *e == '\0')
        if(INT_MIN <= res && res <= INT_MAX ){
            *resI = res;
            return 1;
        }
        
    return 0;
}

void manual(const char *mes){
    const char *Instruction =
        "Тест 0. Конструктор по умолчанию.\n"
        "Тест 1. Конструктор преобразования типа.\n"
        "Тест 2. Конструктор копирования.\n"
        "Тест 3. Оператор присваивания (=).\n"
        "Тест 4. Оператор сложения (объединения) (+).\n"
        "Тест 5. Оператор присваивающего сложения (+=).\n"
        "Тест 6. Оператор умножения (пересечения) (*).\n"
        "Тест 7. Оператор присваивающего умножения (*=).\n"
        "Тест 8. Оператор вычитания (-).\n"
        "Тест 9. Оператор присваивающего вычитания (-=).\n"
        "Тест 10. Оператор равенства (==).\n"
        "Тест 11. Оператор неравенства (!=).\n"
        "Тест 12. Операторы сравнения (>, >=).\n"
        "Тест 13. Операторы сравнения (<, <=).\n"
        "Тест 14. Метод принадлежности элемента множеству.\n"
        "Тест 15. Метод проверки множества на пустоту .isEmpty().\n"
        "Тест 16. Метод, возвращающий размер множества .size().\n";

    std::cout << "Usage: " << mes << " ** " << std::endl << Instruction << std::endl;
}

//тесты
void test00(){
    std::cout << std::endl << "Тест 0. Конструктор по умолчанию." << std::endl;
    Set s;
    std::cout << s << std::endl;
}

void test01(){
    std::cout << std::endl << "Тест 1. Конструктор преобразования типа." << std::endl;
    
    try{
        Set s(65);
        std::cout << s << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test02(){
    std::cout << std::endl << "Тест 2. Конструктор копирования." << std::endl;
    
    try{
        Set s1(-129), s2(s1);
        std::cout << "s1: " << s1 << std::endl;
        std::cout << "s2: " << s2 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test03(){
    std::cout << std::endl << "Тест 3. Оператор присваивания (=)." << std::endl;
    
    
    try{
        Set s1 = Set(1) + Set(2) + Set(3), s2;
        s2 = s1;
        
        std::cout << "s1: " << s1 << std::endl;
        std::cout << "s2: " << s2 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test04(){
    std::cout << std::endl << "Тест 4. Оператор сложения (объединения) (+)." << std::endl;
    
    try{
        Set s1 = Set(1) + Set(2) + Set(3), s2 = Set(-10) + Set(1), s3;
        s3 = s1 + s2;
        
        std::cout << "s1: " << s1 << std::endl;
        std::cout << "s2: " << s2 << std::endl;
        std::cout << "s3 = s1 + s2: " << s3 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test05(){
    std::cout << std::endl << "Тест 5. Оператор присваивающего сложения (+=)." << std::endl;
    
    try{
        Set s1 = Set(1) + Set(2) + Set(-10), s2 = Set(-10) + Set(-99);
        std::cout << "s1 old: " << s1 << std::endl;
        std::cout << "s2 old: " << s2 << std::endl;
        
        std::cout << "did: s2 += s1" << std::endl;
        s2 += s1;
        
        std::cout << "s2 new: " << s2 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test06(){
    std::cout << std::endl << "Тест 6. Оператор умножения (пересечения) (*)." << std::endl;
    
    try{
        Set s1 = Set(1) + Set(2) + Set(3), s2 = Set(1) + Set(2) + Set(-10), s3;
        s3 = s1 * s2;
        
        std::cout << "s1: " << s1 << std::endl;
        std::cout << "s2: " << s2 << std::endl;
        std::cout << "s3 = s1 * s2: " << s3 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test07(){
    std::cout << std::endl << "Тест 7. Оператор присваивающего умножения (*=)." << std::endl;
    
    try{
        Set s1 = Set(1) + Set(2) + Set(-10), s2 = Set(-10) + Set(-99);
        std::cout << "s1 old: " << s1 << std::endl;
        std::cout << "s2 old: " << s2 << std::endl;
        
        std::cout << "did: s2 *= s1" << std::endl;
        s2 *= s1;

        std::cout << "s2 new: " << s2 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test08(){
    std::cout << std::endl << "Тест 8. Оператор вычитания (-)." << std::endl;
    
    try{
        Set s1 = Set(1) + Set(2) + Set(100), s2 = Set(1) + Set(2), s3;
        s3 = s1 - s2;
        
        std::cout << "s1: " << s1 << std::endl;
        std::cout << "s2: " << s2 << std::endl;
        std::cout << "s3 = s1 - s2: " << s3 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test09(){
    std::cout << std::endl << "Тест 9. Оператор присваивающего вычитания (-=)." << std::endl;
    
    try{
        Set s1 = Set(1) + Set(2) + Set(3), s2 = Set(10) + Set(-99) + Set(1) + Set(2);
        std::cout << "s1 old: " << s1 << std::endl;
        std::cout << "s2 old: " << s2 << std::endl;
        
        std::cout << "did: s2 -= s1" << std::endl;
        s2 -= s1;
        
        std::cout << "s2 new: " << s2 << std::endl;
    }
    catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void test10(){
    std::cout << std::endl << "Тест 10. Оператор равенства (==)." << std::endl;
    Set s1(35), s2(78), s3 = s1 + s2;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    
    if(s1 == s2)
        std::cout<< "|s1| == |s2| - true" << std::endl;
    else
        std::cout<< "|s1| == |s2| - false" << std::endl;
    
    if(s1 == s3)
        std::cout<< "|s1| == |s3| - true" << std::endl;
    else
        std::cout<< "|s1| == |s3| - false" << std::endl;
}

void test11(){
    std::cout << std::endl << "Тест 11. Оператор неравенства (!=)." << std::endl;
    Set s1(35), s2(78), s3 = s1 + s2;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    
    if(s1 != s2)
        std::cout<< "|s1| != |s2| - true" << std::endl;
    else
        std::cout<< "|s1| != |s2| - false" << std::endl;
    
    if(s1 != s3)
        std::cout<< "|s1| != |s3| - true" << std::endl;
    else
        std::cout<< "|s1| != |s3| - false" << std::endl;
}

void test12(){
    std::cout << std::endl << "Тест 12. Операторы сравнения (>, >=)." << std::endl;
    Set s1(35), s2(78), s3 = s1 + s2;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    
    if(s1 > s2)
        std::cout<< "|s1| > |s2| - true" << std::endl;
    else
        std::cout<< "|s1| > |s2| - false" << std::endl;
    
    if(s1 > s3)
        std::cout<< "|s1| > |s3| - true" << std::endl;
    else
        std::cout<< "|s1| > |s3| - false" << std::endl;
    
    if(s1 >= s2)
        std::cout<< "|s1| >= |s2| - true" << std::endl;
    else
        std::cout<< "|s1| >= |s2| - false" << std::endl;
    
    if(s1 >= s3)
        std::cout<< "|s1| >= |s3| - true" << std::endl;
    else
        std::cout<< "|s1| >= |s3| - false" << std::endl;
}

void test13(){
    std::cout << std::endl << "Тест 13. Операторы сравнения (<, <=)." << std::endl;
    Set s1(35), s2(78), s3 = s1 + s2;
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    
    if(s1 < s2)
        std::cout<< "|s1| < |s2| - true" << std::endl;
    else
        std::cout<< "|s1| < |s2| - false" << std::endl;
    
    if(s1 < s3)
        std::cout<< "|s1| < |s3| - true" << std::endl;
    else
        std::cout<< "|s1| < |s3| - false" << std::endl;
    
    if(s1 <= s2)
        std::cout<< "|s1| <= |s2| - true" << std::endl;
    else
        std::cout<< "|s1| <= |s2| - false" << std::endl;
    
    if(s1 <= s3)
        std::cout<< "|s1| <= |s3| - true" << std::endl;
    else
        std::cout<< "|s1| <= |s3| - false" << std::endl;
}

void test14(){
    std::cout << std::endl << "Тест 14. Метод принадлежности элемента множеству." << std::endl;
    Set s= Set(-90) + Set(5) + Set(0);
    int a = -90, b = 6;
    std::cout << "s: " << s << std::endl;
    
    if(s(a))
        std::cout << a << " принадлежит множеству" << std::endl;
    else
        std::cout << a << " НЕ принадлежит множеству" << std::endl;
    
    if(s(b))
        std::cout << b << " принадлежит множеству" << std::endl;
    else
        std::cout << b << " НЕ принадлежит множеству" << std::endl;
}

void test15(){
    std::cout << std::endl << "Тест 15. Метод проверки множества на пустоту .isEmpty()." << std::endl;
    Set s1, s2(8), s3 = Set(1) + Set(2) + Set(3);
    
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    
    if(s1.isEmpty())
        std::cout << "s1 пустой" << std::endl;
    else
        std::cout << "s1 непустой" << std::endl;
    
    if(s2.isEmpty())
        std::cout << "s2 пустой" << std::endl;
    else
        std::cout << "s2 непустой" << std::endl;
    
    if(s3.isEmpty())
        std::cout << "s3 пустой" << std::endl;
    else
        std::cout << "s3 непустой" << std::endl;
}

void test16(){
    std::cout << std::endl << "Тест 16. Метод, возвращающий размер множества .size()." << std::endl;
    Set s1, s2(8), s3 = Set(1) + Set(2) + Set(3);
    
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    
    std::cout << "Размер s1: " << s1.size() << std::endl;
    std::cout << "Размер s2: " << s2.size() << std::endl;
    std::cout << "Размер s3: " << s3.size() << std::endl;
    
}

int main(int ac, char *av[]) {
    if (ac == 2){
        int i = 0;

        if(toInt(av[1], &i) == 1){
            switch(i){
                case 0:
                    test00();
                    break;
                case 1:
                    test01();
                    break;
                case 2:
                    test02();
                    break;
                case 3:
                    test03();
                    break;
                case 4:
                    test04();
                    break;
                case 5:
                    test05();
                    break;
                case 6:
                    test06();
                    break;
                case 7:
                    test07();
                    break;
                case 8:
                    test08();
                    break;
                case 9:
                    test09();
                    break;
                case 10:
                    test10();
                    break;
                case 11:
                    test11();
                    break;
                case 12:
                    test12();
                    break;
                case 13:
                    test13();
                    break;
                case 14:
                    test14();
                    break;
                case 15:
                    test15();
                    break;
                case 16:
                    test16();
                    break;
                default:
                    std::cout << "Такого теста нет" << std::endl;
                    return -1;
                    break;
            }
        }else if(strcmp(av[1], "all") == 0){
            test00();
            test01();
            test02();
            test03();
            test04();
            test05();
            test06();
            test07();
            test08();
            test09();
            test10();
            test11();
            test12();
            test13();
            test14();
            test15();
            test16();
        }else{
            std::cout << "Некорректные данные" << std::endl;
            return -1;
        }
    }
    else if(ac == 1)
        manual(av[0]);
    else{
        std::cout << "Некорректные данные" << std::endl;
        return -1;
    }
    
    return 0;
}
