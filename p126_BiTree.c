#include <stdio.h>
#include <stdlib.h>
 
typedef char TElemType;
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//按照先序构造二叉树的二叉链表 
void CreateBiTree(BiTree *T) {
	char c = 0;
	c = getchar();
	if(c == '*') {
		(*T) = NULL;
	} else {
		(*T) = (BiTNode *) malloc (sizeof(BiTNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->lchild); //指针的指针 
		CreateBiTree(&(*T)->rchild);
	}
}

//先序遍历打印 
void PreOrderTraverse(BiTree T) {
	if(T == NULL) {
		return;
	} else {
		printf("%c", T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	} 
}

//中序遍历打印
void InOrderTraverse(BiTree T) {
	if(T == NULL) {
		return;
	} else {
		InOrderTraverse(T->lchild);
		printf("%c", T->data);
		InOrderTraverse(T->rchild);
	}
}

//后序遍历打印
void LevelOrderTraverse(BiTree T) {
	if(T == NULL) {
		return;
	} else {
		LevelOrderTraverse(T->lchild);
		LevelOrderTraverse(T->rchild);
		printf("%c", T->data);
	}
}

//返回树T的深度 
int BiTreeDepth(BiTree T) {
	int depth = 0;
    if (T == NULL)
        return 0;
    //树的深度 = max(左子树的高度，右子树的高度) + 1
    else {
        int ldepth = BiTreeDepth(T->lchild);
        int rdepth = BiTreeDepth(T->rchild);
        depth = ldepth >= rdepth ? ldepth + 1 : rdepth + 1;
    }
    return depth;
}

//层序输出函数 
void cengxu(BiTree T,int i) {
	if(T == NULL || i==0) 
		return;
	if(i == 1)
		printf("%c",T->data);
	cengxu(T->lchild, i-1);
	cengxu(T->rchild, i-1);
}
//层序遍历打印 
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
	printf("先序输入二叉树的结点值（以“*”代替空结点）：");	
	CreateBiTree(&T);
	printf("\n先序：");
	PreOrderTraverse(T);
	printf("\n中序：");
	InOrderTraverse(T);
	printf("\n后序：");
	LevelOrderTraverse(T);
	printf("\n层序：");
	cengxuTraverse(T);
	printf("\n深度：%d", BiTreeDepth(T));
	return 0;
}
