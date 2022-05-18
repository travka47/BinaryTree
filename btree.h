#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
using namespace std;

struct trunk {
    trunk *prev;
    string str;
    trunk(trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

struct node {
    int key_value;
    node *left;
    node *right;
};

class btree {
public:
    btree();
    bool is_empty();
    void insert(int key);
    void search(int key);
    void delete_node(int key);
    btree delete_all(btree);
    void print();
    void iteration(int key);
    void inorder();
    void preorder();
    void postorder();
    vector<int> parse(const string &s);

private:
    node *root;

    void insert(int key, node *leaf);
    node *search(int key, node *leaf);
    node *min(node *leaf);
    node *delete_node(int key, node *leaf);
    void print(node *root, trunk *prev, bool is_left);
    node *iteration(int key, node *leaf);
    void inorder(node *leaf);
    void preorder(node *leaf);
    void postorder(node *leaf);
    bool base_check();
    void show_trunks(trunk *p);
};