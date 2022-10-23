#ifndef SORTS_H
#define SORTS_H


typedef struct merge_node merge_node_t;

struct merge_node
{
    int data;
    merge_node_t *next;
};  




void BubbleSort(int *arr, size_t size);
void InsertionSort(int *arr, size_t size);
void SelectionSort(int *arr, size_t size);
int CountingSort(int *arr, size_t size);
int RadixSort(int *arr, size_t size);
void QuickSort(void *base, size_t nmemb, size_t size, int(*compare)(const void*, const void*));
int MergeSort(int *arr_to_sort, size_t num_elements);
int BinarySearch(int *sorted_array, size_t first_index, size_t last_index, int num);
int BinarySearchWithLoop(int *sorted_array, size_t size, int number);
merge_node_t *ListsMergeSort(merge_node_t *head_1, merge_node_t *head_2);


#endif /*SORTS_H */