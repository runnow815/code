/*
 * 实验题5：Prim算法求最小生成树
 * 基于邻接矩阵，实现Prim算法
 * 测试数据：图8.55 无向带权连通图，从顶点0出发
 */

#include "maxtrixGraph/maxtrixGraph.h"

#define MAX_NODES 20

void Prim(MGraph *g, int start) {
    int lowcost[MAX_NODES];   // 到已选集合的最小权值
    int closest[MAX_NODES];   // 记录该边是从哪个顶点来的
    int visited[MAX_NODES] = {0};
    int totalWeight = 0;

    // 初始化：从 start 出发
    for (int i = 0; i < g->nodeNum; i++) {
        lowcost[i] = g->edges[start][i];
        closest[i] = start;
    }
    visited[start] = 1;

    printf("Prim 最小生成树（从 %s 出发）：\n\n", g->vex[start].show);

    for (int k = 1; k < g->nodeNum; k++) {
        // 找未访问顶点中 lowcost 最小的
        int min = INF;
        int u = -1;
        for (int i = 0; i < g->nodeNum; i++) {
            if (!visited[i] && lowcost[i] < min) {
                min = lowcost[i];
                u = i;
            }
        }

        if (u == -1) break;  // 不连通

        visited[u] = 1;
        totalWeight += min;
        printf("  %s --%d--> %s\n",
               g->vex[closest[u]].show, min, g->vex[u].show);

        // 更新 lowcost
        for (int i = 0; i < g->nodeNum; i++) {
            if (!visited[i] && g->edges[u][i] < lowcost[i]) {
                lowcost[i] = g->edges[u][i];
                closest[i] = u;
            }
        }
    }

    printf("\n最小生成树总权值: %d\n", totalWeight);
}

int main() {
    system("chcp 65001>nul");

    // 构建图 8.55：图8.54的无向版，边权值不变
    MGraph g;
    initMGraph(&g, (const char *[]){"A", "B", "C", "D", "E", "F"}, 6, 0, INF);

    addMGraph(&g, 0, 1, 5);
    addMGraph(&g, 0, 3, 7);
    addMGraph(&g, 1, 2, 4);
    addMGraph(&g, 2, 0, 8);   // 无向，addMGraph 自动处理对称
    addMGraph(&g, 2, 5, 9);
    addMGraph(&g, 3, 2, 5);
    addMGraph(&g, 3, 5, 6);
    addMGraph(&g, 4, 3, 5);
    addMGraph(&g, 5, 4, 1);
    addMGraph(&g, 5, 0, 3);

    Prim(&g, 0);

    return 0;
}
