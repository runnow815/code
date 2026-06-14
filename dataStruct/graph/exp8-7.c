/*
 * 实验题7：Dijkstra算法求带权有向图的最短路径
 * 基于邻接矩阵
 * 测试数据：图8.54 有向图，从顶点0出发到其他各顶点
 */

#include "maxtrixGraph/maxtrixGraph.h"

#define MAX_NODES 20

void Dijkstra(MGraph *g, int start) {
    int dist[MAX_NODES];        // 最短路径长度
    int path[MAX_NODES][MAX_NODES];  // path[i] 存储到顶点 i 的路径顶点序列
    int pathLen[MAX_NODES];     // 路径长度
    int visited[MAX_NODES] = {0};

    // 初始化
    for (int i = 0; i < g->nodeNum; i++) {
        dist[i] = g->edges[start][i];
        visited[i] = 0;
        pathLen[i] = 0;
        if (dist[i] < INF) {
            path[i][pathLen[i]++] = start;
            path[i][pathLen[i]++] = i;
        }
    }
    visited[start] = 1;
    dist[start] = 0;

    // 主循环
    for (int k = 1; k < g->nodeNum; k++) {
        // 找未访问顶点中 dist 最小的
        int min = INF;
        int u = -1;
        for (int i = 0; i < g->nodeNum; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;  // 剩下的不可达

        visited[u] = 1;

        // 更新从 u 出发到其他顶点的距离
        for (int i = 0; i < g->nodeNum; i++) {
            if (!visited[i] && g->edges[u][i] < INF) {
                int newDist = dist[u] + g->edges[u][i];
                if (newDist < dist[i]) {
                    dist[i] = newDist;
                    // 复制路径：start -> ... -> u -> i
                    pathLen[i] = 0;
                    for (int j = 0; j < pathLen[u]; j++) {
                        path[i][pathLen[i]++] = path[u][j];
                    }
                    path[i][pathLen[i]++] = i;
                }
            }
        }
    }

    // 输出结果
    printf("Dijkstra 从 %s 到各顶点的最短路径：\n\n", g->vex[start].show);
    for (int i = 0; i < g->nodeNum; i++) {
        if (i == start) continue;
        printf("  %s -> %s : ", g->vex[start].show, g->vex[i].show);
        if (dist[i] < INF) {
            printf("距离 = %d, 路径: ", dist[i]);
            for (int j = 0; j < pathLen[i]; j++) {
                printf("%s", g->vex[path[i][j]].show);
                if (j < pathLen[i] - 1) printf(" -> ");
            }
            printf("\n");
        } else {
            printf("不可达\n");
        }
    }
}

int main() {
    system("chcp 65001>nul");

    MGraph g;
    initMGraph(&g, (const char *[]){"A", "B", "C", "D", "E", "F"}, 6, 1, INF);

    addMGraph(&g, 0, 1, 5);
    addMGraph(&g, 0, 3, 7);
    addMGraph(&g, 1, 2, 4);
    addMGraph(&g, 2, 0, 8);
    addMGraph(&g, 2, 5, 9);
    addMGraph(&g, 3, 2, 5);
    addMGraph(&g, 3, 5, 6);
    addMGraph(&g, 4, 3, 5);
    addMGraph(&g, 5, 4, 1);
    addMGraph(&g, 5, 0, 3);

    Dijkstra(&g, 0);

    return 0;
}
