#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

const int SZ_ARR = 100;

int* insertion_sort(int arr[]) {
    int curr_idx;

    for(int i = 1; i < SZ_ARR; i++) {
        curr_idx = i;
        // if current selection smaller than previous, insert it before
        while(curr_idx >= 1 && (arr[curr_idx] < arr[curr_idx - 1])) {
            // current element at i smaller than prev so swap them
            // set current element to new swapped location
            int temp = arr[curr_idx - 1];
            arr[curr_idx - 1] = arr[curr_idx];
            arr[curr_idx] = temp;
            curr_idx = curr_idx - 1;      // keep checking
        }
    }
    return arr;
}

int* selection_sort(int arr[]) {
    int sorted[SZ_ARR];

    for(int i = 0; i < SZ_ARR; i++) {
        // traverse original array 
        int min_idx = i;
        for(int j = i + 1; j < SZ_ARR; j++) {
            if(arr[j] < arr[min_idx])
                min_idx = j;
        }
        // swap current element an minimum element
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
    return arr;
}

void merge(int arr[], int left, int middle, int right) {
    int num_first_list = middle - left + 1;     // number of elements in first list
    int num_second_list = right - middle;       // number of elements in second list
    int i, j, k;

    int first_half[num_first_list];             // holds first list elements
    int second_half[num_second_list];           // holds second list elements

    // split up data from original array into the first and second lists
    for(i = 0; i < num_first_list; i++) {
        first_half[i] = arr[left + i];          // first half
    }
    for(j = 0; j < num_second_list; j++) {
        second_half[j] = arr[middle + 1 + j];   // second half
    }

    i = 0;
    j = 0;
    k = left;

    while(i < num_first_list && j < num_second_list) {
        if(first_half[i] <= second_half[j]) {      
            arr[k] = first_half[i];          // if first list element smaller, add it
            i++;
        } else {
            arr[k] = second_half[j];        // otherwise, add second element
            j++;
        }
        k++;
    }

    // opy the remaining elements of the first list if there are any
    while (i < num_first_list) {
        arr[k] = first_half[i];
        i++;
        k++;
    }
 
    // copy the remaining elements of the second list if there are any
    while (j < num_second_list) {
        arr[k] = second_half[j];
        j++;
        k++;
    }
}

/* Keeps splitting up the array into halves until we get individual chunks */
void merge_recurse(int arr[], int left, int right) {
    if(left >= right)
        return;                             // stops when we have divided into individual pieces
    int middle = (left + right)/2;          // get midpoint to split list in half
    merge_recurse(arr, left, middle);       // recurse on first half of list
    merge_recurse(arr, middle + 1, right);  // recurse on second half of list
    merge(arr, left, middle, right);
}

int* merge_sort(int arr[]) {
    int left = 0;
    int right = SZ_ARR - 1;

    merge_recurse(arr, left, right);

    return arr;

}

int print(int sorted[]) {
    for(int i = 0; i < SZ_ARR; i++) {
        cout << sorted[i] << " ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}

int main() {
    int arr[SZ_ARR];

    // fill up array with random numbers from 0-9
    for(int i = 0; i < SZ_ARR; i++) {
        arr[i] = rand() % 10;
    }

    //int * arr2 = insertion_sort(arr);
    //print(insertion_sort(arr));
    //print(selection_sort(arr));
    print(merge_sort(arr));

    return 0;
}