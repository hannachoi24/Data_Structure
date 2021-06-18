#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>

#define NUMBER 10
#define MAX_VTXS 5000

using namespace std;
// 가중치 있는
class AdjMatGraph
{
protected:
    int vertices[MAX_VTXS]; // 각 Vertex의 이름 (한 글자로...)
    //int adj[MAX_VTXS][MAX_VTXS]; // Adjacency matrix
    int **adj; // 동적할당

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
        if (0 <= adj[i][j] && adj[i][j] <= 9999)
        {
            return adj[i][j];
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
        setEdge(v, u, 1);
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

#define INF 9999

class WGraph : public AdjMatGraph
{
public:
    WGraph() {}
    ~WGraph() {}

    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }
    void insertEdge(int u, int v, int weight)
    {
        if (weight >= INF)
        {
            weight = INF;
        }
        setEdge(u, v, weight);
        setEdge(v, u, weight);
    } // 방향성이 없는 그래프이기때문에 행렬성분 양쪽 모두에 가중치를 추가
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
                    insertEdge(i, j, val);
                }
            }
        }
        ifs.close();
    }
};

class RandomWalker
{
public:
    int start; // 어느 노드에서 시작할건지
    int next;
    int probability = 0; // 어떤 노드로 갈 확률
    int time;            // 반복 횟수

    RandomWalker() {}
    RandomWalker(int start_, int time_)
    {
        start = start_;
        time = time_;
    }
    ~RandomWalker() {}

    int setProb(int a, AdjMatGraph g) // 확률 설정 부분
    {
        int arr[MAX_VTXS] = {
            0,
        }; // 해당 노드의 행 성분
        float prob[MAX_VTXS] = {
            0,
        };             // 해당 노드 행 성분이 걸릴 확률
        int count = 0; // 해당 노드의 행 성분들의 합

        ////////////////////////////arr 배열 설정////////////////////////////
        for (int i = 0; i < g.size; i++)
        {
            if (0 <= g.getEdge_count(a, i) && g.getEdge_count(a, i) < 9999)
            {
                count += g.getEdge_count(a, i);
                arr[i] = g.getEdge_count(a, i);
            } // 행 성분이 0~9998 일 경우 배열에 추가 및 count값 증가
              // 행 성분이 0 인 경우는 간선(Edge)는 존재하나 가중치가 0인경우
            else if (g.getEdge_count(a, i) == 9999)
            {
                arr[i] = g.getEdge_count(a, i);
            } // 행 성분이 9999 (INF) 일 경우 배열에만 추가
              // 행 성분이 9999 (INF) 인 경우는 간선(Edge)가 존재X
        }
        ////////////////////////////////////////////////////////////////////

        ////////////////////////////prob 배열 설정(다른 노드로 갈 확률)///////////////////////////
        for (int i = 0; i < g.size; i++)
        {
            if (0 <= arr[i] && arr[i] < 9999)
            {
                float tmp = arr[i] / float(count); // 각 배열의 값을 그 배열의 합 값으로 나눠줌
                prob[i] = round(tmp * 100) / 100;  // 소수점 2자리까지 확률 표현
            }
        }
        ////////////////////////////////////////////////////////////////////

        // std::cout << "해당 idx의 확률 배열 : ";
        // for (int i = 0 ; i < g.size; i++){
        //     std::cout << prob[i] << " ";
        // }

        /////////////////////////////예외 처리///////////////////////////////
        float check = 0;
        for (int i = 0; i < g.size; i++)
        {
            check += prob[i];
        }
        if (check == 0)
        { // 확률 배열의 합이 0인 경우 갈 곳이 없는 노드이기에 예외 처리
            std::cout << "경로가 없습니다." << std::endl;
            return -1;
        }
        ////////////////////////////////////////////////////////////////////

        /////////////////////////////확률 계산///////////////////////////////
        else
        {                                               // 확률 배열의 합이 0이 아닌 경우 밑의 코드 시행
            float random = (float)(rand() % 100) / 100; // 확률 0.00~0.99
            //std::cout << random;
            int match = 1;
            int idx = 0;
            float init = 0.00;
            for (int i = 0; i < g.size; i++)
            {
                if (prob[i] == 0)
                {
                    idx++;
                }
                else if (prob[i] != 0)
                {
                    init += prob[i];
                    if (init >= random)
                    {
                        start = idx;
                        break;
                    }
                    else
                    {
                        idx++;
                    }
                }
            }
        }
        ////////////////////////////////////////////////////////////////////
        // std::cout << "확률 : " << random << std::endl;
    }
};
////////////////////////일정시간마다 일정확률로 다른 node로 jump////////////////////////
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
    std::ifstream fin("C:/Users/choihanna/Desktop/C++/Data_Structure/termProject/dataset/starwars/starwars-episode-1-interactions-allCharacters-links.tsv");
    if (!fin)
    {
        std::cout << "파일 오픈 실패" << std::endl;
        exit(100);
    }

    for (int i = 0; i < 408; i++)
    {
        fin >> array1[i];
    }

    for (int i = 3; i < 408; i++)
    {
        //std::cout << array1[i] << " ";
        array2[i - 3] = stoi(array1[i]);
        //std::cout << array2[i-3] << " ";
    }

    for (int i = 0; i < 135; i++)
    {
        int r = i * 3;
        int v = i * 3 + 1;
        int z = i * 3 + 2;
        source[i] = array2[r];
        target[i] = array2[v];
        weight[i] = array2[z];
    }
    int random = rand() % 135;
    int select = rand() % 1;
    if (select == 0)
    {
        std::cout << "\n";
        std::cout << "새로운 노드: " << source[random];
        std::cout << "\n";
        return source[random]; // source 배열에 있는 값들 중 랜덤추첨
    }
    std::cout << "\n";
    std::cout << "새로운 노드: " << target[random];
    std::cout << "\n";
    return target[random];
}
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////pageRank함수 구현/////////////////////////////////
typedef std::pair<int, int> int_int_pair; // pair(해당노드 방문횟수, 노드 인덱스)

bool comparator(const int_int_pair &l, const int_int_pair &r)
{
    return l.first > r.first;
}

void pageRank(RandomWalker rw, int *arr, std::vector<int_int_pair> A) // 각 노드의 방문 횟수를 arr로 만들어둠
{
    for (int i = 0; i < 38; i++)
    { // 루프의 범위 : tsv파일 source,target중 max의 값 + 1
        // tsv파일 source,target중 max의 값 + 1 = node의 갯수, 인접행렬의 size
        A.push_back(int_int_pair(arr[i], i));
    }
    std::cout << "TOP3 최다 방문 노드 순서 출력 (0회 방문시 출력 X)" << std::endl;
    stable_sort(A.begin(), A.end(), comparator); // 가장 많이 방문한 인덱스(노드) 기준으로 정렬(노드와 방문수를 알 수 있음)
    for (int i = 0; i < 3; i++)
    { // TOP N번째까지 출력 설정
        if (A[i].first == 0)
        { // 0회 방문했을 경우부터는 출력 X
            break;
        }
        printf("%d번 노드 : %d번 방문\n", A[i].second, A[i].first); // 배열이 막 들어있기 때문에 각 인덱스와 그 값이랑 매칭시켜 저장하기 위해 만듬
    }
}
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    WGraph g;
    g.load("graph.txt");
    //g.display();

    RandomWalker rw;
    rw.start = 0;     // start하는 노드 설정
    rw.time = NUMBER; // 노드를 이동하는 횟수 설정
    rw.next = rw.start;
    int arr[38] = {
        0,
    }; // tsv파일 source,target중 max의 값 + 1
    std::vector<int_int_pair> A;

    std::string array1[2000]; // 임의로 설정
    int array2[408];          // tsv파일의 line수 * 3 크기로 설정
    int source[135];          // tsv파일의 line수 -1 크기로 설정
    int target[135];          // tsv파일의 line수 -1 크기로 설정
    int weight[135];          // tsv파일의 line수 -1 크기로 설정
    std::string arr3[3];
    std::ifstream fin("C:/Users/choihanna/Desktop/C++/Data_Structure/termProject/dataset/starwars/starwars-episode-1-interactions-allCharacters-links.tsv");
    if (!fin)
    {
        std::cout << "파일 오픈 실패" << std::endl;
        exit(100);
    }

    ///////////////////////////////tsv파일 읽어서 배열 저장/////////////////////////////////
    for (int i = 0; i < 408; i++)
    {
        fin >> array1[i];
    }

    for (int i = 3; i < 408; i++)
    {
        //std::cout << array1[i] << " ";
        array2[i - 3] = stoi(array1[i]);
        //std::cout << array2[i-3] << " ";
    }

    for (int i = 0; i < 135; i++)
    {
        int r = i * 3;
        int v = i * 3 + 1;
        int z = i * 3 + 2;
        source[i] = array2[r];
        target[i] = array2[v];
        weight[i] = array2[z];
    }
    //////////////////////////////////////////////////////////////////////////////////////

    ///////////max값(현재 사용X)/////////////
    int max = source[0];
    for (int i = 1; i < 135; i++)
    {
        if (max < source[i])
        {
            max = source[i];
        }
    }
    ////////////////////////////////////////

    /////////////////tsv파일로부터 저장한 배열로 그래프 생성////////////////////
    WGraph h;
    int graph_size = 0;
    for (int i = 0; i < 38; i++)
    {
        h.insertVertex(i);
        graph_size++;
    }
    for (int i = 0; i < 135; i++)
    {
        h.insertEdge(source[i], target[i], weight[i]);
        //h.setEdge(source[i],target[i],weight[i]);
    }
    //h.display();
    /////////////////////////////////////////////////////////////////////////

    ////////////////////////Random Walker함수 실행////////////////////////////
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
    ////////////////////////////////////////////////////////////////////////

    pageRank(rw, arr, A);

    return 0;
}
