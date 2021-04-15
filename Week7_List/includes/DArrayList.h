#pragma once
#include <iostream>

inline void error(const char *str)
{
    std::cerr << str << "\n";
    exit(1);
};

class DArrayList
{
private:
    int *data;
    size_t length;       // 현재 리스트의 길이
    size_t current_size; // 현재 할당된 크기
    size_t resize_unit;  // 할당 크기 변화 기준

public:
    DArrayList(size_t init_size = 10) // 생성자
    {
        std::cout << "\n<Initialize to:" << init_size << "> ";
        data = new int[init_size];
        current_size = init_size;
        resize_unit = init_size;
        length = 0;
    }
    ~DArrayList()
    {
        delete[] data;
    } // 동적할당이므로 제대로 지워줘야 한다.

    void resize(size_t newsize)
    {
        int *temparray = new int[newsize];
        std::cout << "\n<Resize to: " << newsize << "> ";
        for (int i = 0; i < length; i++)
        {
            temparray[i] = data[i]; // 새로만든 temparray에 기존에 있던 data들을 그대로 복사
        }
        delete[] data; // 기존에 있던 데이터 삭제
        current_size = newsize;
        data = temparray;
    }

    void insert(int pos, int e)
    {
        if (pos >= 0 && pos <= length)
        {
            if (isFull())
            {
                // array 공간 여유가 없을 때
                resize(current_size + resize_unit);
            }
            for (int i = length; i > pos; i--)
                data[i] = data[i - 1]; // position 왼쪽에 있는 것들을 position 오른쪽으로 옮겨줌 (가장 뒤에 있는 데이터 부터 한자리씩 옮김)
            data[pos] = e;
            length++;
        }
        else
        {
            std::cout << "포화상태 오류 또눈 삽입 위치 오류\n";
        }
    }

    void remove(int pos)
    {
        if (!isEmpty() && pos >= 0 && pos < length)
        {
            if (current_size > resize_unit + length)
            {
                // array 공간 여유가 resize_unit 보다 클 때
                resize(current_size - resize_unit);
            }
            for (int i = pos + 1; i < length; i++)

                data[i - 1] = data[i]; // position 오른쪽에 있는 것들을 position 왼쪽으로 옮겨줌
            length--;
        }
        else
        {
            std::cout << "공백상태 오류 또는 삽입 위치 오류\n";
        }
    }

    int getEntry(int pos) { return data[pos]; }

    bool isEmpty() { return length == 0; }

    bool isFull() { return length == current_size; }

    bool find(int item)
    {
        for (int i = 0; i < length; i++)
            if (data[i] == item)
            {
                return true;
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
            std::cout << "공백상태 오류 또는 치환 위치 오류\n";
        }
    }

    int size() { return length; }

    void display()
    {
        std::cout << "Array List의 총 항목 수: " << length;
        for (int i = 0; i < length; i++)
            std::cout << "[" << data[i] << "]";
        std::cout << "\n";
    }

    void clear()
    {
        length = 0;
        resize(resize_unit);
    }
};