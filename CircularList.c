#include <stdio.h>
#include <stdlib.h>
// 单向循环链表的实现 
// 总体思想和单链表相同，只是在遍历时条件不是temp->next，而是temp->next != head 
typedef struct Node{
	int data;
	struct Node *next;
}Node;

// 打印链表 
void printList(Node *head) {
	if(!head) return;
	Node* temp = head; 
	printf("LinkList: \t");
	while(temp->next != head) {  // 这里与单链表不同，单链表仅有 temp->next
		printf("%d \t", temp->next->data);
		temp = temp->next;
	}
	printf("\n");
}

// 初始化链表
Node* initList() {
	Node* head;	
	head = (Node*) malloc (sizeof(Node));
	head->next = head;
	return head;
}

// 创建一个新节点，单链表没有此方法 
Node* getNewNode() {
	Node* node;	
	node = (Node*) malloc (sizeof(Node));
	node->next = NULL;
	return node;
}

// 获取链表的长度 
int getLength(Node* head) {
	if(!head) return 0;
	Node* temp = head; 
	int len = 0; 
	while(temp->next != head) {  // 这里与单链表不同，单链表仅有 temp->next
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
	while((temp->next != head) && i < pos-1) {  // 这里与单链表不同，单链表仅有 temp->next
		temp = temp->next;
		i++;
	}
	if(pos > i+1) return;
	// 当temp->next为null时，即temp指向链表最后一个节点，允许在链表末尾插入节点
	Node* newNode = getNewNode();
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

// 逆转链表
void changeoverList(Node* head) {
	if(!head || !head->next->next) return;
	Node* newHead = initList();
	Node* temp = head;
	while(temp->next != head) {
		insertAtHead(newHead, temp->next->data);
		temp = temp->next;
	}
	Node* temp2 = newHead;
	// 将temp2指针指向newHead最后一个节点 
	while(temp2->next != newHead)
		temp2 = temp2->next;
	// head指向新链表，新链表尾指针指向head 
	head->next = newHead->next;
	temp2->next = head;
}

void main() {
	printf("\n init list A, ");
	Node* list = initList();
	for(int i = 1; i <= 6; i++) 
		insertAtPos(list, i, i);
	printList(list);
	printf("\n insert A at end, ");
	insertAtEnd(list, 2);
	printList(list);
	
	printf("\n insert A at head, ");
	insertAtHead(list, 5);
	printList(list);
	
	printf("\n changeover list A, ");
	changeoverList(list);
	printList(list);
}
