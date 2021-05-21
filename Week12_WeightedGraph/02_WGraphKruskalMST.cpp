#include "includes/WGraphMST.h"
#include <iostream>

int main(void)
{
    WGraphMST g;
    g.load("graph.txt");
    g.display();

    std::cout << "MST By Kruskal's Algorithm\n";
    g.Kruskal();

    return 0;
}