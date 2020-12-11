#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
typedef int InfoType;
typedef int VertexType; 

//弧的结构体 
typedef struct ArcNode {
	int adjvex;		//该弧所指向的顶点 
	struct ArcNode *nextare;	//指向下一条弧的指针 
	InfoType *info;		//该弧相关信息的指针，例如权值等 
}ArcNode;

//顶点结构体 
typedef struct VNode {
	VertexType data;	//顶点信息 
	ArcNode *firstarc;		//指向第一条依附该顶点的弧的指针 
}VNode, AdjList[MAX_VERTEX_NUM];	 

//图的结构体 
typedef struct ALGraph {
	AdjList vertices;		//顶点表 
	int vexnum, arcnum;		//图的当前顶点数和弧数 
	int kind;		//图的种类标志， 1表示无向图，2表示有向图 
}ALGraph;

void display(ALGraph G) {
	printf("\n无向图G的邻接表：\n");
	for (int i = 0; i < G.vexnum; ++i) {
		printf("%d V%d", i, i+1);
		while(G.vertices[i].firstarc != NULL) {
			printf("->%d", G.vertices[i].firstarc->adjvex);
			G.vertices[i].firstarc = G.vertices[i].firstarc->nextare;
		}
		printf("\n");
    }
} 

void createALGraph(ALGraph *G) {
//	int kind;
//	printf("输入图G的类型，1表示无向图，2表示有向图：");
//	scanf("%d", &kind);
//	if(kind == 1 || kind == 2) 
//		G->kind = kind;
//	else {
//		printf("输入错误！");
//		return;
//	}
	G->kind = 1;
	printf("输入图G的顶点数和弧（边）数，空格隔开：");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	printf("\n");
	if (G->kind = 1) {
		//第一步建立顶点表 
		for (int i = 0; i < G->vexnum; i++) {
			fflush(stdin);
			printf("建立第%d个顶点表, 输入第%d个顶点的值: ", i, i+1);
			int v_data;		//顶点信息 
			scanf("%d", &v_data);
			G->vertices[i].data = v_data;
			G->vertices[i].firstarc = NULL;
   		}
   		printf("\n");
   		//建立边的链表
   		for (int k = 0; k < G->arcnum; k++) {		//无向图 
   			//读入(vi-vj)的顶点对序号
   			fflush(stdin);
			printf("以“顶点 顶点”的格式输入第%d条边：", k+1);
			int i, j;
			scanf("%d%d",&i,&j);
			ArcNode *N = (ArcNode*) malloc (sizeof(ArcNode));
			N->adjvex = j;
			N->nextare = G->vertices[i].firstarc;  //将j插入表头
			G->vertices[i].firstarc = N;
			
			N = (ArcNode*) malloc (sizeof(ArcNode));
			N->adjvex = i;
			N->nextare = G->vertices[j].firstarc;  //将i插入表头
			G->vertices[j].firstarc = N;
   		}
   		printf("\n");
		 
	} else {		//有向图 
		
	}
}


int main() {
	ALGraph G;
	createALGraph(&G);
	display(G);
	return 0;
} 
