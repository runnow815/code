/*
 * 实验题1：实现图的邻接矩阵和邻接表的存储
 * 建立图8.54所示有向图的邻接矩阵和邻接表，并输出它们
 */

#include "adjacencyList/adjacencyList.h"
#include "maxtrixGraph/maxtrixGraph.h"

void printMGraph(MGraph *graph) {
    printf("====== 邻接矩阵 ======\n");
    printf("    ");
    for (int i = 0; i < graph->nodeNum; ++i) {
        printf(" %s  ", graph->vex[i].show);
    }
    printf("\n");

    for (int i = 0; i < graph->nodeNum; ++i) {
        printf("%s  ", graph->vex[i].show);
        for (int j = 0; j < graph->nodeNum; ++j) {
            if (graph->edges[i][j] == INF) {
                printf(" ∞  ");
            } else {
                printf(" %d  ", graph->edges[i][j]);
            }
        }
        printf("\n");
    }

    printf("\n边列表：\n");
    for (int i = 0; i < graph->nodeNum; ++i) {
        for (int j = 0; j < graph->nodeNum; ++j) {
            if (graph->edges[i][j] != INF) {
                printf("  %s--%d-->%s\n",
                       graph->vex[i].show,
                       graph->edges[i][j],
                       graph->vex[j].show);
            }
        }
    }
    printf("\n");
}

void printAGraph(AGraph *graph) {
    printf("====== 邻接表 ======\n");
    for (int i = 0; i < graph->nodenum; ++i) {
        printf("  %s(%d): ", graph->nodes[i].show, graph->nodes[i].no);
        ArcEdge *edge = graph->nodes[i].firstEdge;
        while (edge != NULL) {
            printf(" -> %d(weight=%d)", edge->no, edge->weight);
            edge = edge->next;
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    system("chcp 65001>nul");

    /* -------- 邻接矩阵 ---------- */
    MGraph mg;
    initMGraph(&mg, (const char *[]){"A", "B", "C", "D", "E", "F"}, 6, 1, INF);

    addMGraph(&mg, 0, 1, 5);
    addMGraph(&mg, 0, 3, 7);
    addMGraph(&mg, 1, 2, 4);
    addMGraph(&mg, 2, 0, 8);
    addMGraph(&mg, 2, 5, 9);
    addMGraph(&mg, 3, 2, 5);
    addMGraph(&mg, 3, 5, 6);
    addMGraph(&mg, 4, 3, 5);
    addMGraph(&mg, 5, 4, 1);
    addMGraph(&mg, 5, 0, 3);

    printMGraph(&mg);

    /* -------- 邻接表 ---------- */
    AGraph *ag = createAGraph(6);
    const char *name[] = {"0", "1", "2", "3", "4", "5"};
    initAGraph(ag, name, 6, 1);

    addAGraph(ag, 0, 1, 5);
    addAGraph(ag, 0, 3, 7);
    addAGraph(ag, 1, 2, 4);
    addAGraph(ag, 2, 0, 8);
    addAGraph(ag, 2, 5, 9);
    addAGraph(ag, 3, 2, 5);
    addAGraph(ag, 3, 5, 6);
    addAGraph(ag, 4, 3, 5);
    addAGraph(ag, 5, 4, 1);
    addAGraph(ag, 5, 0, 3);

    printAGraph(ag);

    printf("销毁邻接表\n");
    destroyAGraph(ag);

    return 0;
}
