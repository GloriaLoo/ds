/*
DFS�㷨���ʺ����鷨����ͼ 
�ȹ���ͼ
�ٱ��� 
*/

#include <stdio.h>
#include<stdlib.h>
#define INFINITY INT_MAX
#define MAX_V_NUM 20
typedef char VertexType;
typedef int InfoType; 
typedef int GKind;		//����ͼ������ͼ 
typedef struct ArcCell {
	int adj;		//��ʾ�����ϵ���ͣ�������Ȩͼ��1��0->���ڡ������ڣ�����Ȩͼ���ʾȨֵ���� �������ã� 
	InfoType *info;		//�û������Ϣ��ָ�룬����Ȩֵ�� //��ʱ����Ҫ������Ϣ 
}AcrCell, AdjMatrix[MAX_V_NUM][MAX_V_NUM];
typedef struct {
	VertexType vexs[MAX_V_NUM];		//�����ݵ�һά���� 
	AdjMatrix arcs;
	int vexnum, arcnum;
	GKind kind;
}MGraph;

//����ͼʱ��Ҫ��LocateVex����
//���ض���v��ͼG�е�λ�ã�û���򷵻�-1 
int LocateVex(MGraph *G, VertexType v) {
    int i = 0;
    //����һά���飬�ҵ�����v
    for (i = 0; i < G->vexnum; i++) 
        if (G->vexs[i] == v) 
        	return i;
            
    //����Ҳ���, ����-1
    if (i > G->vexnum) {
        printf("���������\n");
        return -1;
    }
    return -1; 
}

void CreateMGraph(MGraph *G) {
//	int kind;
//	printf("����ͼG�����ͣ�1��ʾ����ͼ��2��ʾ����ͼ��");
//	scanf("%d", &kind);
//	if(kind == 1 || kind == 2) 
//		G->kind = kind;
//	else {
//		printf("�������");
//		return;
//	}
	
	printf("����ͼ�Ķ��������������ÿո������: "); 
    scanf("%d %d", &(G->vexnum), &(G->arcnum));
	getchar();
	G->kind = 1; 
    printf("\n");
    
    for (int i = 0; i < G->vexnum; i++) { 	//���춥������ 
    	printf("�����%d�������ֵ�����춥��������", i+1); 
		scanf("%c", &(G->vexs[i]));
		getchar();
	} 
	printf("\n");
	fflush(stdin);
	
	//��ʼ���ڽӾ��� 
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            G -> arcs[i][j].adj = 0;
            G -> arcs[i][j].info = NULL;		//��ʱ����Ҫ������Ϣ 
        }
    }
    fflush(stdin);
    
    //�����ά���� 
    for (int k = 0; k < G->arcnum; k++) {
    	printf("�ԡ�����,���㡱�ĸ�ʽ�����%d���ߣ�", k+1);		//���붥���ֵ 
        VertexType v1, v2;		//����<v1, v2> 
        scanf("%c %c",&v1, &v2);
        getchar();
        int i = LocateVex(G, v1);	//��ȡv1��G�е�λ�� 
        int j = LocateVex(G, v2);
        printf("λ�÷ֱ�Ϊ%d %d\n", i, j);
        if (i == -1 || j == -1) {
            printf("�������\n");
            return;
        }
        //���軡������������Ϣ
		//���У���Ҫ���벢���浽G.[i][j].info�У�Ҫ�������Ϣ����̫�࣬����ʵ�� 
        G -> arcs[i][j].adj = 1;
		G -> arcs[i][j].adj = 1;
    }
}

//FirstAdjVex��NextAdjVexΪDFS��Ҫ�ĺ��� 
//����v�ĵ�һ���ڽӶ����λ�ã������򷵻�-1 
int FirstAdjVex(MGraph G,int v) {
    for(int i = 0; i < G.vexnum; i++)
        if(G.arcs[v][i].adj == 1)
            return i;
            
    return -1;
}

//����v��G�������w����һ���ڽӶ����λ�ã������򷵻�-1 
int NextAdjVex(MGraph G,int v,int w) {
    for(int i = w+1; i < G.vexnum; i++)
        if(G.arcs[v][i].adj == 1)
            return i;

    return -1;
}


//DFS��ȫ�ֱ��� 
int visited[MAX_V_NUM];

void VisitFunc(MGraph G, int v) {
    printf("%c  ",G.vexs[v]);
}

//���ʺ������ӵ�v����������ݹ��������ȱ���G 
void DFS(MGraph G, int v) {
	visited[v] = 1;
	VisitFunc(G, v);
	for(int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
        if(visited[w] == 0)
            DFS(G,w);
}

//������ȱ��� 
void DFSTraverse(MGraph G) {
	int i;
	for (i = 0; i < G.vexnum; i++) 
		visited[i] = 0;		//��ʼ�����ʱ�־���飬��ֵΪ0����ʾδ������
	for (i = 0; i < G.vexnum; i++) 
		if (visited[i] == 0) 
			DFS(G, i);
}


int main() {
	fflush(stdin);
	MGraph G;
	CreateMGraph(&G);
	printf("\n������ȱ���Ϊ��"); 
	DFSTraverse(G); 
	
	return 0;
} 
