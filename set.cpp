#include "set.h"

//вспомогательные функции
//определение знака int
int sgn(int p){
    unsigned int i = 1u << 31;
    
    if(p == 0)
        return 0;
    
    if((p&i) == 0){
        return 1;
    }else{
        return -1;
    }
}

//посчитать кол-во единиц в унсигнутом инте
int ucount(unsigned int x){
    unsigned int i, k = 0;
    for(i = 1u; i != (1u << 31); i <<= 1){
        if(x&i)
            k++;
    }
    return k;
}

//конструктор по умолчанию
Set::Set(): sizepos_(0), sizeneg_(0), datapos_(nullptr), dataneg_(nullptr), n_(0){}

//создаём одноэлементное множество
Set::Set(int p): sizepos_(0), sizeneg_(0), datapos_(nullptr), dataneg_(nullptr), n_(1){
    try{
        if(sgn(p) != -1){
            sizepos_ = p/32 + 1;
            datapos_ = new unsigned int[sizepos_]();
            datapos_[p/32] |= (1u << p%32);
        }else{
            sizeneg_ = (-p-1)/32 + 1;
            dataneg_ = new unsigned int[sizeneg_]();
            dataneg_[(-p-1)/32] |= (1u << ((-p-1)%32));
        }
    }
    catch(const std::bad_alloc& e){
        throw;
    }

}

//конструктор копирования
Set::Set(const Set &s){
    try{
        size_t sp = s.sizepos_, sn = s.sizeneg_;
        datapos_ = new unsigned int[sp];
        dataneg_ = new unsigned int[sn];
        
        n_ = s.n_;
        sizepos_ = sp;
        sizeneg_ = sn;
        
        memcpy(datapos_, s.datapos_, sizepos_*sizeof(unsigned int));
        memcpy(dataneg_, s.dataneg_, sizeneg_*sizeof(unsigned int));
    }
    catch(const std::bad_alloc& e){
        throw;
    }

}

Set::~Set(){
    delete[] dataneg_;
    delete[] datapos_;
}



void Set::swap(Set &s) {
    size_t  sp = sizepos_, sn = sizeneg_;
    unsigned int *dp = datapos_, *dn = dataneg_;
    unsigned int nnew = n_; 

    sizepos_ = s.sizepos_;
    sizeneg_ = s.sizeneg_;
    datapos_ = s.datapos_;
    dataneg_ = s.dataneg_;
    n_ = s.n_;

    s.sizepos_ = sp;
    s.sizeneg_ = sn;
    s.datapos_ = dp;
    s.dataneg_ = dn;
    s.n_ = nnew;
}

//мощность множества
int Set::size() const{
    return n_;
}

int Set::isEmpty() const{
    if(n_ == 0)
        return 1;
    else
        return 0;
}

//принадлежность элемента множеству
int Set::operator() (int p) const{
    unsigned int x;
    
    //если чиселко положительное или ноль
    if(sgn(p) != -1){
        if((int)sizepos_ < p/32)
            return 0;
        
        x = datapos_[p/32];
        
        if(x & (1u<<(p%32)))
            return 1;
        else
            return 0;
    }else{
        //если чиселко отрицательное
        if((int)sizeneg_ < (-p-1)/32)
            return 0;
        
        x = dataneg_[(-p-1)/32];
        
        if(x & (1u<<((-p-1)%32)))
            return 1;
        else
            return 0;
    }
}

//объединение
Set Set::operator+(const Set &s) const{
    try{
        //результативное множество 
        Set res;
        size_t i, maxpos, minpos, maxneg, minneg;
        
        maxpos = std::max(sizepos_, s.sizepos_);
        minpos = std::min(sizepos_, s.sizepos_);
        
        maxneg = std::max(sizeneg_, s.sizeneg_);
        minneg = std::min(sizeneg_, s.sizeneg_);
        
        //подготовка:
        //расширяем массивы до максимального из двух
        
        res.datapos_ = new unsigned int[maxpos];
        res.dataneg_ = new unsigned int[maxneg];
        
        res.sizepos_ = maxpos;
        res.sizeneg_ = maxneg;
        res.n_ = 0;
        //-------------------------------------------
        
        //для положительных
        for(i = 0; i < minpos; ++i){
            res.datapos_[i] = datapos_[i] | s.datapos_[i];
            res.n_ += ucount(res.datapos_[i]);
        }
        if(sizepos_ >= s.sizepos_){
            for(i = minpos; i < maxpos; ++i){
                res.datapos_[i] = datapos_[i];
                res.n_ += ucount(res.datapos_[i]);
            }
        }else{
            for(i = minpos; i < maxpos; ++i){
                res.datapos_[i] = s.datapos_[i];
                res.n_ += ucount(res.datapos_[i]);
            }
        }
        //
        
        //для отрицательных
        for(i = 0; i < minneg; ++i){
            res.dataneg_[i] = dataneg_[i] | s.dataneg_[i];
            res.n_ += ucount(res.dataneg_[i]);
        }
        if(sizeneg_ >= s.sizeneg_){
            for(i = minneg; i < maxneg; ++i){
                res.dataneg_[i] = dataneg_[i];
                res.n_ += ucount(res.dataneg_[i]);
            }
        }else{
            for(i = minneg; i < maxneg; ++i){
                res.dataneg_[i] = s.dataneg_[i];
                res.n_ += ucount(res.dataneg_[i]);
            }
        }
        //
        
        return res;
    }
    catch(const std::bad_alloc& e){
        throw;
    }

}

Set& Set::operator+=(const Set &s){
    Set res(s + *this);
    swap(res);
    return *this;
}


//пересечение
Set Set::operator*(const Set &s) const{
    try{
        //результативное множество 
        Set res;
        size_t i, maxpos, minpos, maxneg, minneg;
        
        maxpos = std::max(sizepos_, s.sizepos_);
        minpos = std::min(sizepos_, s.sizepos_);
        
        maxneg = std::max(sizeneg_, s.sizeneg_);
        minneg = std::min(sizeneg_, s.sizeneg_);
        
        //подготовка:
        //расширяем массивы до максимального из двух
        res.datapos_ = new unsigned int[maxpos];
        res.dataneg_ = new unsigned int[maxneg];
        
        res.sizepos_ = maxpos;
        res.sizeneg_ = maxneg;
        
        res.n_ = 0;
        //-------------------------------------------
        
        //для положительных
        for(i = 0; i < minpos; ++i){
            res.datapos_[i] = datapos_[i] & s.datapos_[i];
            res.n_ += ucount(res.datapos_[i]);
        }
        for(i = minpos; i < maxpos; ++i){
            res.datapos_[i] = 0u;
        }
        //
        
        //для отрицательных
        for(i = 0; i < minneg; ++i){
            res.dataneg_[i] = dataneg_[i] & s.dataneg_[i];
            res.n_ += ucount(res.dataneg_[i]);
        }
        for(i = minneg; i < maxneg; ++i){
            res.dataneg_[i] = 0u;
        }
        //
        
        return res;
    }
    catch(const std::bad_alloc& e){
        throw;
    }

}

Set& Set::operator*=(const Set &s){
    Set res(s * *this);
    swap(res);
    return *this;
}


//разность
Set Set::operator-(const Set &s) const{
    try{
        //результативное множество 
        Set res;
        size_t i, maxpos, minpos, maxneg, minneg;
        
        maxpos = std::max(sizepos_, s.sizepos_);
        minpos = std::min(sizepos_, s.sizepos_);
        
        maxneg = std::max(sizeneg_, s.sizeneg_);
        minneg = std::min(sizeneg_, s.sizeneg_);
        
        //подготовка:
        //расширяем массивы до максимального из двух
        res.datapos_ = new unsigned int[maxpos];
        res.dataneg_ = new unsigned int[maxneg];
        
        res.sizepos_ = maxpos;
        res.sizeneg_ = maxneg;
        
        res.n_ = 0;
        //-------------------------------------------
        
        //для положительных
        for(i = 0; i < minpos; ++i){
            res.datapos_[i] = datapos_[i] & ~s.datapos_[i];
            res.n_ += ucount(res.datapos_[i]);
        }
        if(sizepos_ >= s.sizepos_){
            for(i = minpos; i < maxpos; ++i){
                res.datapos_[i] = datapos_[i];
                res.n_ += ucount(res.datapos_[i]);
            }
        }else{
            for(i = minpos; i < maxpos; ++i){
                res.datapos_[i] = 0u;
            }
        }
        //
        
        //для отрицательных
        for(i = 0; i < minneg; ++i){
            res.dataneg_[i] = dataneg_[i] & ~s.dataneg_[i];
            res.n_ += ucount(res.dataneg_[i]);
        }
        if(sizeneg_ >= s.sizeneg_){
            for(i = minneg; i < maxneg; ++i){
                res.dataneg_[i] = dataneg_[i];
                res.n_ += ucount(res.dataneg_[i]);
            }
        }else{
            for(i = minneg; i < maxneg; ++i){
                res.dataneg_[i] = 0u;
            }
        }
        //
        
        return res;
    }
    catch(const std::bad_alloc& e){
        throw;
    }

}

Set& Set::operator-=(const Set &s){
    Set res(s - *this);
    swap(res);
    return *this;
}

//оператор присваивания
Set& Set::operator=(const Set &s){
    Set res(s);
    swap(res);
    return *this;
}

//--------------------------------------
int Set::operator==(const Set &s) const{
    return n_ == s.n_;
}

int Set::operator!=(const Set &s) const{
    return n_ != s.n_;
}
    
int Set::operator>(const Set &s) const{
    return n_ > s.n_;
}

int Set::operator>=(const Set &s) const{
    return n_ >= s.n_;
}
    
int Set::operator<(const Set &s) const{
    return n_ < s.n_;
}

int Set::operator<=(const Set &s) const{
    return n_ <= s.n_;
}
//--------------------------------------

//функция печати
std::ostream &operator<<(std::ostream &o, const Set &s) {
    size_t i;
    unsigned int j, k, f;
    o << "{";
    
    //выводим отрицательные
    f = 0;
    for(i = 0; i < s.sizeneg_; ++i){
        
        k=1;
        for(j = 1u; j != (1u << 31); j <<= 1){
            if(s.dataneg_[i] & j){
                if(f == 0){
                    o << "-" << (i*32 + k);
                    f = 1;
                }else{
                    o << ", " << "-" << (i*32 + k);
                }
            }
            k++;
        }
    }
    
    //выводим положительные (и ноль)
    for(i = 0; i < s.sizepos_; ++i){
        
        k=1;
        for(j = 1u; j != (1u << 31); j <<= 1){
            if(s.datapos_[i] & j){
                if(f == 0){
                    o << (i*32 + k - 1);
                    f = 1;
                }else{
                    o << ", " << (i*32 + k - 1);
                }
            }
            k++;
        }
    }
    o << "}"; 
    return o;
}
