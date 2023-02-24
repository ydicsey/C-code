#include<stdio.h>

int main()
{
    int I;
    int i, j;

    while(scanf("%d", &I) && I){

        int P = 0;
        int bit[31] = {0};

        for(i = 0; I > 0; i++){
            bit[i] = I & 1;

            if(bit[i]){
                P++;
            }
            I >>= 1;
        }

        printf("The parity of ");
        for(j = i - 1; j >= 0; j--){
            printf("%d", bit[j]);
        }
        printf(" is %d (mod 2).\n", P);
    }
    return 0;
}