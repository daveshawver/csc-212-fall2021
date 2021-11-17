#include "bst.h"

/*
 * Node Class Functions
*/

BSTNode::BSTNode(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

BSTNode::~BSTNode(){

}

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

BSTNode* BSTree::insert(int data, BSTNode* root){
    if(!root){
        return new BSTNode(data);
    }

    if(data < root->data){
        root->left = insert(data, root->left);
    }else{
        root->right = insert(data, root->right);
    }

    return root;
}

int BSTree::height(BSTNode* root){
    if(!root){
        return -1;
    }
    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left + 1 : right + 1);
}

void BSTree::preorder(BSTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    os << root->data << ", ";
    this->preorder(root->left, os);
    this->preorder(root->right, os);

    return;
}

void BSTree::inorder(BSTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->inorder(root->left, os);
    os << root->data << ", ";
    this->inorder(root->right, os);

    return;
}

void BSTree::postorder(BSTNode* root, std::ostream& os){
    if(!root){
        return;
    }

    this->postorder(root->left, os);
    this->postorder(root->right, os);
    os << root->data << ", ";

    return;
}

void BSTree::destroy(BSTNode* root){
    if(!root){
        return;
    }

    this->destroy(root->left);
    this->destroy(root->right);
    delete root->left;
    delete root->right;
}

bool BSTree::search(int data, BSTNode* root){
    if(!root){
        return false;
    }

    if(data == root->data){
        return true;
    }

    if(data < root->data){
        return this->search(data, root->left);
    }else{
        return this->search(data, root->right);
    }
}

/*
 * Public Functions
*/

BSTree::BSTree(){
    this->root = nullptr;
}

BSTree::~BSTree(){
    delete this->root;
}

void BSTree::insert(int data){
    this->root = this->insert(data, this->root);
}

int BSTree::height(){
    return this->height(this->root);
}

void BSTree::preorder(std::ostream& os){
    this->preorder(this->root, os);
    os << "\n";
}

void BSTree::inorder(std::ostream& os){
    this->inorder(this->root, os);
    os << "\n";
}

void BSTree::postorder(std::ostream& os){
    this->postorder(this->root, os);
    os << "\n";
}

bool BSTree::search(int data){
    return this->search(data, this->root);
}