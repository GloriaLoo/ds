#include <stdio.h>
#include <string.h>
#define MAX 255
typedef unsigned char SString[MAX+1];

//��ʼ����S[0]Ϊ����ʵ�ʳ��ȣ���length 
void init(SString *S, int length) {
	(*S)[0] = length;
	char c;
	for(int i = 1; i<=length; i++){
		printf("�����%d���ַ���", i);
		scanf("%c", &c);
		getchar();
		(*S)[i] = c;
	}
}
//��ӡ�� 
void display(SString S) {
	printf("��ǰ����Ԫ�ظ���Ϊ%d����", S[0]);
	for(int i = 1; i<=S[0]; i++) {
		printf("%2c", S[i]);
	}
	printf("\n\n");
}

int index(SString S, SString T, int pos) {
	int i = pos, j = 1;
	while(i<=S[0] && j<=T[0]) {
		if (S[i] == T[j]) {
			++i;
			++j;
		} else {
			i = i - j + 2;
			j = 1;
		}
	}
	if (j>T[0]) return i - T[0] - pos;
	else return 0;
}

int main() {
	SString S, T;
	printf("����S�ĳ��ȣ�");
	int S_len;
	scanf("%d", &S_len);
	getchar();
	init(&S, S_len);
	display(S);
	printf("ģʽT�ĳ��ȣ�");
	int T_len;
	scanf("%d", &T_len);
	getchar();
	init(&T, T_len);
	display(T);
	int index_pos;
	printf("index_pos��");
	scanf("%d", &index_pos); 
	printf("T��S�ĵ�%d��λ��֮��ĵ�%dλ", index_pos, index(S, T, index_pos));
	return 0;
}
