#include<stdio.h>

void main() {
	int n, i, j, k, x;
	printf("Enter the number of nodes : ");
	scanf("%d", &n);
	int rt[n][n];
	printf("Reading routing table : ");
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf("[%d][%d] : ", i,j);
			scanf("%d", &rt[i][j]);
		}
	}
	
	for (x=0; x<n; x++) {
		for (i=0; i<n; i++) {
			for (j=0; j<n; j++) {
				for (k=0; k<n; k++) {
					if (rt[i][j] > rt[i][k] + rt[k][j]) 
						rt[i][j] = rt[i][k] + rt[k][j];
				}
			}
		}
	}
	
	printf("\nDVT : \n");
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			printf("%d\t", rt[i][j]);
		}
		printf("\n");
	}
}
