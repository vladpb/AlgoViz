#include "sorting.h"

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void bubbleSortStep(int* array, int size, SortingState* state) {
    state->compareIndex1 = state->compareIndex2 = -1;
    state->swapIndex1 = state->swapIndex2 = -1;

    if (!state->isCompleted && state->hasStarted) {
        // Initialize indices if necessary
        if (state->i < 0) {
            state->i = 0;
            state->j = 0;
        }

        // Reset comparison and swap indices
        state->compareIndex1 = state->compareIndex2 = -1;
        state->swapIndex1 = state->swapIndex2 = -1;

        if (state->j < size - state->i - 1) {
            state->compareIndex1 = state->j;
            state->compareIndex2 = state->j + 1;

            if (array[state->j] > array[state->j + 1]) {
                state->swapIndex1 = state->j;
                state->swapIndex2 = state->j + 1;
                swap(&array[state->j], &array[state->j + 1]);
            }

            state->j++;
            state->currentStep++;
        } else {
            state->j = 0;
            state->i++;
            if (state->i >= size - 1) {
                state->isCompleted = true;
                state->compareIndex1 = state->compareIndex2 = -1;
            }
        }
    }
}


void quickSortStep(int* array, int size, SortingState* state) {
    static int stack[ARRAY_SIZE];
    static int top = -1;
    static bool initialized = false;

    if (!state->isCompleted && state->hasStarted && !state->isPaused) {
        if (!initialized) {
            state->low = 0;
            state->high = size - 1;
            stack[++top] = state->low;
            stack[++top] = state->high;
            initialized = true;
        }

        if (top >= 0) {
            state->high = stack[top--];
            state->low = stack[top--];

            int pivot = partition(array, state->low, state->high, state);
            state->currentStep++;

            // Push left side to stack
            if (pivot - 1 > state->low) {
                stack[++top] = state->low;
                stack[++top] = pivot - 1;
            }

            // Push right side to stack
            if (pivot + 1 < state->high) {
                stack[++top] = pivot + 1;
                stack[++top] = state->high;
            }
        } else {
            state->isCompleted = true;
            initialized = false;
            top = -1;
            // Reset comparison and swap indices
            state->compareIndex1 = state->compareIndex2 = -1;
            state->swapIndex1 = state->swapIndex2 = -1;
            state->pivotIndex = -1;
        }
    }
}

int partition(int* array, int low, int high, SortingState* state) {
    int pivot = array[high];
    int i = low - 1;

    state->pivotIndex = high; // Store pivot index for visualization

    for (int j = low; j <= high - 1; j++) {
        state->compareIndex1 = j;
        state->compareIndex2 = high; // Compare with pivot

        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);

            state->swapIndex1 = i;
            state->swapIndex2 = j;

            // Optionally, return here to visualize each swap step
            // return high; // Uncomment if you wish to step through each swap
        }
    }

    swap(&array[i + 1], &array[high]);

    state->swapIndex1 = i + 1;
    state->swapIndex2 = high;

    // Optionally, return here to visualize the final swap
    // return high; // Uncomment if you wish to step through each swap

    return i + 1;
}

