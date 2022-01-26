#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <vector>
#include <string>

#define GREEN 0
#define YELLOW 1
#define ORANGE 2
#define RED 3
#define BROWN 4


using namespace std;

/**
 * Definition for a binary tree node aka Maple Leaf.
 **/
struct MapleLeaf {
    int color;                  // NOT unique color [0,4]
    int margin;                 // unique edge length
    MapleLeaf * left;
    MapleLeaf * right;

    // constructors
    MapleLeaf () : color (GREEN), margin (0), left (nullptr), right (nullptr) {}
    MapleLeaf (int c, int m) : color (c), margin (m), left (nullptr), right (nullptr) {}

    // compare if one leaf is smaller than another (e.g. leafA < leafB)
    bool operator< ( MapleLeaf * other ) {
        return this->margin < other->margin ? true : false;
    }

    // compare if one leaf is bigger than another (e.g. leafA > leafB)
    bool operator> ( MapleLeaf * other ) {
        return this->margin > other->margin ? true : false;
    }

    // compare if same leaf (e.g. leafA == leafB)
    bool operator== ( MapleLeaf * other ) {
        return this->margin == other->margin ? true : false;
    }
};

// sort tree so that the children of a maple leaf are not lighter than it
int countLeavesAtLevel (MapleLeaf * root, int level) {
    if (!root || level < 1)
        return 0;

    if (level == 1) 
        return 1;
    else
        return countLeavesAtLevel (root->left, level - 1) + countLeavesAtLevel (root->right, level - 1);
}

void printLeavesAtLevel (MapleLeaf * root, int level) {
    if (!root)
        return;

    if (level == 1)
        cout << "(" << root->margin << ") ";
    else {
        printLeavesAtLevel (root->left, level - 1);
        printLeavesAtLevel (root->right, level - 1);
    }
}

void DFS (MapleLeaf * root) {
    if (!root)
        return;

    DFS (root->left);
    cout << "(" << root->margin << ") [" << root->color << "]\n";
    DFS (root->right);
}

int getHeight (MapleLeaf * root) {
    if (!root)
        return 0;
    
    if (getHeight (root->left) > getHeight (root->right))
        return 1 + getHeight (root->left);
    else
        return 1 + getHeight (root->right);
}

void recursiveInsert (MapleLeaf * root, int kidColor, int kidMargin) {
    // no duplicates for margin (edge length) allowed
    if (root->margin == kidMargin)
        return;

    // if kid smaller + parent has no left, add
    if ( !root->left && (kidMargin < root->margin) ) {
        root->left = new MapleLeaf (kidColor, kidMargin);
        return;
    }

    // if kid bigger + parent has no right, add
    if ( !root->right && (kidMargin > root->margin) ) {
        root->right = new MapleLeaf (kidColor, kidMargin);
        return;
    }

    // else recurse
    if (kidMargin < root->margin) {
        recursiveInsert (root->left, kidColor, kidMargin);
    } else {
        recursiveInsert (root->right, kidColor, kidMargin);
    }
}


/**
 * @brief Builds up a Maple tree from a set of numbers representing the
 * edge length of the leaves. No duplicates allowed.
 * Note: this is allocating memory
 * 
 * @param colors vector of ints representing colors for each leaf
 * @param margins vector of ints representing length of edge of each leaf
 * @return MapleLeaf* pointer to the root
 */
MapleLeaf * insert (vector<int> colors, vector<int> margins) {
    MapleLeaf * root = nullptr;

    // if nothing to add, just return empty tree
    if (colors.size() < 1)
        return root;

    // first add the root (assume valid color)
    vector<int>::iterator col = colors.begin();
    vector<int>::iterator mar = margins.begin();
    root = new MapleLeaf (*col++, *mar++);

    // while there are still leaves to add, create a leaf
    // with the color then add it to the left or right of the parent
    // according to BST
    while (col != colors.end()) {
        recursiveInsert (root, *col++, *mar++);
    }
    return root;
}

MapleLeaf * getParent (MapleLeaf * root, MapleLeaf * kid) {
    // the kid is one of the parent's children
    if ( (root->left && (root->left == kid)) || (root->right && (root->right == kid)) ) {
        return root;
    // no way to traverse further
   } else if ( (!root->left && !root->right) || root == kid) {
       return nullptr;
   } else {
        if (kid < root)
            return getParent (root->left, kid);
        else
            return getParent (root->right, kid);
   }
}

// MapleLeaf * removeByColor (MapleLeaf * root, int color) {

// }

// MapleLeaf * remove (MapleLeaf * root, int margin) {

// }



int main () {
    //vector<int> colors 
    //int arr[] = { 10, 20, 30 };
    int colorsRaw[] = { RED, RED, GREEN, YELLOW, BROWN, GREEN, YELLOW, YELLOW, ORANGE, ORANGE, RED };
    int marginsRaw[] = { 8, 7, 12, 16, 3, 7, 1, 9, 17, 5, 2 };
    int n = sizeof(colorsRaw) / sizeof(colorsRaw[0]);
    vector<int> colors (colorsRaw, colorsRaw + n);
    vector<int> margins (marginsRaw, marginsRaw + n);
    //vector<int>& refColors = colors;
    
    MapleLeaf * root = insert (colors, margins);
    printLeavesAtLevel (root, 1);
    cout << endl;
    printLeavesAtLevel (root, 2);
    cout << endl;
    printLeavesAtLevel (root, 3);
    cout << endl;
    printLeavesAtLevel (root, 4);
    cout << endl;
    printLeavesAtLevel (root, 5);
    cout << endl;
    
    DFS (root);

    return EXIT_SUCCESS;
}