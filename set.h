#ifndef _SET_H_
#define _SET_H_

#include <cstdio>
#include <iosfwd>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <climits>

int sgn(int p);

class Set{
public:
    Set();      // конструктор по умолчанию
    Set(int p); // конструктор преобразования типа
    Set(const Set &s); //конструктор копирования
    ~Set(); //деструктор
    
    void swap(Set &s);
    //-----------------------------------------------
    Set operator+(const Set &s) const; //объединение
    Set& operator+=(const Set &s);
    
    Set operator*(const Set &s) const; // пересечение
    Set& operator*=(const Set &s);
    
    Set operator-(const Set &s) const; //разность
    Set& operator-=(const Set &s);
    //-----------------------------------------------
    
    Set& operator=(const Set &s);
    
    int operator==(const Set &s) const;
    int operator!=(const Set &s) const;
    int operator>(const Set &s) const;
    int operator>=(const Set &s) const;
    int operator<(const Set &s) const;
    int operator<=(const Set &s) const;
    
    int size() const; //размер множества
    int isEmpty() const; //проверяет пустоту (1 если пустой, 0 если нет)
    int operator() (int p) const; //проверка принадлежности элемента множеству (0 или 1)
    
    friend std::ostream &operator<<(std::ostream &o, const Set &s); //дружественная функция печати    

private:
    size_t  sizepos_, sizeneg_;
    unsigned int *datapos_, *dataneg_; //массивы унсигнутых интов для положительных и отрицательных
    unsigned int n_; //количество элементов в множестве
    //в одном унсигнутом инте 32 числа
};

#endif
