#pragma once
#include <iostream>

#define MAX_STACK_SIZE 100

inline int error(const char *str)
{
    std::cerr << str << "\n";
    exit(1);
}; // inline: 인라인 함수는 함수를 호출하지 않고, 함수를 사용하는
// 위치에 컴파일러가 코드 자체를 복사해줍니다 (그래서 라인 안에 들어가있다고 inline...)

class ArrayStack
{
private:
    int data[MAX_STACK_SIZE]; // 요소의 배열
    int top;                  // 요소의 개수

public:
    ArrayStack() { top = -1; }
    ~ArrayStack() {}
    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK_SIZE - 1; }

    void push(int e)
    {
        if (isFull())
            error("스택 포화 에러");
        data[++top] = e;
    }

    int pop()
    {
        if (isEmpty())
            error("스택 공백 에러");
        return data[top--];
    }

    int peek()
    {
        if (isEmpty())
            error("스택 공백 에러");
        return data[top];
    }

    void display()
    {
        std::cout << "[스택 항목의 수 = " << top + 1 << "]";
        for (int i = 0; i <= top; i++)
            std::cout << "<" << data[i] << ">";
        std::cout << "\n";
    }
};