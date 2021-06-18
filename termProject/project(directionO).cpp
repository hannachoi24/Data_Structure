#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <time.h>

#define NUMBER 1000
#define MAX_VTXS 5000

using namespace std;

class AdjMatGraph
{
protected:
    int vertices[MAX_VTXS]; // 각 Vertex의 이름 (한 글자로...)
    //int adj[MAX_VTXS][MAX_VTXS]; // Adjacency matrix
    int **adj;

public:
    AdjMatGraph()
    {
        adj = new int *[MAX_VTXS];
        if (adj)
        {
            for (int i = 0; i < MAX_VTXS; i++)
            {
                adj[i] = new int[MAX_VTXS];
            }
        }
        reset();
    }
    ~AdjMatGraph() {}

    int size; // 전체 Graph의 사이즈 (Vertex의 수)

    int getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    int getEdge_count(int i, int j)
    {
        if (adj[i][j] == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    void reset()
    {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
        {
            for (int j = 0; j < MAX_VTXS; j++)
            {
                setEdge(i, j, 0);
            }
        }
    }

    void insertVertex(int name)
    {
        if (!isFull())
        {
            vertices[size++] = name;
        }
        else
        {
            std::cout << "Exceeding maximum number of vertices";
        }
    }

    void insertEdge(int u, int v)
    {
        if (u < 0 || u >= size)
        {
            std::cout << "out of range";
            exit(0);
        }
        setEdge(u, v, 1);
        //setEdge(v, u, 1);
    } // 방향이 없는 그래프이기 때문에 양쪽 edge를 동시에 추가해 주어야 합니다.

    void display()
    {
        std::cout << size << "\n";
        for (int i = 0; i < size; i++)
        {
            std::cout << getVertex(i) << "  ";
            for (int j = 0; j < size; j++)
                std::cout << getEdge(i, j) << " ";
            std::cout << "\n";
        }
    }

    void load(std::string filename)
    {
        std::ifstream ifs(filename);
        std::string line;
        std::getline(ifs, line);
        std::cout << line << std::endl;
        std::stringstream ls(line);
        int n;
        ls >> n;
        for (int i = 0; i < n; i++)
        {
            std::getline(ifs, line);
            int str;
            int val;
            std::stringstream ls(line);
            ls >> str;
            insertVertex(str);
            for (int j = 0; j < n; j++)
            {
                ls >> val;
                if (val != 0)
                {
                    insertEdge(i, j);
                }
            }
        }
        ifs.close();
    }

    void store(std::string filename)
    {
        std::ofstream ofs(filename);
        ofs << size << "\n";
        for (int i = 0; i < size; i++)
        {
            ofs << getVertex(i) << "  ";
            for (int j = 0; j < size; j++)
                ofs << getEdge(i, j) << " ";
            ofs << "\n";
        }
        ofs.close();
    }
};
class RandomWalker
{
public:
    int start;
    int next;
    int probability = 0;
    int time;

    RandomWalker() {}
    RandomWalker(int start_, int time_)
    {
        start = start_;
        time = time_;
    }
    ~RandomWalker() {}

    int setProb(int a, AdjMatGraph g)
    {
        int arr[MAX_VTXS] = {
            0,
        };
        int count = 0;
        for (int i = 0; i < g.size; i++)
        {
            if (g.getEdge_count(a, i) == 1)
            {
                count += g.getEdge_count(a, i);
                arr[i] = 1;
            }
        }
        probability = count;

        if (probability == 0)
        {
            return -1;
        }
        else
        {
            int random = rand() % probability + 1;
            int match = 1;
            int idx = 0;
            for (int i = 0; i < g.size; i++)
            {
                if (arr[i] == 1)
                {
                    if (match == random)
                    {
                        start = idx;
                        break;
                    }
                    else
                    {
                        match++;
                        idx++;
                    }
                }
                else
                { //( arr[i] == 0 )
                    idx++;
                }
            }
        }
        return 0;
    }
};

int changeNode(int old_node, int graph_size)
{ // old_node = 현재 위치
    int arr[4653] = {
        0,
    }; // tsv파일 source,target중 max의 값 + 1

    std::string array1[2000]; // 임의로 설정
    int array2[825];          // tsv파일의 line수 * 3 크기로 설정
    int source[274];          // tsv파일의 line수 -1 크기로 설정
    int target[274];          // tsv파일의 line수 -1 크기로 설정
    int weight[274];          // tsv파일의 line수 -1 크기로 설정
    std::string arr3[3];
    std::ifstream fin("C:/Users/choihanna/Desktop/C++/Data_Structure/termProject/dataset/bicycle/bicycle_trips_over_100.tsv");
    if (!fin)
    {
        std::cout << "파일 오픈 실패" << std::endl;
        exit(100);
    }
    for (int i = 0; i < 825; i++)
    { // tsv파일의 line수 * 3 크기로 설정
        fin >> array1[i];
        //std::cout << array1[i] << " ";
    }

    for (int i = 3; i < 825; i++)
    { // tsv파일의 line수 * 3 크기로 설정
        //std::cout << array1[i] << " ";
        array2[i - 3] = stoi(array1[i]);
        //std::cout << array2[i-3] << " ";
    }

    for (int i = 0; i < 274; i++)
    { // tsv파일의 line수 -1 크기로 설정
        int r = i * 3;
        int v = i * 3 + 1;
        int z = i * 3 + 2;
        source[i] = array2[r];
        target[i] = array2[v];
        weight[i] = array2[z];
    }
    int random = rand() % 274;
    //std::cout << "새로운 노드: " << source[random];

    return source[random];
}

typedef std::pair<int, int> int_int_pair;

bool comparator(const int_int_pair &l, const int_int_pair &r)
{
    return l.first > r.first;
}

void pageRank(RandomWalker rw, int *arr, std::vector<int_int_pair> A)
{
    for (int i = 0; i < rw.time; i++)
    {
        A.push_back(int_int_pair(arr[i], i));
    }
    std::cout << "TOP5 최다 방문 노드 순서 출력 (0회 방문시 출력 X)" << std::endl;
    stable_sort(A.begin(), A.end(), comparator);
    for (int i = 0; i < 5; i++)
    {
        if (A[i].first == 0)
        {
            break;
        }
        printf("%d번 노드 : %d번 방문\n", A[i].second, A[i].first);
    }
}

int main(void)
{
    AdjMatGraph g;
    for (int i = 0; i < 6; i++)
    {
        g.insertVertex(i);
    }
    g.insertEdge(0, 2);
    g.insertEdge(1, 5);
    g.insertEdge(4, 5);
    g.insertEdge(2, 3);
    g.insertEdge(2, 4);

    //g.display();

    RandomWalker rw;
    rw.start = 207;
    rw.time = NUMBER;
    rw.next = rw.start;
    int arr[NUMBER] = {
        0,
    };
    std::vector<int_int_pair> A;
    std::string array1[2000];
    int array2[825];
    int source[274];
    int target[274];
    std::string arr3[3];
    std::ifstream fin("C:/Users/choihanna/Desktop/C++/Data_Structure/termProject/dataset/bicycle/bicycle_trips_over_100.tsv");
    if (!fin)
    {
        std::cout << "파일 오픈 실패" << std::endl;
        exit(100);
    }

    for (int i = 0; i < 825; i++)
    {
        fin >> array1[i];
    }

    for (int i = 3; i < 825; i++)
    {
        //std::cout << array1[i] << " ";
        array2[i - 3] = stoi(array1[i]);
        //std::cout << array2[i-3] << " ";
    }

    for (int i = 0; i < 274; i++)
    {
        int r = i * 3;
        int v = i * 3 + 1;
        //int z = i*3 + 2;
        source[i] = array2[r];
        target[i] = array2[v];
        //weight[i] = array2[z];
    }

    int max = source[0];
    for (int i = 1; i < 274; i++)
    {
        if (max < source[i])
        {
            max = source[i];
        }
    }
    //std::cout << max <<std::endl;

    AdjMatGraph h;
    int graph_size = 0;
    for (int i = 0; i < 4653; i++)
    {
        h.insertVertex(i);
        graph_size++;
    }
    for (int i = 0; i < 274; i++)
    {
        h.insertEdge(source[i], target[i]);
    }
    //h.display();
    std::cout << rw.start << "->";
    arr[rw.start]++;
    srand((unsigned int)time(NULL)); // srand함수를 통해 난수 생성
    for (int i = 0; i < rw.time; i++)
    {
        int k = i + 1;
        rw.setProb(rw.start, h);
        if (rw.setProb(rw.start, h) == -1)
        {
            std::cout << rw.start << std::endl
                      << "더 이상 경로가 없습니다" << std::endl;
            arr[rw.start]++;
            break;
        }
        arr[rw.start]++;

        if ((k % 20) == 0)
        {
            rw.start = changeNode(rw.start, graph_size);
            rw.setProb(rw.start, h);
            i++;
        }
        std::cout << rw.start << "->";
    }
    pageRank(rw, arr, A);

    fin.close();

    return 0;
}
