#pragma once
#include <iostream>
#include <string>

class node
{
private:
    int data;
    node *next; // 다음번 노드를 pointing 하는 next

public:
    node(int val = 0)
    {
        data = val;
        next = nullptr;
    }

    node *getLink() { return next; } // getLink(): 다음번 노드를 가리키는 포인터를 리턴해줌

    int getData() { return data; }

    void setLink(node *target) { next = target; } // next 포인터가 우리가 받은 node 포인터(target)와 같게 해준다.

    void insertNext(node *newnode)
    {
        if (newnode != nullptr)
        {
            newnode->next = next; // ex) A - > B(데이터삽입) -> C -> : newnode - > C
            next = newnode;       // B - > newnode
        }
    } // 노드의 다음 자리에 새 노드를 넣는 연산

    node *removeNext()
    {
        node *removed = next; // 다음거는 지워진 노드
        if (removed != nullptr)
            next = removed->next;
        return removed;
    } // 노드의 다음 자리 노드를 지우는 연산
};

class hn_s_linked_list
{
protected:
    node origin; // origin: headnode 전에 있는 가상의 노드

public:
    hn_s_linked_list() : origin(0) {} // 생성자
    ~hn_s_linked_list() { clear(); }  //소멸자

    void clear();    // 리스트를 지우는 연산
    node *getHead(); // 첫 노드를 부르는 연산
    bool isEmpty();  // 공백 확인

    node *getEntry(int pos);        // 조회연산
    void insert(int pos, node *n);  // 삽입연산
    void remove(int pos);           // 삭제연산
    node *find(int value);          // 검색연산
    void replace(int pos, node *n); // 치환연산
    size_t size();                  // 사이즈 구하기
    void display();                 // Linked List의 전체 내용 출력
};

void hn_s_linked_list::clear()
{
    while (!isEmpty())
    {
        remove(0);
    }
} // 리스트를 지우는 연산

node *hn_s_linked_list::getHead()
{
    return origin.getLink();
} // 첫 노드를 부르는 연산

bool hn_s_linked_list::isEmpty()
{
    return getHead() == nullptr;
} // 공백 확인

node *hn_s_linked_list::getEntry(int pos)
{
    node *n = &origin;                               // origin을 가리키는 포인터 생성
    for (int i = -1; i < pos; i++, n = n->getLink()) // -1인 이유: origin 부터 가서
                                                     // n을 getLink로 다음번 노드를 포인팅하는 포인터로 바꿔줌
    {
        if (n == nullptr)
        {
            break;
        }
    }
    return n;
} // 조회연산

void hn_s_linked_list::insert(int pos, node *n)
{
    node *prev = getEntry(pos - 1); // 우리가 원하는 position 하나 전에 있는 포인터를 가져온다.
    if (prev != nullptr)
    {
        prev->insertNext(n); // 직전노드의 다음노드에 n 삽입
    }
} // 삽입연산

void hn_s_linked_list::remove(int pos)
{
    node *prev = getEntry(pos - 1);
    delete prev->removeNext();
} // 삭제연산

node *hn_s_linked_list::find(int value)
{
    for (node *p = getHead(); p != nullptr; p = p->getLink())
    {
        if (p->getData() == value)
        {
            return p;
        }
    }
    return nullptr;
} // 검색연산 (value와 같은 값을 찾음). 가장 먼저 나오는 노드를 리턴

void hn_s_linked_list::replace(int pos, node *n)
{
    node *prev = getEntry(pos - 1);
    if (prev != nullptr)
    {
        delete prev->removeNext(); // 지우고
        prev->insertNext(n);       // 그자리에 새로운 거 삽입
    }
} // 치환연산

size_t hn_s_linked_list::size()
{
    int count = 0;
    for (node *p = getHead(); p != nullptr; p = p->getLink())
    {
        count++;
    }
    return count;
} // 사이즈 구하기

void hn_s_linked_list::display()
{
    std::cout << "전체 항목의 수: " << size() << ", ";
    for (node *p = getHead(); p != nullptr; p = p->getLink())
    {
        std::cout << p->getData() << " ";
    }
} // Linked List의 전체 내용 출력