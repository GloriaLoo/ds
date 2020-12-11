#include <stdio.h>
#include <string.h>
#define MAX 255
typedef unsigned char SString[MAX+1];

//��ʼ��S 
void init(SString *S) {
	char temp[MAX];
	scanf("%s", temp);
	for(int i = 0; i < strlen(temp); i++) {
		(*S)[i+1] = temp[i];
	}
	(*S)[0] = strlen(temp);	
}

void display(SString S) {
	printf("��ǰ��(length = %d): ", S[0]);
	for(int i = 1; i <= S[0]; i++) 
		printf("%c", S[i]);
	printf("\n\n");
}

//���KMP�㷨��next�㷨 
void get_next(SString T, int next[]) {
	int i = 1, j = 0;
	next[1] = 0;
	while (i<T[0]) {
		if (j == 0 || T[i] == T[j]) {
			++i;
			++j;
			next[i] = j;
		} else j = next[j];
	}
}

//KMP�㷨������pos�����ʼλ 
int index_KMP(SString S, SString T, int pos) {
	int next[T[0]+1];
	get_next(T, next);		//���T��next���� 
	
	int i = pos, j = 1;
	while (i<=S[0] && j<=T[0]) {
		if (j == 0 || S[i] == T[j]) {
			++i;
			++j;
		} else j = next[j];
	}
	if (j > T[0]) return i-T[0]-pos;
	else return 0;
} 

int main() {
	SString S, T;
	printf("-----��ʼ������S-----\n����S��"); 
	init(&S);
	display(S);
	printf("-----��ʼ��ģʽ��T-----\n����T��"); 
	init(&T);
	display(T);
	
	int pos;
	printf("pos = "); 
	scanf("%d", &pos);
	
	int index = index_KMP(S, T, pos); 
	if(pos != 0)
		printf("T��S�ĵ�%d��ĵ�%dλ", pos, index);
	else printf("S�ĵ�%dλ����û��T", pos);
	
	return 0;
}
