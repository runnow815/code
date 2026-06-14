/*
 * 实验题8：Floyd算法求带权有向图的最短路径
 * 基于邻接矩阵
 * 测试数据：图8.54 有向图，所有顶点对之间的最短路径
 */

#include "maxtrixGraph/maxtrixGraph.h"

#define MAX_NODES 20

void Floyd(MGraph *g) {
    int n = g->nodeNum;
    int dist[MAX_NODES][MAX_NODES];
    int path[MAX_NODES][MAX_NODES];  // path[i][j] 记录 i->j 路径上的中间点

    // 初始化 dist 和 path
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = g->edges[i][j];
            path[i][j] = -1;  // 表示直达
        }
        dist[i][i] = 0;  // 自己到自己是0
    }

    // Floyd 主循环
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                int newDist = dist[i][k] + dist[k][j];
                if (newDist < dist[i][j]) {
                    dist[i][j] = newDist;
                    path[i][j] = k;
                }
            }
        }
    }

    // 输出路径
    void printPath(int i, int j) {
        if (path[i][j] == -1) {
            printf(" -> ");
        } else {
            int k = path[i][j];
            printPath(i, k);
            printf("%s", g->vex[k].show);
            printPath(k, j);
        }
    }

    printf("Floyd 所有顶点对之间的最短路径：\n\n");
    printf("    ");
    for (int i = 0; i < n; i++) printf("  %s  ", g->vex[i].show);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("  %s  ", g->vex[i].show);
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("  ∞  ");
            else
                printf(" %3d ", dist[i][j]);
        }
        printf("\n");
    }

    printf("\n详细路径：\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] < INF) {
                printf("  %s -> %s : 距离=%d  路径: %s",
                       g->vex[i].show, g->vex[j].show, dist[i][j],
                       g->vex[i].show);
                printPath(i, j);
                printf("%s\n", g->vex[j].show);
            }
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

    Floyd(&g);

    return 0;
}
