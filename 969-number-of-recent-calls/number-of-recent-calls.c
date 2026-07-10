#include <stdlib.h>

typedef struct {
    int *q;
    int front;
    int rear;
} RecentCounter;

RecentCounter* recentCounterCreate() {
    RecentCounter* obj = (RecentCounter*)malloc(sizeof(RecentCounter));
    obj->q = (int*)malloc(sizeof(int) * 10000);
    obj->front = 0;
    obj->rear = 0;
    return obj;
}

int recentCounterPing(RecentCounter* obj, int t) {
    obj->q[obj->rear++] = t;

    while (obj->q[obj->front] < t - 3000) {
        obj->front++;
    }

    return obj->rear - obj->front;
}

void recentCounterFree(RecentCounter* obj) {
    free(obj->q);
    free(obj);
}