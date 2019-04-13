#ifndef ARRAY_H
#define ARRAY_H

#pragma once
#include <iostream>
#include <algorithm>

template <class T>
class Array
{
    public:
        Array();
        Array(int);
        Array(const Array<T>&);

        int size() const {return aend - abegin;};
        void push_back(T);
        void insert(T, int);
        void drop(int);

        T* v_begin() { return abegin; };
        T* v_end() { return aend; };

        T& operator[](int pos) {return arr[pos];};

        void operator+=(T);
        void operator*=(T);
        template <class TT>
        friend Array<TT> operator+(const Array<TT>&, const Array<TT>&);

        template <class TT>
        friend Array<TT> operator*(const Array<TT>&, const Array<TT>&);

        template <class TT>
        friend Array<TT> operator+(const double&, const Array<TT>&);

        template <class TT>
        friend Array<TT> operator*(const double&, const Array<TT>&);

        template <class TT>
        friend bool operator==(const Array<TT>&, const Array<TT>&);

        template <class TT>
        friend bool operator!=(const Array<TT>&, const Array<TT>&);

        template <class TT>
        friend std::ostream& operator<<(std::ostream&, const Array<TT>&);

        template <class TT>
        friend std::istream& operator>>(std::istream&, Array<TT>&);

        ~Array();

    protected:
        T *arr, *abegin, *aend;
        int _size;

        void resize();
        void resize_to(int);
};

template <class T>
Array<T>::Array()
{
    _size = 10;
    arr = new T [_size + 10];
    abegin = arr;
    aend = arr;
}

template <class T>
Array<T>::Array(int n)
{
    _size = n;
    arr = new T [_size + 10];
    abegin = arr;
    aend = arr;
}

template <class T>
Array<T>::Array(const Array<T>& other)
{
    _size = other.size() + 10;
    arr = new T [_size];
    abegin = arr;
    aend = arr + (_size - 10);
    std::copy(other.v_begin(), other.v_end(), abegin);
}

template <class T>
void Array<T>::resize()
{
    try{
        _size *= 2;
        T *_new = new T [_size];
        int newsize = size();
        aend = newsize + (abegin = _new);
        for (int i = 0; i < newsize; i++)
            _new[i] = arr[i];
        delete [] arr;
        arr = _new;
    }
    catch (std::bad_alloc){};
}

template <class T>
void Array<T>::resize_to(int newsize)
{
    _size = newsize + 10;
    T *_new = new T [_size];
    int oldsize = size();
    abegin = _new;
    aend = newsize + abegin;
    for (int i = 0; i < oldsize; i++)
        _new[i] = arr[i];
    for (int i = oldsize; i < newsize; i++)
        _new[i] = 0;
    delete [] arr;
    arr = _new;
}

template <class T>
void Array<T>::push_back(T val)
{
    if (aend - abegin == _size - 1)
        resize();
    *(aend++) = val;
}

template <class T>
void Array<T>::insert(T val, int pos)
{
    if(pos < 0)
        throw -1;
    if (pos > _size){
        resize_to(pos);
        arr[pos] = val;
        return;
    }
    else if (aend - abegin == _size - 1)
        resize();
    if (pos < size()){
        for (int i = aend - abegin; i > pos; i--)
            std::swap(arr[i], arr[i - 1]);
        arr[pos] = val;
        aend++;
    }
    else {
        for(;aend - abegin < pos; *aend++ = 0);
        *(aend++) = val;
    }
}

template <class T>
void Array<T>::drop(int pos)
{
    if (pos > 0 and pos < size()){
        for (int i = pos; i < size(); i++)
            std::swap(arr[i],arr[i+1]);
        aend--;
    }
}

template <class T>
void Array<T>::operator+=(T val)
{
    for (T *i = abegin; i < aend; *(i++) += val);
}

template <class T>
void Array<T>::operator*=(T val)
{
    for (T *i = abegin; i < aend; *(i++) *= val);
}

template <class T>
Array<T>::~Array()
{
    if (arr) delete [] arr;
    arr = abegin = aend = 0;
}

template <class TT>
Array<TT> operator+(const Array<TT>& a1, const Array<TT>& a2)
{
    Array<TT> rez(a1.size()+a2.size());
    for (TT *i = a1.abegin; i < a1.aend; i++)
        rez.push_back(*i);
    for (TT *i = a2.abegin; i < a2.aend; i++)
        rez.push_back(*i);
    return  rez;
}

template <class TT>
Array<TT> operator*(const Array<TT>& a1, const Array<TT>& a2)
{
    Array<TT> rez(a1.size()+a2.size());
    for (TT *i = a1.abegin; i < a1.aend; i++)
        for (TT *j = a2.abegin; j < a2.aend; j++)
            if(*i == *j)
                rez.push_back(*i);
}

template <class TT>
Array<TT> operator+(const double addend, const Array<TT>& a)
{
    Array<TT> rez = a;
    for (TT *i = a.abegin; i < a.aend; *(i++) += addend);
}

template <class TT>
Array<TT> operator*(const double multiplicand, const Array<TT>& a)
{
    Array<TT> rez = a;
    for (TT *i = a.abegin; i < a.aend; *(i++) *= multiplicand);
}

template <class TT>
bool operator==(const Array<TT>& a1, const Array<TT>& a2)
{
    if (a1.size() == a2.size()){
        for (int i = 0; i < a1.size(); i++)
            if (a1.arr[i] != a2.arr[i])
                return false;
        return true;
    }
    return false;
}

template <class TT>
bool operator!=(const Array<TT>& a1, const Array<TT>& a2)
{
    return !(a1 == a2);
}

template <class TT>
std::ostream& operator<<(std::ostream& out, const Array<TT>& a)
{
    for (TT *i = a.abegin; i < a.aend; out << *i++ << '\t');
    out << '\n';
    return out;
}

template <class TT>
std::istream& operator>>(std::istream& in, Array<TT>& a)
{
    for (TT *i = a.abegin; in.good() and i < a.aend; in >> *i++);
    return in;
}
#endif // ARRAY_H
