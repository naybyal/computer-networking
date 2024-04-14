#include <stdio.h>

void main() {
    int n,i,j,k,x;
    
    printf("Enter the number of nodes... ");
    scanf("%d", &n);

    int routingTable[n][n];
    printf("Reading the routing table...\n");
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            printf("[%d][%d] : ", i, j);
            scanf("%d", &routingTable[i][j]);
        }
    }

    for (x=0; x<n; x++) {
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                for (k=0; k<n; k++) {
                    if (routingTable[i][j] > routingTable[i][k] + routingTable[k][j])
                        routingTable[i][j] = routingTable[i][k] + routingTable[k][j];
                }
            }
        }
    }

    printf("\n DVT ..\n");
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++)
            printf("%d\t", routingTable[i][j]);
        printf("\n");
    }
}