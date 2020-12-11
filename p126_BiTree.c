#include <stdio.h>
#include <stdlib.h>
 
typedef char TElemType;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//����������������Ķ������� 
void CreateBiTree(BiTree *T) {
	char c = 0;
	c = getchar();
	if(c == '*') {
		(*T) = NULL;
	} else {
		(*T) = (BiTNode *) malloc (sizeof(BiTNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->lchild); //ָ���ָ�� 
		CreateBiTree(&(*T)->rchild);
	}
}

//���������ӡ 
void PreOrderTraverse(BiTree T) {
	if(T == NULL) {
		return;
	} else {
		printf("%c", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	} 
}

//���������ӡ
void InOrderTraverse(BiTree T) {
	if(T == NULL) {
		return;
	} else {
		InOrderTraverse(T->lchild);
		printf("%c", T->data);
		InOrderTraverse(T->rchild);
	}
}

//���������ӡ
void LevelOrderTraverse(BiTree T) {
	if(T == NULL) {
		return;
	} else {
		LevelOrderTraverse(T->lchild);
		LevelOrderTraverse(T->rchild);
		printf("%c", T->data);
	}
}

//������T����� 
int BiTreeDepth(BiTree T) {
	int depth = 0;
    if (T == NULL)
        return 0;
    //������� = max(�������ĸ߶ȣ��������ĸ߶�) + 1
    else {
        int ldepth = BiTreeDepth(T->lchild);
        int rdepth = BiTreeDepth(T->rchild);
        depth = ldepth >= rdepth ? ldepth + 1 : rdepth + 1;
    }
    return depth;
}

//����������� 
void cengxu(BiTree T,int i) {
	if(T == NULL || i==0) 
		return;
	if(i == 1)
		printf("%c",T->data);
	cengxu(T->lchild, i-1);
	cengxu(T->rchild, i-1);
}
//���������ӡ 
void cengxuTraverse(BiTree T) {
	if(T == NULL)
		return;
	else {
		int depth = BiTreeDepth(T);
		for(int i = 1; i <= depth; i++) 
			cengxu(T,i);
	}
} 


int main() {
	BiTree T;
	printf("��������������Ľ��ֵ���ԡ�*������ս�㣩��");	
	CreateBiTree(&T);
	printf("\n����");
	PreOrderTraverse(T);
	printf("\n����");
	InOrderTraverse(T);
	printf("\n����");
	LevelOrderTraverse(T);
	printf("\n����");
	cengxuTraverse(T);
	printf("\n��ȣ�%d", BiTreeDepth(T));
	return 0;
}
