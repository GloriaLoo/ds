#include <stdio.h>
#include <stdlib.h>
// ������ĵ�����ʵ�� 
typedef struct Node{
	int data;
	struct Node *next;
}Node;

// ��ӡ���� 
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
 
// ��ʼ������
Node* initList() {
	Node* head;	
	head = (Node*) malloc (sizeof(Node));
	head->next = NULL;
	return head;
}

// ��ȡ����ĳ��� 
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

// �������pos��λ�ò���data��pos��1��ʼ 
void insertAtPos(Node* head, int pos, int data) {
	if(!head || pos < 1) return;
	Node* temp = head;
	int i = 0;
	// �ҵ�posǰһ��λ�� 
	while(temp->next && i < pos-1) {
		temp = temp->next;
		i++;
	}
	if(pos > i+1) return;
	// ��temp->nextΪnullʱ����tempָ���������һ���ڵ㣬����������ĩβ����ڵ�
	Node* newNode = initList();
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

// ɾ����pos���ڵ㣬pos��1��ʼ 
void deleteByPos(Node* head, int pos) {
	if(!head || pos < 1 || !head->next) return;
	Node* temp = head;
	int i = 0;
	// �ҵ�posǰһ��λ�� 
	while(temp->next && i < pos-1) {
		temp = temp->next;
		i++;
	}
	if(pos > i+1 || !temp->next) return;
	temp->next = temp->next->next;
} 

// ��ͷ��ɾ���ڵ�
void deleteTheHead(Node* head) {
	deleteByPos(head, 1); 
}

// ��β��ɾ���ڵ� 
void deleteTheEnd(Node* head) {
	deleteByPos(head, getLength(head));
}

// ��ת����
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

// �����ݲ�������������� 
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

// ���򣬽��Ϊ����ֱ�Ӳ������� 
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

// ��������������ϲ�������һ�������� 
Node* mergeList(Node* headA, Node* headB) {
	if(!headA || !headB) return NULL;
	Node* temp = headA;
	Node* temp2 = headB;
	Node* newHead = initList();
	while(temp->next) { // �Ƚ�����һ�������Ƶ��������� 
		insertAtEnd(newHead, temp->next->data);
		temp = temp->next;
	}
	while(temp2->next) {  // �ٽ�����һ������ڵ�������뵽������ĺ���λ�� 
		insertIntoSortedList(newHead, temp2->next->data);
		temp2 = temp2->next;
	}
	return newHead;
}

// �ж�data�Ƿ��������У����򷵻�1�����򷵻�0 
int isExist(Node* head, int data) {
	if(!head) return 0;
	Node* temp = head;
	while(temp->next) {
		if(temp->next->data == data) return 1;
		temp = temp->next;
	}
	return 0;
}

// ��������Ľ�����������洢������������ 
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

