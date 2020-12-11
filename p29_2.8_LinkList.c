#include <stdlib.h>  
#include <stdio.h>
#include <windows.h>
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

int createList(LinkList *L, int n){//����һ����ͷ�������� 
	LinkList newLNode, head, temp;
	int i;
	ElemType data;
	head = (LinkList) malloc (sizeof(LNode));
	temp = head;
	for(i=0; i<n; i++){
		newLNode = (LinkList) malloc (sizeof(LNode));//�����½ڵ�
		printf("�����%d��Ԫ�ص�ֵ��",i+1);
		scanf("%d", &data);
		newLNode->data = data;
		temp->next = newLNode;
		temp = newLNode;
	}
	newLNode->next = NULL;
	*L = head;
	return 0;
}//createList
int print_List(LinkList head) {//��ӡ 
	printf("��ǰ����");
    LinkList temp;
    if(head == NULL || head->next == NULL) {
        printf("�ձ�\n");
    }
    temp = head;
    while(temp->next) {
        printf("%d ", temp->next->data);
        temp = temp->next;
    }
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
int getElem(LinkList L, int i){//��λ��ȡ�����ص�i��Ԫ�ص�ֵ 
	LinkList temp;
	temp = L;
	for(int j = 1; j<=i; j++){
		temp = temp->next;
	}
	return temp->data;
}
int listInsert(LinkList L, int i, ElemType e){//��λ����Ԫ��
	LinkList p = L;
	int j = 0;
	while(p && j<i-1) {
		p = p->next;
		++j; 
	}
	if(!p || j>i-1) return -1;
	LinkList s = (LinkList) malloc (sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return 0;
} 
int listDelete(LinkList L, int i){//��λɾ��,���ر�ɾ����Ԫ�ص�ֵ
	LinkList p, q;
	p = L;
	int j = 0;
	while(p->next && j<i-1) {
		p = p->next;
		++j;
	}
	if(!(p->next) || j>i-1) return -1;
	q = p->next;
	p->next = q->next;
	ElemType e = q->data;
	free(q);
	return e;
}
LinkList mergeList(LinkList La, LinkList Lb) {//�ǵݼ���ϲ�
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	LNode newNode;
	LinkList Lc;//�������ͷ���
	Lc = &newNode;
    pc = Lc;//������ĵ�ǰ���
    pc->next = NULL;
	while(pa && pb) {
		if(pa->data <= pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		} else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb);
	print_List(Lc);
	return Lc;
}

int main(){
	printf("�������������������ȣ�");
	int length;
	scanf("%d", &length);
	LinkList L;
	createList(&L, length);
	print_List(L);
	
	printf("��Ҫ��ȡ�ڼ���Ԫ�أ�");
	int elemIndex;
	scanf("%d", &elemIndex);	 
	int get_e = getElem(L, elemIndex);
	printf("��%d��Ԫ�ص�ֵΪ %d\n", elemIndex, get_e);
	print_List(L);
	
	printf("�����λ�ã�");
	int inserIndex;
	scanf("%d", &inserIndex);
	printf("��������ݣ�");
	int inserData;
	scanf("%d", &inserData);
	listInsert(L, inserIndex, inserData);
	print_List(L); 
	
	printf("ɾ���ڼ���Ԫ�أ�");
	int deleIndex;
	scanf("%d", &deleIndex); 
	ElemType dele_e = listDelete(L, deleIndex); 
	printf("��ɾ��Ԫ�أ�%d\n", dele_e);
	print_List(L);
	printf("--------�ǵݼ�����ĺϲ�--------\n\n\n");  
	LinkList La, Lb;
	int len1=4,len2=3;
	printf("�����һ���ǵݼ���������Ϊ4����\n");
	createList(&La, len1);
	print_List(La);
	printf("����ڶ����ǵݼ���������Ϊ3����\n");
	createList(&Lb, len2);
	print_List(Lb); 
	printf("�ϲ��������");
	mergeList(La, Lb);
	system("pause");
	return 0;
}







