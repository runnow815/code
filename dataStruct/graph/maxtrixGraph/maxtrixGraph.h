#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 宏定义
#define MaxNodeNum 20     // 最大顶点数
#define INF 1e4          // 表示无穷大（无边）

// 顶点结构
typedef struct {
    int no;              // 顶点的编号
    const char *show;    // 存储顶点表示的数据（如顶点名称）  这是一个指针，指向常量字符串
} MatrixVertex;//Matrix矩阵Vertex顶点

// 定义边的结构（邻接矩阵中边用整数表示权重）
typedef int MatrixEdge;

// 邻接矩阵表示图结构
typedef struct {
    MatrixVertex vex[MaxNodeNum];           // 顶点数组
    MatrixEdge edges[MaxNodeNum][MaxNodeNum]; // 邻接矩阵（存储边权重）
    int nodeNum;                            // 顶点数量，约束访问边界
    int edgeNum;                            // 边的个数
    int directed;                           // 是否有向图（1=有向，0=无向）
} MGraph;  

// 函数声明
void initMGraph(MGraph *graph, const char *name[], int num, int directed, int edgeValue);
void addMGraph(MGraph *graph, int x, int y, int w);