#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

int sudoku[SIZE][SIZE];

int valid[11] = {0};

void *check_rows(void *arg) {
    for (int i = 0; i < SIZE; i++) {
        int check[SIZE] = {0};
        for (int j = 0; j < SIZE; j++) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || check[num - 1]++) return NULL;
        }
    }
    valid[0] = 1;
    return NULL;
}

void *check_cols(void *arg) {
    for (int j = 0; j < SIZE; j++) {
        int check[SIZE] = {0};
        for (int i = 0; i < SIZE; i++) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || check[num - 1]++) return NULL;
        }
    }
    valid[1] = 1;
    return NULL;
}

void *check_subgrid(void *arg) {
    int index = *(int *)arg;
    int row = (index / 3) * 3;
    int col = (index % 3) * 3;
    int check[SIZE] = {0};

    for (int i = row; i < row + 3; i++) {
        for (int j = col; j < col + 3; j++) {
            int num = sudoku[i][j];
            if (num < 1 || num > 9 || check[num - 1]++) return NULL;
        }
    }
    valid[index + 2] = 1;
    return NULL;
}

int main() {
    printf("input sudocu:\n");
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            scanf("%d", &sudoku[i][j]);
        }
    }
    pthread_t threads[11];
    int indices[9];

    pthread_create(&threads[0], NULL, check_rows, NULL);
    pthread_create(&threads[1], NULL, check_cols, NULL);
    
    for (int i = 0; i < 9; i++) {
        indices[i] = i;
        pthread_create(&threads[i + 2], NULL, check_subgrid, &indices[i]);
    }

    for (int i = 0; i < 11; i++) pthread_join(threads[i], NULL);

    for (int i = 0; i < 11; i++) {
        if (valid[i] == 0) {
            printf("Invalid Sudoku\n");
            return 0;
        }
    }

    printf("Valid Sudoku\n");
    return 0;
}
