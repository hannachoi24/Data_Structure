#pragma once
#include <iostream>
#include "BinaryNode.h"
#include "CircularQueue.h" // 레벨 순회용

class BinaryTree
{
protected:
    BinaryNode *root;
    // 트리의 순회연산

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() {}

    void setRoot(BinaryNode *node)
    {
        root = node;
    }
    BinaryNode *getRoot()
    {
        return root;
    }
    bool isEmpty()
    {
        return root == nullptr;
    }
    // 전위순회
    void preorder(BinaryNode *node)
    {
        if (node != nullptr)
        {
            std::cout << " [" << node->getData() << "]";
            if (node->getLeft() != nullptr)
            {
                preorder(node->getLeft());
            }
            if (node->getRight() != nullptr)
            {
                preorder(node->getRight());
            }
        }
    }
    // 파라미터가 아무것도 없을 경우 함수오버로딩을 통해서 아래의 형태로 root를 불러오는 함수 구현
    void preorder()
    {
        std::cout << "preorder: ";
        preorder(root);
        std::cout << "\n";
    }
    // 중위순회
    void inorder(BinaryNode *node)
    {
        if (node != nullptr)
        {
            if (node->getLeft() != nullptr)
            {
                inorder(node->getLeft());
            }
            std::cout << "[" << node->getData() << "]";
            if (node->getRight() != nullptr)
            {
                inorder(node->getRight());
            }
        }
    }
    // 파라미터가 아무것도 없을 경우 함수오버로딩을 통해서 아래의 형태로 root를 불러오는 함수 구현
    void inorder()
    {
        std::cout << "inorder: ";
        inorder(root);
        std::cout << "\n";
    }
    // 후위순회
    void postorder(BinaryNode *node)
    {
        if (node != nullptr)
        {
            if (node->getLeft() != nullptr)
            {
                postorder(node->getLeft());
            }
            if (node->getRight() != nullptr)
            {
                postorder(node->getRight());
            }
            std::cout << "[" << node->getData() << "]";
        }
    }
    // 파라미터가 아무것도 없을 경우 함수오버로딩을 통해서 아래의 형태로 root를 불러오는 함수 구현
    void postorder()
    {
        std::cout << "postorder: ";
        postorder(root);
        std::cout << "\n";
    }
    // level순회는 큐가 필요
    // 레벨이 높은 자식들이 먼저 큐에 넣어져서 나올 때도 레벨이 높은 자식들이 먼저 나옴 -> 상위 레벨부터 순회하고 하위 레벨 순회
    void levelorder()
    {
        std::cout << "levelorder: ";
        if (!isEmpty())
        {
            CircularQueue q;
            q.enqueue(root);
            while (!q.isEmpty())
            {
                BinaryNode *n = q.dequeue();
                if (n != nullptr)
                {
                    std::cout << "[" << n->getData() << "]";
                    q.enqueue(n->getLeft());
                    q.enqueue(n->getRight());
                }
            }
        }
        std::cout << "\n";
    }
    // 노드의 수
    int getCount()
    {
        return isEmpty() ? 0 : getCount(root);
    }

    int getCount(BinaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + getCount(node->getLeft()) + getCount(node->getRight());
    }
    // 잎 노드의 수
    int getLeafCount()
    {
        return isEmpty() ? 0 : getLeafCount(root);
    }
    int getLeafCount(BinaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->isLeaf())
        {
            return 1;
        }
        else
            return getLeafCount(node->getLeft()) + getLeafCount(node->getRight()); // 자기 왼쪽 자손들 중에 leaf를 count + 자기 오른쪽 자손들 중에 leaf를 count
    }
    // 트리의 높이
    int getHeight()
    {
        return isEmpty() ? 0 : getHeight(root);
    }
    int getHeight(BinaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int hLeft = getHeight(node->getLeft());
        int hRight = getHeight(node->getRight());
        return (hLeft > hRight) ? hLeft + 1 : hRight + 1; // 높이구할 때 결과는 가장 높은 높이+1
    }
    // 용량 계산
    int calcSize()
    {
        return calcSize(root);
    }
    int calcSize(BinaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return node->getData() + calcSize(node->getLeft()) + calcSize(node->getRight());
    }
    // 수식 계산 함수
    // 파라미터가 아무것도 없을 경우 함수오버로딩을 통해서 root 부터 시작하는 함수 구현
    int evaluate()
    {
        return evaluate(root);
    }
    int evaluate(BinaryNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->isLeaf())
            return node->getData();
        else
        {
            int op1 = evaluate(node->getLeft());
            int op2 = evaluate(node->getRight());
            switch (node->getData())
            {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
            }
            return 0;
        }
    }
};
