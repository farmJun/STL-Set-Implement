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

Created by 장태양 on 11/23/23.
 */

#include "AVLTree.h"
#include <iostream>

using namespace std;

void AVLTree::rank(int key) {
    if (findWithoutPrint(key) == nullptr) {
        cout << 0 << '\n';
        return;
    }

    pair<int, int> result = rank(root, key, 0, 0);
    cout << result.second << " " << result.first << '\n';
}

pair<int, int> rankAndDepth(NodePointer currentNode, int key, int currentDepth, int currentRank) {
    if (currentNode == nullptr) {
        return { 0, 0 };
    }

    int leftSubtreeSize = currentNode->left->subtreeSize;
    if (key == currentNode->key) {
        return { currentRank + leftSubtreeSize + 1, currentDepth };
    }
    else if (key < currentNode->key) {
        return rankAndDepth(currentNode->left, key, currentDepth + 1, currentRank);
    }
    else {//key > currentNode->key
        return rankAndDepth(currentNode->right, key, currentDepth + 1, currentRank + leftSubtreeSize + 1);
    }
}