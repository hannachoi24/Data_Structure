#pragma once

class BinaryNode
{
protected:
    int data;
    BinaryNode *left;
    BinaryNode *right;

public:
    BinaryNode(int val = 0, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
        : data(val), left(l), right(r) {}
    ~BinaryNode() {}

    void setData(int val)
    {
        data = val;
    }

    void setLeft(BinaryNode *l)
    {
        left = l;
    }

    void setRight(BinaryNode *r)
    {
        right = r;
    }

    int getData()
    {
        return data;
    }

    BinaryNode *getLeft() // 왼쪽 자손
    {
        return left;
    }

    BinaryNode *getRight() // 오른쪽 자손
    {
        return right;
    }

    bool isLeaf()
    {
        return left == nullptr && right == nullptr;
    }
};