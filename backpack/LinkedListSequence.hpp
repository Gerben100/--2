#pragma once
#include <iostream>
#include "LinkedList.hpp"
#include "Sequence.hpp"

template <typename T>
class LinkedListSequence : public Sequence<T>
{
private:
    int size;
    LinkedList<T>* list;

public:
    LinkedListSequence()
    {
        this->list = new LinkedList<T>();
    }

    LinkedListSequence(T* items, int count)
    {
        this->list = new LinkedList<T>(items, count);
    }

    LinkedListSequence(LinkedList<T>& list)
    {
        this->list = new LinkedList<T>(list);
    }

    T GetFirst() override
    {
        return this->list->GetFirst();
    }

    T GetLast() override
    {
        return this->list->GetLast();
    }

    T Get(int index) override
    {
        return this->list->Get(index);
    }

    void Set(int index, T value) override
    {
        this->list->Set(index, value);
    }

    int GetLength() override
    {
        return this->list->GetLength();
    }

    Sequence<T>* GetSubSequence(int startIndex, int endIndex) override
    {
        LinkedList<T>* pointerList = (this->list->GetSubSequence(startIndex, endIndex));
        LinkedList<T>& Link = *pointerList;
        Sequence<T>* newSequence = new LinkedListSequence(Link);
        return newSequence;
    }

    void Append(T item) override
    {
        this->list->Append(item);
    }

    void Prepend(T item) override
    {
        this->list->Prepend(item);
    }

    void InsertAt(T item, int index) override
    {
        this->list->InsertAt(item, index);
    }

    void Print()
    {
        for (int i = 0; i < this->GetLength(); i++)
        {
            std::cout << this->Get(i) << "\t\t";
        }
        std::cout << std::endl;
    }

    Sequence<T>* Concat(Sequence<T>* list) override
    {
        T* array = new T[this->GetLength() + list->GetLength()];
        for (int i = 0; i < this->GetLength(); i++)
        {
            array[i] = this->Get(i);
        }
        for (int i = 0; i < list->GetLength(); i++)
        {
            array[i + list->GetLength()] = list->Get(i);
        }
        Sequence<T>* newSequence = new LinkedListSequence(array, this->GetLength() + list->GetLength());
        return newSequence;
    }
};