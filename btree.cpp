#include "btree.h"

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

void btree::show_trunks(trunk *p) {
    if (p == nullptr) return;
    show_trunks(p->prev);
    cout << p->str;
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

vector<int> btree::parse(const string &s) {
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
