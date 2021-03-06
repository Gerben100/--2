#pragma once
#include <string>
#include <iostream>

template <typename T>
class LinkedList
{
private:
    template <typename T1>
    class Node
    {
    public:
        Node* pointerNext;
        Node* pointerPrev;
        T1 data;

        Node(T1 data, Node* pointerNext = nullptr, Node* pointerPrev = nullptr)
        {
            this->data = data;
            this->pointerNext = pointerNext;
            this->pointerPrev = pointerPrev;
        }
    };

    int size;
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList()
    {
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    LinkedList(T* items, int count)
    {
        Node<T>* prev = nullptr;
        Node<T>* current = nullptr;

        this->size = count;

        for (int i = 0; i < count; i++)
        {
            if (i == 0)
            {
                prev = new Node<T>(items[i]);
                this->head = prev;
                i++;
            }

            current = new Node<T>(items[i]);
            current->pointerPrev = prev;
            prev->pointerNext = current;

            if (i == count - 1)
            {
                this->tail = current;
                return;
            }

            prev = current;
            current = nullptr;
        }
    }

    LinkedList(LinkedList<T>& list)
    {
        Node<T>* prev = nullptr;
        Node<T>* current = nullptr;
        Node<T>* next = nullptr;
        T* items = new T[list.size];

        for (int i = 0; i < list.size; i++)
        {
            items[i] = list.Get(i);
        }

        for (int i = 0; i < list.size; i++)
        {
            if (i == 0)
            {
                prev = new Node<T>(items[i]);
            }

            current = new Node<T>(items[i]);
            current->pointerPrev = prev;
            prev->pointerNext = current;

            if (i == list.size - 1)
            {
                this->tail = next;
                return;
            }

            prev = current;
            current = nullptr;
        }

        this->size = list.size;
    }

    T GetFirst()
    {
        return this->head->data;
    }

    T GetLast()
    {
        return this->tail->data;
    }

    T Get(int index)
    {
        Node<T>* current = nullptr;
        current = this->head;

        for(int i = 0; i < index; i++)
        {
            current = current->pointerNext;
        }

        return current->data;
    }

    void Set(int index, T value)
    {
        Node<T>* current = nullptr;
        current = this->head;

        for (int i = 0; i < index; i++)
        {
            current = current->pointerNext;
        }

        current->data = value;
    }

    LinkedList<T>* GetSubSequence(int startIndex, int endIndex)
    {
        LinkedList<T>* newList =  new LinkedList<T>;

        Node<T>* current = this->head;

        for(int i = 0; i < endIndex; i++)
        {
            current = current->pointerNext;

            if (i < startIndex)
                continue;

            newList->Append(current->data);
        }
        return newList;
    }

    int GetLength()
    {
        return this->size;
    }

    void Prepend(T item)
    {
        this->head->pointerPrev = new Node<T>(item);
        this->head->pointerPrev->pointerNext = this->head;
        this->head = this->head->pointerPrev;
        this->size++;
    }

    void Append(T item)
    {
        if (this->head == NULL && this->tail == NULL)
        {
            this->head = this->tail = new Node<T>(item);
            this->size++;
            return;
        }
        this->tail->pointerNext = new Node<T>(item);
        this->tail->pointerNext->pointerPrev = this->tail;
        this->tail = this->tail->pointerNext;
        this->size++;
    }

    void InsertAt(T item, int index)
    {
        Node<T>* newNode =  new Node<T>(item);
        Node<T>* current = this->head;

        for(int i = 0; i < index - 1; i++)
        {
            current = current->pointerNext;
        }

        newNode->pointerPrev = current;
        newNode->pointerNext = current->pointerNext;
        current->pointerNext = newNode;
        newNode->pointerNext->pointerPrev = newNode;

        this->size++;
    }

    LinkedList<T>* Concat(LinkedList<T>* list)
    {
        Node<T>* current = nullptr;

        current = list->head;

        for (int i = 0; i < list->size; i++)
        {
            this->Append(current->data);
            current = current->pointerNext;
        }

        return this;
    }
};

