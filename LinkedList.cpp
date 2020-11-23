#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
 * Definition for a singly linked list node.
 **/
struct ListNode {
    char val;
    ListNode * next;

    // constructors
    ListNode() : val('\0'), next(nullptr) {}
    ListNode(char x) : val(x), next(nullptr) {}
};

bool palindrome(ListNode** head) {
    ListNode* curr = *head;
    stack<char> st;

    // add all elements to stack 
    while(curr) {
        st.push(curr->val);
        curr = curr->next;
    }

    curr = *head;

    // compare top of stack to head of list
    while(curr) {
        char top_ch = st.top();
        st.pop();

        if(curr->val != top_ch) {
            cout << curr->val << " not = " << top_ch << endl;
            return false;
        }

        curr = curr->next;
    }

    return true;
}

void insert_tail(ListNode** head, int data) {
    ListNode * ref = new ListNode(data);        // will have next = nullptr
    ListNode * prev = *head;

    if(*head == nullptr) {             // if list empty, make this the head
        *head = ref;
        return;
    }

    // else, traverse the list till we get last node
    while(prev->next) {
        prev = prev->next;
    }

    prev->next = ref;
    return;
}

void insert_head(ListNode** head, int data) {
    ListNode * ref = new ListNode(data);        // will have next = nullptr
    ListNode * prev = *head;

    if(*head == nullptr) {             // if list empty, make this the head
        *head = ref;
        return;
    }

    // else set new node's next to prev head and it becomes the head
    ref->next = prev;
    *head = ref;
    return;
}

void reverse(ListNode** head) {
    ListNode* prev = nullptr;
    ListNode* curr = *head;
    ListNode* next = nullptr;

    if(*head == nullptr)
        return;

    while(curr) {
        next = curr->next;          // store next node
        cout << "next (" << next->val << ")\n";
        curr->next = prev;          // change next node pointer (reverse ptr)
        prev = curr;
        cout << "prev now (" << prev->val << ")\n";
        curr = next;
        cout << "curr now (" << curr->val << ")\n";
    }
    head = &prev;
}

int main() {
    ListNode* head = nullptr;
    char str[] = "abadaba";
    int sz = sizeof(str)/sizeof(str[0]);
    cout << sizeof(str) << endl;
/*
    insert_tail(&head, 'a');
    insert_tail(&head, 'b');
    insert_tail(&head, 'a');
    insert_tail(&head, 'd');
    insert_tail(&head, 'a');
    insert_tail(&head, 'b');
    insert_tail(&head, 'a');*/

    insert_tail(&head, 'r');
    insert_tail(&head, 'a');
    insert_tail(&head, 'd');
    insert_tail(&head, 'b');
    insert_tail(&head, 'x');

    //cout << head->val << endl;
    //cout << "is palindrome? " << palindrome(&head) << endl;
    reverse(&head);
    cout << head->val << endl;
    //cout << head->next->val << endl;
    //cout << head->next->next->val << endl;


    return 0;
}