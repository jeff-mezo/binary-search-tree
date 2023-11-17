/* 
    BINARY SEARCH TREE
    Venmark Recla | Jeffer John Mezo
*/
#include <iostream>

using namespace std;

struct Node{ // Struct for tree Node
    int key;
    int count;
    struct Node *left, *right; // Points to left and right child nodes

    Node(){ // Default constructor
        left = NULL;
        right = NULL;
        count = 0;
    }

    Node(int val){ // Constructor with value
        key = val;
        left = NULL;
        right = NULL;
        count = 0;
    }
};

struct Node* newNode(int key) { // Creates new node
    struct Node* newNode = new Node(key); 
    return newNode;
}

struct Node* inOrderTraverse(Node* root) {  // In-order traversal and prints each node
    if(root == NULL) {
        return root;
    }

    inOrderTraverse(root->left);
    cout << root->key << " ";
    inOrderTraverse(root->right);
    return root;
}

struct Node* preOrderTraverse(Node *root) { // Pre-order traversal
    if (root == NULL) {
        return root;
    }

    cout << root->key << " ";
    preOrderTraverse(root->left);
    preOrderTraverse(root->right);
    return root;
}

struct Node* postOrderTraverse(Node *root) { // Post-order traversal
    if (root == NULL) {
        return root;
    }

    postOrderTraverse(root->left);
    postOrderTraverse(root->right);
    cout << root->key << " ";
    return root;
}

struct Node* insert(Node* root, int key){ // Insert a new node with the given key
    //If tree is empty, return a new node
    if(root == NULL) {
        root = newNode(key);
        return root;
    }

    //Else, recur down the tree
    if(key < root->key) {
        root->left = insert(root->left, key);
    } 
    else if(key > root->key) {
        root->right = insert(root->right, key);
    }

    //Return the node pointer 
    return root;
}

struct Node* deleteBranch(Node*& root) { // Delete the entire branch starting from the given root
    if (root == nullptr) {
        return nullptr;
    }
    deleteBranch(root->left);
    deleteBranch(root->right);
    delete root;
    return nullptr;
}

struct Node* deleteNode(Node* root, int key) { // Delete a specific node and its branches 
    if (root == nullptr) {
        return nullptr;
    }
    if (root->key > key) {
        root->left = deleteNode(root->left, key);
    } else if (root->key < key) {
        root->right = deleteNode(root->right, key);
    } else {
        root = deleteBranch(root);
    }

    return root;
}

struct Node* Search(Node* root, int key) { // Searches given key in the tree

    if(root == NULL) {
        return root;
    }

    // Traverse the tree 
    if(key == root->key) {
        return root;
    } else if(key < root->key) {
        root = Search(root->left, key);
    } else if(key > root->key) {
        root = Search(root->right, key);
    }

    return root;

}

struct Node* findMaximum(Node* root) { // Finds node with the maximum value
    if(root == NULL) {
        return root;
    } else if(root->right != NULL) {
        root = findMaximum(root->right);
    }

    return root;
}

struct Node* findMinimum(Node* root) { // Finds node with the minimum value
    if(root == NULL) {
        return root;
    } else if(root->left != NULL) {
        root = findMinimum(root->left);
    }

    return root;
}

struct Node *findSuccessor(Node *root, int key) // Find successor of a node
{
    Node *current = Search(root, key);
    if (current == NULL)
    {
        cout << "Item not found.\n";
        return NULL;
    }

    // Case 1: Node has a right subtree
    if (current->right != NULL)
    {
        return findMinimum(current->right);
    }

    // Case 2: Node does not have a right subtree
    Node *successor = NULL;
    Node *ancestor = root;

    while (ancestor != current)
    {
        if (current->key < ancestor->key)
        {
            successor = ancestor;
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }

    return successor;
}

struct Node *findPredecessor(Node *root, int key) // Find predecessor of a node
{
    Node *current = Search(root, key);
    if (current == NULL)
    {
        cout << "Item not found.\n";
        return NULL;
    }

    // Case 1: Node has a left subtree
    if (current->left != NULL)
    {
        return findMaximum(current->left);
    }

    // Case 2: Node does not have a left subtree
    Node *predecessor = NULL;
    Node *ancestor = root;

    while (ancestor != current)
    {
        if (current->key > ancestor->key)
        {
            predecessor = ancestor;
            ancestor = ancestor->right;
        }
        else
        {
            ancestor = ancestor->left;
        }
    }

    return predecessor;
}


// MAIN CODE
int main() {
    struct Node* root = NULL;
    struct Node* temp = NULL; // temporary node for storing returns of functions
    int choice = 1;
    int key;

    while(choice != 0) {
        cout << "Binary Search Tree\n [1] Insert Item\n [2] Delete Item\n [3] Search Item\n [4] Find Maximum\n [5] Find Minimum\n [6] Find Successor\n [7] Find Predecessor\n [8] Display Tree\n [0] Exit\n\nChoice: ";
        cin >> choice;
        system("cls");
        switch(choice){
            case 1: // INSERT
            {
                cout << "Enter Tree Data: ";
                cin >> key;

                root = insert(root, key);
                system("cls"); 

                cout << "Tree(Inorder Traversal): ";
                inOrderTraverse(root);
                cout << "\n\n";
            }
            break;

            case 2: // DELETE
                {    
                    if(root == NULL) {
                        cout << "Tree is Empty!\n\n";
                        break;
                    }

                    cout << "Tree(Inorder Traversal): ";
                    inOrderTraverse(root);
                    cout << "\n\n";
                    
                    cout << "Enter data to delete: ";
                    cin >> key;
                    if(Search(root, key)) {
                        system("cls");
                        root = deleteNode(root, key);
                        if(root != NULL) cout << "Node " << key << " deleted.\n\n";
                        else cout << "Tree is now empty.\n\n";
                    } else {
                        system("cls");
                        cout << "Item " << key << " not found.\n\n";
                    }  
                }
            break;

            case 3: // SEARCH
            {
                if(root == NULL) {
                    cout << "Tree is Empty!\n\n";
                    break;
                }
                int item;
                cout << "Enter Item to Search: ";
                cin >> item;
                system("cls");
                if(Search(root, item)) {
                    cout << "Item " << item << " is in the Tree.\n\n";
                } else {
                    cout << "Item " << item << " not found.\n\n";
                }
            }
            break;

            case 4: // MAXIMUM
                if(root == NULL) cout << "Tree is Empty!\n\n";
                else cout << "Maximum Item in Tree: " << findMaximum(root)->key << "\n\n";
            break;

            case 5: // MINIMUM
                if(root == NULL) cout << "Tree is Empty!\n\n";
                else cout << "Minimum Item in Tree: " << findMinimum(root)->key << "\n\n";
            break;

           case 6: // FIND SUCCESSOR
            {
                if (root == NULL)
                    cout << "Tree is Empty!\n\n";

                else {
                    int item;
                    cout << "Enter Item to Find Successor: ";
                    cin >> item;
                    Node *successor = findSuccessor(root, item);

                    if (successor)
                        cout << "Successor of " << item << ": " << successor->key << "\n\n";
                }
            }
            break;

            case 7: // FIND PREDECESSOR
            {
                if (root == NULL)
                    cout << "Tree is Empty!\n\n";
                else {
                    int item;
                    cout << "Enter Item to Find Predecessor: ";
                    cin >> item;
                    Node *predecessor = findPredecessor(root, item);

                    if (predecessor)
                        cout << "Predecessor of " << item << ": " << predecessor->key << "\n\n";
                }
            }
            break;

            case 8: // DISPLAY
            {
                if(root == NULL) cout << "Tree is Empty!\n\n";
                else 
                {
                    int c;
                    cout << "Choose Traversal Method: \n [1] Inorder\n [2] Pre-order\n [3] Post-Order\nChoice: ";
                    cin >> c;
                    system("cls");
                    switch (c)
                    {
                    case 1:
                        cout << "Inorder Tree: ";
                        inOrderTraverse(root);
                        cout << "\n\n";
                        break;
                    
                    case 2:
                        cout << "Pre-Order Tree: ";
                        preOrderTraverse(root);
                        cout << "\n\n";
                        break;

                    case 3:
                        cout << "Post-Order Tree: ";
                        postOrderTraverse(root);
                        cout << "\n\n";
                        break;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
            break;

            default:
            break;
        }
    }

    return 0;
}