#include "includes/LinkedListQueue.h"

int main()
{
    LinkedListQueue que;
    for (int i = 1; i < 10; i++)
    {
        que.enqueue(i);
    }
    que.display();
    que.depueue();
    que.depueue();
    que.depueue();
    que.display();
    return 0;
}