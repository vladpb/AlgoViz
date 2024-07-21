#ifndef ALGOVIZ_SORTING_H
#define ALGOVIZ_SORTING_H

#include "visualization.h"

void bubbleSortStep(int* array, int size, SortingState* state);
void quickSortStep(int* array, int size, SortingState* state);
void swap(int* a, int* b);
int partition(int* array, int low, int high);

#endif //ALGOVIZ_SORTING_H