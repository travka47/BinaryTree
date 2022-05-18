#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

/////////////////////////////////////PARSER/////////////////////////////////////

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
    if (v.empty())
        cout << "ERROR: Invalid input" << endl;
    return v;
}

/////////////////////////////////////TRUNK/////////////////////////////////////
// Helper function to print branches of the binary tree

struct trunk {
    trunk *prev;
    string str;
    trunk(trunk *prev, string str) {
        this->prev = prev;
        this->str = str;
    }
};

void show_trunks(trunk *p) {
    if (p == nullptr) return;
    show_trunks(p->prev);
    cout << p->str;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////BINARY TREE/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

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
};

/////////////////////////////////////PRIVATE FUNCTIONS/////////////////////////////////////

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
    if (n->left == nullptr)
        return n;
    return min(n->left);
}

node *btree::delete_node(int value, node *node) {
    if (node == nullptr)
        return node;

    if (value < node->key_value)
        node->left = delete_node(value, node->left);
    else
        if (value > node->key_value)
            node->right = delete_node(value, node->right);
    else
        if (node->right != nullptr && node->left != nullptr) {
            node->key_value = min(node->right)->key_value;
            node->right = delete_node(node->key_value, node->right);
        }
    else {
        if (node->left != nullptr)
            node = node->left;
        else
            if (node->right != nullptr)
                node = node->right;
            else
                node = nullptr;
    }

    return node;
}

void btree::print(node* root, trunk *prev, bool is_left) {
    if (root == nullptr)
        return;

    string prev_str = "    ";
    trunk *tr = new trunk(prev, prev_str);

    print(root->right, tr, true);

    if (!prev)
        tr->str = "———";
    else {
        if (is_left) {
            tr->str = ".———";
            prev_str = "   |";
        }
        else {
            tr->str = "`———";
            prev->str = prev_str;
        }
    }

    show_trunks(tr);
    cout << " " << root->key_value << endl;

    if (prev)
        prev->str = prev_str;
    tr->str = "   |";

    print(root->left, tr, false);
}

node *btree::iteration(int key, node *leaf) {
    node* current = root;
    node* successor = nullptr;
    while (current != nullptr) {
        if (key < current->key_value) {
            successor = current;
            current = current->left;
        }
        else
            current = current->right;
    }
    return successor;
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

bool btree::base_check() {
    if (!cin.good()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Invalid input" << endl;
        return false;
    }
    if (is_empty()) {
        cout << "ERROR: The tree is empty" << endl;
        return false;
    }
    return true;
}

/////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////

btree::btree() {
    root=NULL;
}

bool btree::is_empty() {
    return root == NULL;
}

void btree::insert(int key) {
    if (search(key, root) == NULL) {
        if(root!=NULL)
            insert(key, root);
        else {
            root=new node;
            root->key_value=key;
            root->left=NULL;
            root->right=NULL;
        }
    }
    else
        cout << "ERROR: Element with value " << key << " already exists in the tree" << endl;
}

void btree::search(int key) {
    if (base_check()) {
        if (!search(key, root))
            cout << "There is NO element with this value" << endl;
        else
            cout << "Element with this value exists" << endl;
    }
}

void btree::delete_node(int value) {
    if (base_check()) {
        if (!search(value, root))
            cout << "ERROR: Value NOT found" << endl;
        else {
            root = delete_node(value, root);
            cout << "Value was deleted" << endl;
        }
    }
}

btree btree::delete_all(btree obj) {
    if (is_empty())
        cout << "ERROR: The tree has already been cleared" << endl;
    else {
        obj = btree();
        cout << "All elements were deleted" << endl;
    }
    return obj;
}

void btree::print() {
    if (is_empty())
        cout << "The tree is empty" << endl;
    else
        print(root, nullptr, false);
}

void btree::iteration(int key) {
    node* res;
    if (base_check()) {
        if (!search(key, root))
            cout << "ERROR: There is NO element with this value" << endl;
        else {
            res = iteration(key, root);
            res == nullptr ? cout << "Next element is undefined" << endl : cout << "Next value: " << res->key_value << endl;
        }
    }
}

void btree::inorder() {
    if (is_empty())
        cout << "The tree is empty" << endl;
    else {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }
}

void btree::preorder() {
    if (is_empty())
        cout << "The tree is empty" << endl;
    else {
        cout << "Preorder traversal: ";
        preorder(root);
        cout << endl;
    }
}

void btree::postorder() {
    if (is_empty())
        cout << "The tree is empty" << endl;
    else {
        cout << "Postorder traversal: ";
        postorder(root);
        cout << endl;
    }
}

/////////////////////////////////////MAIN/////////////////////////////////////

int main() {
    btree obj;
    int option, val;
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
        cout << "7. Preorder traversal" << endl; //прямой обход
        cout << "8. Inorder traversal" << endl; //симметричный обход
        cout << "9. Postorder traversal" << endl; //обратный обход
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
                for (auto el : v)
                    obj.insert(el);
                break;
            case 2:
                cout << "Enter value to SEARCH: ";
                cin >> val;
                obj.search(val);
                break;
            case 3:
                cout << "Enter value to DELETE: ";
                cin >> val;
                obj.delete_node(val);
                break;
            case 4:
                obj = obj.delete_all(obj);
                break;
            case 5:
                obj.print();
                break;
            case 6:
                cout << "Enter value to ITERATE: ";
                cin >> val;
                obj.iteration(val);
                break;
            case 7:
                obj.preorder();
                break;
            case 8:
                obj.inorder();
                break;
            case 9:
                obj.postorder();
                break;
            default:
                cout << "Enter proper option number" << endl;
        }

    } while (option != 0);

    return 0;
}