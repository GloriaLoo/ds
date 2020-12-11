#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAXQSIZE 100
typedef struct {
	int *base;//初始化分配的空间的地址 
	int front; 
	int rear; 
}SqQueue; 

//初始化 
void InitQueue(SqQueue *Q) {
	Q->base = (int *) malloc (MAXQSIZE * sizeof(int));
	if(!Q->base) exit (-1);
	Q->front = Q->rear = 0;
	printf("初始化完成，当前为队空。\n\n");
	Sleep(1000); 
} 

//返回元素个数 
int QueueLength (SqQueue Q) {
	int length = (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
	return length;
}

//队尾插入元素e 
void EnQueue (SqQueue *Q, int e) {
	if((Q->rear+1) % MAXQSIZE == Q->front) exit (-1);
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear+1) % MAXQSIZE;
}

//删除元素，用e返回 
int DeQueue (SqQueue *Q, int *e) {
	if(Q->front == Q->rear) {
		printf("队空！");
		return 0;
	} 
	*e = Q->base[Q->front];
	Q->front = (Q->front+1) % MAXQSIZE;
	return 1;
}

//遍历队列 
int display(SqQueue Q) {
	if(Q.front == Q.rear) {
		printf("队空！");
		return 0;
	} 
	printf("遍历队列（长度为%d）: ", QueueLength(Q));
	int temp =  Q.front;
	while(temp != Q.rear) {
		printf("%3d", Q.base[temp]);
		temp = (temp+1) % MAXQSIZE;
	} 
	printf("\n\n"); 
	return 1;
}

int main() {
	SqQueue  Q;
	InitQueue(&Q);
	
	printf("需要几个元素入队？(小于%d): ", MAXQSIZE);
	int q_length;
	scanf("%d", &q_length); 
	for(int i=0; i<q_length; i++){
		printf("输入第%d个元素: ", i+1);
		int en_e;
		scanf("%d", &en_e);
		EnQueue(&Q, en_e);
		printf("%d已入队\n", en_e);
	}
	display(Q);
	
	printf("需要几个元素出队？");
	int de_length;
	scanf("%d", &de_length);
	for(int i=0; i<de_length; i++) {
		int de_e;
		DeQueue(&Q,&de_e);
		printf("%d已出队\n\n", de_e);
	} 
	display(Q);
	return 0;
}
