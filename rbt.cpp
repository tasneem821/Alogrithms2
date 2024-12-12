#include <iostream>
#include <algorithm>
using namespace std;
enum Color { RED, BLACK };

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int data) : data(data), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    Node* root;

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

    Node* insertBST(Node* root, Node* node) {
        if (!root) return node;

        if (node->data < root->data) {
            root->left = insertBST(root->left, node);
            root->left->parent = root;
        } else if (node->data > root->data) {
            root->right = insertBST(root->right, node);
            root->right->parent = root;
        }

        return root;
    }

    Node* minValueNode(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

//    void fixDelete(Node* x) {
//        while (x != root && (x == nullptr || x->color == BLACK)) {
//            //the node I want to delete in the left to the parent
//            //so the brother in the right
//            if (x == x->parent->left) {
//                Node* sibling = x->parent->right;
//                //if the brother is RED
//                //rotation and recolor(parent,brother)
//                if (sibling->color == RED) {
//                    sibling->color = BLACK;
//                    x->parent->color = RED;
//                    leftRotate(x->parent);
//                    sibling = x->parent->right;//update sibling after rotation
//                }
//                    /* Brother is Black */
//                //if children of brother is black
//                //pass the problem to the parent(will take DB)
//                //if p is red->black
//                //if p is black -> DB
//                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
//                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
//                    sibling->color = RED;
//                    x = x->parent; // Propagate double black to parent
//                } else {
//                    //sibling's Right Child is Black, Left Child is Red
//                    //(the near is Red)
//                    //rotate and recolor(brother and child)
//                    //perform the case of(far Red)
//                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
//                        if (sibling->left) sibling->left->color = BLACK;
//                        sibling->color = RED;
//                        rightRotate(sibling);
//                        sibling = x->parent->right;
//                    }
//                    //after handle the near is red -> handle the far is red
//                    //rotate(parent,brother) , remove DB
//                    //recolor: parent->black
//                    // children of your brother->black
//                    // brother-> original color of the parent
//                    sibling->color = x->parent->color;
//                    x->parent->color = BLACK;
//                    if (sibling->right) sibling->right->color = BLACK;
//                    leftRotate(x->parent);
//                    x = root;
//                }
//                //x is right to the parent mirror the previous ):
//            } else {
//                Node* sibling = x->parent->left;
//
//                if (sibling->color == RED) {
//                    sibling->color = BLACK;
//                    x->parent->color = RED;
//                    rightRotate(x->parent);
//                    sibling = x->parent->left;
//                }
//
//                if ((!sibling->left || sibling->left->color == BLACK) &&
//                    (!sibling->right || sibling->right->color == BLACK)) {
//                    sibling->color = RED;
//                    x = x->parent;
//                } else {
//                    if (!sibling->left || sibling->left->color == BLACK) {
//                        if (sibling->right) sibling->right->color = BLACK;
//                        sibling->color = RED;
//                        leftRotate(sibling);
//                        sibling = x->parent->left;
//                    }
//
//                    sibling->color = x->parent->color;
//                    x->parent->color = BLACK;
//                    if (sibling->left) sibling->left->color = BLACK;
//                    rightRotate(x->parent);
//                    x = root;
//                }
//            }
//        }
//
//        if (x) x->color = BLACK;
//    }
//
//
//    Node* deleteBST(Node* root, int data) {
//        //if the tree is empty
//        //there is no thing to delete
//        if (root == nullptr) return root;
//        //search to find the node
//        if (data < root->data) {
//            root->left = deleteBST(root->left, data);
//        } else if (data > root->data) {
//            root->right = deleteBST(root->right, data);
//        } else {
//            //Case1:Node with no children
//            if (root->left == nullptr and root->right == nullptr) {
//                delete root;
//                root = nullptr;
//            }
//            //Case2: Node with only one child
//            else if (root->left == nullptr || root->right == nullptr)
//            {
//                Node* tmp;
//                if(root->left != nullptr )
//                {
//                    tmp = root->left;
//                }
//                else
//                {
//                    tmp = root->right;
//                }
//                *root = *tmp; //copy the content of the child to root
//                delete tmp; //delete the child(assume this case child is RED)
//
//            }
//                //Case3: Node with two children
//            else {
//                //get the inorder successor(smallest in the right subtree)
//                Node* temp = minValueNode(root->right);
//                //copy the inorder successor's data to this node
//                root->data = temp->data;
//                //delete the inorder successor
//                root->right = deleteBST(root->right, temp->data);
//            }
//        }
//
//        return root;
//    }
    void fixDelete(Node* x) {
        while (x != root && (x == nullptr || x->color == BLACK)) {
            if (x == x->parent->left) {
                Node* sibling = x->parent->right;

                // Case 4: If DB's sibling is red
                if (sibling->color == RED) {
                    sibling->color = BLACK; // Swap color of DB's parent with DB's sibling
                    x->parent->color = RED;
                    leftRotate(x->parent); // Perform rotation at parent node in the direction of DB node
                    sibling = x->parent->right;
                }

                // Case 3: If DB's sibling is black and its children are black
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED; // Make DB's sibling red
                    x = x->parent; // Move DB upwards
                } else {
                    // Case 5: DB's sibling is black and its far child is black, near child is red
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left) sibling->left->color = BLACK; // Swap color of sibling with its red child
                        sibling->color = RED;
                        rightRotate(sibling); // Perform rotation at sibling node in the opposite direction of DB
                        sibling = x->parent->right;
                    }

                    // Case 6: DB's sibling is black and its far child is red
                    sibling->color = x->parent->color; // Swap color of DB's parent with sibling's color
                    x->parent->color = BLACK;
                    if (sibling->right) sibling->right->color = BLACK; // Change color of sibling's far red child to black
                    leftRotate(x->parent); // Perform rotation at DB's parent in the direction of DB
                    x = root; // Remove DB sign and make the node normal black node
                }
            } else {
                Node* sibling = x->parent->left;

                // Case 4: If DB's sibling is red
                if (sibling->color == RED) {
                    sibling->color = BLACK; // Swap color of DB's parent with DB's sibling
                    x->parent->color = RED;
                    rightRotate(x->parent); // Perform rotation at parent node in the direction of DB node
                    sibling = x->parent->left;
                }

                // Case 3: If DB's sibling is black and its children are black
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED; // Make DB's sibling red
                    x = x->parent; // Move DB upwards
                } else {
                    // Case 5: DB's sibling is black and its far child is black, near child is red
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right) sibling->right->color = BLACK; // Swap color of sibling with its red child
                        sibling->color = RED;
                        leftRotate(sibling); // Perform rotation at sibling node in the opposite direction of DB
                        sibling = x->parent->left;
                    }

                    // Case 6: DB's sibling is black and its far child is red
                    sibling->color = x->parent->color; // Swap color of DB's parent with sibling's color
                    x->parent->color = BLACK;
                    if (sibling->left) sibling->left->color = BLACK; // Change color of sibling's far red child to black
                    rightRotate(x->parent); // Perform rotation at DB's parent in the direction of DB
                    x = root; // Remove DB sign and make the node normal black node
                }
            }
        }

        if (x) x->color = BLACK; // Ensure DB is removed and root becomes black if necessary
    }

    Node* deleteBST(Node* root, int data) {
        if (root == nullptr) return root;

        if (data < root->data) {
            root->left = deleteBST(root->left, data);
        } else if (data > root->data) {
            root->right = deleteBST(root->right, data);
        } else {
            // Case 1: Node to be deleted is a red leaf node
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr; // If null DB, delete the node
                } else {
                    *root = *temp; // Copy the content of the child node
                }

                delete temp;
            } else {
                // Node with two children, use inorder successor (minimum value in the right subtree)
                Node* temp = minValueNode(root->right);
                root->data = temp->data; // Replace data with inorder successor's data
                root->right = deleteBST(root->right, temp->data); // Delete the successor
            }
        }

        return root;
    }

public:
    RedBlackTree() : root(nullptr) {}

//    void insert(int data) {
//        Node* node = new Node(data);
//        root = insertBST(root, node);
//        fixInsert(node);
//    }
    void insert(int data) {
        //If tree is empty, create root node and color it black
        if (root == nullptr) {
            root = new Node(data);
            root->color = BLACK;
            return;
        }
        //If tree is not empty, create new node as leaf with color red
        //color red is default in the constructor
        Node* current = root;
        Node* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (data < current->data)
                current = current->left;
            else if (data > current->data)
                current = current->right;
            else
                return; // No duplicates allowed(equal nodes not allow)
        }

        Node* newNode = new Node(data);
        newNode->parent = parent;
        if (data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
        // If parent is black, we're done
        if (parent->color == BLACK)
            return;
        //Fix Red-Black Tree properties
        fixInsert(newNode);
    }

    void deleteNode(int data) {
        Node* nodeToDelete = deleteBST(root, data);
        if (nodeToDelete == nullptr) return;
        fixDelete(nodeToDelete);
    }


    void inorderTraversal(Node* node) {
        if (!node) return;
        inorderTraversal(node->left);
        cout << "Node: " << node->data << ", Color: "
             << (node->color == RED ? "RED" : "BLACK") << endl; // Prints node color
        inorderTraversal(node->right);
    }

    void display() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    RedBlackTree rbt;
    rbt.insert(8);
    rbt.insert(18);
    rbt.insert(5);
    rbt.insert(15);
    rbt.insert(17);
    rbt.insert(25);
    rbt.insert(40);
    rbt.insert(80);
/*********************/
    rbt.deleteNode(8);
    rbt.deleteNode(18);

/*****************/
//    rbt.insert(30);
//    rbt.insert(20);
//    rbt.insert(40);
//    rbt.insert(10);
//    rbt.deleteNode(10);
//    rbt.insert(50);
//    rbt.deleteNode(20);
/**************************/
//    rbt.insert(7);
//    rbt.insert(5);
//    rbt.insert(9);
//    rbt.insert(4);
//    rbt.insert(5);
//    rbt.insert(8);
//    rbt.insert(11);
//    rbt.insert(10);
//    rbt.insert(12);
    cout << "Inorder traversal of Red-Black Tree: " << endl;
    rbt.display();


    return 0;
}
