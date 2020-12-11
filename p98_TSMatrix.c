#include <stdio.h>
#include <stdlib.h>  
#define MAXSIZE 12500

typedef struct {
	int i, j;		//	����Ԫ���кţ��к� 
	int e; 
}Triple;

typedef struct {
	Triple data[MAXSIZE+1];
	int mu, nu, tu;		//���������������������Ԫ���� 
}TSMatrix;

//����ϡ����� 
void create(TSMatrix *M, int mu, int nu, int tu) {
	(*M).mu = mu;
	(*M).nu = nu;
	(*M).tu = tu;
	M = (TSMatrix *) malloc (tu * sizeof(Triple));
}

//ѹ���洢ϡ����� 
void init(TSMatrix *M) {
	printf("�������Ԫ����ʽΪ���к� �к� ֵ�����ո��������\n"); 
	for(int n = 1; n <= (*M).tu; n++) {
		int row, col, value;
		scanf("%d %d %d", &row, &col, &value);
		(*M).data[n].i = row;
		(*M).data[n].j = col;
		(*M).data[n].e = value;
	}
}

//��ӡϡ����� 
//����һ 
//�Ƚ�ѹ��ϡ�����ת��Ϊ��ͨϡ�����
//��������forѭ�����Ծ��󣨱����ʽ��� 
//��������ֱ�������û�и�ʽ 
void display_TSMatrix(TSMatrix M) {
//	for (int row = 1; row <= M.mu; row++) {
//		for (int col; col <= M.nu; col++) {
//			printf("%3d", M.data[mu*(row-1)+col].e);
//		}
//		printf("\n");
//	} 
	for (int n = 1; n <= M.tu; n++) {
		printf("��%d��%d��%d��\n", M.data[n].i, M.data[n].j, M.data[n].e);
	}
	printf("\n\n");
}

//��ѹ��ϡ�����Mת�ã�������ת�ú��ѹ��ϡ����� 
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

//��ѹ��ϡ�����M��ת�õڶ��ַ���
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
	printf("����ϡ�����������������ͷ���Ԫ��������Ӣ�Ķ��Ÿ�������");
	scanf("%d,%d,%d", &m_mu, &m_nu, &m_tu);
	create(&M, m_mu, m_nu, m_tu);
	init(&M);
	printf("����M: \n");
	display_TSMatrix(M);
	
	TSMatrix T = TransposeSMatrix(M);
	printf("Mת�ú�ľ���Ϊ��\n");
	display_TSMatrix(T);
	T = FastTransposeSMatrix(M);
	printf("Mת�ú�ľ���Ϊ������ת�ã���\n");
	display_TSMatrix(T);
	
	
	return 0;
}
