#include "adjacencyList.h"



void printAGraph(AGraph *graph){
    printf("邻接表：\n");
    for(int i=0;i<graph->nodenum;++i){
        printf("%s(%d): ", graph->nodes[i].show, graph->nodes[i].no);
        ArcEdge *edge = graph->nodes[i].firstEdge;
        while(edge != NULL){
            printf(" -> %d(weight=%d)", edge->no, edge->weight);
            edge = edge->next;
        }
        printf("\n");
    }
}

int main(){
    system("chcp 65001>nul");
    AGraph *g=createAGraph(6);

    const char* name[]={"0", "1", "2", "3", "4", "5"};
    initAGraph(g, name, sizeof(name)/sizeof(name[0]), 1);

    addAGraph(g,0,1,5);
    addAGraph(g,0,3,7);

    addAGraph(g,1,2,4);

    addAGraph(g,2,0,8);
    addAGraph(g,2,5,9);

    addAGraph(g,3,2,5);
    addAGraph(g,3,5,6);

    addAGraph(g,4,3,5);

    addAGraph(g,5,4,1);
    addAGraph(g,5,0,3);

    printAGraph(g);

    printf("销毁邻接表\n");
    destroyAGraph(g);

    

    return 0;
}