#pragma once
#include <iostream>>
#include "BinaryTree.h"

class BinSrchTree : public BinaryTree
{
public:
    BinSrchTree(void) {}
    ~BinSrchTree(void) {}

    BinaryNode *serach(int key)
    { // root부터 key까지 탐색을 불러옴
        BinaryNode *node = search(root, key);
        if (node != nullptr)
        {
            std::cout << "탐색 성공. Key: " << key;
            std::cout << "노드: " << node->getData();
        }
        else
        {
            std::cout << "탐색 실패. Key: " << key;
        }
        return node;
    }

    BinaryNode *search(BinaryNode *n, int key) // 함수 오버로딩을 통해 실제 탐색, 추후에 삽입연산 할 때 쓰임
                                               // (시작노드, key)
    {
        if (n == nullptr)
        {
            return nullptr;
        }
        if (key == n->getData())
        {
            return n;
        }
        else if (key < n->getData()) // key값이 노드의 key값보다 작으면  왼쪽
        {
            return search(n->getLeft(), key);
        }
        else
        {
            return search(n->getRight(), key); // key값이 노드의 key값보다 크면 오른쪽
        }
    }

    void insert(BinaryNode *n) // (n은 새로운 노드)
    {
        if (n == nullptr)
        {
            return;
        }
        if (isEmpty())
        {
            root = n;
        }
        else
        {
            insert(root, n); // root 부터 시작해서 새로운 노드를 삽입
        }
    }

    void insert(BinaryNode *r, BinaryNode *n) // 함수 오버로딩을 통해 삽입 연산
                                              // (탐색하고 싶은 위치, 삽입하고 싶은 new node)
    {
        if (n->getData() == r->getData())
        {
            return;
        }
        else if (n->getData() < r->getData())
        {
            if (r->getLeft() == nullptr)
            { // 탐색에 실패했으니까 r의 왼쪽에 n 삽입
                r->setLeft(n);
            }
            else
            {
                insert(r->getLeft(), n);
            }
        }
        else
        {
            if (r->getRight() == nullptr)
            { // 탐색에 실패했으니까 r의 오른쪽에 n 삽입
                r->setRight(n);
            }
            else
            {
                insert(r->getRight(), n);
            }
        }
    }

    void remove(int data)
    {
        if (isEmpty())
        {
            return;
        }
        BinaryNode *parent = nullptr; // 부모노드 필요
        BinaryNode *node = root;      // 현재노드 필요
        while (node != nullptr && node->getData() != data)
        {
            parent = node;
            node = (data < node->getData()) ? node->getLeft() : node->getRight(); // 데이터의 key값이 노드의 key값보다 작으면 왼쪽 크면 오른쪽
        }
        if (node == nullptr)
        {
            std::cout << "Key " << data << "does not exist";
        }
        else
        {
            remove(parent, node);
        }
    }

    void remove(BinaryNode *parent, BinaryNode *node)
    { // 함수 오버로딩을 통해 삭제연산
        // 삭제 위치가 단말 노드일 경우
        if (node->isLeaf())
        {
            if (parent == nullptr) // node = root 라는 의미
            {
                root = nullptr;
            }
            else
            {
                if (parent->getLeft() == node)
                {
                    parent->setLeft(nullptr);
                }
                else
                {
                    parent->setRight(nullptr);
                }
            }
        }
        // 한 쪽 서브트리만 있는 경우
        // parent(노드의 부모) -> node(child의 부모가 노드) -> child(노드의 자식 즉,서브트리) => parent -> child
        else if (node->getLeft() == nullptr || node->getRight() == nullptr)
        {
            BinaryNode *child = (node->getLeft() != nullptr) ? node->getLeft() : node->getRight(); // 노드 기준 어느쪽 서브트리가 있는지 보고 서브트리가 존재하는 쪽이 child

            if (node == root)
            {
                root = child;
            }
            else
            {
                if (parent->getLeft() == node)
                {
                    parent->setLeft(child); // parent(노드의 부모) -> node(child의 부모가 노드) -> child(노드의 자식 즉,서브트리) => parent -> child
                }
                else
                {
                    parent->setRight(child);
                }
            }
        }
        // 양쪽 서브트리가 다 있는 경우
        // 오른쪽 트리를 기준으로만 구현 (양쪽 다 하기 길고 복잡함)
        else
        {
            BinaryNode *succp = node;            // 후계자의 바로 위 부모 노드
            BinaryNode *succ = node->getRight(); // 후계자 노드
            while (succ->getLeft() != nullptr)
            {
                succp = succ;             // 후계자의 부모를 전에 후계자였던 노드로 바꿔줌
                succ = succ->getLeft();   // 새 후계자 정의
            }                             // 오른쪽 트리에서 가장 작은 노드를 골라냄
            if (succp->getLeft() == succ) // 가장 작은 노드가 왼쪽 노드일 때
            {
                succp->setLeft(succ->getRight()); // 후계자 부모의 왼쪽 노드를 후계자의 오른쪽 자식노드로 정해준다.
            }
            else
            {
                succp->setRight(succ->getRight());
            }
            // 가장 작은 노드가 오른쪽 노드일 때
            // 후계자 부모의 오른쪽 노드를 후계자의 오른쪽 자식노드로 정해준다.
            // 왜냐하면 후계자가 사라지고 그 밑에 자식들을 붙여줄 것이기 때문에
            // 이 부분이 들어가는 이유는 처음에 오른쪽을 골랐기 때문에(BinaryNode *succ = node->getRight();)
            node->setData(succ->getData()); // node의 데이터를 후계자의 데이터로 바꿔줌
            node = succ;
        }
        delete node; // 원래 노드 위치 복사해줬으니 지금의 node 필요 없어짐
    }
};