//
// Created by gburk on 2/15/2024.
//

#ifndef PROJECT1_2_AVL_H
#define PROJECT1_2_AVL_H

#endif //PROJECT1_2_AVL_H

#pragma once
#include <queue>
using namespace std;

// Video Demo, Project 1 Helper Files, used for lines 15-27,
class Node {
public:
    string name;
    string ufid;
    int height;
    Node *left;
    Node *right;
    Node(string name, string ufid) : name(name), ufid(ufid), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int max(int a, int b) {
        if (a > b)
            return a;
        else
            return b;
    }

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return (node->height);
    }

    Node* rotateLeft(Node* node) {
        Node* grandChild = node->right->left;
        Node* newParent = node->right;
        newParent->left = node;
        node->right = grandChild;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

        return newParent;
    }

    Node* rotateRight(Node* node) {
        Node* grandChild = node->left->right;
        Node* newParent = node->left;
        newParent->right = node;
        node->left = grandChild;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

        return newParent;
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left ) - getHeight(node->right);
    }

    Node* insertHelper(Node* node, string& name, string& ufid) {
        if (node == nullptr)
            return new Node(name, ufid);
        if (ufid < node->ufid)
            node->left = insertHelper(node->left, name, ufid);
        else if (ufid > node->ufid)
            node->right = insertHelper(node->right, name, ufid);
        else
            return node;

        node -> height = 1 + max(getHeight(node->left), getHeight(node->right));

        if (getBalanceFactor(node) > 1 && ufid < node->left->ufid)
            return rotateRight(node);

        if (getBalanceFactor(node) < -1 && ufid > node->right->ufid)
            return rotateLeft(node);

        if (getBalanceFactor(node) > 1 && ufid > node->left->ufid) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (getBalanceFactor(node) < -1 && ufid < node->right->ufid) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Trees Slides, slide 52, used for lines 104-111
    void inorderHelper(Node* node, vector<string>& names) {
        if (node == nullptr) {
            return;
        }
        else {
            inorderHelper(node->left, names);
            names.push_back(node->name);
            inorderHelper(node->right, names);
        }
    }

    void preorderHelper(Node* node, vector<string>& names) {
        if (node == nullptr) {
            return;
        }
        else {
            names.push_back(node->name);
            preorderHelper(node->left, names);
            preorderHelper(node->right, names);
        }
    }

    void postorderHelper(Node* node, vector<string>& names) {
        if (node == nullptr) {
            return;
        }
        else {
            postorderHelper(node->left, names);
            postorderHelper(node->right, names);
            names.push_back(node->name);
        }
    }

    int levelCountHelper(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int level = 0;
        queue<Node *> q;
        q.push(node);
        while(!q.empty()) {
            int size = q.size();
            while (size > 0) {
                if (q.front()->left != nullptr)
                    q.push(q.front()->left);
                if (q.front()->right != nullptr)
                    q.push(q.front()->right);
                q.pop();
                size--;
            }
            level++;
        }
        return level;
    }

    string searchIDHelper(Node* node, string& target) {
        if (node == nullptr)
            return "unsuccessful";
        if (target < node->ufid)
            return searchIDHelper(node->left, target);
        else if (target > node->ufid)
            return searchIDHelper(node->right, target);
        else
            return node->name;
    }

    vector<string> searchNameHelper(Node* node, string& target) {
        vector<string> result;
        if (node == nullptr) {
            return result;
        }
        if (node->name == target) {
            result.push_back(node->ufid);
        }
        vector<string> leftResults = searchNameHelper(node->left, target);
        vector<string> rightResults = searchNameHelper(node->right, target);
        for (int i = 0; i < (int)leftResults.size(); i++)
            result.push_back(leftResults[i]);
        for (int i = 0; i < (int)rightResults.size(); i++)
            result.push_back(rightResults[i]);
        return result;
     }

    Node* findMinValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* removeIDHelper(Node* node, string& ufid, bool& removed) {
        if (node == nullptr)
            return node;

        if (ufid < node->ufid)
            node->left = removeIDHelper(node->left, ufid, removed);
        else if (ufid > node->ufid)
            node->right = removeIDHelper(node->right, ufid, removed);
        else {
            removed = true;
            if ((node->left == nullptr) || (node->right == nullptr)) {
                Node *temp;
                if (node->left != nullptr) {
                    temp = node->left;
                } else {
                    temp = node->right;
                }
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else
                    *node = *temp;
                delete temp;
            } else {
                Node *temp = findMinValueNode(node->right);
                node->ufid = temp->ufid;
                node->name = temp->name;
                node->right = removeIDHelper(node->right, temp->ufid, removed);
            }
        }
        return node;
    }

    string removeInorderHelper(Node* node, int& n) {
        if (node == nullptr) {
            return "";
        }
        string ufid = removeInorderHelper(node->left, n);
        if (!ufid.empty())
            return ufid;
        if (n == 0) {
            return node->ufid;
        }
        n--;
        return removeInorderHelper(node->right, n);
    }

    void printNames(vector<string>& names) {
        for (int i = 0; i < (int)names.size(); i++) {
            cout << names[i];
            if (i < (int)names.size() - 1) {
                cout << ", ";
            }
            if (i == (int)names.size() - 1) {
                cout << endl;
            }
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(string name, string ufid) {
        this->root = insertHelper(this->root, name, ufid);
    }

    void printInorder() {
        vector<string> names;
        inorderHelper(this->root, names);
        printNames(names);
    }

    void printPreorder() {
        vector<string> names;
        preorderHelper(this->root, names);
        printNames(names);
    }

    void printPostorder() {
        vector<string> names;
        postorderHelper(this->root, names);
        printNames(names);
    }

    void printLevelCount() {
        int height = levelCountHelper(this->root);
        cout << height << endl;
    }

    void searchID(string& ufid) {
        string target = searchIDHelper(this->root, ufid);
        cout << target << endl;
    }

    void searchName(string& name) {
        string outcome;
        vector<string> result = searchNameHelper(this->root, name);
        if (result.empty())
            cout << "unsuccessful" << endl;
        for (int i = 0; i < (int)result.size(); i++) {
             cout << result[i] << endl;
        }
    }

    void removeID(string ufid) {
        bool removed = false;
        this->root = removeIDHelper(this->root, ufid, removed);
        if (removed) {
            cout << "successful" << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }

    void removeInorder(int& n) {
        string ufid = removeInorderHelper(this->root, n);
        if (!ufid.empty())
            removeID(ufid);
        else
            cout << "unsuccessful" << endl;
    }
};