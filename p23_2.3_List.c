#include <stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct SqList{
	int *elem;
	int length;
	int listsize;
}SqList; 

//���� 
int InitList_Sq(SqList L){
	L.elem = (int *)malloc(100*sizeof(int));
	L.length = 0;
	L.listsize = 100;
	printf("�����ɹ���\n");
	return 0;
}

//����
int ListInsert_Sq(SqList *L,int i, int e){
	SqList *p;
	int *q, *newbase;
	if((*L).length>=(*L).listsize){
		newbase = (int *)realloc((*L).elem,((*L).listsize + 100)*sizeof(int));
		(*L).elem = newbase;
		(*L).listsize += 100;
	}
	q = &((*L).elem[i-1]);
	for(p = &((*L).elem[(*L).length-1]); p>=q; --p)
		*(p+1) = *p;
	*q = e;
	++(*L).length;
	printf("����ɹ���\n");
	return 0;
} 

//ɾ��
int ListDelete_Sq(SqList *L, int i, int *e){
	int *p,*q;
	p = &((*L).elem[i-1]);
	e = *p;
	q = (*L).elem + (*L).length - 1;
	for(++p; p<=q; ++p)
		*(p-1) = *p;
	--(*L).length;
	printf("ɾ���ɹ���\n");
	return 0;
} 


int main(){
	SqList L;
	InitList_Sq(L);
	ListInsert_Sq(&L,3,3);
	//int e;
	//ListDelete_Sq(&L, 3, e);
	//printf("%d",e);
	return 0;
} 
