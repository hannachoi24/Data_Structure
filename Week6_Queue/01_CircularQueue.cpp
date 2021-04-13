#include "includes/CircularQueue.h"

int main()
{
    CircularQueue que;
    for (int i = 0; i < 10; i++)
    {
        que.enqueue(i);
    }
    que.display();
    que.dequeue();
    que.dequeue();
    que.dequeue();
    que.display();
    return 0;
}
