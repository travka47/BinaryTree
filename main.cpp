#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct node {
    int key_value;
    node *left;
    node *right;
};

struct Trunk {
    Trunk *prev;
    string str;
    Trunk(Trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

class btree {
public:
    btree();

    node *root;
    void insert(int key);
    node *search(int key);
    node *iteration(int key);
    bool delete_node(int key);
    bool is_empty();
    void print();
    void inorder();
    void preorder();
    void postorder();

private:
    void insert(int key, node *leaf);
    node *search(int key, node *leaf);
    node *iteration(int key, node *leaf);
    node *delete_node(int key, node *leaf);
    node *min(node *leaf);
    bool is_empty(node *leaf);
    void print(node *root, Trunk *prev, bool isLeft);
    void inorder(node *leaf);
    void preorder(node *leaf);
    void postorder(node *leaf);
};

btree::btree() {
    root=NULL;
}

void btree::insert(int key, node *leaf) {
    if(key< leaf->key_value) {
        if(leaf->left!=NULL)
            insert(key, leaf->left);
        else {
            leaf->left=new node;
            leaf->left->key_value=key;
            leaf->left->left=NULL;
            leaf->left->right=NULL;
        }
    }
    else if(key>leaf->key_value) {
        if(leaf->right!=NULL)
            insert(key, leaf->right);
        else {
            leaf->right=new node;
            leaf->right->key_value=key;
            leaf->right->left=NULL;
            leaf->right->right=NULL;
        }
    }
}

node *btree::search(int key, node *leaf) {
    if(leaf!=NULL) {
        if(key==leaf->key_value)
            return leaf;
        if(key<leaf->key_value)
            return search(key, leaf->left);
        else
            return search(key, leaf->right);
    }
    else return NULL;
}

node* btree::min(node *n) {
    if (n->left == nullptr) return n;
    return min(n->left);
}

node *btree::delete_node(int value, node *node) {
    if (node == nullptr) return node;
    if (value < node->key_value) node->left = delete_node(value, node->left);
    else if (value > node->key_value) node->right = delete_node(value, node->right);
    else if (node->right != nullptr && node->left != nullptr) {
        node->key_value = min(node->right)->key_value;
        node->right = delete_node(node->key_value, node->right);
    }
    else {
        if (node->left != nullptr) node = node->left;
        else if (node->right != nullptr) node = node->right;
        else node = nullptr;
    }
    return node;
}

bool btree::delete_node(int value) {
    if (!search(value, root)) return false;
    root = delete_node(value, root);
    return true;
}

node *btree::iteration(int key, node *leaf) {
    node* current = root;
    node* successor = nullptr;
    while (current != nullptr) {
        if (key < current->key_value) {
            successor = current;
            current = current->left;
        }
        else current = current->right;
    }
    return successor;
}

bool btree::is_empty(node *leaf) {
    return root == NULL;
}

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p) {
    if (p == nullptr) return;
    showTrunks(p->prev);
    cout << p->str;
}

void btree::print(node* root, Trunk *prev, bool isLeft) {
    if (root == nullptr) return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    print(root->right, trunk, true);

    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft) {
        trunk->str = ".———";
        prev_str = "   |";
    } else {
        trunk->str = "`———";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->key_value << endl;

    if (prev) prev->str = prev_str;
    trunk->str = "   |";

    print(root->left, trunk, false);
}

void btree::insert(int key) {
    if (search(key) == NULL) {
        if(root!=NULL)
            insert(key, root);
        else {
            root=new node;
            root->key_value=key;
            root->left=NULL;
            root->right=NULL;
        }
    }
    else {
        cout << "ERROR: Element with value " << key << " already exists in the tree" << endl;
    }
}

node *btree::search(int key) {
    return search(key, root);
}

node *btree::iteration(int key) {
    return iteration(key, root);
}

bool btree::is_empty() {
    is_empty(root);
}

void btree::print() {
    if (is_empty()) {
        cout << "The tree is empty" << endl;
    }
    else {
        print(root, nullptr, false);
    }
}

void btree::inorder(node *leaf) {
    if (leaf) {
        inorder(leaf->left);
        cout << leaf->key_value << " ";
        inorder(leaf->right);
    }
}

void btree::preorder(node *leaf) {
    if (leaf) {
        cout << leaf->key_value << " ";
        preorder(leaf->left);
        preorder(leaf->right);
    }
}

void btree::postorder(node *leaf) {
    if (leaf) {
        postorder(leaf->left);
        postorder(leaf->right);
        cout << leaf->key_value << " ";
    }
}

void btree::inorder() {
    if (is_empty()) {
        cout << "The tree is empty" << endl;
    }
    else {
        cout << "Inorder traversal: ";
        inorder(root);
    }}

void btree::preorder() {
    if (is_empty()) {
        cout << "The tree is empty" << endl;
    }
    else {
        cout << "Preorder traversal: ";
        preorder(root);
    }
}

void btree::postorder() {
    if (is_empty()) {
        cout << "The tree is empty" << endl;
    }
    else {
        cout << "Postorder traversal: ";
        postorder(root);
    }
}

vector<int> parse(const string &s) {
    vector<int> v;
    stringstream ss{s};
    int n;
    while (ss >> n || !ss.eof()) {
        if (ss.fail()) {
            ss.clear();
            ss.ignore(1);
            continue;
        }
        v.push_back(n);
    }
    if (v.empty()) cout << "ERROR: Invalid input" << endl;
    return v;
}

int main() {
    btree obj;
    int option, val, n;
    string values;
    vector<int> v;

    do {
        cout << endl << "................................." << endl;
        cout << "Select option number" << endl;
        cout << "1. Insert element(s)" << endl;
        cout << "2. Search element" << endl;
        cout << "3. Delete element" << endl;
        cout << "4. Delete all elements" << endl;
        cout << "5. Print tree" << endl;
        cout << "6. Iteration" << endl;
        cout << "7. Preorder traversal" << endl; //прямой
        cout << "8. Inorder traversal" << endl; //симметричный
        cout << "9. Postorder traversal" << endl; //обратный
        cout << "0. Exit Program" << endl;
        cout << "................................." << endl;

        cin >> option;

        switch (option) {
            case 0:
                break;
            case 1:
                cout << "Enter value(s) to INSERT: ";
                cin.clear();
                cin.sync();
                getline(cin, values);
                getline(cin, values);
                v = parse(values);
                for (auto el : v) obj.insert(el);
                break;
            case 2:
                cout << "Enter value to SEARCH: ";
                cin >> val;
                if (obj.search(val) != NULL) {
                    cout << "Element with this value exists" << endl;
                }
                else {
                    cout << "There is NO element with this value" << endl;
                }
                break;
            case 3:
                cout << "Enter value to DELETE: ";
                cin >> val;
                if (obj.is_empty()) {
                    cout << "ERROR: The tree is empty, nothing to delete" << endl;
                }
                else {
                    if (obj.search(val) != NULL) {
                        obj.delete_node(val);
                        cout << "Value was deleted" << endl;
                    }
                    else {
                        cout << "ERROR: Value NOT found" << endl;
                    }
                }
                break;
            case 4:
                if (obj.is_empty()) {
                    cout << "ERROR: the tree has already been cleared" << endl;
                }
                else {
                    obj = btree();
                    cout << "All elements were deleted" << endl;
                }
                break;
            case 5:
                obj.print();
                break;
            case 6:
                cout << "Enter value to ITERATE: ";
                cin >> val;
                node* res;
                if (obj.is_empty()) cout << "ERROR: The tree is empty" << endl;
                else if (!cin.good()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Element must be int" << endl;
                }
                else {
                    if (!obj.search(val)) {
                        cout << "ERROR: There is NO element with this value" << endl;
                    }
                    else {
                        res = obj.iteration(val);
                        res == nullptr ? cout << "Next element is undefined" << endl : cout << res->key_value << endl;
                    }
                }
                break;
            case 7:
                obj.preorder();
                cout << endl;
                break;
            case 8:
                obj.inorder();
                cout << endl;
                break;
            case 9:
                obj.postorder();
                cout << endl;
                break;
            default:
                cout << "Enter proper option number" << endl;
        }

    } while (option != 0);

    return 0;
}