	//ASSG1_C_B220009CS_CS03_AFSHEEN_5
//Given an array A of N integers and an integer K, return the count of distinct integers in all windows of size K.
#include <stdio.h>

#define MAX_SIZE 1000001

//counting the distinct numbers in every window
void window_dist_count(int arr[], int N, int K) {
    int window[MAX_SIZE] = {0};
    int distinct_count = 0;

    for (int i = 0; i < K; i++) {
        if (window[arr[i]] == 0) {
            distinct_count++;
        }
        window[arr[i]]++;
    }

    printf("%d ", distinct_count);

    for (int i = K; i < N; i++) {
        int left_element = arr[i - K];
        window[left_element]--;
        if (window[left_element] == 0) {
            distinct_count--;
        }

        int right_element = arr[i];
        if (window[right_element] == 0) {
            distinct_count++;
        }
        window[right_element]++;

        printf("%d ", distinct_count);
    }
}

//main function
int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    int arr[MAX_SIZE];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    window_dist_count(arr, N, K);

    return 0;
}


