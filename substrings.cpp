#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

/**
 * Find the longest repeating, non-overlapping substring
 */


/**
 * Length of longest substring where the characters in that substring appear an EVEN number of times
 * ex. 324425 --> 44 or 2442 because characters repeat twice = length of 4
 * ex. 233015150 --> 33 or or 1515 or 015150 because all charcters repeat twice = length of 6
 */

/**
 * Helper Method for Length of longest substring
 * Note: Use sets over hashmap when you just want to submit the value not a key-value pair
 */
bool is_unique(string str, int left, int right) {
    set<char> char_table;                   // keeps track of all chars we've used in this string

    for(int i = left; i < right; i++) {
        char letter = str.at(i);            // current letter of substring

        // if can't find this letter/empty, add it
        if(char_table.find(letter) == char_table.end()) {
            char_table.insert(letter);
        } else {                // found it so got a repeat
            return false;
        }
    }
    return true;
}

/**
 * BRUTE FORCE: Length of longest substring without repeating characters
 * Time complexity: O(n^3)
 */
int length_LongestSubstring(string str) {
    int length = 0;                         // length of longest substring
   
    for(int i = 0; i < str.length(); i++) {
        // substring from position i to whatever j is
        for(int j = i + 1; j <= str.length(); j++) {
            /* if this substring has no repeating chars, compare its length 
             * to current to see if we should update it */
            if(is_unique(str, i, j)) {
                length = max(length, j - i);
            }
        }
    }
        
    return length;
}

/**
 * SLIDING WINDOW: Length of longest substring without repeating characters
 * Time complexity: O(n)
 */
int length_LongestSubstring_SW(string str) {
    int length = 0;
    int i = 0;
    int j = 0;
    set<char> char_table;

    while(i < str.length() && j < str.length()) {
        char letter = str.at(j);
        // if empty or don't have char then add it
        if(char_table.find(letter) == char_table.end()) {
            char_table.insert(letter);
            j++;
            length = max(length, j - i);
        // current char is a match to remove first instance of it aka first in set
        } else {
            char_table.erase(str.at(i++));
        }
    }
    return length;
}

/**
 * OPTIMIZED: Length of longest substring without repeating characters
 * Time complexity: O(n)
 */
int length_LongestSubstring_OP(string str) {

}


int main() {
    //cout << length_LongestSubstring("catiscat");
    cout << length_LongestSubstring_SW("catsst");
    return EXIT_SUCCESS;
}