#include <stdio.h>
#include <string.h>
#include <windows.h> 
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

//��ӡS 
int display(SString S) {
	if(strlen(S) == 0) {
		printf("\n\n��ǰ��Ϊ�մ�\n");
		return -1;
	}
	
	for(int i = 1; i <= S[0]; i++) 
		printf("%c", S[i]);
	printf("(length = %d)\n\n", S[0]);
	return 0;
}

//�ж��Ƿ���ȣ�����1��ʾ��ȣ�0��ʾ���� 
int equal(SString S1, SString S2) {
	if(S1[0] != S2[0]) return 0;
	
	int i = 1;
	for(i = 1; i<S1[0]; i++) {
		if(S1[i] != S2[i]) break;
	}
	if(i == S1[0]) return 1;
	else return 0;
}

//�ϲ���������1��ʾ�ضϣ�0��ʾδ�ض�
//��S1��S2�ϲ�ΪT 
void concat(SString *T, SString S1, SString S2) {
	if (S1[0] + S2[0] <= MAX) {			//δ�ض� 
		for(int i = 1; i<=S1[0]; i++)
			(*T)[i] = S1[i];
			
		int j = 1;
		for(int i = S1[0] + 1; i<=S1[0] + S2[0], j<=S2[0] ; i++, j++)
			(*T)[i] = S2[j];
		(*T)[0] = S1[0] + S2[0];
	} else if(S1[0] < MAX) {			//�ض� 
		for (int i = 1; i<=S1[0]; i++)
			(*T)[i] = S1[i];
			
		int j = 1;
		for(int i = 1; i<MAX - S1[0]; i++, j++)
			(*T)[S1[0]+i] = S2[j];
		(*T)[0] = MAX;
	} else {			//��ȡS1 ��S[0] = MAX 
		for (int i = 0; i<=MAX; i++)
			(*T)[i] = S1[i];
	}
}

//���Ӵ�����Sub����S�е�pos���ַ��𳤶�Ϊlen���ִ� 
//����1��ʾ���ҳɹ�������-1��ʾʧ�� 
int subString(SString *Sub, SString S, int pos, int len) {
	if(pos + len - 1 > S[0]) {
		printf("-----Խ�磬�ò����Ӵ�-----");
		return -1;
	}
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos +1) return -1;
	for (int i = 1; i<=len; i++)
		(*Sub)[i] = S[pos+i-1];
	(*Sub)[0] = len;
	return 1;
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

//�滻���е�һ����Ϊ����һ���� 
//�滻S�е�replacedTΪreplacementT 
//���������
//length��replacedT�� < length��replacementT�� 
//length��replacedT�� > length��replacementT��
//length��replacedT���� length��replacementT�����ʱ���㷨������������ͬ 
void replace(SString *S, SString replacedT, SString replacementT) {
	int len1 = replacedT[0];
	int len2 = replacementT[0]; 
	int index = index_KMP(*S, replacedT, 0);
	if(len1 <= len2) {
		(*S)[0] = (*S)[0] + len2 - len1;
		for(int i = (*S)[0]; i>= index + len1; i--)
			(*S)[i + len2 - len1] = (*S)[i]; 
		
		for(int i = index, j = 1; j <= len2; i++, j++)	
			(*S)[i] = replacementT[j];
	} else {
		(*S)[0] = (*S)[0] + len2 - len1;
		for(int i = index + len2; i <= (*S)[0]; i++)
			(*S)[i] = (*S)[i + len1 - len2];  
		for(int i = index, j = 1; j <= len2; i++, j++)	
			(*S)[i] = replacementT[j];
	}
	if(index_KMP(*S, replacedT, 0) != 0)
		replace(S, replacedT, replacementT);
}

	
//ɾ����
void deleteS(SString *S) {
	SString temp;
	temp[0] = 0;
	for(int i = 0; i < strlen(*S); i++) {
		(*S)[i] = temp[i];
	}
} 

int main() {
	printf("-----��ʼ��S1-----\n����S1��"); 
	SString S1;
	init(&S1);
	printf("S1: ");
	display(S1); 
	printf("-----��ʼ��S2-----\n����S2��"); 
	SString S2;
	init(&S2);
	printf("S2: ");
	display(S2);
	
	//�ж�S1��S2�Ƿ���� 
	if(equal(S1, S2) == 1) printf("\nS1��S2���\n\n\n");
	else printf("\nS1��S2�����\n\n\n"); 
	
	//�ϲ�S1��S2 
	SString concat_T;
	concat(&concat_T, S1, S2);
	printf("S1��S2�ϲ���"); 
	display(concat_T);
	
	//���Ӵ� 
	SString sub;
	int pos, sub_len; 
	printf("\n�Ӵ���ʼ��λ�� pos = ");
	scanf("%d", &pos);
	printf("�Ӵ��ĳ��� sub_len = "); 
	scanf("%d", &sub_len);
	if(subString(&sub, S1, pos, sub_len) == 1) {		//�Ӵ����ҳɹ� 
		printf("�Ӵ���"); 
		display(sub);
	}
 
	//�滻���е�һ����Ϊ����һ����
	printf("-----���滻�Ĵ�T1-----\n����T1��"); 
	SString T1;
	init(&T1);
	printf("T1: ");
	display(T1);
	printf("-----�滻�ߵĴ�T2-----\n����T2��"); 
	SString T2;
	init(&T2);
	printf("T2: ");
	display(T2);
	 
	printf("��S1�е�T1�滻ΪT2: ");
	replace(&S1, T1, T2);
	display(S1);
	
//	//ɾ����S1��S2 
//	printf("2���ɾ����S1��S2");
//	Sleep(2000);
//	deleteS(&S1);
//	display(S1);
//	deleteS(&S2);
//	display(S2); 
	
	return 0;
}
