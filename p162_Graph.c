#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
typedef int InfoType;
typedef int VertexType; 

//���Ľṹ�� 
typedef struct ArcNode {
	int adjvex;		//�û���ָ��Ķ��� 
	struct ArcNode *nextare;	//ָ����һ������ָ�� 
	InfoType *info;		//�û������Ϣ��ָ�룬����Ȩֵ�� 
}ArcNode;

//����ṹ�� 
typedef struct VNode {
	VertexType data;	//������Ϣ 
	ArcNode *firstarc;		//ָ���һ�������ö���Ļ���ָ�� 
}VNode, AdjList[MAX_VERTEX_NUM];	 

//ͼ�Ľṹ�� 
typedef struct ALGraph {
	AdjList vertices;		//����� 
	int vexnum, arcnum;		//ͼ�ĵ�ǰ�������ͻ��� 
	int kind;		//ͼ�������־�� 1��ʾ����ͼ��2��ʾ����ͼ 
}ALGraph;

void display(ALGraph G) {
	printf("\n����ͼG���ڽӱ�\n");
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
//	printf("����ͼG�����ͣ�1��ʾ����ͼ��2��ʾ����ͼ��");
//	scanf("%d", &kind);
//	if(kind == 1 || kind == 2) 
//		G->kind = kind;
//	else {
//		printf("�������");
//		return;
//	}
	G->kind = 1;
	printf("����ͼG�Ķ������ͻ����ߣ������ո������");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	printf("\n");
	if (G->kind = 1) {
		//��һ����������� 
		for (int i = 0; i < G->vexnum; i++) {
			fflush(stdin);
			printf("������%d�������, �����%d�������ֵ: ", i, i+1);
			int v_data;		//������Ϣ 
			scanf("%d", &v_data);
			G->vertices[i].data = v_data;
			G->vertices[i].firstarc = NULL;
   		}
   		printf("\n");
   		//�����ߵ�����
   		for (int k = 0; k < G->arcnum; k++) {		//����ͼ 
   			//����(vi-vj)�Ķ�������
   			fflush(stdin);
			printf("�ԡ����� ���㡱�ĸ�ʽ�����%d���ߣ�", k+1);
			int i, j;
			scanf("%d%d",&i,&j);
			ArcNode *N = (ArcNode*) malloc (sizeof(ArcNode));
			N->adjvex = j;
			N->nextare = G->vertices[i].firstarc;  //��j�����ͷ
			G->vertices[i].firstarc = N;
			
			N = (ArcNode*) malloc (sizeof(ArcNode));
			N->adjvex = i;
			N->nextare = G->vertices[j].firstarc;  //��i�����ͷ
			G->vertices[j].firstarc = N;
   		}
   		printf("\n");
		 
	} else {		//����ͼ 
		
	}
}


int main() {
	ALGraph G;
	createALGraph(&G);
	display(G);
	return 0;
} 
