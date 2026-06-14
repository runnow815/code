/*
 * 实验题3：求连通图的所有深度优先遍历序列
 * 采用邻接表存储，输出所有DFS序列
 * 测试数据：图8.1(a) 无向图，从顶点1出发
 */

#include "adjacencyList/adjacencyList.h"

#define MAX_NODES 20

static int count = 0;  // 序列计数器

// 检查是否所有顶点都已访问
static int allVisited(AGraph *g, int visited[]) {
    for (int i = 0; i < g->nodenum; i++) {
        if (!visited[i]) return 0;
    }
    return 1;
}

// 回溯法生成所有DFS序列
void findAllDFS(AGraph *g, int v, int visited[], int path[], int depth) {
    visited[v] = 1;
    path[depth] = v;

    if (allVisited(g, visited)) {
        count++;
        printf("  [%2d] ", count);
        for (int i = 0; i <= depth; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        // 尝试当前顶点的每个未访问邻接点
        ArcEdge *e = g->nodes[v].firstEdge;
        while (e != NULL) {
            if (!visited[e->no]) {
                findAllDFS(g, e->no, visited, path, depth + 1);
            }
            e = e->next;
        }
    }

    visited[v] = 0;  // 回溯
}

int main() {
    system("chcp 65001>nul");

    // 构建图 8.1(a) 无向图，5个顶点，6条边
    AGraph *g = createAGraph(5);
    const char *name[] = {"0", "1", "2", "3", "4"};
    initAGraph(g, name, 5, 0);  // 0 = 无向图

    // 添加边（注意：无向图在 addAGraph 中会自动添加双向）
    addAGraph(g, 0, 1, 1);
    addAGraph(g, 0, 3, 1);
    addAGraph(g, 1, 2, 1);
    addAGraph(g, 1, 4, 1);
    addAGraph(g, 2, 3, 1);
    addAGraph(g, 2, 4, 1);

    printf("图 8.1(a) 从顶点 1 出发的所有DFS序列：\n\n");
    int visited[MAX_NODES] = {0};
    int path[MAX_NODES];

    findAllDFS(g, 1, visited, path, 0);

    printf("\n共 %d 个序列\n", count);

    destroyAGraph(g);
    return 0;
}
