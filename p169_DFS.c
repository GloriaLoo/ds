/*
DFS算法更适合数组法构建图 
先构建图
再遍历 
*/

#include <stdio.h>
#include<stdlib.h>
#define INFINITY INT_MAX
#define MAX_V_NUM 20
typedef char VertexType;
typedef int InfoType; 
typedef int GKind;		//有向图，无向图 
typedef struct ArcCell {
	int adj;		//表示顶点关系类型，对于无权图，1、0->相邻、不相邻；对有权图则表示权值类型 （很少用） 
	InfoType *info;		//该弧相关信息的指针，例如权值等 //暂时不需要弧的信息 
}AcrCell, AdjMatrix[MAX_V_NUM][MAX_V_NUM];
typedef struct {
	VertexType vexs[MAX_V_NUM];		//存数据的一维数组 
	AdjMatrix arcs;
	int vexnum, arcnum;
	GKind kind;
}MGraph;

//构造图时需要的LocateVex函数
//返回顶点v在图G中的位置，没有则返回-1 
int LocateVex(MGraph *G, VertexType v) {
    int i = 0;
    //遍历一维数组，找到变量v
    for (i = 0; i < G->vexnum; i++) 
        if (G->vexs[i] == v) 
        	return i;
            
    //如果找不到, 返回-1
    if (i > G->vexnum) {
        printf("输入结点错误！\n");
        return -1;
    }
    return -1; 
}

void CreateMGraph(MGraph *G) {
//	int kind;
//	printf("输入图G的类型，1表示无向图，2表示有向图：");
//	scanf("%d", &kind);
//	if(kind == 1 || kind == 2) 
//		G->kind = kind;
//	else {
//		printf("输入错误！");
//		return;
//	}
	
	printf("输入图的顶点数、弧数（用空格隔开）: "); 
    scanf("%d %d", &(G->vexnum), &(G->arcnum));
	getchar();
	G->kind = 1; 
    printf("\n");
    
    for (int i = 0; i < G->vexnum; i++) { 	//构造顶点数组 
    	printf("输入第%d个顶点的值，构造顶点向量：", i+1); 
		scanf("%c", &(G->vexs[i]));
		getchar();
	} 
	printf("\n");
	fflush(stdin);
	
	//初始化邻接矩阵 
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G -> arcs[i][j].adj = 0;
            G -> arcs[i][j].info = NULL;		//暂时不需要弧的信息 
        }
    }
    fflush(stdin);
    
    //构造二维矩阵 
    for (int k = 0; k < G->arcnum; k++) {
    	printf("以“顶点,顶点”的格式输入第%d条边：", k+1);		//输入顶点的值 
        VertexType v1, v2;		//顶点<v1, v2> 
        scanf("%c %c",&v1, &v2);
        getchar();
        int i = LocateVex(G, v1);	//获取v1在G中的位置 
        int j = LocateVex(G, v2);
        printf("位置分别为%d %d\n", i, j);
        if (i == -1 || j == -1) {
            printf("输入错误！\n");
            return;
        }
        //假设弧不含有其他信息
		//若有，则要输入并保存到G.[i][j].info中，要保存的信息类型太多，难以实现 
        G -> arcs[i][j].adj = 1;
		G -> arcs[i][j].adj = 1;
    }
}

//FirstAdjVex和NextAdjVex为DFS需要的函数 
//返回v的第一个邻接顶点的位置，若无则返回-1 
int FirstAdjVex(MGraph G,int v) {
    for(int i = 0; i < G.vexnum; i++)
        if(G.arcs[v][i].adj == 1)
            return i;
            
    return -1;
}

//返回v在G中相对于w的下一个邻接顶点的位置，若无则返回-1 
int NextAdjVex(MGraph G,int v,int w) {
    for(int i = w+1; i < G.vexnum; i++)
        if(G.arcs[v][i].adj == 1)
            return i;

    return -1;
}


//DFS的全局变量 
int visited[MAX_V_NUM];

void VisitFunc(MGraph G, int v) {
    printf("%c  ",G.vexs[v]);
}

//访问函数，从第v个顶点出发递归的深度优先遍历G 
void DFS(MGraph G, int v) {
	visited[v] = 1;
	VisitFunc(G, v);
	for(int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
        if(visited[w] == 0)
            DFS(G,w);
}

//深度优先遍历 
void DFSTraverse(MGraph G) {
	int i;
	for (i = 0; i < G.vexnum; i++) 
		visited[i] = 0;		//初始化访问标志数组，初值为0，表示未被访问
	for (i = 0; i < G.vexnum; i++) 
		if (visited[i] == 0) 
			DFS(G, i);
}


int main() {
	fflush(stdin);
	MGraph G;
	CreateMGraph(&G);
	printf("\n深度优先遍历为："); 
	DFSTraverse(G); 
	
	return 0;
} 
