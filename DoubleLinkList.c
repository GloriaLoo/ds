#include <stdio.h>
#include <stdlib.h>
// ˫�������ʵ��
// �͵�����ͬ�ľ�����β�����롢ɾ��ʱҪ�����Ĵ��� 
typedef struct Node{
	struct Node *prior;
	int data;
	struct Node *next;
}Node;

// ��ʼ�� 
Node* initList() {
	Node* head = (Node*) malloc (sizeof(Node));
	head->prior = NULL;
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

// ��ӡ���� 
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

// �������pos��λ�ò���data��pos��1��ʼ 
void insertAtPos(Node* head, int pos, int data) {
	if(!head || pos < 1) return;
	Node* temp = head;
	int i = 0;
	// �ҵ�posλ�� 
	while(temp->next && i < pos) {
		temp = temp->next;
		i++;
	}
	Node* newNode = initList();
	newNode->data = data;
	if(pos > i+1) return;
	// ��pos=i+1ʱ����Ҫ������ĩβ����ڵ�
	if(pos == i+1) {
		temp->next = newNode;
		newNode->prior = temp;
		return;
	}
	// �������м����ڵ� 
	newNode->prior = temp->prior;
	temp->prior->next = newNode;
	newNode->next = temp;
	temp->prior = newNode;
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
	// �ҵ�posλ�� 
	while(temp->next && i < pos) {
		temp = temp->next;
		i++;
	}
	if(pos > i) return;
	// ɾ���������һ���ڵ�
	if(!temp->next) {
		temp->prior->next = NULL;
		temp->prior = NULL;
		return;
	}
	// ɾ�������м�Ľڵ� 
	temp->prior->next = temp->next;
	temp->next->prior = temp->prior;
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
