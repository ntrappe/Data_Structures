#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/**
 * Definition for a singly linked list node.
 */
struct ListNode {
    char val;
    ListNode * next;

    // constructors
    ListNode() : val('\0'), next(nullptr) {}
    ListNode(char x) : val(x), next(nullptr) {}
};

/**
 * Checks if a given word is a palindrome (read the same way forwards or backwards)
 * Input: pointer to a pointer to a ListNode (head of Linked List)
 *        each node is a character so from head to tail, it forms a word
 * Uses a stack to first go from head to tail, adding each character to the stack
 * then goes from head to tail but this times pops from the stack and if the top
 * differs from current nodes in list, not a match.
 */
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

/**
 * Insert Tail
 * Inserts a new node into the end of the Linked List
 * Input: head of Linked list and data to insert
 */
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

/**
 * Insert Head
 * Inserts a new node at the head of the Linked List
 * Input: head of Linked list and data to insert
 */
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

/**
 * Remove 
 * Removes a node from the Linked List by deleting it and rearranging pointers
 * Input: head of Linked list and data to remove
 */
void remove(ListNode** head, int data) {
    ListNode* curr = *head;
    ListNode* prev = nullptr;

    // if deleting from head
    if(curr && curr->val == data) {
        head = &(curr->next);           // set head to next item
        delete curr;
        return;
    }

    // search for node to remove
    while(curr && curr->val != data) {
        prev = curr;
        curr = curr->next;
    }

    if(!curr)       // didn't find (went thru list)
        return;

    // got a match so unlink it
    prev->next = curr->next;
    delete curr;
}

/**
 * Reverse
 * Reverses a linked list so what was the head is now the tail and we now have a pointer
 * to the new head which was the tail
 *      ex. --> (1) --> (2) is now --> (2) --> (1)
 * Input: head of Linked list
 */
void reverse(ListNode** head) {         // could also do ListNode* &head then do normal pointer
    ListNode* prev = nullptr;
    ListNode* curr = *head;
    ListNode* next = nullptr;

    if(*head == nullptr)
        return;

    while(curr) {
        next = curr->next;          // store next node
        curr->next = prev;          // change next node pointer (reverse ptr)
        prev = curr;
        curr = next;
    }
    *head = prev;
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