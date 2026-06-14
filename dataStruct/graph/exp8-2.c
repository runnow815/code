/*
 * 实验题2：实现图的遍历算法
 * 基于邻接表实现 DFS（递归和非递归）以及 BFS
 * 测试数据：图 8.54 有向图
 */

#include "adjacencyList/adjacencyList.h"

#define MAX_NODES 20

/* ---------- DFS 递归 ---------- */
static void DFS(AGraph *g, int v, int visited[]) {
    visited[v] = 1;
    printf("%d ", v);

    ArcEdge *e = g->nodes[v].firstEdge;
    while (e != NULL) {
        if (!visited[e->no]) {
            DFS(g, e->no, visited);
        }
        e = e->next;
    }
}

void DFS_recursive(AGraph *g, int start) {
    int visited[MAX_NODES] = {0};
    printf("DFS（递归）: ");
    DFS(g, start, visited);
    printf("\n");
}

/* ---------- DFS 非递归（栈） ---------- */
void DFS_nonrecursive(AGraph *g, int start) {
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = -1;

    printf("DFS（非递归）: ");

    // 初始顶点入栈并标记
    stack[++top] = start;
    visited[start] = 1;
    printf("%d ", start);

    while (top != -1) {
        int v = stack[top];  // 窥探栈顶
        ArcEdge *e = g->nodes[v].firstEdge;

        // 寻找第一个未访问的邻接点
        int found = 0;
        while (e != NULL) {
            if (!visited[e->no]) {
                // 找到则入栈并标记
                stack[++top] = e->no;
                visited[e->no] = 1;
                printf("%d ", e->no);
                found = 1;
                break;
            }
            e = e->next;
        }

        if (!found) {
            top--;  // 所有邻接点已访问，回溯
        }
    }
    printf("\n");
}

/* ---------- BFS（队列） ---------- */
void BFS(AGraph *g, int start) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    printf("BFS: ");

    // 初始顶点入队
    queue[rear++] = start;
    visited[start] = 1;

    while (front != rear) {
        int v = queue[front++];  // 出队
        printf("%d ", v);

        ArcEdge *e = g->nodes[v].firstEdge;
        while (e != NULL) {
            if (!visited[e->no]) {
                queue[rear++] = e->no;
                visited[e->no] = 1;
            }
            e = e->next;
        }
    }
    printf("\n");
}

/* ---------- main ---------- */
int main() {
    system("chcp 65001>nul");

    // 构建图 8.54（有向图，6个顶点）
    AGraph *g = createAGraph(6);
    const char *name[] = {"0", "1", "2", "3", "4", "5"};
    initAGraph(g, name, 6, 1);

    addAGraph(g, 0, 1, 5);
    addAGraph(g, 0, 3, 7);
    addAGraph(g, 1, 2, 4);
    addAGraph(g, 2, 0, 8);
    addAGraph(g, 2, 5, 9);
    addAGraph(g, 3, 2, 5);
    addAGraph(g, 3, 5, 6);
    addAGraph(g, 4, 3, 5);
    addAGraph(g, 5, 4, 1);
    addAGraph(g, 5, 0, 3);

    printf("图 8.54 从顶点 0 开始的遍历结果：\n\n");

    DFS_recursive(g, 0);
    DFS_nonrecursive(g, 0);
    BFS(g, 0);

    printf("\n");
    destroyAGraph(g);
    return 0;
}
