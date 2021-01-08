#pragma once
#include <iostream>
#include "DynamicArray.hpp"
#include "Sequence.hpp"

template <typename T>
class ArraySequence : public Sequence<T>
{
private:
    DynamicArray<T>* items;
    int size;

public:
    ArraySequence()
    {
        this->items = new DynamicArray<T>(0);
    }
    ArraySequence(int count)
    {
        this->items = new DynamicArray<T>(count);
    }

    ArraySequence(T* items, int count)
    {
        this->items = new DynamicArray<T>(items, count);
    }

    ArraySequence(DynamicArray<T>& array)
    {
        this->items = new DynamicArray<T>(array);
    }

    T GetFirst() override
    {
        return this->items->Get(0);
    }

    T GetLast() override
    {
        return this->items->Get(this->items->GetSize() - 1);
    }

    T Get(int index) override
    {
        return this->items->Get(index);
    }

    void Set(int index, T value) override
    {
        this->items->Set(index,value);
    }

    int GetLength() override
    {
        return this->items->GetSize();
    }

    void InsertAt(T item, int index) override
    {
        DynamicArray<T>* newArray = new DynamicArray<T>(this->items->GetSize() +1);

        for (int i = 0; i < index; i++)
        {
            newArray->Set(i, this->items->Get(i));
        }

        newArray->Set(index, item);

        for (int i = index + 1; i < newArray->GetSize(); i++)
        {
            newArray->Set(i, this->items->Get(i-1));
        }

        //delete[] this->items;

        this->items = newArray;
    }

    void Prepend(T item) override
    {
        DynamicArray<T>* newArray = new DynamicArray<T>(this->items->GetSize() + 1);

        for (int i = 1; i < newArray->GetSize(); i++)
        {
            newArray->Set(i, this->items->Get(i-1));
        }

        newArray->Set(0, item);

        //delete[] this->items;

        this->items = newArray;
    }

    void Append(T item) override
    {
        DynamicArray<T>* newArray = new DynamicArray<T>(this->items->GetSize() + 1);

        for (int i = 0; i < newArray->GetSize(); i++)
        {
            newArray->Set(i, this->items->Get(i));
        }

        newArray->Set(this->items->GetSize(), item);

        //delete[] this->items;

        this->items = newArray;
    }

    void Print()
    {
        for (int i = 0; i < this->GetLength(); i++)
        {
            std::cout << this->Get(i) << "\t\t";
        }
        std::cout << std::endl;
    }

    Sequence<T>* GetSubSequence(int startIndex, int endIndex) override
    {
        T* array = new T[endIndex - startIndex];

        for (int i = 0; i <= endIndex - startIndex; i++)
        {
            array[i] = this->items->Get(i + startIndex);
        }

        Sequence<T>* newSequence = new ArraySequence<T>(array, endIndex - startIndex);

        //delete[] array;

        return newSequence;
    }

    Sequence<T>* Concat(Sequence<T>* array) override
    {
        T* newArray = new T[this->GetLength() + array->GetLength()];

        for (int i = 0; i < this->GetLength(); i++)
        {
            newArray[i] = this->Get(i);
        }

        for (int i = 0; i < array->GetLength(); i++)
        {
            newArray[i + this->GetLength()] = array->Get(i);
        }

        Sequence<T>* newSequence = new ArraySequence<T>(newArray, this->GetLength() + array->GetLength());

        //delete[] newArray;

        return newSequence;
    }
};
