#include "btree.h"
using namespace std;

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
                v = obj.parse(values);
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