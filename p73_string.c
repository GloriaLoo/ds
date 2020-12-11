#include <stdio.h>
#include <string.h>
#include <windows.h> 
#define MAX 255
typedef unsigned char SString[MAX+1];

//初始化S 
void init(SString *S) {
	char temp[MAX];
	scanf("%s", temp);
	for(int i = 0; i < strlen(temp); i++) {
		(*S)[i+1] = temp[i];
	}
	(*S)[0] = strlen(temp);	
}

//打印S 
int display(SString S) {
	if(strlen(S) == 0) {
		printf("\n\n当前串为空串\n");
		return -1;
	}
	
	for(int i = 1; i <= S[0]; i++) 
		printf("%c", S[i]);
	printf("(length = %d)\n\n", S[0]);
	return 0;
}

//判断是否相等，返回1表示相等，0表示不等 
int equal(SString S1, SString S2) {
	if(S1[0] != S2[0]) return 0;
	
	int i = 1;
	for(i = 1; i<S1[0]; i++) {
		if(S1[i] != S2[i]) break;
	}
	if(i == S1[0]) return 1;
	else return 0;
}

//合并串，返回1表示截断，0表示未截断
//将S1、S2合并为T 
void concat(SString *T, SString S1, SString S2) {
	if (S1[0] + S2[0] <= MAX) {			//未截断 
		for(int i = 1; i<=S1[0]; i++)
			(*T)[i] = S1[i];
			
		int j = 1;
		for(int i = S1[0] + 1; i<=S1[0] + S2[0], j<=S2[0] ; i++, j++)
			(*T)[i] = S2[j];
		(*T)[0] = S1[0] + S2[0];
	} else if(S1[0] < MAX) {			//截断 
		for (int i = 1; i<=S1[0]; i++)
			(*T)[i] = S1[i];
			
		int j = 1;
		for(int i = 1; i<MAX - S1[0]; i++, j++)
			(*T)[S1[0]+i] = S2[j];
		(*T)[0] = MAX;
	} else {			//截取S1 即S[0] = MAX 
		for (int i = 0; i<=MAX; i++)
			(*T)[i] = S1[i];
	}
}

//求子串，用Sub返回S中第pos个字符起长度为len的字串 
//返回1表示查找成功，返回-1表示失败 
int subString(SString *Sub, SString S, int pos, int len) {
	if(pos + len - 1 > S[0]) {
		printf("-----越界，得不到子串-----");
		return -1;
	}
	if(pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos +1) return -1;
	for (int i = 1; i<=len; i++)
		(*Sub)[i] = S[pos+i-1];
	(*Sub)[0] = len;
	return 1;
} 

//获得KMP算法的next算法 
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

//KMP算法，返回pos后的起始位 
int index_KMP(SString S, SString T, int pos) {
	int next[T[0]+1];
	get_next(T, next);		//获得T的next数组 
	
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

//替换串中的一部分为另外一个串 
//替换S中的replacedT为replacementT 
//两种情况，
//length（replacedT） < length（replacementT） 
//length（replacedT） > length（replacementT）
//length（replacedT）和 length（replacementT）相等时，算法和以上两种相同 
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

	
//删除串
void deleteS(SString *S) {
	SString temp;
	temp[0] = 0;
	for(int i = 0; i < strlen(*S); i++) {
		(*S)[i] = temp[i];
	}
} 

int main() {
	printf("-----初始化S1-----\n输入S1："); 
	SString S1;
	init(&S1);
	printf("S1: ");
	display(S1); 
	printf("-----初始化S2-----\n输入S2："); 
	SString S2;
	init(&S2);
	printf("S2: ");
	display(S2);
	
	//判断S1、S2是否相等 
	if(equal(S1, S2) == 1) printf("\nS1和S2相等\n\n\n");
	else printf("\nS1和S2不相等\n\n\n"); 
	
	//合并S1、S2 
	SString concat_T;
	concat(&concat_T, S1, S2);
	printf("S1与S2合并后："); 
	display(concat_T);
	
	//求子串 
	SString sub;
	int pos, sub_len; 
	printf("\n子串开始的位置 pos = ");
	scanf("%d", &pos);
	printf("子串的长度 sub_len = "); 
	scanf("%d", &sub_len);
	if(subString(&sub, S1, pos, sub_len) == 1) {		//子串查找成功 
		printf("子串："); 
		display(sub);
	}
 
	//替换串中的一部分为另外一个串
	printf("-----被替换的串T1-----\n输入T1："); 
	SString T1;
	init(&T1);
	printf("T1: ");
	display(T1);
	printf("-----替换者的串T2-----\n输入T2："); 
	SString T2;
	init(&T2);
	printf("T2: ");
	display(T2);
	 
	printf("将S1中的T1替换为T2: ");
	replace(&S1, T1, T2);
	display(S1);
	
//	//删除串S1、S2 
//	printf("2秒后删除串S1、S2");
//	Sleep(2000);
//	deleteS(&S1);
//	display(S1);
//	deleteS(&S2);
//	display(S2); 
	
	return 0;
}
