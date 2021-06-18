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

#define NUMBER 500
#define MAX_VTXS 5000

using namespace std;

class AdjMatGraph
{
protected:
    int vertices[MAX_VTXS]; // 각 Vertex의 이름 (한 글자로...)
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

    int setProb(int a, WGraph g)
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

        ////////////////////////////prob 배열 설정///////////////////////////
        //std:: cout <<"해당 노드의 count값 : " << count ;
        for (int i = 0; i < g.size; i++)
        {
            if (0 <= arr[i] && arr[i] < 9999)
            {
                if (count == 0)
                {
                    return -1;
                }
                float tmp = arr[i] / float(count);
                prob[i] = round(tmp * 100) / 100; // 소수점 2자리까지 확률 표현
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
        // std::cout <<"해당 노드 확률 배열 : ";
        // for (int i = 0 ;  i < g.size; i++){
        //     std::cout << prob[i] <<" ";
        // }
        if (check == 0)
        { // 확률 배열의 합이 0인 경우 갈 곳이 없는 노드이기에 예외 처리
            //std::cout <<"경로가 없습니다."<<std::endl;
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
        return 0;
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
/////////////////////////////////////////////////////////////////////////////////

///////////////////////////////pageRank함수 구현/////////////////////////////////
typedef std::pair<int, int> int_int_pair; // pair(해당노드 방문횟수, 노드 인덱스)

bool comparator(const int_int_pair &l, const int_int_pair &r)
{
    return l.first > r.first;
}

void pageRank(RandomWalker rw, int *arr, std::vector<int_int_pair> A)
{
    for (int i = 0; i < 4653; i++)
    { // 루프의 범위 : tsv파일 source,target중 max의 값 + 1
        // tsv파일 source,target중 max의 값 + 1 = node의 갯수, 인접행렬의 size
        A.push_back(int_int_pair(arr[i], i));
    }
    std::cout << "TOP3 최다 방문 노드 순서 출력 (0회 방문시 출력 X)" << std::endl;
    stable_sort(A.begin(), A.end(), comparator);
    for (int i = 0; i < 3; i++)
    { // TOP N번째까지 출력 설정
        if (A[i].first == 0)
        { // 0회 방문했을 경우부터는 출력 X
            break;
        }
        printf("%d번 노드 : %d번 방문\n", A[i].second, A[i].first);
    }
}
////////////////////////////////////////////////////////////////////////////////

int main(void)
{
    WGraph g;
    g.load("graph.txt");
    //g.display();

    RandomWalker rw;
    rw.start = 207;   // start하는 노드 설정
    rw.time = NUMBER; // 노드를 이동하는 횟수 설정
    rw.next = rw.start;
    int arr[4653] = {
        0,
    }; // tsv파일 source,target중 max의 값 + 1
    std::vector<int_int_pair> A;

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

    ///////////////////////////////tsv파일 읽어서 배열 저장/////////////////////////////////
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
    // for (int i = 0 ; i < 274; i++){ // tsv파일의 line수 -1 크기로 설정
    //     std::cout << target[i] << " ";
    // }
    //////////////////////////////////////////////////////////////////////////////////////

    ///////////max값(현재 사용X)/////////////
    int max;
    int max_source = source[0];
    for (int i = 1; i < 274; i++)
    { // tsv파일의 line수 -1 크기로 설정
        if (max_source < source[i])
        {
            max_source = source[i];
        }
    }

    int max_target = target[0];
    for (int i = 1; i < 274; i++)
    { // tsv파일의 line수 -1 크기로 설정
        if (max_target < target[i])
        {
            max_target = target[i];
        }
    }
    if (max_source >= max_target)
    {
        max = max_source;
    }
    if (max_source < max_target)
    {
        max = max_target;
    }

    //std::cout << "max값은 : "<<max; // max값 확인
    // for (int i = 0 ; i < 274; i++){ // tsv파일의 line수 -1 크기로 설정
    //     std::cout << source[i] << " ";
    // }
    ////////////////////////////////////////

    /////////////////tsv파일로부터 저장한 배열로 그래프 생성////////////////////
    WGraph h;
    int graph_size = 0;
    for (int i = 0; i < 4653; i++)
    {
        h.insertVertex(i);
        graph_size++;
    }
    for (int i = 0; i < 274; i++)
    {
        h.insertEdge(source[i], target[i], weight[i]);
    }

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

        if ((k % 3) == 0)
        {
            rw.start = changeNode(rw.start, graph_size);
            rw.setProb(rw.start, h);
            i++;
        }
        std::cout << rw.start << "->";
    }
    // for (int i = 0; i < 38; i++){
    //     std::cout<<arr[i]<<" ";
    // }
    // std::cout<<std::endl;
    ////////////////////////////////////////////////////////////////////////

    pageRank(rw, arr, A);

    return 0;
}
