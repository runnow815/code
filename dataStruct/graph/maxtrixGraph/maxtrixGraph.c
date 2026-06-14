#include "maxtrixGraph.h"


void initMGraph(MGraph *graph, const char *name[], int num, int directed, int edgeValue) {
    //可以对整个空间memset
    //结构体MGraph内部使用的是固定大小的数组
    // 初始化图的基本信息
    graph->directed = directed;  // 设置是否有向
    graph->nodeNum = num;        // 设置顶点数量
    graph->edgeNum = 0;          // 初始边数为0
    
    // 初始化顶点数组（清零）
    memset(graph->vex, 0, sizeof(graph->vex));
    memset(graph->edges, 0, sizeof(MatrixEdge)*MaxNodeNum*MaxNodeNum);
    
    // 设置每个顶点的信息
    for (int i = 0; i < num; ++i) {
        graph->vex[i].no = i;          // 顶点编号
        graph->vex[i].show = name[i];  //只是复制指针，不复制字符串内容顶点显示名称
        
        // 初始化邻接矩阵：将所有边的权重设为初始值
        for (int j = 0; j < num; ++j) {
            graph->edges[i][j] = edgeValue;  // 通常INF表示无边，0或其他值表示有边
        }
    }
}

// 辅助函数：判断是否为有效边（在邻接矩阵中使用）
static int isEdge(int weight) {
    if (weight > 0 && weight < INF) {
        return 1;  // 是有效边
    }
    return 0;      // 不是有效边（无边或权重无效）
}
// 向邻接矩阵图中添加边
void addMGraph(MGraph *graph, int x, int y, int w) {
    // 检查顶点编号是否有效
    if (x < 0 || x >= graph->nodeNum) {  // 修正：应该是>=而不是>
        return;
    }
    if (y < 0 || y >= graph->nodeNum) {  // 修正：应该是>=而不是>
        return;
    }
    
    // 检查边是否已经存在（避免重复计数）
    if (!isEdge(graph->edges[x][y])) {
        graph->edges[x][y] = w;  // 设置从x到y的边权重
        
        // 如果是无向图，还需要设置对称位置的边
        if (graph->directed == 0) {
            graph->edges[y][x] = w;  // 无向图的邻接矩阵是对称的
        }
        
        graph->edgeNum++;  // 边数增加
    }
}