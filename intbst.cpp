// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (root = nullptr) {
        return;
    }
    // Recursively delete all nodes
    clear(n->left);
    clear(n->right);
    delete n;
    
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (n->info == value) {
        return false;
    }

    if (value < n->info) {
        if(!n->left) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        
        else {
            return insert(value, n->left);
        }
    }

    else {
        if(!n-> right) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        else {
            return insert(value, n->right);
        }
    }
}
    
// print tree data pre-order
void IntBST::printPreOrder() const {
   printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == nullptr) return; 
    cout << n->info << " ";   
    printPreOrder(n->left);    
    printPreOrder(n->right);  
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr) return; 
    printPreOrder(n->left);   
    cout << n->info << " ";   
    printPreOrder(n->right);  
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr) return; 
    printPreOrder(n->left);    
    printPreOrder(n->right); 
    cout << n->info << " ";  
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root); // REPLACE THIS NON-SOLUTION
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr) {
        return 0;
    }

    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n == nullptr) {
        return 0;
    }

    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const {
    if (!n) {
        return nullptr;
    }
    
    if (value == n->info) {
        return n;
    }
    if (value < n->info) {
        return getNodeFor(value, n->left);
    }

    if (value > n->info) {
        return getNodeFor(value, n->right);
    }

    return nullptr;
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    Node* node = getNodeFor(value, root); 

    if (node != nullptr) {
        return true; 
    } 
    else {
        return false; 
    }
}


// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const {
   Node* node = getNodeFor(value, root);
    if (node == nullptr) {
        return nullptr; 
    }

    if (node->left != nullptr) {
        Node* current = node->left;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

// No Left
    Node* predecessor = node->parent;
    while (predecessor != nullptr && node == predecessor->left) {
        node = predecessor;
        predecessor = predecessor->parent;
    }
    return predecessor; 
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const {
    Node* predecessorNode = getPredecessorNode(value);
    if (predecessorNode != nullptr) {
        return predecessorNode->info;
    } 
    else {
        return 0; 
    }
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
     Node* node = getNodeFor(value, root);
    if (node == nullptr) {
        return nullptr; // Value not found
    }

    if (node->right != nullptr) {
        Node* current = node->right;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

// No right
    Node* successor = node->parent;
    while (successor != nullptr && node == successor->right) {
        node = successor;
        successor = successor->parent;
    }
    return successor; 
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* successorNode = getSuccessorNode(value);
    if (successorNode != nullptr) {
        return successorNode->info; 
    } 
    else {
        return 0;
    }
}
// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value) {
    Node* removal = getNodeFor(value, root);
    if (removal == nullptr) {
        return false; 
    }

    // No children 
    if (removal->left == nullptr && removal->right == nullptr) {
        if (removal->parent != nullptr) {
            if (removal == removal->parent->left) {
                removal->parent->left = nullptr;
            } else {
                removal->parent->right = nullptr;
            }
        } else {
            root = nullptr; 
        }
    }
    // One child
    else if (removal->left == nullptr || removal->right == nullptr) {
        Node* child = (removal->left != nullptr) ? removal->left : removal->right;
        if (removal->parent != nullptr) {
            if (removal == removal->parent->left) {
                removal->parent->left = child;
            } 
            else {
                removal->parent->right = child;
            }
        } 
        else {
            root = child; 
        }
        child->parent = removal->parent;
    }
    // Two children
    else {
        Node* successorNode = getSuccessorNode(value);
        removal->info = successorNode->info; 
        remove(successorNode->info);
        return true; // 
    }

    delete removal; 
    return true; 
}