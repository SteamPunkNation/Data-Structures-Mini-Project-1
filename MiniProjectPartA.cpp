#include <iostream>
#include <vector>

//Node class
class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node *parent;
    int key;

    Node() {
        data = 0;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        key = 0;
    }

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        key = 0;
    }
};

//Prototypes
Node *Rebalance(Node *N);

//Functions
//BSTFunctions.cpp
void inorder(Node *currentPtr) {
    if (currentPtr != nullptr) {
        inorder(currentPtr->left); // Go Left.
        std::cout << " " << currentPtr->data; // Print the root.
        inorder(currentPtr->right); // Go Right.
    }
}

Node *insert(Node *root, Node *element) {
    // Inserting into an empty tree.
    if (root == nullptr) {
        return element;
    } else {
        //element should be inserted to the right.
        if (element->data > root->data) {
            //There is a right subtree to insert the node.
            if (root->right != nullptr)
                root->right = insert(root->right, element);
                //Place the node directly to the right of root.
            else
                root->right = element;
        }
            //element should be inserted to the left.
        else {
            //There is a left subtree to insert the node.
            if (root->left != nullptr)
                root->left = insert(root->left, element);
                //Place the node directly to the left of root.
            else
                root->left = element;
        }
        //Return the root pointer of the updated tree.
        return root;
    }
}

int add(Node *currentPtr) {
    if (currentPtr != nullptr)
        return currentPtr->data + add(currentPtr->left) +
               add(currentPtr->right);
    else
        return 0;
}

int find(Node *currentPtr, int val) {
    //Check if there are nodes in the tree.
    if (currentPtr != nullptr) {
        //Found the value at the root.
        if (currentPtr->data == val)
            return 1;
        //Search to the left.
        if (val < currentPtr->data)
            return find(currentPtr->left, val);
            //Or search to the right.
        else
            return find(currentPtr->right, val);
    } else
        return 0;
}

// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, nullptr will be returned.
Node *parent(Node *root, Node *node) {
    // Take care of nullptr cases.
    if (root == nullptr || root == node)
        return nullptr;
    // The root is the direct parent of node.
    if (root->left == node || root->right == node)
        return root;
    // Look for node's parent on the left side of the tree.
    if (node->data < root->data)
        return parent(root->left, node);
        // Look for node's parent on the right side of the tree.
    else if (node->data > root->data)
        return parent(root->right, node);
    return nullptr; // For any other cases.
}

Node *minVal(Node *root) {
    //Root stores the minimal value.
    if (root->left == nullptr)
        return root;
        //The left subtree of the root stores the minimal value.
    else
        return minVal(root->left);
}

Node *maxVal(Node *root) {
    //Root stores the maximal value.
    if (root->right == nullptr)
        return root;
        //The right subtree of the root stores the maximal value.
    else
        return maxVal(root->right);
}

//Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(Node *node) {
    return (node->left == nullptr && node->right == nullptr);
}

//Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(Node *node) {
    return (node->left != nullptr && node->right == nullptr);
}

//Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(Node *node) {
    return (node->left == nullptr && node->right != nullptr);
}

//Returns a pointer to a node that stores value in it in the subtree
Node *findNode(Node *currentPtr, int value) {
    // Check if there are nodes in the tree.
    if (currentPtr != nullptr) {
        //Found the value at the root.
        if (currentPtr->data == value)
            return currentPtr;
        //Search to the left.
        if (value < currentPtr->data)
            return findNode(currentPtr->left, value);
            //Or search to the right.
        else
            return findNode(currentPtr->right, value);
    } else
        return nullptr; // No node found.
}

//Will delete the node storing value in the tree rooted at root. The
//value must be present in the tree in order for this function to work.
//The function returns a pointer to the root of the resulting tree.
Node *deleteNode(Node *root, int value) {
    Node *delnode, *newDelNode, *saveNode;
    Node *par;
    int saveVal;

    delnode = findNode(root, value); // Get a pointer to the node to delete.

    par = parent(root, delnode); // Get the parent of this node.

    //Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode)) {// case 1

        //Deleting the only node in the tree.
        if (par == nullptr) {
            delete root; // free the memory for the node.
            return nullptr;
        }

        //Deletes the node if it's a left child.
        if (value < par->data) {
            delete par->left; // Free the memory for the node.
        }

            //Deletes the node if it's a right child.
        else {
            delete par->right; // Free the memory for the node.
            par->right = nullptr;
        }

        return root; //Return the root of the new tree.
    }

    //Take care of the case where the node to be deleted only has a left
    //child.
    if (hasOnlyLeftChild(delnode)) {

        //Deleting the root node of the tree.
        if (par == nullptr) {
            saveNode = delnode->left;
            delete delnode; //Free the node to delete.
            return saveNode; //Return the new root node of the resulting tree.
        }

        // Deletes the node if it's a left child.
        if (value < par->data) {
            saveNode = par->left; //Save the node to delete.
            par->left = par->left->left; //Readjust the parent pointer.
            delete saveNode; //Free the memory for the deleted node.
        }

            //Deletes the node if it's a right child.
        else {
            saveNode = par->right; //Save the node to delete.
            par->right = par->right->left; //Readjust the parent pointer.
            delete saveNode; //Free the memory for the deleted node.
        }

        return root; //Return the root of the tree after the deletion.
    }

    //Takes care of the case where the deleted node only has a right child.
    if (hasOnlyRightChild(delnode)) {

        //Node to delete is the root node.
        if (par == nullptr) {
            saveNode = delnode->right;
            delete delnode;
            return saveNode;
        }

        //Delete the node if it is a left child.
        if (value < par->data) {
            saveNode = par->left;
            par->left = par->left->right;
            delete saveNode;
        }

            //Delete the node if it is a right child.
        else {
            saveNode = par->right;
            par->right = par->right->right;
            delete saveNode;
        }
        return root;
    }
//when del node has two children
    //Find the new physical node to delete.
    newDelNode = minVal(delnode->right);
    saveVal = newDelNode->data;

    deleteNode(root, saveVal);  //Now, delete the proper value.

    //Restore the data to the original node to be deleted.
    delnode->data = saveVal;

    return root;
}

//PPT Functions

//Helper function to move to the next node in an inorder traversal.
Node *Next(Node *root, int value) {
    Node *current = root;
    Node *next = nullptr;

    while (current != nullptr) {
        if (current->data > value) {
            next = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return next;
}


// Check if a node is unbalanced.
bool IsUnbalanced(Node *N) {
    if (N == nullptr) {
        return false;
    } else if (N->data < -1 || N->data > 1) {
        return true;
    } else {
        return IsUnbalanced(N->left) || IsUnbalanced(N->right);
    }
}


//Helper function to compute the height of each node in the tree.
int ComputeHeight(Node *x) {
    if (x == nullptr)
        return 0;
    else {
        int leftHeight = ComputeHeight(x->left);
        int rightHeight = ComputeHeight(x->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
}


//Helper function to compute the balance factor of each node in the tree.
int ComputeBF(Node *X) {
    int leftHeight = (X->left != nullptr) ? X->left->data : -1;
    int rightHeight = (X->right != nullptr) ? X->right->data : -1;
    X->data = leftHeight - rightHeight;
    return X->data;
}

// Adjust the height of a node.
void AdjustHeight(Node *N) {
    ComputeHeight(N);
    ComputeBF(N);
    if (IsUnbalanced(N)) {
        Rebalance(N);
    }
}

//Helper function to perform a right rotation on node x.
Node *RotateRight(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    y->right = x;
    //Update the heights of x and y.
    AdjustHeight(x);
    AdjustHeight(y);
    //Return the new root of the subtree.
    return y;
}

//Helper function to perform a left rotation on node x.
Node *RotateLeft(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    //Update the heights of x and y.
    AdjustHeight(x);
    AdjustHeight(y);
    //Return the new root of the subtree.
    return y;
}

//Helper function to rebalance the tree at node N.
Node *Rebalance(Node *N) {
    if (N == nullptr)
        return nullptr;
    if (N->data < -1) {
        if (N->right != nullptr && N->right->data > 0)
            N->right = RotateRight(N->right);
        N = RotateLeft(N);
    } else if (N->data > 1) {
        if (N->left != nullptr && N->left->data < 0)
            N->left = RotateLeft(N->left);
        N = RotateRight(N);
    }
//Update the heights and balance factors of each node.
    ComputeHeight(N);
    ComputeBF(N);
//Return the new root of the subtree.
    return N;
}

//Helper function to insert an element in an AVL tree.
Node *Insert(int k, Node *R) {
    Node *element = new Node(k);
    if (R == nullptr)
        R = element;
    else {
//Insert element into the BST.
        R = insert(R, element);
//Update the height and balance factors of each node.
        ComputeHeight(R);
        ComputeBF(R);
//Check if the tree is unbalanced.
        if (IsUnbalanced(R)) {
//Fix the unbalanced tree.
            R = Rebalance(R);
        }
    }
    return R;
}


// Rebalance the right subtree of a node.
void RebalanceRight(Node *N) {
    if (N->right != nullptr) {
        Rebalance(N->right);
    }
}

// Rebalance the left subtree of a node.
void RebalanceLeft(Node *N) {
    if (N->left != nullptr) {
        Rebalance(N->left);
    }
}

// Find the left descendant of a node.
Node *LeftDescendant(Node *N) {
    if (N->left == nullptr) {
        return nullptr;
    } else {
        Node *temp = N->left;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }
}

// Find the right ancestor of a node.
Node *RightAncestor(Node *N) {
    if (N == nullptr) {
        return nullptr;
    } else if (N->parent == nullptr) {
        return nullptr;
    } else if (N == N->parent->left) {
        return N->parent;
    } else {
        return RightAncestor(N->parent);
    }
}

// Find a node in the AVL tree with the given key, within the range of [x, y].
Node *FindSearch(int x, int y, Node *N) {
    if (N == nullptr) {
        return nullptr;
    }
    if (N->key >= x && N->key <= y) {
        return N;
    }
    if (N->key < x) {
        return FindSearch(x, y, N->right);
    }
    if (N->key > y) {
        return FindSearch(x, y, N->left);
    }
    return nullptr;
}

Node *AVLDelete(int k, Node *R) {
    // Step 1: Find the node to be deleted.
    Node *toDelete = FindSearch(k, k, R);
    if (toDelete == nullptr) {
        return R; // Key not found.
    }
    // Step 2: If the node has no children.
    if (toDelete->left == nullptr && toDelete->right == nullptr) {
        if (toDelete == R) {
            R = nullptr; // Deleting root node.
        } else if (toDelete->parent->left == toDelete) {
            toDelete->parent->left = nullptr;
        } else {
            toDelete->parent->right = nullptr;
        }
        delete toDelete;
        return R;
    }
    // Step 3: If the node has one child.
    if (toDelete->left == nullptr) {
        if (toDelete == R) {
            R = toDelete->right; // Deleting root node.
        } else if (toDelete->parent->left == toDelete) {
            toDelete->parent->left = toDelete->right;
        } else {
            toDelete->parent->right = toDelete->right;
        }
        toDelete->right->parent = toDelete->parent;
        delete toDelete;
        AdjustHeight(toDelete->right);
        RebalanceRight(toDelete->right);
        return R;
    } else if (toDelete->right == nullptr) {
        if (toDelete == R) {
            R = toDelete->left; // Deleting root node.
        } else if (toDelete->parent->left == toDelete) {
            toDelete->parent->left = toDelete->left;
        } else {
            toDelete->parent->right = toDelete->left;
        }
        toDelete->left->parent = toDelete->parent;
        delete toDelete;
        AdjustHeight(toDelete->left);
        RebalanceLeft(toDelete->left);
        return R;
    }
    // Step 4: If the node has two children.
    Node *successor = LeftDescendant(toDelete->right);
    toDelete->key = successor->key;
    toDelete->data = successor->data;
    if (successor->parent->left == successor) {
        successor->parent->left = successor->right;
    } else {
        successor->parent->right = successor->right;
    }
    if (successor->right != nullptr) {
        successor->right->parent = successor->parent;
    }
    delete successor;
    AdjustHeight(toDelete);
    RebalanceRight(toDelete->right);
    return R;
}

void inorderRange(Node *node, int x, int y) {
    if (node == nullptr) {
        return;
    }
    if (node->data > x) {
        inorderRange(node->left, x, y);
    }
    if (node->data >= x && node->data <= y) {
        std::cout << node->data << " ";
    }
    if (node->data < y) {
        inorderRange(node->right, x, y);
    }
}

int addRange(Node *node, int x, int y) {
    if (node == nullptr) {
        return 0;
    }
    if (node->data < x) {
        return addRange(node->right, x, y);
    }
    if (node->data <= y) {
        return node->data + addRange(node->left, x, y) + addRange(node->right, x, y);
    }
    return addRange(node->left, x, y);
}

//TODO
// Main
//int main() {
//    Node *root = nullptr;
//
//    root = insert(root, new Node(5));
//    root = insert(root, new Node(3));
//    root = insert(root, new Node(7));
//    root = insert(root, new Node(1));
//    root = insert(root, new Node(9));
//
//    std::cout << "Inorder traversal of the BST: ";
//    inorder(root);
//    std::cout << std::endl;
//
//    int sum = add(root);
//    std::cout << "Sum of all elements in the BST: " << sum << std::endl;
//
//    int value = 3;
//    Node *nextNode = Next(root, value);
//    if (nextNode != nullptr) {
//        std::cout << "Next element of " << value << " is " << nextNode->data << std::endl;
//    } else {
//        std::cout << "Next element of " << value << " not found in the BST" << std::endl;
//    }
//
//    int x = 1;
//    int y = 7;
//    std::cout << "Elements between " << x << " and " << y << ": ";
//    inorderRange(root, x, y);
//    std::cout << std::endl;
//
//    int height = ComputeHeight(root);
//    std::cout << "Height of the tree is " << height << std::endl;
//
//    int rangeSum = addRange(root, x, y);
//    std::cout << "Sum of elements between " << x << " and " << y << ": " << rangeSum << std::endl;
//
//    std::cout << "Inorder traversal of the BST: ";
//    inorder(root);
//    std::cout << std::endl;
//
//    int deleteValue = 5;
//    Node *nodeToDelete = findNode(root, deleteValue);
//    if (nodeToDelete != nullptr) {
//        std::cout << "Deleting node with value " << nodeToDelete->data << std::endl;
//        root = deleteNode(root, nodeToDelete->data);
//    }
//
//    std::cout << "Inorder traversal of the BST after deleting a node: ";
//    inorder(root);
//    std::cout << std::endl;
//
//    return 0;
//}

int main() {
    Node *root = nullptr;

    int choice = 0;
    while (choice != 10) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Insert an item into your tree\n";
        std::cout << "2. Delete an item from your tree\n";
        std::cout << "3. Search for an item in our tree\n";
        std::cout << "4. Print the sum of the nodes of the tree\n";
        std::cout << "5. Print the next element of the node with key x\n";
        std::cout << "6. Print the elements between x, and y\n";
        std::cout << "7. Print the height of the tree with root x\n";
        std::cout << "8. Print the sum of the list of elements between x, and y.\n";
        std::cout << "9. Print out the tree in an in-order traversal\n";
        std::cout << "10. Exit\n\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                root = insert(root, new Node(value));
                break;
            }
            case 2: {
                int value;
                std::cout << "Enter value to delete: ";
                std::cin >> value;
                Node *nodeToDelete = findNode(root, value);
                if (nodeToDelete != nullptr) {
                    root = deleteNode(root, nodeToDelete->data);
                    std::cout << "Node with value " << value << " deleted from tree.\n";
                } else {
                    std::cout << "Node with value " << value << " not found in tree.\n";
                }
                break;
            }
            case 3: {
                int value;
                std::cout << "Enter value to search for: ";
                std::cin >> value;
                Node *node = findNode(root, value);
                if (node != nullptr) {
                    std::cout << "Node with value " << value << " found in tree.\n";
                } else {
                    std::cout << "Node with value " << value << " not found in tree.\n";
                }
                break;
            }
            case 4: {
                int sum = add(root);
                std::cout << "Sum of all elements in the BST: " << sum << std::endl;
                break;
            }
            case 5: {
                int value;
                std::cout << "Enter value to find the next element of: ";
                std::cin >> value;
                Node *nextNode = Next(root, value);
                if (nextNode != nullptr) {
                    std::cout << "Next element of " << value << " is " << nextNode->data << std::endl;
                } else {
                    std::cout << "Next element of " << value << " not found in the BST" << std::endl;
                }
                break;
            }
            case 6: {
                int x, y;
                std::cout << "Enter x and y: ";
                std::cin >> x >> y;
                std::cout << "Elements between " << x << " and " << y << ": ";
                inorderRange(root, x, y);
                std::cout << std::endl;
                break;
            }
            case 7: {
                int x;
                std::cout << "Enter root value: ";
                std::cin >> x;
                int height = ComputeHeight(findNode(root, x));
                std::cout << "Height of tree with root " << x << ": " << height << std::endl;
                break;
            }
            case 8: {
                int x, y, sum;
                std::cout << "Enter x and y: ";
                std::cin >> x >> y;
                sum = addRange(root, x, y);
                std::cout << "Sum of elements between " << x << " and " << y << ": " << sum << std::endl;
                break;
            }
                // Print the tree in an in-order traversal
            case 9: {
                std::cout << "In-order traversal of the BST: ";
                inorder(root);
                std::cout << std::endl;
                break;
            }
            case 10: {
                std::cout << "Exiting program...\n";
                exit(0);
            }
        }
    }
}