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

Created by 박준영 on 11/27/23.
 */
#include <AVLTree.h>

int getHeight(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int getBalanceFactor(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}


int getSubtreeSize(Node *node) {
    return node != nullptr ? node->subtreeSize : 0;
}

Node *getMinimumNodeOfSubTree(Node *node) {
    Node *current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node *rightRotate(Node *currentRoot) {
    Node *newRoot = currentRoot->left;
    Node *subtree = newRoot->right;

    newRoot->right = currentRoot;
    currentRoot->left = subtree;

    currentRoot->height = max(getHeight(currentRoot->left), getHeight(currentRoot->right)) + 1;
    currentRoot->subtreeSize = 1 + getSubtreeSize(currentRoot->left) + getSubtreeSize(currentRoot->right);

    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    newRoot->subtreeSize = 1 + getSubtreeSize(newRoot->left) + getSubtreeSize(newRoot->right);

    return newRoot;
}

Node *leftRotate(Node *currentRoot) {
    Node *newRoot = currentRoot->right;
    Node *subtree = newRoot->left;

    newRoot->left = currentRoot;
    currentRoot->right = subtree;

    currentRoot->height = max(getHeight(currentRoot->left), getHeight(currentRoot->right)) + 1;
    currentRoot->subtreeSize = 1 + getSubtreeSize(currentRoot->left) + getSubtreeSize(currentRoot->right);

    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    newRoot->subtreeSize = 1 + getSubtreeSize(newRoot->left) + getSubtreeSize(newRoot->right);

    return newRoot;
}


Node *eraseNode(Node *root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = eraseNode(root->left, key);
    } else if (key > root->key) {
        root->right = eraseNode(root->right, key);
    } else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            Node *temp = getMinimumNodeOfSubTree(root->right);
            root->key = temp->key;
            root->right = eraseNode(root->right, temp->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    root->subtreeSize = 1 + getSubtreeSize(root->left) + getSubtreeSize(root->right);

    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

void AVLTree::erase(int key) {
    if (findWithoutPrint(key) == nullptr) {
        cout << 0 << '\n';
        return;
    }
    find(key);
    sizeOfTree--;
    root = eraseNode(root, key);
}
