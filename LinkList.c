#include <stdio.h>
#include <stdlib.h>
// 最基础的单链表的实现 
typedef struct Node{
	int data;
	struct Node *next;
}Node;

// 打印链表 
void printList(Node *head) {
	if(!head) return;
	Node* temp = head; 
	printf("LinkList: \t");
	while(temp->next) {
		printf("%d \t", temp->next->data);
		temp = temp->next;
	}
	printf("\n");
}
 
// 初始化链表
Node* initList() {
	Node* head;	
	head = (Node*) malloc (sizeof(Node));
	head->next = NULL;
	return head;
}

// 获取链表的长度 
int getLength(Node* head) {
	if(!head) return 0;
	Node* temp = head; 
	int len = 0; 
	while(temp->next) {
		len++;
		temp = temp->next;
	}
	return len;
}

// 在链表第pos个位置插入data，pos从1开始 
void insertAtPos(Node* head, int pos, int data) {
	if(!head || pos < 1) return;
	Node* temp = head;
	int i = 0;
	// 找到pos前一个位置 
	while(temp->next && i < pos-1) {
		temp = temp->next;
		i++;
	}
	if(pos > i+1) return;
	// 当temp->next为null时，即temp指向链表最后一个节点，允许在链表末尾插入节点
	Node* newNode = initList();
	newNode->data = data;
	newNode->next = temp->next;
	temp->next = newNode;
}

// 在链表尾部插入节点 
void insertAtEnd(Node* head, int data) {
	insertAtPos(head, getLength(head)+1, data);
}

// 在链表头部插入节点 
void insertAtHead(Node* head, int data) {
	insertAtPos(head, 1, data);
}

// 删除第pos个节点，pos从1开始 
void deleteByPos(Node* head, int pos) {
	if(!head || pos < 1 || !head->next) return;
	Node* temp = head;
	int i = 0;
	// 找到pos前一个位置 
	while(temp->next && i < pos-1) {
		temp = temp->next;
		i++;
	}
	if(pos > i+1 || !temp->next) return;
	temp->next = temp->next->next;
} 

// 在头部删除节点
void deleteTheHead(Node* head) {
	deleteByPos(head, 1); 
}

// 在尾部删除节点 
void deleteTheEnd(Node* head) {
	deleteByPos(head, getLength(head));
}

// 逆转链表
void changeoverList(Node* head) {
	if(!head || !head->next->next) return;
	Node* newHead = initList();
	Node* temp = head;
	while(temp->next) {
		insertAtHead(newHead, temp->next->data);
		temp = temp->next;
	}
	head->next = newHead->next;
}

// 将数据插入有序的链表中 
void insertIntoSortedList(Node* head, int data) {
	if(!head) return;
	Node* temp = head;
	int pos = 1;
	while(temp->next && temp->next->data < data) {
		temp = temp->next;
		pos++;
	}
	insertAtPos(head, pos, data);
}

// 排序，结果为升序，直接插入排序 
void sortList(Node* head) {
	if(!head || !head->next) return;
	Node* temp = head;
	Node* newHead = initList();
	while(temp->next) {
		insertIntoSortedList(newHead, temp->next->data);
		temp = temp->next;
	}
	head->next = newHead->next;
}

// 将两条不减链表合并，返回一条新链表 
Node* mergeList(Node* headA, Node* headB) {
	if(!headA || !headB) return NULL;
	Node* temp = headA;
	Node* temp2 = headB;
	Node* newHead = initList();
	while(temp->next) { // 先将其中一条链表复制到新链表中 
		insertAtEnd(newHead, temp->next->data);
		temp = temp->next;
	}
	while(temp2->next) {  // 再将另外一条链表节点逐个插入到新链表的合适位置 
		insertIntoSortedList(newHead, temp2->next->data);
		temp2 = temp2->next;
	}
	return newHead;
}

// 判断data是否在链表中，是则返回1，否则返回0 
int isExist(Node* head, int data) {
	if(!head) return 0;
	Node* temp = head;
	while(temp->next) {
		if(temp->next->data == data) return 1;
		temp = temp->next;
	}
	return 0;
}

// 求两链表的交集，将结果存储在新链表并返回 
Node* getOverlapList(Node* headA, Node* headB) {
	if(!headA || !headB) return NULL;
	Node* temp1 = headA;
	Node* temp2 = headB;
	Node* newHead = initList();
	while(temp1->next) {
		if(isExist(temp2, temp1->next->data)) 
			insertAtHead(newHead, temp1->next->data);
		temp1 = temp1->next;
	}
	return newHead;
} 

void main() {
	printf("\n init list A, ");
	Node* list = initList();
	for(int i = 1; i <= 6; i++) 
		insertAtPos(list, i, (i-4)*(i-4)*(i-4)*(i-4));
	printList(list);
	printf("\n insert A at head, ");
	insertAtHead(list, 7);
	printList(list);
	printf("\n insert A at end, ");
	insertAtEnd(list, 25);
	printList(list);
	printf("\n delete the A head, ");
	deleteTheHead(list);
	printList(list);
	printf("\n delete the A end, ");
	deleteTheEnd(list);
	printList(list);
	printf("\n changeover list A, ");
	changeoverList(list);
	printList(list);
	printf("\n sort list A, ");
	sortList(list);
	printList(list);
	
	printf("\n init list B, ");
	Node* list2 = initList();
	for(int i = 1; i <= 5; i++) 
		insertAtPos(list2, i, (i-3)*(i-3));
	printList(list2);
	printf("\n sort list B, ");
	sortList(list2);
	printList(list2);
	printf("\n merge list A B, ");
	printList(mergeList(list, list2));
	
	printf("\n list A B overlap, ");
	printList(getOverlapList(list, list2)); 
}

