#include <stdio.h>
#include <iostream>

struct node
{
    int data;
    node *next;
};

class s_linked_list
{
protected:
    node *head, *tail;
    int size = 0;

public:
    s_linked_list()
    {
        head = nullptr;
        tail = nullptr;
    }
    ~s_linked_list()
    {
    }

    void GenerateList(int n);
    void display_contents();
    int getSize()
    {
        return size;
    }
    void CopyLStoDA(int array[], s_linked_list list);
};

void s_linked_list::GenerateList(int n)
{
    for (int i = 0; i < n; i++)
    {
        node *ptr = new node;
        ptr->data = i;
        ptr->next = nullptr;
        if (head == nullptr)
        {
            head = ptr;
            tail = ptr;
        }
        else
        {
            tail->next = ptr;
            tail = tail->next;
        }
        size++;
    }
}

void s_linked_list::display_contents()
{
    node *ptr = head;
    while (ptr != nullptr)
    {
        std::cout << ptr->data << "->";
        ptr = ptr->next;
    }
    std::cout << "nullptr"
              << "\n";
}

void s_linked_list::CopyLStoDA(int array[], s_linked_list list)
{
    node *ptr = head;
    for (int i = 0; i < list.getSize(); i++)
    {
        array[i] = ptr->data;
        ptr = ptr->next;
    }
}

int main()
{
    s_linked_list LinkedList;
    int n;
    std::cout << "Linked List 길이를 입력하세요: ";
    std::cin >> n;
    LinkedList.GenerateList(n);
    LinkedList.display_contents();
    int a = LinkedList.getSize();
    std::cout << a << std::endl;
    int *Array;
    Array = new int[4];
    LinkedList.CopyLStoDA(Array, LinkedList);
    std::cout << "Array = {" << Array[0] << "," << Array[1] << "," << Array[2] << "," << Array[3] << "}" << std::endl;
    return 0;
}