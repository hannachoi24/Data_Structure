#include "includes/DArrayList.h"
#include <iostream>

int main()
{
    DArrayList list(10);
    for (int i = 0; i < 20; i++)
    {
        list.insert(list.size(), i);
        if (i % 10 == 9)
        {
            list.display();
        }
    }

    for (int i = 0; i < 20; i++)
    {
        list.remove(list.size() - 1);
        if (i % 10 == 9)
        {
            list.display();
        }
    }
    list.display();
}