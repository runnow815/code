#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ancEdge {
    int no;            // 目标顶点编号
    int weight;        // 边权重
    struct ancEdge *next;  // 指向下一条边的指针
} ArcEdge;

typedef struct {
    int no;            // 顶点自身的编号
    const char *show;  // 顶点显示名称
    ArcEdge *firstEdge;// 指向该顶点的第一条边
} ArcNode;
typedef struct{
    ArcNode *nodes;//指向顶点数组的指针
    int nodenum;
    int edgenum;
    int directed; // 是否为有向图
} AGraph;

//动态产生n个节点
AGraph *createAGraph(int n);
//初始化邻接表的结构
void initAGraph(AGraph *graph, const char *name[], int num, int directed);
//添加边的信息
void addAGraph(AGraph *graph, int x, int y, int w);

void destroyAGraph(AGraph *graph);