#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define n 4

int main(int argc, char *argv[])
{
    float a[n][n][n], b[n][n][n];

    int i, j, k;
    int ii, jj, kk;

    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            for (k=0; k<n; k++) {
                b[i][j][k] = 1;
            }
        }
    }

    for (i=1; i<n-1; i++)
        for (j=1; j<n-1; j++)
            for (k=1; k<n-1; k++) {
                a[i][j][k]=0.8*(b[i-1][j][k]+b[i+1][j][k]+b[i][j-1][k]
                + b[i][j+1][k]+b[i][j][k-1]+b[i][j][k+1]);
            }

    printf("RESULTS a:\n");

    for (i=1; i<n-1; i++){
        for (j=1; j<n-1; j++){
            for (k=1; k<n-1; k++) {
                printf("%.1f  ", a[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

}