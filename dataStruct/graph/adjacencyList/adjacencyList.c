#include "adjacencyList.h"
AGraph *createAGraph(int n) {
    AGraph *graph = malloc(sizeof(AGraph));
    if (graph == NULL) {
        return NULL;
    }
    graph->edgenum = 0;
    graph->nodenum = n;
    
    graph->nodes = malloc(sizeof(ArcNode) * n);
    memset(graph->nodes, 0, sizeof(ArcNode) * n);
    return graph;
}

void initAGraph(AGraph *graph, const char *name[], int num, int directed) {
    graph->directed = directed;
    for (int i = 0; i < num; ++i) {
        graph->nodes[i].no = i;
        graph->nodes[i].show = name[i];
        graph->nodes[i].firstEdge = NULL;
    }
}

static ArcEdge *createArcEdge(int no, int w) {
    ArcEdge *edge = malloc(sizeof(ArcEdge));
    if (edge == NULL) {
        return NULL;
    }
    edge->no = no;
    edge->weight = w;
    edge->next = NULL;
    return edge;
}

//x: 起点编号
//y: 终点编号
void addAGraph(AGraph *graph, int x, int y, int w) {
   
    if (x < 0 || x >= graph->nodenum || y < 0 || y >= graph->nodenum) {
        return;
    }
    if (x == y) {
        return;
    }
    // 使用头插法进行边信息的维护
    ArcEdge* edge = createArcEdge(y, w);
    edge->next = graph->nodes[x].firstEdge;
    graph->nodes[x].firstEdge = edge;
    graph->edgenum++;
    
    if (graph->directed == 0) {    // 无向图
        edge = createArcEdge(x, w);
        edge->next = graph->nodes[y].firstEdge;
        graph->nodes[y].firstEdge = edge;
        graph->edgenum++;
    }
}

void destroyAGraph(AGraph *graph){
    if(graph == NULL){
        return;
    }
    for (int i = 0; i < graph->nodenum; ++i) {
        ArcEdge *edge = graph->nodes[i].firstEdge;
        while (edge != NULL) {
            ArcEdge *temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph->nodes);
    free(graph);
}