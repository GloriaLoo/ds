#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct{
	int *base;
	int *top;
	int stacksize;
}SqStack;

//����������һ��ջ 
SqStack Create(int length){
	SqStack S; 
	S.base = (int *) malloc (STACK_INIT_SIZE * sizeof(int));
	S.top = S.base;
	for(int i=0; i<length; i++) {
		int e;
		printf("�����%d��Ԫ�أ�", i+1);
		scanf("%d", &e);
		*(S.top) = e;
		S.top++;
	}
	S.stacksize = S.top - S.base;//�����ɹ� 
	printf("\n");
	return S;
}

//����ջ��Ԫ�أ�����ջ�� 
int GetTop(SqStack S) {
	int get_top = *(S.top-1);
	return get_top;
}

//����ջ��Ԫ�� 
int Push (SqStack *S, int e) {
	if((S->top - S->base) >= S->stacksize*4) {
		S->base = (int *) realloc (S->base, (S->stacksize + STACKINCREMENT) * sizeof(int));
		if(!S->base) exit(0);
		S->top = S->base + S->stacksize;
		S->stacksize += STACKINCREMENT; 
	}
	
	*(S->top) = e;
	S->top++;
	S->stacksize++;
	return 1;
}

//��ջ����e���� 
int Pop(SqStack *S){
	int e;
	if(S->top == S->base) return 0;
	e = *((*S).top - 1);
	(*S).top--;
	(*S).stacksize--;
	return e;
}

//����ջ�ĳ��ȣ���Ԫ�ظ��� 
int Stacklength (SqStack S){
	return S.stacksize; 
}

//�Ƿ�Ϊ�գ�����1��Ϊ�գ�0Ϊ�ǿ� 
int StackEmpty (SqStack S){
	if(S.top == S.base)
		return 1;
	return 0;
}

//���� ???
int DestroyStack(SqStack *S){
	int length = Stacklength((*S));
	for(int i = 0; i<length; i++){
		free((*S).top - 1);
	}
	
}

//��S��Ϊ��ջ 
void ClearStack(SqStack *S){
	S->top = S->base;
}

//��ӡջ
int display(SqStack S) {
	if(Stacklength(S) == 0){
		printf("��ջ");
		return 0;
	}
	printf("��ǰջ(����Ϊ%d)��", S.stacksize);
	for(int i=S.stacksize; i>0; i--){
		printf("%d\t", *(S.top-1));
		S.top--;
	}
	printf("\n\n");
	return 1;
}

//ʮ����ת�˽��� 
void conversion() {
	SqStack S;
	S = Create(0);
	int N;
	printf("����ʮ����������"); 
	scanf("%d", &N);
	printf("%d��", N);
	while(N) {
		Push(&S, N%8);
		N = N/8;
	}
	printf("�˽�����Ϊ��");
	while (!StackEmpty(S)) {
		printf("%d", Pop(&S));
	}
	printf("\n\n");
} 

//move
int hanoi_count = 1;
void hanoi_move(int x, int n, int z) {
	printf("%d.Move disk %i from %c to %c\n", hanoi_count++, n, x, z);
}
//hanoi������
void hanoi(int n, char x, char y, char z) {
	if(n==1)
		hanoi_move(x, 1, z);
	else{
		hanoi(n-1, x, z, y);
		hanoi_move(x, n ,z);
		hanoi(n-1, y, x, z);
	}
} 

int main(){
//	printf("------��46ҳ����ջ���书��ʵ��------\n\n"); 
//	int n;
//	printf("���뺺ŵ���Ĳ�����");
//	scanf("%d", &n);
//	char x = 'x',y = 'y', z = 'z';
//	hanoi(n, x, y, z);
//	printf("\n\n"); 
	
	//����һ������Ϊlength��ջ
	int length;
	printf("������Ҫ������ջ�ĳ��ȣ�"); 
	scanf("%d", &length);
	SqStack S;
	S = Create(length);
	
	display(S); //��ӡ��ʼջ
	 
	//��ȡջ��Ԫ��
	int top_e = GetTop(S);
	printf("ջ��Ԫ�أ�%d\n\n", top_e); 
	
	//����Ԫ�ص�ջ��
	int push_e;
	printf("��Ҫ���뼸��Ԫ�ص�ջ����");
	int push_len;
	scanf("%d", &push_len);
	for(int i = 1; i<=push_len; i++) {
		printf("�����%d��Ԫ�أ�", S.stacksize+1);
		scanf("%d", &push_e);
		Push(&S, push_e);
	}
	display(S);//��ӡpush���ջ 
	
	
	//��ջ�����س�ջԪ��
	int pop_e;
	printf("��Ҫ����Ԫ�س�ջ��");
	int pop_len;
	scanf("%d", &pop_len);
	for(int i = 0; i<pop_len; i++)
		pop_e = Pop(&S);
	display(S);//��ӡpop���ջ 
	
	printf("ջ�ĳ���: %d\n\n", Stacklength(S));//ջ�ĳ��� 
	printf("3������ջ\n\n");
	Sleep(3000); 
	ClearStack(&S);//���ջ
	
	//�ж�ջ�Ƿ�Ϊ�� 
	int emp = StackEmpty(S);
	if(emp == 1)
		printf("��ǰջΪ��\n\n");
	else 
		printf("��ǰջ�ǿ�\n\n");
		
	//ʮ����ת�˽���
	conversion();
	
	return 0;
}


