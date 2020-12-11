#include <stdio.h>
#include <stdlib.h>  
#define MAXSIZE 12500
#define MAXRC 100 
typedef struct {
	int i, j;		//	非零元的行号，列号 
	int e; 
}Triple;

typedef struct {
	Triple data[MAXSIZE+1];
	int rpos[MAXRC+1];
	int mu, nu, tu;		//矩阵的行数，列数，非零元个数 
}RLSMatrix;

void init(RLSMatrix *M, int mu, int nu, int tu) {
	(*M).mu = mu;
	(*M).nu = nu;
	(*M).tu = tu;
	for(int i = 1; i <= (*M).mu; i++) {
		printf("输入第%d行第一个非零元的位置（英文逗号隔开），若没有则输入 “0”：", i);
		int loc;
		scanf("%d", &loc);
		if (loc == 0) continue;
		(*M).rpos[i] = loc;
	}
	printf("\n");
	
	for(int n = 1; n <= (*M).tu; n++) {
		printf("输入第%d个非零元，格式为“行号 列号 值”（空格隔开）：", n); 
		int row, col, value;
		scanf("%d %d %d", &row, &col, &value);
		(*M).data[n].i = row;
		(*M).data[n].j = col;
		(*M).data[n].e = value;
	}
	printf("\n\n");
}

void display_RLSMatrix(RLSMatrix M) {
	for (int n = 1; n <= M.tu; n++) {
		printf("第%d行%d列为%d\n", M.data[n].i, M.data[n].j, M.data[n].e);
	}
	printf("\n\n");
}

int MultSMatrix(RLSMatrix M, RLSMatrix N, RLSMatrix *Q) {
	if (M.mu != N.mu)	return -1;
	(*Q).mu = M.mu;
	(*Q).nu = N.nu;
	(*Q).tu = 0;
	if (M.tu * N.tu != 0)	{
		for (int arow = 1; arow <= M.tu; ++arow) {
			int ctemp[MAXRC];
			(*Q).rpos[arow] = (*Q).tu + 1;
			int tp;
			if(arow < M.tu) tp = M.rpos[arow+1];
			else tp = M.tu + 1;
			for (int p = M.rpos[arow]; p < tp; ++p) {
				int brow = M.data[p].j;
				int t;
				if (brow < N.mu)	t = N.rpos[brow+1];
				else t = N.tu + 1;
				for (int q = N.rpos[brow]; q < t; ++q) {
					int ccol = N.data[q].j;
					ctemp[ccol] += M.data[p].e * N.data[q].e;
				}
			}
			for (int ccol = 1; ccol <= (*Q).nu; ++ccol)
				if (ctemp[ccol]) {
					if (++(*Q).tu > MAXSIZE) return -1;
					(*Q).data[(*Q).tu].i = arow;
					(*Q).data[(*Q).tu].j = ccol;
					(*Q).data[(*Q).tu].e = ctemp[ccol];
				}
		}
	}
	return 1;
} 

int main() {
	RLSMatrix M, N, Q;
	
	printf("输入矩阵M的行数、列数和非零元个数（用英文逗号隔开）：");
	int m_mu, m_nu, m_tu;
	scanf("%d,%d,%d", &m_mu, &m_nu, &m_tu);
	init(&M, m_mu, m_nu, m_tu);
	display_RLSMatrix(M);
	
	printf("输入矩阵N的行数、列数和非零元个数（用英文逗号隔开）：");
	int n_mu, n_nu, n_tu;
	scanf("%d,%d,%d", &n_mu, &n_nu, &n_tu);
	init(&N, n_mu, n_nu, n_tu);
	display_RLSMatrix(N);
	
	MultSMatrix(M, N, &Q);
	display_RLSMatrix(Q);
	printf("Q.mu = %d\n", Q.mu); 
	printf("Q.nu = %d\n", Q.nu);
	printf("Q.tu = %d\n", Q.tu);
	
	
	
	return 0;
}
