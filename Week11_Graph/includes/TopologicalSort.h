#pragma once
#include "AdjListGraph.h"
#include "ArrayStack.h"

// 그래프의 위상 정렬 구현

class TopoSortGraph : public AdjListGraph
{
public:
    TopoSortGraph(void) {}
    ~TopoSortGraph(void) {}

    void insertDirEdge(int u, int v)
    { // u->v의 방향성 있는 edge를 만든다.
        adj[u] = new Node(v, adj[u]);
    }

    void TopoSort()
    {
        ArrayStack s;

        int *inDeg = new int[size]; // 모든 정점의 in-degree를 구한다

        for (int i = 0; i < size; i++)
        { // indegree 초기화
            inDeg[i] = 0;
        }

        for (int i = 0; i < size; i++)
        {
            Node *node = adj[i];
            while (node != NULL)
            {
                inDeg[node->getId()]++; // 전체 순회 하면서 indegree가 몇 개 인지 체크한 다음에 자기 indegree만큼 올려줌
                node = node->getLink(); // 다음 노드로 옮겨감
            }
        }

        for (int i = 0; i < size; i++)
        {
            if (inDeg[i] == 0)
            {
                s.push(i);
            }
        } // indegree가 0인 vertex들을 stack에 삽입
          // 이 vertex들이 위상정렬에서 처음 나오는 vertex들

        while (s.isEmpty() == false)
        {
            int w = s.pop();
            std::cout << getVertex(w) << " ";
            Node *node = adj[w];
            while (node != nullptr)
            {
                int u = node->getId(); // seed vertex의 이웃 vertex에 대해 연산을 수행
                inDeg[u]--;            // 그 노드들의 in-degree를 하나씩 줄여줌
                if (inDeg[u] == 0)
                    s.push(u);          // in-degree가 0이 되면 그 노드를 다시 stack으로 넣어준다
                node = node->getLink(); // 다음 이웃을 조회
            }
        }

        std::cout << "\n";
        delete[] inDeg; // 동적 할당해줬기 때문에 삭제연산 필수!! 안해줬을경우 사이즈 오류 발생
        // array 삭제는 delete []
    }
};