#include "sorting.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSortStep(int* array, int size, SortingState* state) {
    if (state->currentStep < size - 1) {
        for (int j = 0; j < size - state->currentStep - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
        state->currentStep++;
    } else {
        state->isCompleted = true;
    }
}

void quickSortStep(int* array, int size, SortingState* state) {
    static int quickSortTop = -1;
    static struct {
        int low;
        int high;
    } quickSortStack[ARRAY_SIZE];

    if (!state->isCompleted && !state->isPaused) {
        if (quickSortTop == -1) {
            quickSortStack[++quickSortTop] = (typeof(*quickSortStack)){0, size - 1};
        }

        if (quickSortTop >= 0) {
            int low = quickSortStack[quickSortTop].low;
            int high = quickSortStack[quickSortTop--].high;
            int pivot = partition(array, low, high);

            if (pivot - 1 > low) {
                quickSortStack[++quickSortTop] = (typeof(*quickSortStack)){low, pivot - 1};
            }
            if (pivot + 1 < high) {
                quickSortStack[++quickSortTop] = (typeof(*quickSortStack)){pivot + 1, high};
            }
        } else {
            state->isCompleted = true;
        }
        state->currentStep++;
    }
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}