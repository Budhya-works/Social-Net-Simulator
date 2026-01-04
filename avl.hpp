#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Node{
    string content;
    long long timestamp;
    int height;
    Node *left, *right;

    Node(string cont, long long time) : content(cont), timestamp(time), height(0){
        left = right = nullptr;
    }
};

class Avl{
    Node* root;

    int H(Node* node){
        return node ? node->height : -1;
    }

    int bal(Node* node){
        return H(node->left) - H(node->right);
    }

    Node* rightRotate(Node* y){
        Node* x = y->left;
        Node* T2 = x->right;

        y->left = T2;
        x->right = y;

        y->height = max(H(y->left), H(y->right))+1;
        x->height = max(H(x->left), H(x->right))+1;

        return x;
    }

    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;

        x->right = T2;
        y->left = x;

        x->height = max(H(x->left), H(x->right))+1;
        y->height = max(H(y->left), H(y->right))+1;

        return y;
    }

    Node* insert(Node* node, string cont, long long time){
        if(!node) return new Node(cont, time);
        if(time < node->timestamp){
            node->left = insert(node->left, cont, time);
        }
        else
            node->right = insert(node->right, cont, time);
        node->height = max(H(node->left), H(node->right))+1;
        int Balance = bal(node);
        if(Balance > 1 && time < node->left->timestamp)    // Left Left Case
            return rightRotate(node);
        if(Balance < -1 && time > node->right->timestamp)   // Right Right Case
            return leftRotate(node);
        if(Balance > 1 && time > node->left->timestamp){    // Left Right Case
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(Balance < -1 && time < node->right->timestamp){  // Right Left Case
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    void printInOrder(Node* node, int &N){
        if(N == -1 && node){
            printInOrder(node->right, N);
            cout << node->content << "\n";
            printInOrder(node->left, N);
            return;
        }
        if(!node || N == 0) 
            return;
        printInOrder(node->right, N);
        if(N > 0){
            cout << node->content << "\n";
            N--;
        }
        printInOrder(node->left, N);
    }
    public:
        Avl() : root(nullptr) {}
        void addPost(string content, long long timestamp){
            root = insert(root, content, timestamp);
        }

        void printPosts(int N){
            printInOrder(root, N);
        }
};