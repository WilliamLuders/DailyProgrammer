/*
 ============================================================================
 Name        : Challenge341.c
 Author      : William Luders
 Description : Solve a system of two linear equations parametrically
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
	float x_1, y_1, a_1;
	float x_2, y_2, a_2;
	float x, y; // final answer
	float cosa1,cosa2,sina1,sina2; // avoid recalculating
	float detA;
	static float A[2][2]; // static for passing as arguments??
	static float B[2][1];
	static float C[2][1];
	int i,j,k; // iterators for matMul/whatever
	float tempTotal; // for use during dot product calc
int main(void) {

	acceptInput();

	cosa1=cos(a_1);	cosa2=cos(a_2);	sina1=sin(a_1);	sina2=sin(a_2); // avoid recalculating

	//A is inverted transform matrix
	detA = sin(a_1-a_2); // used trig identity. I hope a trig function is cheaper than two multiplications
	if (detA==0){
		printf("Rays do not intersect!\n");
		scanf("%d", &i);
		return EXIT_SUCCESS;
	}
	A[0][0] = -sina2/detA;
	A[0][1] = cosa2/detA;
	A[1][0] = -sina1/detA;
	A[1][1] = cosa1/detA;

	//B is vector of deltax, deltay
	B[0][0] = x_2-x_1;
	B[1][0] = y_2-y_1;

	//solving C=A^(-1)*B, C is vector of parameters
	for (i=0; i<2; i++){ // i is current row in A
		for (j=0; j<1; j++){ // j is current column in B
			for (k=0; k<2; k++){ // k is current index during dot product calculation
				tempTotal+=A[i][k]*B[k][j];
			}
			C[i][j]= tempTotal;
			tempTotal=0;
		}
	}

	//matMult(A,B,C);
	if(C[0][0]<0||C[1][0]<0){
		printf("Rays do not intersect!\n");
	} else{
		x=x_1+C[0][0]*cosa1;
		y=y_1+C[0][0]*sina1;
		printf("Aircraft located at %f, %f", x, y);
	}

//	printf	("%f %f\n", C[0][0], C[1][0]);
	scanf("%d", &i);

	return EXIT_SUCCESS;
}

void matMult(float** a, float** b, float** c){ // A*B=C
	int i,j,k;
	float tempTotal;
	int m1 = sizeof(a[0])/sizeof(a[0][0]);
	int n1 = sizeof(a)/sizeof(a[0]);
	int m2 = sizeof(b[0])/sizeof(b[0][0]);
	int n2 = sizeof(b)/sizeof(b[0]);

//	c = calloc(m1,sizeof(float*)); // A*B=C
//	for (i=0; i<m1; i++){
//		C[i] = calloc(n2,sizeof(float));
//	}


	//assert(n1==m2);

	for (i=0; i<m1; i++){ // i is current row in A
		for (j=0; j<n2; j++){ // j is current column in B
			for (k=0; k<n1; k++){ // k is current index during dot product calculation
				tempTotal+=A[i][k]*B[k][j];
			}
			//c[i][j]= tempTotal;
			tempTotal=0;
		}
	}


	return;
}
void acceptInput(){
	puts("Enter coordinates of 1st radar tower:");
	fflush(stdout);
	scanf("%f  %f",&x_1,&y_1);
	puts("Enter bearing detected by 1st tower in degrees (0 deg = North):");
	fflush(stdout);
	scanf("%f", &a_1);
	a_1=(90-a_1)*M_PI/180; // convert to standard angle measure
	puts("Enter coordinates of 2nd radar tower:");
	fflush(stdout);
	scanf("%f  %f",&x_2,&y_2);
	puts("Enter bearing detected by 2nd tower in degrees (0 deg = North):");
	fflush(stdout);
	scanf("%f", &a_2);
	a_2=(90-a_2)*M_PI/180;
}
