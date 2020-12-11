#include <stdlib.h>  
#include <stdio.h>
#include <windows.h>
typedef int ElemType;
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

int createList(LinkList *L, int n){//创建一个带头结点的链表 
	LinkList newLNode, head, temp;
	int i;
	ElemType data;
	head = (LinkList) malloc (sizeof(LNode));
	temp = head;
	for(i=0; i<n; i++){
		newLNode = (LinkList) malloc (sizeof(LNode));//生成新节点
		printf("输入第%d个元素的值：",i+1);
		scanf("%d", &data);
		newLNode->data = data;
		temp->next = newLNode;
		temp = newLNode;
	}
	newLNode->next = NULL;
	*L = head;
	return 0;
}//createList
int print_List(LinkList head) {//打印 
	printf("当前链表：");
    LinkList temp;
    if(head == NULL || head->next == NULL) {
        printf("空表\n");
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
int getElem(LinkList L, int i){//按位获取，返回第i个元素的值 
	LinkList temp;
	temp = L;
	for(int j = 1; j<=i; j++){
		temp = temp->next;
	}
	return temp->data;
}
int listInsert(LinkList L, int i, ElemType e){//按位插入元素
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
int listDelete(LinkList L, int i){//按位删除,返回被删除的元素的值
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
LinkList mergeList(LinkList La, LinkList Lb) {//非递减表合并
	LinkList pa, pb, pc;
	pa = La->next;
	pb = Lb->next;
	LNode newNode;
	LinkList Lc;//新链表的头结点
	Lc = &newNode;
    pc = Lc;//新链表的当前结点
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
	printf("创建链表，请输入链表长度：");
	int length;
	scanf("%d", &length);
	LinkList L;
	createList(&L, length);
	print_List(L);
	
	printf("需要获取第几个元素？");
	int elemIndex;
	scanf("%d", &elemIndex);	 
	int get_e = getElem(L, elemIndex);
	printf("第%d个元素的值为 %d\n", elemIndex, get_e);
	print_List(L);
	
	printf("插入的位置：");
	int inserIndex;
	scanf("%d", &inserIndex);
	printf("插入的数据：");
	int inserData;
	scanf("%d", &inserData);
	listInsert(L, inserIndex, inserData);
	print_List(L); 
	
	printf("删除第几个元素？");
	int deleIndex;
	scanf("%d", &deleIndex); 
	ElemType dele_e = listDelete(L, deleIndex); 
	printf("已删除元素：%d\n", dele_e);
	print_List(L);
	printf("--------非递减链表的合并--------\n\n\n");  
	LinkList La, Lb;
	int len1=4,len2=3;
	printf("输入第一个非递减链表（长度为4）：\n");
	createList(&La, len1);
	print_List(La);
	printf("输入第二个非递减链表（长度为3）：\n");
	createList(&Lb, len2);
	print_List(Lb); 
	printf("合并后的链表：");
	mergeList(La, Lb);
	system("pause");
	return 0;
}







