#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAXQSIZE 100
typedef struct {
	int *base;//��ʼ������Ŀռ�ĵ�ַ 
	int front; 
	int rear; 
}SqQueue; 

//��ʼ�� 
void InitQueue(SqQueue *Q) {
	Q->base = (int *) malloc (MAXQSIZE * sizeof(int));
	if(!Q->base) exit (-1);
	Q->front = Q->rear = 0;
	printf("��ʼ����ɣ���ǰΪ�ӿա�\n\n");
	Sleep(1000); 
} 

//����Ԫ�ظ��� 
int QueueLength (SqQueue Q) {
	int length = (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
	return length;
}

//��β����Ԫ��e 
void EnQueue (SqQueue *Q, int e) {
	if((Q->rear+1) % MAXQSIZE == Q->front) exit (-1);
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear+1) % MAXQSIZE;
}

//ɾ��Ԫ�أ���e���� 
int DeQueue (SqQueue *Q, int *e) {
	if(Q->front == Q->rear) {
		printf("�ӿգ�");
		return 0;
	} 
	*e = Q->base[Q->front];
	Q->front = (Q->front+1) % MAXQSIZE;
	return 1;
}

//�������� 
int display(SqQueue Q) {
	if(Q.front == Q.rear) {
		printf("�ӿգ�");
		return 0;
	} 
	printf("�������У�����Ϊ%d��: ", QueueLength(Q));
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
	
	printf("��Ҫ����Ԫ����ӣ�(С��%d): ", MAXQSIZE);
	int q_length;
	scanf("%d", &q_length); 
	for(int i=0; i<q_length; i++){
		printf("�����%d��Ԫ��: ", i+1);
		int en_e;
		scanf("%d", &en_e);
		EnQueue(&Q, en_e);
		printf("%d�����\n", en_e);
	}
	display(Q);
	
	printf("��Ҫ����Ԫ�س��ӣ�");
	int de_length;
	scanf("%d", &de_length);
	for(int i=0; i<de_length; i++) {
		int de_e;
		DeQueue(&Q,&de_e);
		printf("%d�ѳ���\n\n", de_e);
	} 
	display(Q);
	return 0;
}
