#include <stdio.h>
#include <stdlib.h>
// ����ѭ�������ʵ�� 
// ����˼��͵�������ͬ��ֻ���ڱ���ʱ��������temp->next������temp->next != head 
typedef struct Node{
	int data;
	struct Node *next;
}Node;

// ��ӡ���� 
void printList(Node *head) {
	if(!head) return;
	Node* temp = head; 
	printf("LinkList: \t");
	while(temp->next != head) {  // �����뵥����ͬ����������� temp->next
		printf("%d \t", temp->next->data);
		temp = temp->next;
	}
	printf("\n");
}

// ��ʼ������
Node* initList() {
	Node* head;	
	head = (Node*) malloc (sizeof(Node));
	head->next = head;
	return head;
}

// ����һ���½ڵ㣬������û�д˷��� 
Node* getNewNode() {
	Node* node;	
	node = (Node*) malloc (sizeof(Node));
	node->next = NULL;
	return node;
}

// ��ȡ����ĳ��� 
int getLength(Node* head) {
	if(!head) return 0;
	Node* temp = head; 
	int len = 0; 
	while(temp->next != head) {  // �����뵥����ͬ����������� temp->next
		len++;
		temp = temp->next;
	}
	return len;
}

// �������pos��λ�ò���data��pos��1��ʼ 
void insertAtPos(Node* head, int pos, int data) {
	if(!head || pos < 1) return;
	Node* temp = head;
	int i = 0;
	// �ҵ�posǰһ��λ�� 
	while((temp->next != head) && i < pos-1) {  // �����뵥����ͬ����������� temp->next
		temp = temp->next;
		i++;
	}
	if(pos > i+1) return;
	// ��temp->nextΪnullʱ����tempָ���������һ���ڵ㣬����������ĩβ����ڵ�
	Node* newNode = getNewNode();
	newNode->data = data;
	newNode->next = temp->next;
	temp->next = newNode;
}

// ������β������ڵ� 
void insertAtEnd(Node* head, int data) {
	insertAtPos(head, getLength(head)+1, data);
}

// ������ͷ������ڵ� 
void insertAtHead(Node* head, int data) {
	insertAtPos(head, 1, data);
}

// ��ת����
void changeoverList(Node* head) {
	if(!head || !head->next->next) return;
	Node* newHead = initList();
	Node* temp = head;
	while(temp->next != head) {
		insertAtHead(newHead, temp->next->data);
		temp = temp->next;
	}
	Node* temp2 = newHead;
	// ��temp2ָ��ָ��newHead���һ���ڵ� 
	while(temp2->next != newHead)
		temp2 = temp2->next;
	// headָ��������������βָ��ָ��head 
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
