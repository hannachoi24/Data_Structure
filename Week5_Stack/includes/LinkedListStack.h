#pragma once
#include "SingleLinkedList.h"
#include <iostream>

inline void error(const char *str)
{
    std::cerr << str << "\n";
    exit(1);
};

class LinkedListStack : public s_linked_list
{
public:
    LinkedListStack() : s_linked_list() {}
    bool isEmpty() { return Size() == 0; }
    void push(int e)
    {
        push_front(e);
    }
    int pop()
    {
        if (isEmpty())
            error("스택 공백 에러");
        return pop_front();
    }
    int peek()
    {
        if (isEmpty())
            error("스택 공백 에러");
        return head->data;
    }
    void display()
    {
        node *ptr = head;
        std::cout << "[전체 스택의 수 = " << Size() << "]";
        for (int i = 0; i < Size(); i++)
        {
            std::cout << "<" << ptr->data << ">";
            ptr = ptr->next;
        }
        std::cout << "\n";
    }
};