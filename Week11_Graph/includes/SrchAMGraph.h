#pragma once
#include <iostream>
#include "AdjMatGraph.h"
#include "CircularQueue.h"

// 그래프의 깊이/너비 우선 탐색(인접 행렬)

class SrchAMGraph : public AdjMatGraph
{
protected:
    bool visited[MAX_VTXS];

public:
    void resetVisited()
    {
        for (int i = 0; i < size; i++)
            visited[i] = false;
    } // 방문기록을 모두 삭제

    bool isLinked(int u, int v) {}

    // 깊이 우선 탐색(DFS)
    void DFS(int v)
    {
        visited[v] = true;
        std::cout << getVertex(v) << " ";
        for (int w = 0; w < size; w++)
        {
            if (isLinked(v, w) && visited[w] == false)
            {
                DFS(w);
            }
            // 이웃한 모든 vertex에 대해서 깊이 우선 탐색을 수행
            // 재귀호출을 사용
            // 방문한 기록이 있다면 깊이 우선 탐색을 하지 않음
            // 주의할 점: self-loop이 있는 네트워크에서는 제대로 작동하지 않을 수 있음
        }
    }

    // 너비 우선 탐색(BFS)
    void BFS(int v)
    {
        visited[v] = true;
        std::cout << getVertex(v) << " ";
        CircularQueue que;
        que.enqueue(v);        // queue에 v를 삽입연산
        while (!que.isEmpty()) // 큐가 빌 때 까지
        {
            int v = que.dequeue();
            // queued에 남아 있는 vertex중 가장 먼저 삽입한 vetex를 가져옴
            for (int w = 0; w < size; w++)
            {
                if (isLinked(v, w) && visited[w] == false)
                {
                    visited[w] = true;
                    std::cout << getVertex(w) << " ";
                    que.enqueue(w);
                }
                // 이웃한 모든 vertex를 일단 queue에 삽입
                // 큐에서 먼저 삽입한 순서 (= seed 노드에서 가까운 순서)로 꺼내서 탐색
            }
        }
    }
};