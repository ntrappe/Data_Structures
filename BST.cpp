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

/**
 * Height of the BST
 * Works by finding the longest max subtree
 **/
int get_height(TreeNode* root) {
    if(root == nullptr)
        return 0;
    else {
        int max_left = get_height(root->left);
        int max_right = get_height(root->right);
        if(max_left > max_right)
            return max_left + 1;
        else
            return max_right + 1;
    }
}

/**
 * Count all the nodes at a given level.
 * For example: level 1 = the root node so we should return 1
 *              if root has 2 kids, level 2 should return 2
 **/
int count_nodes_atlevel(TreeNode* root, int level) {
    if(!root)
        return 0;
    if(level == 1)
        return 1;
    else {
        return count_nodes_atlevel(root->left, level - 1) + count_nodes_atlevel(root->right, level - 1);
    }
}

// prints out the nodes for a given level
void print_level(TreeNode* root, int level) {
    if(!root)
        return;
    if(level == 1)
        cout << root->val << " ";
    else {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

/** 
 * Prints out the nodes in a tree for each level at a time
 * For example: level 1 = will just print out root node
 * Note: number of levels in a tree corresponds to the height
 **/
void level_order(TreeNode* root) {
    int level = get_height(root);
    cout << "height of " << level << endl;

    for(int i = 1; i <= level; i++) {
        print_level(root, i);
        cout << endl;
    }
    cout << endl;
}

/**
 * In order traversal: left, root, right
 * DFS, O(n)
 **/
void in_order(TreeNode* root) {
    if(!root)
        return;
    in_order(root->left);
    cout << root->val << " ";
    in_order(root->right);
}

/**
 * Post order traversal: left, right, root
 * DFS, O(n)
 **/
void post_order(TreeNode* root) {
    if(!root)
        return;
    post_order(root->left);
    post_order(root->right);
    cout << root->val << " ";
}

/**
 * Pre order traversal: root, left, right
 * DFS, O(n)
 **/
void pre_order(TreeNode* root) {
    if(!root)
        return;
    cout << root->val << " ";
    pre_order(root->left);
    pre_order(root->right);
}


int BFS(TreeNode* root) {
    if(!root)
        return EXIT_FAILURE;
    level_order(root);
}

/**
 * Depth First Search
 * pre-order, post-order, in-order
 **/
int DFS(TreeNode* root, string type) {
    if(type == "pre_order" || type == "pre-order")
        pre_order(root);
    else if(type == "post_order" || type == "post-order")
        post_order(root);
    else
        in_order(root);
    
    return EXIT_SUCCESS;
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
TreeNode* get_parent(TreeNode* root, int val) {
    //cout << "parent is " << root->val << endl;
    if((root->left && root->left->val == val) || (root->right && root->right->val == val)) {
        //cout << "child has " << val << endl;
        return root;
    // either no children left to search or root matches our val 
    // so cannot return anything
    } else if((!root->left && !root->right) || root->val == val) {
        return nullptr;
    // keep traversing
    } else {
        if(val < root->val)
            return get_parent(root->left, val);
        return get_parent(root->right, val);
    }
    
}

/**
 * Finds the smallest value in a subtree (keeps staying left)
 **/
TreeNode* min_val(TreeNode* root) {
    if(!root->left)
        return root;
    return min_val(root->left);
}

/**
 * Root has 2 kids and we want to delete the root so decide which
 * kid becomes new root and where the other goes
 * 
 * In-order Traversal: right once then all the way left
 **/
TreeNode* successor(TreeNode* root) {
    TreeNode* successor;
    TreeNode* parent;

    // try to go right first, if can't, return null
    if(!root->right)
        successor = nullptr;

    successor = min_val(root->right);
    parent = get_parent(root, successor->val);

    cout << "successor is " << successor->val << endl;
    if(parent)
        cout << "parent is " << parent->val << endl;

    // create a "new successor" by just modifying data
    parent->val = successor->val;
    
    // case 1: successor's parent is node to remove so update data (skip over)
    if(parent == root) {
        cout << "remove parent node case\n";
        parent->right = successor->right;

    // case 2: successor's parent NOT to remove so just detach pointer (just remove)
    } else {
        cout << "parent (" << parent->val << ") used to point to (" << parent->left->val <<")\n";
        parent->left = nullptr;
    }
   
    delete successor;

    return root;
}

/**
 * Worst case O(log n)
 **/
TreeNode* remove(TreeNode* root, int val) {
    TreeNode* ref;                      // will point to node to remove (for freeing memory)
    TreeNode* parent;
    TreeNode* grandkidL = nullptr;
    TreeNode* grandkidR = nullptr;

    // case 0: remove root
    if(root->val == val) {
        cout << "remove root\n";
        return successor(root);
    }

    parent = get_parent(root, val);

    // save node to remove to ref pointer
    if(val < parent->val)
        ref = parent->left;
    ref = parent->right;

    // save kids of node to remove
    if(ref->left)
        grandkidL = ref->left;
    if(ref->right)
        grandkidR = ref->right;

    // case 1: node to remove has no kids
    if(!grandkidL && !grandkidR) {
        parent->left = nullptr;
        parent->right = nullptr;
        delete ref;
    }

    // case 2: node to remove has 1 kid
    else if(grandkidL && !grandkidR) {
        parent->left = grandkidL;
        delete ref;
    }
    else if(grandkidR && !grandkidL) {
        parent->right = grandkidR;
        delete ref;
    }

    // case 3: node has 2 kids so choose successor
    else {
        // if node to remove is left child, replace it with successor
        if(parent->left->val == val) {
            parent->left = successor(ref);
        // otherwise, replace right child with successor
        } else {
            parent->right = successor(ref);
        }
    }

    return root;
}

/**
 * O(n) to traverse to ends of all subtrees to find leaves
 **/
int count_all_leaves(TreeNode* root) {
    if(!root)
        return 0;
    else if(!root->left && !root->right)
        return 1;
    else {
        return count_all_leaves(root->left) + count_all_leaves(root->right);
    }

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
    //level_order(start);
    /*
    TreeNode * prev = get_parent(start, 20);
    if(prev)
        cout << "prev " << prev->val << endl;
    else
        cout << "didn't find prev\n";*/
    //TreeNode * start2 = remove(start, 5);       // try to remove root
    
    // TEST 4:
    /**         5
     *        3    10
     *      2    8   13
     *    1    7        15
     *                    20
     **/
    int woop[] = {5, 3, 10, 2, 1, 8, 13, 7, 15, 20};
    vector<int> vect4(woop, woop + sizeof(woop) / sizeof(woop[0]));
    start = insert(vect4);
    //TreeNode* start2 = remove(start, 10);
    //level_order(start2);
    //cout << "# leaves: " << count_all_leaves(start) << endl;
    //cout << "# nodes: " << count_nodes_atlevel(start, 5) << endl;

    BFS(start);


    return EXIT_SUCCESS;
}
