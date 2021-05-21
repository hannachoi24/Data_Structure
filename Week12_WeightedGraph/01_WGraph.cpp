#include "includes/WGraph.h"

int main(void)
{
    WGraph g;
    g.load("graph.txt");
    g.display();

    /*
    printf("MST By Kruskal's Algorithm\n");
    g.Kruskal();
    printf("MST By Prim's Algorithm\n");
    g.Prim();
    g.store("g2.txt");
    */
    return 0;
}