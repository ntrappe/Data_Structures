#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for a binary tree node.
 **/
struct TreeNode {
    int val;
    TreeNode * left;
    TreeNode * right;

    // constructors
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


int get_height(TreeNode* root) {
    if(root == nullptr)
        return -1;
    else {
        int max_left = get_height(root->left);
        int max_right = get_height(root->right);
        if(max_left > max_right)
            return max_left + 1;
        else
            return max_right + 1;
    }
}

// Insert should be O(log n) unless leaning tree which is O(n)
void recurse_insert(TreeNode* root, int val) {
    // already have this in tree (no duplicates)
    if(val == root->val) {
        return;
    // if val is smaller + there's no left child, it becomes new left child
    } else if(val < root->val && !root->left) {
        root->left = new TreeNode(val);
        return;
    // if val is bigger + there's no right child, it becomes new right child
    } else if(val > root->val && !root->right) {
        root->right = new TreeNode(val);
        return;
    // need to find an available spot so keep going through tree
    } else {
        if(val < root->val)
            recurse_insert(root->left, val);
        if(val > root->val)
            recurse_insert(root->right, val);
    }
}


TreeNode* insert(vector<int>& nums) {
    TreeNode* root;
    auto it = nums.begin();

    // bad, empty vector
    if(it == nums.end())
        return nullptr;
    
    // can assume we have at least 1 node so make that the root
    root = new TreeNode(*it++);

    // we were only given 1 node so added that as root and now done
    if(it == nums.end())
        return root;;

    // now recursively add remaining nums to tree
    // should take ave O(log n) for each node so total: O(n log n)
    while(it != nums.end()) {
        recurse_insert(root, *it);
        it++;
    }
    return root;
}

/**
 * Gives you a pointer to the parent node of the value we want
 */
TreeNode* get_prev(TreeNode* root, int val) {
    cout << "parent is " << root->val << endl;
    if((root->left && root->left->val == val) || (root->right && root->right->val == val)) {
        cout << "child has " << val << endl;
        return root;
    // either no children left to search or root matches our val 
    // so cannot return anything
    } else if((!root->left && !root->right) || root->val == val) {
        return nullptr;
    // keep traversing
    } else {
        if(val < root->val)
            return get_prev(root->left, val);
        return get_prev(root->right, val);
    }
    
    
}

/**
 * Worst case O(log n)
 **/
TreeNode* remove(TreeNode* root, int val) {
    TreeNode* ref;          // will point to node to remove (for freeing memory)
    //auto it = root.begin();

    return nullptr;
}



// prints out the nodes for a given level
void print_level(TreeNode* root, int level) {
    if(root == nullptr)
        return;
    if(level == 1)
        cout << root->val << " ";
    else {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

// prints out the nodes in a tree for each level at a time
void level_order(TreeNode* root) {
    int level = get_height(root);
    cout << "height of " << level << endl;

    for(int i = 0; i <= level; i++) {
        print_level(root, i);
        cout << endl;
    }
    cout << endl;
}

int main() {
    // TEST 1: empty vect
    int invalid[] = {};
    vector<int> vect1(invalid, invalid + sizeof(invalid) / sizeof(invalid[0]));

    // TEST 2: 1 item
    int root[] = {5};
    vector<int> vect2(root, root + sizeof(root) / sizeof(root[0]));

    // TEST 3:
    /**         5
     *        4   6
     *      3       7
     *                8
     *                  11
     *                    20
     **/
    int leaning[] = {5, 4, 6, 3, 7, 8, 11, 20};
    vector<int> vect3(leaning, leaning + sizeof(leaning) / sizeof(leaning[0]));

    //cout << insert(vect1) << endl;
    //cout << insert(vect2) << endl;
    TreeNode * start = insert(vect3);
    level_order(start);
    TreeNode * prev = get_prev(start, 20);
    if(prev)
        cout << "prev " << prev->val << endl;
    else
        cout << "didn't find prev\n";
    

    return EXIT_SUCCESS;
}