#pragma once
#include <iostream>
#define MAX_LIST_SIZE 100000

inline void error(const char *str)
{
    std::cerr << str << "\n";
    exit(1);
};

class ArrayList
{
private:
    int data[MAX_LIST_SIZE];
    size_t length;

public:
    ArrayList(void) { length = 0; } // 생성자

    void insert(int pos, int e)
    {
        if (!isFull() && pos >= 0 && pos <= length) // pos <= length: 새 데이터가 들어가기 때문에(length 위치는 데이터가 없는 곳에 위치)
        {
            for (int i = length; i > pos; i--) // 뒤에서 부터 해야지 모든 데이터들이 빠짐없이 옮겨짐
                data[i] = data[i - 1];         // position 왼쪽에 있는 것들을 position 오른쪽으로 옮겨줌 (가장 뒤에 있는 데이터 부터 한자리씩 옮김)
            data[pos] = e;
            length++; // 데이터가 들어왔기 때문에
        }
        else
        {
            error("포화상태 오류 또는 삽입 위치 오류 \n");
        }
    }

    void remove(int pos)
    {
        if (!isEmpty() && pos >= 0 && pos < length)
        { // pos < length: 차있는 상태에서 인덱스가 0번부터 시작하기 때문
            for (int i = pos + 1; i < length; i++)
                data[i - 1] = data[i]; // position 오른쪽에 있는 것들을 position 왼쪽으로 옮겨줌
            length--;
        }
        else
        {
            error("공백상태 오류 또는 삭제 위치 오류 \n");
        }
    }

    int getEntry(int pos) { return data[pos]; }

    bool isEmpty() { return length == 0; }

    bool isFull() { return length == MAX_LIST_SIZE; }

    bool find(int item)
    {
        for (int i = 0; i < length; i++)
        {
            if (data[i] == item)
            {
                return true;
            }
        }
        return false;
    }

    void replace(int pos, int e)
    {
        if (!isEmpty() && pos >= 0 && pos < length)
        {
            data[pos] = e;
        }
        else
        {
            error("공백상태 오류 또는 치환 위치 오류 \n");
        }
    }

    int size() { return length; }

    void display()
    {
        std::cout << "Array List의 총 항목 수: " << length;
        for (int i = 0; i < length; i++)
        {
            std::cout << "[" << data[i] << "]";
            std::cout << "\n";
        }
    }

    void clear() { length = 0; }
};