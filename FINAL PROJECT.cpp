#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string wordType;
    string word;
    Node *left;
    Node *right;

    Node(string type, string w) : wordType(type), word(w), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node *root;

    void insert(Node* &node, string wordType, string word) {
        if (node == nullptr) {
            node = new Node(wordType, word);
        } else if (wordType < node->wordType) {
            insert(node->left, wordType, word);
        } else {
            insert(node->right, wordType, word);
        }
    }

    void preorderTraversal(Node *node) {
        if (node != nullptr) {
            cout << node->wordType << ": " << node->word << "\n ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void inorderTraversal(Node *node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->wordType << ": " << node->word << "\n ";
            inorderTraversal(node->right);
        }
    }

    void postorderTraversal(Node *node) {
        if (node != nullptr) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->wordType << ": " << node->word << "\n ";
        }
    }

    Node* search(Node* node, string wordType) {
        if (node == nullptr || node->wordType == wordType) return node;
        if (wordType < node->wordType) return search(node->left, wordType);
        return search(node->right, wordType);
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, string wordType) {
        if (node == nullptr) return node;

        if (wordType < node->wordType) {
            node->left = deleteNode(node->left, wordType);
        } else if (wordType > node->wordType) {
            node->right = deleteNode(node->right, wordType);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->wordType = temp->wordType;
            node->word = temp->word;
            node->right = deleteNode(node->right, temp->wordType);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(string wordType, string word) {
        insert(root, wordType, word);
    }

    void preorderTraversal() {
        preorderTraversal(root);
        cout << endl;
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }

    void postorderTraversal() {
        postorderTraversal(root);
        cout << endl;
    }

    string getWord(string wordType){
        Node* found = search(root, wordType);
        return (found != nullptr) ? found->word : "";
    }

    void deleteWord(string wordType){
        root = deleteNode(root, wordType);
    }
};

int main() {
    BST madLibs;

    cout << "Hello! Welcome to my Mad Libs game!\n";
    cout << "We're going to create a story based on your input.\n";
    cout << "Prepare your 3 words:\n";
    cout<< "NOTE:first word will be a name of person  \n";
    string wordTypes[] = {"noun", "verb", "adverb"};
    string words[3];


    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ") Enter a word (" << wordTypes[i] << "): ";
        getline(cin, words[i]); 
        madLibs.insert(wordTypes[i], words[i]);
    }

    string finalStory ="My friend, [noun], came over my room while I was working. Suddenly, she spilled her coffee to my papers, and I [verb]. My deadline is now completely and [adverb] missed";

    for (int i = 0; i < 3; ++i) {
        size_t pos = finalStory.find("[" + wordTypes[i] + "]");
        if (pos != string::npos) {
            finalStory.replace(pos, wordTypes[i].length() + 2, madLibs.getWord(wordTypes[i]));
        }
    }

    cout << "\nHere's your Mad Libs story:\n" << finalStory << endl;

    cout << "\nInorder Traversal:\n ";
    madLibs.inorderTraversal();
    cout << "\nPreorder Traversal: \n ";
    madLibs.preorderTraversal();
    cout << "\nPostorder Traversal:\n ";
    madLibs.postorderTraversal();


    cout << "\nEnter a word type to delete: ";
    string wordToDelete;
    getline(cin, wordToDelete);
    madLibs.deleteWord(wordToDelete);
    cout << "Word deleted.\n";
    cout << "New Inorder Traversal: \n";
    madLibs.inorderTraversal();
    cout << "New Preorder Traversal: \n";
    madLibs.preorderTraversal();
    cout << "New Postorder Traversal: \n";
    madLibs.postorderTraversal();
    cout << endl;

    return 0;
}