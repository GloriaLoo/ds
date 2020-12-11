#include <stdio.h>
#include <stdlib.h>  
#define MAXSIZE 12500

typedef struct {
	int i, j;		//	非零元的行号，列号 
	int e; 
}Triple;

typedef struct {
	Triple data[MAXSIZE+1];
	int mu, nu, tu;		//矩阵的行数，列数，非零元个数 
}TSMatrix;

//创建稀疏矩阵 
void create(TSMatrix *M, int mu, int nu, int tu) {
	(*M).mu = mu;
	(*M).nu = nu;
	(*M).tu = tu;
	M = (TSMatrix *) malloc (tu * sizeof(Triple));
}

//压缩存储稀疏矩阵 
void init(TSMatrix *M) {
	printf("输入非零元，格式为“行号 列号 值”（空格隔开）：\n"); 
	for(int n = 1; n <= (*M).tu; n++) {
		int row, col, value;
		scanf("%d %d %d", &row, &col, &value);
		(*M).data[n].i = row;
		(*M).data[n].j = col;
		(*M).data[n].e = value;
	}
}

//打印稀疏矩阵 
//方法一 
//先将压缩稀疏矩阵转化为普通稀疏矩阵
//再用两层for循环，以矩阵（表格）形式输出 
//方法二，直接输出，没有格式 
void display_TSMatrix(TSMatrix M) {
//	for (int row = 1; row <= M.mu; row++) {
//		for (int col; col <= M.nu; col++) {
//			printf("%3d", M.data[mu*(row-1)+col].e);
//		}
//		printf("\n");
//	} 
	for (int n = 1; n <= M.tu; n++) {
		printf("（%d，%d，%d）\n", M.data[n].i, M.data[n].j, M.data[n].e);
	}
	printf("\n\n");
}

//对压缩稀疏矩阵M转置，并返回转置后的压缩稀疏矩阵 
TSMatrix TransposeSMatrix(TSMatrix M) {
	TSMatrix T;
	create(&T, M.nu, M.mu, M.tu);
	if(T.tu) {
		int q = 1;
		for (int col = 1; col <= M.mu; ++col)
			for (int p = 1; p <= M.tu; ++p)
				if(M.data[p].j == col) {
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					++q;
				}
	}
	return T;
}

//对压缩稀疏矩阵M的转置第二种方法
TSMatrix FastTransposeSMatrix(TSMatrix M) {
	TSMatrix T;
	create(&T, M.nu, M.mu, M.tu);
	int num[M.tu], cpot[M.tu];
	if (T.tu != 0){
		for(int col=1; col <= M.nu; ++col) 
			num[col] = 0;
		for(int t = 1; t<=M.tu; ++t) 
			++num[M.data[t].j];
		cpot[1]= 1;
		for(int col = 2; col <= M.nu; ++col) 
			cpot[col] = cpot[col-1] + num[col-1];
		
		for(int p=1; p<= M.tu; ++p){
			int col = M.data[p].j;
			int q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++ cpot[col];
		}
	}
	return T;
} 

int main() {
	
	TSMatrix M;
	int m_mu, m_nu, m_tu; 
	printf("输入稀疏矩阵的行数、列数和非零元个数（以英文逗号隔开）：");
	scanf("%d,%d,%d", &m_mu, &m_nu, &m_tu);
	create(&M, m_mu, m_nu, m_tu);
	init(&M);
	printf("矩阵M: \n");
	display_TSMatrix(M);
	
	TSMatrix T = TransposeSMatrix(M);
	printf("M转置后的矩阵为：\n");
	display_TSMatrix(T);
	T = FastTransposeSMatrix(M);
	printf("M转置后的矩阵为（快速转置）：\n");
	display_TSMatrix(T);
	
	
	return 0;
}
