#include "includes/WGraphDijkstra.h"

int main(void)
{
    WGraphDijkstra g;

    g.load("graph_sp.txt");
    std::cout << "File loaded\n";
    g.display();

    std::cout << "Shortest Path By Dijkstra Algorithm\n";
    g.ShortestPath(0);
    std::cout << "Finding completed\n";
    for (int i = 0; i < 7; i++)
    {
        g.PrintPath(0, i);
    }

    for (int j = 0; j < 7; j++)
    {
        g.ShortestPath(j);
        std::cout << "Finding completed\n";
        for (int i = 0; i < 7; i++)
        {
            g.PrintPath(j, i);
        }
    }
}