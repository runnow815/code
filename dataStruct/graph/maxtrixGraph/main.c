#include"maxtrixGraph.h"



int main(){

    system("chcp 65001>nul"); // 设置控制台输出编码为UTF-8，确保中文字符正确显示

    MGraph g;

    initMGraph(&g,(const char*[]){"A","B","C","D","E","F"},6,1,INF);
    addMGraph(&g,0,1,5);
    addMGraph(&g,0,3,7);

    addMGraph(&g,1,2,4);

    addMGraph(&g,2,0,8);
    addMGraph(&g,2,5,9);

    addMGraph(&g,3,2,5);
    addMGraph(&g,3,5,6);

    addMGraph(&g,4,3,5);

    addMGraph(&g,5,4,1);
    addMGraph(&g,5,0,3);
    
    printf("邻接矩阵：\n");
    
    for(int i=0;i<g.nodeNum;i++){
    
        for(int j=0;j<g.nodeNum;j++){
            if(g.edges[i][j] == INF)continue;
                
            printf("%d--%d-->%d  ",i,g.edges[i][j],j);
            printf("\n");
        }
    
        printf("\n");
    }

    return 0;
}