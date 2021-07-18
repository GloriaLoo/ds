#include <stdio.h>
#include <stdlib.h>
// 双向链表的实现
// 和单链表不同的就是在尾部插入、删除时要独立的代码 
typedef struct Node{
	struct Node *prior;
	int data;
	struct Node *next;
}Node;

// 初始化 
Node* initList() {
	Node* head = (Node*) malloc (sizeof(Node));
	head->prior = NULL;
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

// 打印链表 
void printList(Node *head) {
	if(!head) return;
	Node* temp = head; 
	printf("\nDoubleLinkList: \t");
	while(temp->next) {
		printf("%d \t", temp->next->data);
		temp = temp->next;
	}
	printf("\n");
}

// 在链表第pos个位置插入data，pos从1开始 
void insertAtPos(Node* head, int pos, int data) {
	if(!head || pos < 1) return;
	Node* temp = head;
	int i = 0;
	// 找到pos位置 
	while(temp->next && i < pos) {
		temp = temp->next;
		i++;
	}
	Node* newNode = initList();
	newNode->data = data;
	if(pos > i+1) return;
	// 当pos=i+1时，即要在链表末尾插入节点
	if(pos == i+1) {
		temp->next = newNode;
		newNode->prior = temp;
		return;
	}
	// 在链表中间插入节点 
	newNode->prior = temp->prior;
	temp->prior->next = newNode;
	newNode->next = temp;
	temp->prior = newNode;
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
	// 找到pos位置 
	while(temp->next && i < pos) {
		temp = temp->next;
		i++;
	}
	if(pos > i) return;
	// 删除链表最后一个节点
	if(!temp->next) {
		temp->prior->next = NULL;
		temp->prior = NULL;
		return;
	}
	// 删除链表中间的节点 
	temp->prior->next = temp->next;
	temp->next->prior = temp->prior;
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

void main() {
	Node* list = initList();
	for(int i = 1; i <= 5; i++)
		insertAtPos(list, i, 2*i);
	insertAtPos(list, 3, 22);
	insertAtHead(list, 7);
	insertAtEnd(list, 2);
	printList(list);
	deleteTheHead(list);
	printList(list);
	deleteTheEnd(list);
	printList(list);
	changeoverList(list);
	printList(list);
	sortList(list); 
	printList(list);
	Node* list2 = initList();
	for(int i = 1; i <= 5; i++)
		insertAtPos(list2, i, 2*i-1);
	printList(list2);
	sortList(list2);
	printList(list2);
	printList(mergeList(list, list2));

}
