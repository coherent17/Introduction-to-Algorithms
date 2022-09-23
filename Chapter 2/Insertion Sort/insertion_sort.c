#include <stdio.h>

void printArray(int *array, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void insertion_sort(int *array, int size){
    for(int i = 1; i < size; i++){
        int key = array[i];

        int index = i - 1;
        while(index >= 0 && array[index] > key){
            array[index + 1] = array[index];
            index = index - 1;
        }
        array[index + 1] = key;
        printArray(array, size);
    }
}

int main(){
    int array[] = {5, 2, 4, 6, 1, 3};
    int size = sizeof(array) / sizeof(int);

    insertion_sort(array, size);

    return 0;
}