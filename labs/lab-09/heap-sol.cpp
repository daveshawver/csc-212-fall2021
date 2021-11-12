#include "heap.h"

/*
 * Node Class Functions
*/

HeapNode::HeapNode(int data){
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

HeapNode::~HeapNode(){

}

/*
 * Tree Class Functions
*/

/*
 * Private Functions
*/

HeapNode* HeapTree::insert(int data, HeapNode* root){
    if(root == nullptr){
        return new HeapNode(data);
    }

    // Changed from min-heap
    if(data > root->data){
        int temp = root->data;
        root->data = data;
        data = temp;
    }


    if((isFull(root) && size(root->left) == size(root->right))|| !isFull(root->left)){
        root->left = insert(data, root->left);
    }else{
        root->right = insert(data, root->right);
    }

    return root;
}

int HeapTree::height(HeapNode* root){
    if(root == nullptr){
        return -1;
    }

    int left = height(root->left);
    int right = height(root->right);

    if(left > right){
        return left + 1;
    }else{
        return right + 1;
    }
}

void HeapTree::preorder(HeapNode* root, std::ostream& os){
    if(root == nullptr){
        return;
    }

    os << root->data << ", ";
    preorder(root->left, os);
    preorder(root->right, os);
}

void HeapTree::inorder(HeapNode* root, std::ostream& os){
    if(root == nullptr){
        return;
    }

    inorder(root->left, os);
    os << root->data << ", ";
    inorder(root->right, os);
}

void HeapTree::postorder(HeapNode* root, std::ostream& os){
    if(root == nullptr){
        return;
    }

    postorder(root->left, os);
    postorder(root->right, os);
    os << root->data << ", ";
}

void HeapTree::destroy(HeapNode* root){
    if(root == nullptr){
        return;
    }
    destroy(root->left);
    destroy(root->right);
    delete root;
}

bool HeapTree::search(int data, HeapNode* root){
    if(root == nullptr){
        return false;
    }

    if(root->data == data){
        return true;
    }

    if(root->data == data){
        return true;
    }

    bool found = search(data, root->left);
    if(found == true){
        return true;
    }

    return search(data, root->right);
}

bool HeapTree::isFull(HeapNode* root){
    if(root == nullptr){
        return true;
    }
    // Handle leaf node logic
    if(root->left == nullptr && root->right == nullptr){
        return true;
    }

    // If this node has two children & they are both Full, return true
    if(root->left != nullptr && root->right != nullptr){
        return isFull(root->left) && isFull(root->right);
    }

    return false;
}

// Index each node & compare it to the # of Nodes in the tree.
// If any node's index is >= the # of nodes we have, the tree is incomplete.
/*
         0
    1        2
3       4 5     6
*/
bool HeapTree::isComplete(HeapNode* root, int index, int node_count){
    if(root == nullptr){
        return true;
    }

    if(index >= node_count){
        return false;
    }

    bool left_complete = isComplete(root->left, 2*index + 1, node_count);
    bool right_complete = isComplete(root->right, 2*index + 2, node_count);

    return left_complete && right_complete;
}

int HeapTree::size(HeapNode* root){
    if(root == nullptr){
        return 0;
    }

    int left_size = size(root->left);
    int right_size = size(root->right);

    return left_size + right_size + 1;
}
/*
HeapNode* HeapTree::max_heapify(HeapNode* root){
    if(root == nullptr){
        return nullptr;
    }

	if(root->left != nullptr){
	    // Changed from min-heap
	    if(root->left->data > root->data){
	        int temp = root->data;
	        root->data = root->left->data;
	        root->left->data = temp;
	    }
	    max_heapify(root->left);
	}

	if(root->right != nullptr){
	    // Changed from min-heap
	    if(root->right->data > root->data){
	        int temp = root->data;
	        root->data = root->right->data;
	        root->right->data = temp;
	    }
	    max_heapify(root->right);
	}

    return root;
}*/

// More robust implementation. Allows you to change 'HeapNode' without needing to revisit this function.
HeapNode* HeapTree::max_heapify(HeapNode* root){
    if(root == nullptr){
        return nullptr;
    }

	if(root->left != nullptr){
	    // Changed from min-heap
	    if(root->left->data > root->data){
            HeapNode* temp_left = root->left->left;
            HeapNode* temp_right = root->left->right;

            root->left->right = root->right;
            root->left->left = root;

            root = root->left;

            root->left->left = temp_left;
            root->left->right = temp_right;
	    }
	    root->left = max_heapify(root->left);
	}

	if(root->right != nullptr){
	    // Changed from min-heap
	    if(root->right->data > root->data){
            HeapNode* temp_left = root->right->left;
            HeapNode* temp_right = root->right->right;

            root->right->left = root->left;
            root->right->right = root;

            root = root->right;

            root->right->left = temp_left;
            root->right->right = temp_right;
	    }
	    root->right = max_heapify(root->right);
	}

    return root;
}

HeapNode* HeapTree::find_last(HeapNode* root, int index, int node_count){
    if(root == nullptr || index >= node_count){
        return nullptr;
    }

	if(2*index + 1 == node_count - 1){
	    HeapNode* temp = root->left;
	    root->left = nullptr;
	    return temp;
	}

	if(2*index + 2 == node_count - 1){
	    HeapNode* temp = root->right;
	    root->right = nullptr;
	    return temp;
	}

	HeapNode* left_result = find_last(root->left, 2*index + 1, node_count);
	if(left_result != nullptr){
	    return left_result;
	}

	return find_last(root->right, 2*index + 2, node_count);
}

void HeapTree::remove_max(HeapNode* root){
    HeapNode* last_node = find_last(this->root, 0, size(this->root));
    root->data = last_node->data;
    delete last_node;
}

void HeapTree::delete_element(int data, HeapNode* root){
    if(root == nullptr){
        return;
    }

    if(root->data == data){
        HeapNode* last_node = find_last(this->root, 0, size(this->root));
        root->data = last_node->data;
        delete last_node;
        return;
    }

    delete_element(data, root->left);
    delete_element(data, root->right);
}

/*
 * Public Functions
*/

HeapTree::HeapTree(){
    this->root = nullptr;
}

HeapTree::~HeapTree(){
    destroy(this->root);
}

void HeapTree::insert(int data){
    this->root = insert(data, this->root);
}

int HeapTree::height(){
    return height(this->root);
}

void HeapTree::preorder(std::ostream& os){
    preorder(this->root, os);
    os << "\n";
}

void HeapTree::inorder(std::ostream& os){
    inorder(this->root, os);
    os << "\n";
}

void HeapTree::postorder(std::ostream& os){
    postorder(this->root, os);
    os << "\n";
}

bool HeapTree::search(int data){
    return search(data, this->root);
}

bool HeapTree::isFull(){
    return isFull(this->root);
}

bool HeapTree::isComplete(){
    return isComplete(this->root, 0, size(this->root));
}

void HeapTree::remove_max(){
    remove_max(this->root);
    this->root = max_heapify(this->root);
}

void HeapTree::delete_element(int data){
    delete_element(data, this->root);
    this->root = max_heapify(this->root);
}

// Strictly used for the test cases
void HeapTree::find_last(std::ostream& os){
    HeapNode* temp = find_last(this->root, 0, size(this->root));
    os << temp->data << std::endl;
}