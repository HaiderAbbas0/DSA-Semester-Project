#include<iostream>
using namespace std;

struct QueueNode{

    int data1;
    Node* next;

};

class Queue{

    private:

    Node* top;

    public:

    Queue(){
        top=nullptr;
    }

    void push(){
        
    }

};



struct Node{
    
    int data;
    Node* left;
    Node* right;

    Node(int data1){
        data=data1;
        left=nullptr;
        right=nullptr;
    }
};

class bfsTree{

    private:

    Node* root;

    public:

    bfsTree(){
        root=nullptr;
    }

    void Insert(int value){
        Node* newNode=new Node(value);

        if(root==nullptr){
            root=newNode;
            return;
        }

        Node* temp=root;
        
        while(true){
            if(value<temp->data){
                if(temp->left==nullptr){
                    temp->left=newNode;
                    return;
                }

                else{
                    temp=temp->left;
                }
            }

            else{
                if(temp->right==nullptr){
                    temp->right=newNode;
                    return;
                }

                else{
                    temp=temp->right;
                }

            }
        }
    }

    void inorder(Node* node){
        if(node==nullptr){
            return;
        }

        inorder(node->left);
        cout<<node->data<<" ";
        inorder(node->right);
    }
    
    void preorder(Node* node){
        if(node==nullptr){
            return;
        }

        cout<<node->data<<" ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node){
        if(node==nullptr){
            return;
        }

        postorder(node->left);
        postorder(node->right);
        cout<<node->data<<" ";
    }

    void inorderTraversal(){
        
        cout<<"Inorder Traversal: ";
        inorder(root);
        cout << endl;
    
    }

    void preorderTraversal(){
        
        cout<<"Preorder Traversal: ";
        preorder(root);
        cout<<endl;
    
    }

    void postorderTraversal(){
        
        cout<<"Postorder Traversal: ";
        postorder(root);
        cout<<endl;
    
    }

    Node* getRoot(){
        return root;
    }

};


int main(){
    
    bfsTree tree;

    tree.Insert(10);
    tree.Insert(6);
    tree.Insert(15);
    tree.Insert(4);
    tree.Insert(5);
    tree.Insert(12);
    tree.Insert(16);

    tree.inorderTraversal(); 
    tree.preorderTraversal();
    tree.postorderTraversal();
    
    return 0;
}