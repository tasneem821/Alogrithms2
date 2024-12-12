#include <iostream>
using namespace std;

enum Color { BLACK , RED };

struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
    Color color;
};

typedef Node* NodePtr;

class RedBlackTree {
private:
    NodePtr root;
    NodePtr TNULL;

    void fixDelete(NodePtr x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                NodePtr sibling = x->parent->right;
                // Case 4: If DB's sibling is red
                if (sibling->color == RED) {
                    sibling->color = BLACK;// Swap color of DB's parent with DB's sibling
                    x->parent->color = RED;
                    leftRotate(x->parent);// Perform rotation at parent node in the direction of DB node
                    sibling = x->parent->right;
                }
                // Case 3: If DB's sibling is black and its children are black
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;// Make DB's sibling red
                    x = x->parent;// Move DB upwards
                } else {
                    // Case 5: DB's sibling is black and its far child is black,
                    // near child is red
                    if (sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;// Swap color of sibling with its red child
                        sibling->color = RED;
                        rightRotate(sibling);// Perform rotation at sibling node in the opposite direction of DB
                        sibling= x->parent->right;
                    }
                    // Case 6: DB's sibling is black and its far child is red
                    sibling->color = x->parent->color;// Swap color of DB's parent with sibling's color
                    x->parent->color = BLACK;
                    sibling->right->color = BLACK;// Change color of sibling's far red child to black
                    leftRotate(x->parent);// Perform rotation at DB's parent in the direction of DB
                    x = root;// Remove DB sign and make the node normal black node
                }
            } else {   /*Mirror*/
                NodePtr sibling = x->parent->left;
                // Case 4: If DB's sibling is red
                if (sibling->color == RED) {
                    sibling->color = BLACK;// Swap color of DB's parent with DB's sibling
                    x->parent->color = RED;
                    rightRotate(x->parent);// Perform rotation at parent node in the direction of DB node
                    sibling = x->parent->left;
                }
                // Case 3: If DB's sibling is black and its children are black
                if (sibling->right->color == BLACK && sibling->right->color == BLACK) {

                    sibling->color = RED;// Make DB's sibling red
                    x = x->parent;// Move DB upwards
                } else {
                    // Case 5: DB's sibling is black and its far child is black, near child is red
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = x->parent->left;
                    }
                    // Case 6: DB's sibling is black and its far child is red
                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;  // Ensure DB is removed and root becomes black
    }

    // Replaces node  with another node in the tree
    void rbReplace(NodePtr node1, NodePtr node2) {
        if (node1->parent == nullptr) {
            root = node2;
        } else if (node1 == node1->parent->left) {
            node1->parent->left = node2;
        } else {
            node1->parent->right = node2; // If node1 is right child of its parent
        }
        node2->parent = node1->parent; //swap parents
    }

    // Deletes a node with the specified key
    void deleteNodeHelper(NodePtr node, int key) {
        NodePtr NodeToDelete = TNULL;
        NodePtr x, y;
       //search for the node that will delete
        while (node != TNULL) {
            if (node->data == key) {
                NodeToDelete = node;
            }
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        if (NodeToDelete == TNULL) {
            cout << "Key not found in the tree" << endl;
            return; // If node is not found
        }

        y = NodeToDelete;
        int y_original_color = y->color;
        //Case 1: Node to be deleted has one child in right
        if (NodeToDelete->left == TNULL) {
            x = NodeToDelete->right;
            rbReplace(NodeToDelete, NodeToDelete->right); // Replace deleted node with its right child
            // Case 2: Node to be deleted has one child in the left
        } else if (NodeToDelete->right == TNULL) {
            x = NodeToDelete->left;
            rbReplace(NodeToDelete, NodeToDelete->left); // Replace deleted node with its left child
        } else {
            //Case 3: Node will be delete has Two Children
            y = minValue(NodeToDelete->right); // Find the inorder successor
            y_original_color = y->color;
            x = y->right;
            //y->inorder successor of the deleteNode
            //x->child of y that will replace with y
            if (y->parent == NodeToDelete) {//if y is directly child of the NodeToDelete
                x->parent = y;
              /*  40(B)                                                                                          40(B)
                /    \                                                                                           /   \
              20(R)  60(B)    --delete 60-->  y=70 is direct child of 60  only -->                            20(R)  70(R)
                     /  \                                                                                             /
                 50(R)  70(R)                                                                                       50(R)

*/
            } else {
                rbReplace(y, y->right); // replace y's right child(remove y)
                y->right = NodeToDelete->right;//y place is used to place the deleted node
                y->right->parent = y;//update the parent of 70 such the example


     /*  40(Black)                                                                                  40(Black)
         /    \                                                                                     /    \
      20(Red)  60(Black)   --delete 60-->  y is 65 replace y with its right chid(null)          20(Red)   65(B)
              /    \                                                                                      /  \
           50(Red)  70(Black)                                                                         50(Red) 70(Black)
                    /
                    65(R)

                 * */
            }
            rbReplace(NodeToDelete, y); // Replace NodeToDelete with y
            y->left = NodeToDelete->left;
            y->left->parent = y;
            y->color = NodeToDelete->color; // Copy NodeToDelete's color ensure the color is the same
        }
        delete NodeToDelete;
        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }


    void fixInsert(Node* node) {
        Node* parent = nullptr;
        Node* grandparent = nullptr;

        while (node != root && node->color == RED && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;
            //if parent is the left child of the grandparent
            // the uncle is the right
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;

                if (uncle && uncle->color == RED) {
                    //Recolor
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;//move up to grandparent to recheck until the root
                } else { //uncle is black or null
                    //if the inserted node is right to the parent
                    if (node == parent->right) {
                        //Left-rotation required
                        leftRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    // Right-rotation required
                    rightRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;

                    /*   insert 25
                     *      30(B)             30(B)                        30(B)                       25(R)                     25(B)
                            /    \   -->     /   \  --left rotation-->     /   \ --right rotation-->   /   \    --swap color-->  /   \
                          20(R) 40(B)      20(R)  40(B)                 25(R)  40(B)                 20(R)  30(B)              20(R) 30(R)
                                             \                           /                                   \                         \
                                             25(R)                     20(R)                                 40(B)                    40(B)

                    */
                }
            } else {
                Node* uncle = grandparent->left;

                if (uncle && uncle->color == RED) {
                    //  Recolor
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        //  Right-rotation required
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Left-rotation required
                    leftRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        root->color = BLACK;
    }




public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    NodePtr minValue(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    Node* rightRotate(Node* y) { // y is the root
        Node* x = y->left;  // x is left to y
        Node* B = x->right; // beta(B) is the rigth sub tree of node x
        // gama which is the left subtree to node x will be the same
        // alpha which is the right subtree to node y will be same as it greater than x and y

        /*      y                    x
        *      / \                  /  \
        *      x  alpha    --->    gama  y
        *     /  \                      /  \
        *    gama  B                   B   alpha
        */
        //perform rotation
        x->right = y;
        y->left = B;

        //after rotation re-link the nodes
        if (B) B->parent = y;//if subtree Beta exist assign it to correct parent
        x->parent = y->parent;
        y->parent = x;
        //if the new root has no parent so it is a root of the tree
        if (!x->parent)
            root = x; //root point to it
            //if x->parent is not null and y was the left child of its parent
            // update the parent's left child to point to x
            //if y was the left child of its parent before the rotation.
        else if (x->parent->left == y)
            x->parent->left = x;
        else
            x->parent->right = x;
        //return the new root of the rotated subtree
        return x;
    }

    Node* leftRotate(Node* x) { // x is the root
        Node* y = x->right;// y is right to x
        Node* B = y->left;// B (beta) is left to y
        // alpha is subtree left to x and it will be the same as it small than x and x small than y (it is the smallest)
        // gama is subtree rigth to y and it will be same

        /*     x                     y
        *     /  \                  / \
        *  alpha  y    ---->       x   gama
                 / \              /  \
                B   gama       alpha  B
        */

        //perform rotation
        y->left = x;
        x->right = B;
        //after rotation re-link the nodes
        if (B) B->parent = x;
        y->parent = x->parent;
        x->parent = y;

        if (!y->parent)
            root = y;
        else if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;

        return y;
    }

    void insert(int data) {
        // Create a new node with the given data
        NodePtr node = new Node;
        node->parent = nullptr;  // has no parent
        node->data = data;
        node->left = TNULL;  // left is Nill empty child (sentinel value for empty nodes)
        node->right = TNULL;
        node->color = RED;  // The new node inserted is red
        NodePtr y = nullptr;  // to keep track of the parent node as we traverse
        NodePtr x = this->root;
        // Find the correct place for the new node in the tree(simple BS tree)
        while (x != TNULL) {  //loop until the nill nodes
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        node->parent = y;
        if (y == nullptr) {  //the tree was empty, so the new node becomes the root
            root = node;
        } else if (node->data < y->data) {  // If the new node's data is smaller, it goes to the left of y
            y->left = node;
        } else {
            y->right = node;
        }
        if (node->parent == nullptr) {  // If the new node is the root
            node->color = BLACK;  // The root always black
            return;
        }
        if (node->parent->parent == nullptr) {  //parent is the root
            return;
        }
        fixInsert(node);
    }


    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

    void inorderTraversal(Node* node) {
        if (node != TNULL) {
            inorderTraversal(node->left);
            cout << "Node: " << node->data << ", Color: "
                 << (node->color == RED ? "RED" : "BLACK") << endl;
            inorderTraversal(node->right);
        }
    }

    void display() {
        inorderTraversal(root);  // Perform in-order traversal to print the nodes in sorted order
        cout << endl;
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(10);
    rbt.insert(5);
    rbt.insert(1);
    rbt.insert(7);
    rbt.insert(20);
    rbt.insert(15);
    rbt.insert(30);
    rbt.insert(25);
    rbt.insert(40);
    rbt.display();
    cout << endl
    << "After deleting" << endl;
    rbt.deleteNode(15);
    rbt.display();
}
