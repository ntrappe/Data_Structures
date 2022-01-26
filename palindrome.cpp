#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Using a stack to detect if the string is a palindrome
// Param: string to check if palindrome
// Return: true if palindrome, false otherwise
bool isPalindromeStack (string input) {
    // check if input valid
    if (input.length() == 0)
        return false;
    if (input.length() == 1)
        return true;

    // iterate through the string, adding each letter to stack
    stack<char> letters;
    for (int i = 0; i < input.length(); i++) {
        letters.push (input.at (i));
        // cout << "adding letter " << input.at (i) << endl;
    }

    int front = 0;
    // compare the front letter and back letter, if any different
    // immediately return bc can't be a palindrome
    while (!letters.empty()) {
        char back = letters.top();
        letters.pop();
        if (back != input.at (front))
            return false;
        front++;
    }

    return true;
}


// Using pointers to detect if the string is a palindrome
bool isPalindromePtr (string input) {
    int front = 0;
    int back = input.length() - 1;

    while (front <= back) {
        if (input.at (front) != input.at (back))
            return false;
        front++;
        back--; 
    }
    return true;
}

int main () {
    const char* words[8] = {"hi", "h", "no", "noon", "hiayaih", "agoga", "teat", "mooooooooooooooooooom"};
    for (int i = 0; i < 8; i++) {
        cout << words[i] << " = " << isPalindromeStack (words[i]) << endl;
        cout << words[i] << " = " << isPalindromePtr (words[i]) << endl;
    }
    return EXIT_SUCCESS;
}