/*
MIT License

Copyright (c) 2023 Inha-Open-Source-Team-BBBig

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Created by 박준영 on 11/18/23.
 */

#include "AVLTree.h"
#include "iostream"

using namespace std;

int height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node *newNode(int key) {
    Node *node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rightRotate(Node *currentRoot) {
    Node *newRoot = currentRoot->left;
    Node *subtree = newRoot->right;
    newRoot->right = currentRoot;
    currentRoot->left = subtree;
    currentRoot->height = max(height(currentRoot->left), height(currentRoot->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

Node *leftRotate(Node *currentRoot) {
    Node *newRoot = currentRoot->right;
    Node *subtree = newRoot->left;
    newRoot->left = currentRoot;
    currentRoot->right = subtree;
    currentRoot->height = max(height(currentRoot->left), height(currentRoot->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

int getDepth(Node *node, int key, int depth) {
    if (node == NULL) {
        return -1;
    }

    if (node->key == key) {
        return depth;
    }

    int downlevel = getDepth(node->left, key, depth + 1);
    if (downlevel != -1) {
        return downlevel;
    }

    downlevel = getDepth(node->right, key, depth + 1);
    return downlevel;
}

Node *insertNode(Node *node, int key) {
    if (node == NULL) {
        return (newNode(key));
    }

    if (key < node->key) {
        node->left = insertNode(node->left, key);
    } else if (key > node->key) {
        node->right = insertNode(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        } else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        } else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

Node *AVLTree::insert(int key) {
    root = insertNode(root, key);
    int depth = getDepth(root, key, 1);
    cout << depth << '\n';
    return root;
}

const NodePointer AVLTree::getRoot() const {
    return root;
}

void printTree(Node *root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        } else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main() {
    AVLTree avlTree;
    avlTree.insert(50);
    printTree(avlTree.getRoot(), "", true);
    avlTree.insert(30);
    printTree(avlTree.getRoot(), "", true);
    avlTree.insert(20);
    printTree(avlTree.getRoot(), "", true);
    avlTree.insert(40);
    printTree(avlTree.getRoot(), "", true);
    avlTree.insert(70);
    printTree(avlTree.getRoot(), "", true);
    avlTree.insert(60);
    printTree(avlTree.getRoot(), "", true);
    avlTree.insert(80);
    printTree(avlTree.getRoot(), "", true);

    return 0;
}
