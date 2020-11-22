#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>

using namespace std;

vector<int> merge_lists(vector<int>& a, vector<int>& b) {
    // merge only odd numbers in each list + in ascending order
    vector<int> new_list;

    auto it_a = a.begin();
    auto it_b = b.begin();

    while(it_a != a.end() && it_b != b.end()) {
        if(*it_a % 2 == 0)
            it_a++;
        else if(*it_b % 2 == 0)
            it_b++;
        else {
            if(*it_a < *it_b) {
                new_list.push_back(*it_a);
                it_a++;
            } else {
                new_list.push_back(*it_b);
                it_b++;
            }
        }
    }

    // once one list has run out, only add odd nums of remaining list
    while(it_a != a.end()) {
        if(*it_a % 2 != 0) {
            new_list.push_back(*it_a);
        }
        it_a++;
    }

    // if still have items remaining in list 2, add the odds
    while(it_b != b.end()) {
        if(*it_b % 2 != 0) {
            new_list.push_back(*it_b);
        }
        it_b++;
    }

    cout << endl;

    return new_list;
}

void print_vector(vector<int>& list) {
    auto it = list.begin();
    while(it != list.end()) {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}

int main() {
    // build up an array in order
    int arr1[] = {1, 3, 4, 7, 8, 9};
    int n = sizeof(arr1) / sizeof(arr1[0]); 
    vector<int> vect_arr1(arr1, arr1 + n); 
    print_vector(vect_arr1);

    // build up an array in order
    int arr2[] = {0, 1, 2, 5, 6, 10};
    int m = sizeof(arr2) / sizeof(arr2[0]); 
    vector<int> vect_arr2(arr2, arr2 + m); 
    print_vector(vect_arr2);

    // print out merged array
    vector<int> vect_merged = merge_lists(vect_arr1, vect_arr2);
    print_vector(vect_merged);

    return EXIT_SUCCESS;
}