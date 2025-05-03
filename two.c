#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int SIZE;
const int mm = 1e5;

int arr[mm];
int sorted[mm];

void bubble_sort(int *start, int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (start[j] > start[j + 1]) {
                int temp = start[j];
                start[j] = start[j + 1];
                start[j + 1] = temp;
            }
        }
    }
}

void *sort_first_half(void *arg) {
    bubble_sort(arr, SIZE / 2);
    return NULL;
}

void *sort_second_half(void *arg) {
    bubble_sort(arr + SIZE / 2, SIZE / 2);
    return NULL;
}

void *merge(void *arg) {
    int i = 0, j = SIZE / 2, k = 0;
    while (i < SIZE / 2 && j < SIZE) {
        if (arr[i] < arr[j])
            sorted[k++] = arr[i++];
        else
            sorted[k++] = arr[j++];
    }
    while (i < SIZE / 2) sorted[k++] = arr[i++];
    while (j < SIZE) sorted[k++] = arr[j++];
    return NULL;
}

int main() {
    scanf("%d", &SIZE);
    for(int i = 0; i < SIZE; i++){
        scanf("%d", &arr[i]);
    }
    pthread_t t1, t2, t3;

    pthread_create(&t1, NULL, sort_first_half, NULL);
    pthread_create(&t2, NULL, sort_second_half, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_create(&t3, NULL, merge, NULL);
    pthread_join(t3, NULL);

    printf("Sorted array:\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", sorted[i]);
    printf("\n");

    return 0;
}