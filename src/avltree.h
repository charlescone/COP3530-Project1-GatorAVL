#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;

class AVLTree {
    // Node struct within the tree.
    struct Node {
        // Initializing Variables
        std::string NAME;
        int ID;
        int balanceFactor = 0;
        Node* left;
        Node* right;
        // Constructors
        Node() : NAME(""), ID(0), left(nullptr), right(nullptr) {}
        Node(string& NAME, int ID) : NAME(NAME), ID(ID), left(nullptr), right(nullptr) {}
        Node(string& NAME, int ID, Node* left, Node* right) : NAME(NAME), ID(ID), left(left), right(right) {}
    };
    // Initialize root as null;
    Node* root = nullptr;
    //Private Functions:

    // Mutators
    Node* insertPrivate(Node* node, string NAME, int ID);
    Node* removeIDPrivate(Node* node, int ID);
    //Rotation Functions
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    // Accessors
    int getMaxHeight(Node* node);
    Node* findSuccessorNode(Node* node);
    Node* removeIDPrivate(Node* node, int ID, string &output);
    Node* searchIDPrivate(Node* node, int ID);
    Node* searchIDPrivate(Node* node, int ID, string& output);
    void printPreOrder(Node* node, vector<Node*>& nodes);
    void printPostOrder(Node* node, vector<Node*>& nodes);
    void printInorder(Node* node, vector<Node*>& nodes);
    void preOrderTraversal(Node* node, string name, vector<int>& nodes);
    void inOrderTraversal(Node* node, vector<Node*>& nodes);
    //Destructor Helper
    void destructorHelper(Node* node);

public:
    // Mutators
    void insert(string NAME, int ID);
    void remove(int ID);
    void removeInorder(int N);
    // Accessors
    void searchID(int ID);
    void searchName(string NAME);
    void inOrder(vector<int>& IDS);
    void preOrder(vector<int>& nodeList);
    void postOrder();
    void printLevelCount();
    //Unit Testing Functions
    string validateInsert(string input);
    string validateSearchID(string input);
    string validateSearchName(string input);
    string validateRemove(string input);
    string validateRemoveInorder(string input);
    // Destructor
    ~AVLTree();
};

//For the Right-Right Case
AVLTree::Node* AVLTree::rotateLeft(Node *node) {
    // Adapted from the Balanced Tree Slideshow from Lecture and Stepik Submission; 9-27-23.
    Node* rightGrandChild = node->right->left;
    Node* rightChild = node->right;
    rightChild->left = node;
    node->right = rightGrandChild;
    return rightChild;
}

//For the Left-Left Case
AVLTree::Node* AVLTree::rotateRight(Node* node) {
    // Adapted from the Balanced Tree Slideshow from Lecture and Stepik Submission; 9-27-23.
    Node* leftGrandChild = node->left->right;
    Node* leftChild = node->left;
    leftChild->right = node;
    node->left = leftGrandChild;
    return leftChild;
}

// For Left-Right Case
AVLTree::Node* AVLTree::rotateLeftRight(Node *node) {
    // Adapted from Stepik Solution manual; 9-27-23.
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// For Right-Left Case
AVLTree::Node* AVLTree::rotateRightLeft(Node *node) {
    // Adapted from Stepik Solution manual; 9-27-23.
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// Helper for getting height of the node
int AVLTree::getMaxHeight(Node* node) {
    // Got the 1 + max(...) from slack/stepik.
    if (node == nullptr)
        return 0;
    return (1 + max(getMaxHeight(node->left), getMaxHeight(node->right)));
}

// Insertion to the AVL Tree
AVLTree::Node* AVLTree::insertPrivate(Node* node, string NAME, int ID) {
    // Inserting
    if (node == nullptr) {
        // Base Case
        cout << "successful" << endl;
        return new Node(NAME, ID);
    }
    if (ID < node->ID) // Inserts on left branch
        node->left = insertPrivate(node->left, NAME, ID);
    else if (ID > node->ID) // Inserts on right branch
        node->right = insertPrivate(node->right, NAME, ID);
    else // Unsuccessful only if ID==Node->ID (The ID already exists and ID's must be unique).
        cout << "unsuccessful" << endl;

    // Balancing
    node->balanceFactor = getMaxHeight(node->left) - getMaxHeight(node->right);
    // Used a GeeksforGeeks article, when I needed to understand balancing better for AVL trees.
    // https://www.geeksforgeeks.org/insertion-in-an-avl-tree/

    // Rotating
    // Left-Left Case
    if (node->balanceFactor > 1 && ID < node->left->ID)
        return rotateRight(node);
    // Right-Right Case
    else if (node->balanceFactor < -1 && ID > node->right->ID)
        return rotateLeft(node);
    // Left-Right Case
    else if (node->balanceFactor > 1 && ID > node->left->ID)
        return rotateLeftRight(node);
    // Right-Left Case
    else if (node->balanceFactor < -1 && ID < node->right->ID)
        return rotateRightLeft(node);
    return node;
}

// Public Facing function where user doesn't interact with the root member variable.
void AVLTree::insert(string NAME, int ID) {
    root = insertPrivate(root, NAME, ID);
}

// Helper function for remove that finds the successor
// for when a node being removed has two children.
AVLTree::Node* AVLTree::findSuccessorNode(Node* node) {
    if (node->right == nullptr)
        return node;
    findSuccessorNode(node->right);
    return nullptr;
}

// Private recursive remove function.
AVLTree::Node* AVLTree::removeIDPrivate(Node *node, int ID) {
    // Base Case where node doesn't exist.
    if(node == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    // Recurse through left subtree.
    if(ID < node->ID)
        node->left = removeIDPrivate(node->left, ID);
        // Recurse through right subtree.
    else if (ID > node->ID)
        node->right = removeIDPrivate(node->right, ID);
        // Else branch is where ID == node->ID.
    else {
        // No children (trivial delete operation)
        if(node->left == nullptr && node->right == nullptr) {
            delete node;
            cout << "successful" << endl;
            return nullptr;
        }
            // One Child Left Side (Like a linked list)
        else if(node->left != nullptr && node->right == nullptr) {
            Node* tempNode = node->left;
            delete node;
            cout << "successful" << endl;
            return tempNode;
        }
            // One Child Right Side (Like a linked list)
        else if(node->left == nullptr && node->right != nullptr) {
            Node* tempNode = node->right;
            delete node;
            cout << "successful" << endl;
            return tempNode;
        }
            // Two Children
        else {
            // Was struggling with the two child case and found a snippet from stackoverflow
            // https://stackoverflow.com/questions/8292661/how-to-delete-a-node-with-2-children-nodes-in-a-binary-search-tree
            Node* tempNode = findSuccessorNode(node->left);
            node->NAME = tempNode->NAME;
            node->ID = tempNode->ID;
            node->left = removeIDPrivate(node->left, tempNode->ID);
        }
    }
    return node;
}

// Overloaded remove function for Unit Testing
AVLTree::Node* AVLTree::removeIDPrivate(Node *node, int ID, string& output) {
    if(node == nullptr) {
        output = "unsuccessful";
        return nullptr;
    }
    if(ID < node->ID)
        node->left = removeIDPrivate(node->left, ID);
    else if (ID > node->ID)
        node->right = removeIDPrivate(node->right, ID);
    else {
        // No children (trivial delete operation)
        if(node->left == nullptr && node->right == nullptr) {
            delete node;
            output = "successful";
            return nullptr;
        }
            // One Child Left Side (Like a linked list)
        else if(node->left != nullptr && node->right == nullptr) {
            Node* tempNode = node->left;
            delete node;
            output = "successful";
            return tempNode;
        }
            // One Child Right Side (Like a linked list)
        else if(node->left == nullptr && node->right != nullptr) {
            Node* tempNode = node->right;
            delete node;
            output = "successful";
            return tempNode;
        }
            // Two Children
        else {
            // Was struggling with the two child case and found a snippet from stackoverflow
            // https://stackoverflow.com/questions/8292661/how-to-delete-a-node-with-2-children-nodes-in-a-binary-search-tree
            Node* tempNode = findSuccessorNode(node->left);
            node->NAME = tempNode->NAME;
            node->ID = tempNode->ID;
            node->left = removeIDPrivate(node->left, tempNode->ID);
        }
    }
    output = "unsuccessful";
    return node;
}

// Public facing remove function.
void AVLTree::remove(int ID) {
    root = removeIDPrivate(root, ID);
}

// Iterates through the AVL Tree until it finds the node with the ID parameter.
AVLTree::Node* AVLTree::searchIDPrivate(Node* node, int ID) {
    if(node == nullptr)
        return nullptr;
    else if(node->ID == ID)
        return node;
    else if(ID < node->ID)
        return searchIDPrivate(node->left, ID);
    else if(ID > node->ID)
        return searchIDPrivate(node->right, ID);
    return nullptr;
}

// Overload for Unit Testing
AVLTree::Node* AVLTree::searchIDPrivate(Node *node, int ID, string &output) {
    if(node == nullptr) {
        output = "unsuccessful";
        return nullptr;
    }
    else if (node == root) {
        output = "successful";
        return root;
    }
    else if(node->ID == ID) {
        output = "successful";
        return node;
    }
    else if(ID < node->ID)
        return searchIDPrivate(node->left, ID);
    else if(ID > node->ID)
        return searchIDPrivate(node->right, ID);
    output = "unsuccessful";
    return nullptr;
}

void AVLTree::searchID(int ID){
    Node* nodeToSearch = searchIDPrivate(root, ID);
    if(nodeToSearch != nullptr){
        cout<< nodeToSearch->NAME << endl;
    }
    else
        cout<< "unsuccessful" << endl;
}

// Iterates through the tree in Preorder (because that is the specification for the search NAME method)
void AVLTree::preOrderTraversal(Node *node, string name, vector<int>& nodes) {
    if (node == nullptr) {
        return;
    }
    if (node->NAME == name) {
        nodes.push_back(node->ID);
    }
    preOrderTraversal(node->left, name, nodes);
    preOrderTraversal(node->right, name, nodes);
}

// Iterates through the vector populated in preOrderTraversal();
// outputting all associated ID's with the inputted name.
void AVLTree::searchName(string NAME) {
    vector<int> nodes;
    preOrderTraversal(root, NAME, nodes);
    if (nodes.empty()) {
        cout << "unsuccessful" << endl;
        return;
    }
    for (int ID : nodes) {
        cout << ID << endl;
    }
}

// Iterating through entire tree Inorder storing all nodes in a vector.
void AVLTree::printInorder(Node* node, vector<Node*>& nodes) {
    if (node == nullptr)
        return;
    printInorder(node->left, nodes);
    nodes.push_back(node);
    printInorder(node->right, nodes);

}

// Public function that prints out all names with proper required formatting.
// Vector IDS is to be used for unit testing.
void AVLTree::inOrder(vector<int>& IDS) {
    vector<Node*> nodes;
    printInorder(root, nodes);
    for (unsigned int i = 0; i < nodes.size()-1; i++) {
        cout << nodes[i]->NAME << ", ";
        IDS.push_back(nodes[i]->ID);
    }
    cout << nodes[nodes.size()-1]->NAME << endl;
    IDS.push_back(nodes[nodes.size()-1]->ID);
}

// Iterating through entire tree storing all nodes in preorder.
void AVLTree::printPreOrder(Node* node, vector<Node*>& nodes) {
    if (node == nullptr)
        return;
    nodes.push_back(node);
    printPreOrder(node->left, nodes);
    printPreOrder(node->right, nodes);
}

// Public function that prints out all the nodes in with the proper formatting.
void AVLTree::preOrder(vector<int>& nodeList) {
    vector<Node*> nodes;
    printPreOrder(root, nodes);
    for (unsigned int i = 0; i < nodes.size()-1; i++) {
        cout << nodes[i]->NAME << ", ";
        nodeList.push_back(nodes[i]->ID);
    }
    cout << nodes[nodes.size()-1]->NAME << endl;
    nodeList.push_back(nodes[nodes.size()-1]->ID);
}

// Iterating through entire tree storing all nodes in postorder.
void AVLTree::printPostOrder(Node* node, vector<Node*>& nodes) {
    if (node == nullptr)
        return;
    printPostOrder(node->left, nodes);
    printPostOrder(node->right, nodes);
    nodes.push_back(node);
}

// Public function that prints all nodes in vector with proper formatting.
void AVLTree::postOrder() {
    vector<Node*> nodes;
    printPostOrder(root, nodes);
    for (unsigned int i = 0; i < nodes.size()-1; i++) {
        cout << nodes[i]->NAME << ", ";
    }
    cout << nodes[nodes.size()-1]->NAME << endl;
}

// With the getMaxHeight, iterates through entire tree and prints the height.
void AVLTree::printLevelCount() {
    cout << getMaxHeight(root) << endl;
}

// Helper function that traverses the tree inorder,
// storing all nodes in a vector to be used in removeInorder().
void AVLTree::inOrderTraversal(Node* node, vector<Node*>& nodes) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->left, nodes);
    nodes.push_back(node);
    inOrderTraversal(node->right, nodes);
}

// Method checks to see if the input index is within the vector nodes, once that is verified
// it just calls the remove function to delete the node at the inputted index.
void AVLTree::removeInorder(int N) {
    vector<Node*> nodes;
    inOrderTraversal(root, nodes);
    if ((unsigned int)N > nodes.size()) {
        cout << "unsuccessful" << endl;
    } else {
        remove(nodes[N]->ID);
    }
}

// Unit testing variations of functions (They have a return value to be used with Catch2).
string AVLTree::validateInsert(string input) {
    regex insertCommand = regex("^insert \"([A-Z]?[a-z]* *)*\" \\d{8}$");
    if (regex_match(input, insertCommand)) {
        string subString = input.substr(8);
        int endOfName = subString.find('"');
        root = insertPrivate(root, input.substr(8, endOfName), stoi(input.substr(endOfName+10, 8)));
        return "successful";
    }
    else {
        return "unsuccessful";
    }
}

string AVLTree::validateSearchID(string input) {
    regex searchIDCommand = regex("^search \\d{8}$");
    if (!regex_match(input, searchIDCommand))
        return "unsuccessful";
    int ID = stoi(input.substr(7));
    string output = "";
    Node* nodeToFind = searchIDPrivate(root, ID, output);
    if (nodeToFind != nullptr)
        return output;
    else
        return "unsuccessful";
}

string AVLTree::validateSearchName(string input) {
    regex searchNameCommand = regex("^search \"([A-Z]?[a-z]* *)*\"$");
    if (regex_match(input, searchNameCommand)) {
        string subString = input.substr(8);
        int endOfName = subString.find('"');
        string NAME = input.substr(8, endOfName);
        vector<int> nodes;
        preOrderTraversal(root, NAME, nodes);
        if (nodes.empty()) {
            cout << "unsuccessful" << endl;
            return "unsuccessful";
        }
        for (int ID : nodes) {
            cout << ID << endl;
        }
        return "successful";
    } else {
        return "unsuccessful";
    }
}

string AVLTree::validateRemove(string input) {
    regex removeCommand = regex("^remove \\d{8}$");
    if (!regex_match(input, removeCommand)) {
        return "unsuccessful";
    }
    string output = "";
    Node* nodeToRemove = removeIDPrivate(root, stoi(input.substr(7)), output);
    if (nodeToRemove != nullptr)
        return output;
    return output;
}

string AVLTree::validateRemoveInorder(string input) {
    regex removeInorderCommand = regex("^removeInorder \\d+$");
    if (regex_match(input, removeInorderCommand)) {
        unsigned int N = stoi(input.substr(14));
        vector<Node *> nodes;
        inOrderTraversal(root, nodes);
        if (N > nodes.size()-1) {
            cout << "unsuccessful" << endl;
            return "unsuccessful";
        }
        remove(nodes[N]->ID);
        return "successful";
    } else {
        return "unsuccessful";
    }
}

// Recursive helper that traverses the tree deleting all nodes.
void AVLTree::destructorHelper(Node *node) {
    // You need recursion to iterate through all nodes to delete them
    // Using a post order traversal
    if (node == nullptr)
        return;
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}

//Destructor
AVLTree::~AVLTree() {
    // To free all the memory the tree is using
    // iterate through the tree starting at the root.
    destructorHelper(root);
}

#endif //AVLTREE_H