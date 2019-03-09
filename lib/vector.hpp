#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "memcheck.hpp"

#define MIN_SIZE (1)

typedef int vector_t;

//***********************************************************************************
//***********************************************************************************
//***********************************************************************************

class Vector
{
private:
    int capacity_;
    int size_;
    vector_t* data_;

private:
    void Expand(int new_size);
    void Shrink(int new_size);

public:
    Vector();
    Vector(int cap);
    Vector(const Vector& that);
    ~Vector();

    const Vector& operator=(const Vector& that);
    const Vector& operator+=(const Vector& that);

    vector_t& At(int idx);
    vector_t& operator[](int idx);

    void Dump();
    void Clear();
    void Push(const vector_t val);
    void Pop();
    void Swap(Vector& that);
};

//***********************************************************************************
//***********************************************************************************
//***********************************************************************************

Vector::Vector():
    capacity_(0),
    size_(0),
    data_(nullptr)
{ }

Vector::Vector(int cap):
    capacity_(cap),
    size_(0),
    data_(new vector_t[capacity_] {})
{ }

Vector:: Vector(const Vector& that):
    capacity_(that.capacity_),
    size_(that.size_),
    data_(new vector_t[size_] {})
{
    for(int i = 0; i < size_; i++)
        data_[i] = that.data_[i];
}

Vector::~Vector()
{
    capacity_ = 0;
    size_ = 0;
    delete[] data_;
    data_ = nullptr;
}

//***********************************************************************************
//***********************************************************************************

void Vector::Expand(int new_size)
{
    vector_t* tmp = new vector_t[new_size];
    for(int i = 0; i < size_; i++)
        tmp[i] = data_[i];
    delete[] data_;
    data_ = tmp;

    capacity_ = new_size;
    return;
}

void Vector::Shrink(int new_size)
{
    vector_t* tmp = new vector_t[new_size];
    for(int i = 0; i < size_; i++)
        tmp[i] = data_[i];
    delete[] data_;
    data_ = tmp;

    capacity_ = new_size;
    return;
}

//***********************************************************************************
//***********************************************************************************

const Vector& Vector::operator=(const Vector& that)
{
    Vector tmp(that);
    Swap(tmp);
    return *this;
}

const Vector& Vector::operator+=(const Vector& that)
{
    Shrink(size_);
    Vector tmp(size_ + that.size_);
    for(int i = 0; i < size_; i++)
        tmp.data_[i] = data_[i];
    for(int i = 0; i < that.size_; i++)
        tmp.data_[size_ + i] = that.data_[i];
    tmp.size_ = size_ + that.size_;
    Swap(tmp);
    return *this;
}

vector_t& Vector::At(int idx)
{
    if(idx >= capacity_)
        Expand(idx + 1);
    while(idx < 0)
        idx += capacity_;
    if(idx + 1 > size_)
        size_ = idx + 1;
    return data_[idx];
}

vector_t& Vector::operator[](int idx)
{
    return At(idx);
}

void Vector::Dump()
{
    printf("Vector at [%p]:\n{\n", this);

    printf("\tcapacity = %d\n", capacity_);
    printf("\tsize = %d\n", size_);

    printf("\tdata at [%p]:\n", data_);
    {
        if(capacity_ == 0)
        {
            puts("\t\tempty\n}");
            return;
        }
        int width = 0;
        for(int i = capacity_ - 1; i > 0; i /= 10)
            width++;

        puts("\t{");
        for(int i = 0; i < capacity_; i++)
        {
            printf("\t%s\t[%*d]: ", (size_ == i + 1) ? "sp  >>" : " ", width, i);
            std::cout << data_[i] << "\n";
        }
        puts("\t}");
    }
    puts("}");

    return;
}

void Vector::Clear()
{
    for(int i = 0; i < capacity_; i++)
        data_[i] = 0;
    return;
}

void Vector::Push(const vector_t val)
{
    At(size_++) = val;
    return;
}

void Vector::Pop()
{
    if(size_ > 0)
        size_--;
    if(MIN_SIZE <= 2 * size_ && 2 * size_ < capacity_)
        Shrink(2 * size_);
    return;
}

void Vector::Swap(Vector& that)
{
    std::swap(capacity_, that.capacity_);
    std::swap(size_,     that.size_);
    std::swap(data_,     that.data_);
    return;
}

#endif // VECTOR_HPP_INCLUDED
