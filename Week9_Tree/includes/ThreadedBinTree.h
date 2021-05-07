#pragma once
#include <iostream>

// 트리의 NULL링크 자리를 이용 -> 순환호출 없이 트리의 노드를 순회
// NULL 대신 중위 순회시 후속 노드인 중위 후속자(inorder successor)를 저장
// leaf node인지 판별을 위해 노드에 추가적인 field가 필요 (isthread)
class ThreadedBinNode
{
protected:
    int data;
    ThreadedBinNode *left;
    ThreadedBinNode *right;

public:
    bool bThread;
    ThreadedBinNode(int val = 0, ThreadedBinNode *l = nullptr, ThreadedBinNode *r = nullptr, bool bTh = false)
        : data(val), left(l), right(r), bThread(bTh) {}

    int getData()
    {
        return data;
    }
    void setRight(ThreadedBinNode *r)
    {
        right = r;
    }
    void setLeft(ThreadedBinNode *l)
    {
        left = l;
    }
    ThreadedBinNode *getLeft()
    {
        return left;
    }
    ThreadedBinNode *getRight()
    {
        return right;
    }
};

class ThreadedBinTree
{
private:
    ThreadedBinNode *root;

public:
    ThreadedBinTree() : root(nullptr) {}
    ~ThreadedBinTree() {}

    void setRoot(ThreadedBinNode *node)
    {
        root = node;
    }
    ThreadedBinNode *getRoot()
    {
        return root;
    }
    bool isEmpty()
    {
        return root == nullptr;
    }
    void threadedInorder()
    {
        if (!isEmpty())
        {
            std::cout << "스레드 이진 트리 중위순회: ";
            ThreadedBinNode *q = root;
            while (q->getLeft())
                q = q->getLeft(); // 가장 왼쪽 노드로 이동

            do
            {
                std::cout << "[" << q->getData() << "]"; // 데이터를 출력하고
                q = findSuccessor(q);                    // 후속자를 불러옴
            } while (q);
            std::cout << "\n";
        }
    }
    ThreadedBinNode *findSuccessor(ThreadedBinNode *p)
    {
        ThreadedBinNode *q = p->getRight(); // 오른쪽 자식 포인터를 저장
        if (q == nullptr || p->bThread)
        {
            // 오른쪽 자식이 nullptr 이거나 스레드이면 오른쪽 포인터를 반환
            return q;
        }
        while (q->getLeft() != nullptr) // 만약 오른쪽 자식이 존재하면 다시 가장 왼쪽 노드로 이동
        {
            q = q->getLeft();
        }
        return q;
    }
};