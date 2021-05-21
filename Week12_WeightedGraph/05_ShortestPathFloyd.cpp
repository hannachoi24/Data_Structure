#include "includes/WGraphFloyd.h"
#include <iostream>

int main()
{
    WGraphFloyd g;
    g.load("graph_sp.txt");
    g.display();
    std::cout << "Shortest Path By Floyd Algorithm\n";
    g.ShortestPathFloyd();
    for (int i = 0; i < 7; i++)
    {
        g.PrintPath(0, i);
    }
}