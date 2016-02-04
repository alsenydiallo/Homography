
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "LUdecomp.h"

#define MAXN 50

double **buildMatrix(int N) {
	double **M = (double **) malloc(N*sizeof(double*));
	for (int i = 0; i < N; i++)
		M[i] = (double*) malloc(N*sizeof(double));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			M[i][j] = (i == j) ? 1.0 : 0.0;
	return M;
}



void homography(double x[], double y[], double dx[], double dy[], int N){
	double **A = buildMatrix(2*N);
	double b[2*N];
	double h[8];

	for(int i=0, j=0; i< 2*N && j<N; i+=2, j++){
		// even row index
		A[i][0] = x[j];
		A[i][1] = y[j];
		A[i][2] = 1;
		A[i][3] = 0;
		A[i][4] = 0;
		A[i][5] = 0;
		A[i][6] = -x[j]*dx[j];
		A[i][7] = -y[j]*dx[j];
		b[i] = dx[j];

		// odd row index
		A[i+1][0] = 0;
		A[i+1][1] = 0;
		A[i+1][2] = 0;
		A[i+1][3] = x[j];
		A[i+1][4] = y[j];
		A[i+1][5] = 1;
		A[i+1][6] = -x[j]*dy[j];
		A[i+1][7] = -y[j]*dy[j];
		b[i+1] = dy[j];

	}
	/*	// print A
for(int i = 0; i < 8; i++){
	for(int j = 0; j < 8; j++)
		printf("%0.1lf  ", A[i][j]);
	printf("\n");
}
// print B
for(int i=0; i < 8; i++)
	printf("%0.1lf\n", b[i]);
	 */

	LUdecomp *LU;

	// if matrix is a 4x4
	if(N == 4){
		//		printf("N == 4\n");
		LU = LUdecompose(8, A);
		LUsolve(LU, b, h);

	} else { // if matrix size is greater than 4
		double **ATA = buildMatrix(2*N);
		double ATb[2*N];

		// compute ATA
		for(int i=0; i<=7; i++){
			for(int j=i; j<=7; j++){
				double sum = 0.0;
				for(int k=0; k<2*N; k++)
					sum += A[k][i]*A[k][j];
				ATA[i][j] = sum;
			}
		}


		// copy the upper portion of the matrix into the corresponding 
		// value below the diagonal
		for( int i=0; i<=7; i++){
			for(int j=0; j<i; j++)
				ATA[i][j] = ATA[j][i];
		}

		// compute ATb
		for(int i=0; i<=7; i++){
			double sum=0.0;
			for(int j=0; j<2*N; j++)
				sum += A[j][i] * b[j];
			ATb[i] = sum;
		}
		// solve the system 
		LU = LUdecompose(8, ATA);
		LUsolve(LU, ATb, h);
	}

	for(int i = 1; i <= 8 ; i++){
		printf("%0.10lf  ", h[i-1]);
		if((i%3)==0) printf("\n");
	}
	printf("%0.10lf \n", 1.0);
}

int main(int argc, char* argv[]){

	int size = 0; // number of point 
	scanf("%d ", &size);
	//	printf("%d\n", size);

	double a=0.0, b=0.0;
	double x[size], y[size], dx[size], dy[size];

	for(int i=0; i < size; i++){
		scanf("%lf %lf",&a, &b);
		x[i] = a;
		y[i] = b;
		//printf("%lf %lf\n", x[i], y[i]);
	}

	for(int i=0; i < size; i++){
		scanf("%lf %lf",&a, &b);
		dx[i] = a;
		dy[i] = b;
		//printf("%lf %lf\n", dx[i], dy[i]);
	}

	homography(x, y, dx, dy, size);
	return 0;
}
