#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

int main(){

    int slength;

    printf("Enter sequence length\n");

    scanf("%d", &slength);

    if(slength == 1)
    {
        printf("Length is 1");
        return 0;
    }

    printf("Enter sequence\n");

    int seq[slength];
    int temp;

    for (int i = 0; i < slength; i++)
    {
        scanf("%d", &temp);
        seq[i] = temp;
    }    
    int lis[slength];
    lis[0] = 1;
    vector<int> lis_path[slength];

    for (int i = 1; i < slength; i++) {
        lis[i] = 1;
        for (int j = 0; j < i; j++)
            if (seq[i] > seq[j] && lis[i] < lis[j] + 1){
                lis[i] = lis[j] + 1;
                lis_path[i].push_back(j);
            }
    }
    printf("Longest Monotonically Increasing Subsequence ending in :\n");
    for (int i = 0; i < slength; i++){
        printf("%d :", i);
        for (auto j: lis_path[i]){
            printf("%d-", seq[j]);
        }
        printf("%d", seq[i]);
        printf("\n");
    }
    
    // Return maximum value in lis[]
    printf ("Max LMIS length = %d", *max_element(lis, lis + slength));

    return 0;
}