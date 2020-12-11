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

//创建并返回一个栈 
SqStack Create(int length){
	SqStack S; 
	S.base = (int *) malloc (STACK_INIT_SIZE * sizeof(int));
	S.top = S.base;
	for(int i=0; i<length; i++) {
		int e;
		printf("输入第%d个元素：", i+1);
		scanf("%d", &e);
		*(S.top) = e;
		S.top++;
	}
	S.stacksize = S.top - S.base;//创建成功 
	printf("\n");
	return S;
}

//返回栈顶元素（不出栈） 
int GetTop(SqStack S) {
	int get_top = *(S.top-1);
	return get_top;
}

//插入栈顶元素 
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

//出栈，用e返回 
int Pop(SqStack *S){
	int e;
	if(S->top == S->base) return 0;
	e = *((*S).top - 1);
	(*S).top--;
	(*S).stacksize--;
	return e;
}

//返回栈的长度，即元素个数 
int Stacklength (SqStack S){
	return S.stacksize; 
}

//是否为空，返回1则为空，0为非空 
int StackEmpty (SqStack S){
	if(S.top == S.base)
		return 1;
	return 0;
}

//销毁 ???
int DestroyStack(SqStack *S){
	int length = Stacklength((*S));
	for(int i = 0; i<length; i++){
		free((*S).top - 1);
	}
	
}

//将S置为空栈 
void ClearStack(SqStack *S){
	S->top = S->base;
}

//打印栈
int display(SqStack S) {
	if(Stacklength(S) == 0){
		printf("空栈");
		return 0;
	}
	printf("当前栈(长度为%d)：", S.stacksize);
	for(int i=S.stacksize; i>0; i--){
		printf("%d\t", *(S.top-1));
		S.top--;
	}
	printf("\n\n");
	return 1;
}

//十进制转八进制 
void conversion() {
	SqStack S;
	S = Create(0);
	int N;
	printf("输入十进制整数："); 
	scanf("%d", &N);
	printf("%d的", N);
	while(N) {
		Push(&S, N%8);
		N = N/8;
	}
	printf("八进制数为：");
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
//hanoi塔问题
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
//	printf("------第46页——栈及其功能实现------\n\n"); 
//	int n;
//	printf("输入汉诺塔的层数：");
//	scanf("%d", &n);
//	char x = 'x',y = 'y', z = 'z';
//	hanoi(n, x, y, z);
//	printf("\n\n"); 
	
	//创建一个长度为length的栈
	int length;
	printf("输入需要创建的栈的长度："); 
	scanf("%d", &length);
	SqStack S;
	S = Create(length);
	
	display(S); //打印初始栈
	 
	//获取栈顶元素
	int top_e = GetTop(S);
	printf("栈顶元素：%d\n\n", top_e); 
	
	//插入元素到栈顶
	int push_e;
	printf("需要插入几个元素到栈顶？");
	int push_len;
	scanf("%d", &push_len);
	for(int i = 1; i<=push_len; i++) {
		printf("输入第%d个元素：", S.stacksize+1);
		scanf("%d", &push_e);
		Push(&S, push_e);
	}
	display(S);//打印push后的栈 
	
	
	//出栈，返回出栈元素
	int pop_e;
	printf("需要几个元素出栈？");
	int pop_len;
	scanf("%d", &pop_len);
	for(int i = 0; i<pop_len; i++)
		pop_e = Pop(&S);
	display(S);//打印pop后的栈 
	
	printf("栈的长度: %d\n\n", Stacklength(S));//栈的长度 
	printf("3秒后将清空栈\n\n");
	Sleep(3000); 
	ClearStack(&S);//清空栈
	
	//判断栈是否为空 
	int emp = StackEmpty(S);
	if(emp == 1)
		printf("当前栈为空\n\n");
	else 
		printf("当前栈非空\n\n");
		
	//十进制转八进制
	conversion();
	
	return 0;
}


