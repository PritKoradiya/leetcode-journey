/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

int compare(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    if (p1->value < p2->value) return -1;
    if (p1->value > p2->value) return 1;
    return 0;
}

int* arrayRankTransform(int* arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;

    if (arrSize == 0) return NULL;

    Pair *pairs = (Pair *)malloc(sizeof(Pair) * arrSize);
    int *result = (int *)malloc(sizeof(int) * arrSize);

    for (int i = 0; i < arrSize; i++) {
        pairs[i].value = arr[i];
        pairs[i].index = i;
    }

    qsort(pairs, arrSize, sizeof(Pair), compare);

    int rank = 1;
    result[pairs[0].index] = rank;

    for (int i = 1; i < arrSize; i++) {
        if (pairs[i].value != pairs[i - 1].value)
            rank++;
        result[pairs[i].index] = rank;
    }

    free(pairs);
    return result;
}