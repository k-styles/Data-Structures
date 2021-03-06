#include<stdio.h>
#include<iostream>
#include"queue.h"
using namespace std;
template<typename T>
class Node{
    public:
        T elem;
        Node<T>* parent = NULL;
        Node<T>* left = NULL;
        Node<T>* right = NULL;
};

template<typename T>
class BinarySearchTree{
    public:
        Node<T>* node_ptr = NULL;
        Node<T>* root_ptr = NULL;
        int num_elems = 0;

        // Private Pre order function (no access to user)
        void private_pre_order(Node<T>* temp_ptr){
            if(temp_ptr==NULL) return;
            cout << temp_ptr->elem << "->";
            private_pre_order(temp_ptr->left);
            private_pre_order(temp_ptr->right);
        }

        // Private In order function (no access to user)
        void private_in_order(Node<T>* temp_ptr){
            if(temp_ptr==NULL) return;
            private_in_order(temp_ptr->left);
            cout << temp_ptr->elem << "->";
            private_in_order(temp_ptr->right);
        }

        // Private Post order function (no access to user)
        void private_post_order(Node<T>* temp_ptr){
            if(temp_ptr==NULL) return;
            private_post_order(temp_ptr->left);
            private_post_order(temp_ptr->right);
            cout << temp_ptr->elem << "->";
        }

    public:
        // **INSERT** an element to the binary tree
        bool insert(T a){
            // Insert root node if it does not exist
            if(this->root_ptr==NULL){
                this->root_ptr = new Node<T>;
                this->node_ptr = this->root_ptr;
                this->root_ptr->elem = a;
                this->num_elems++;
                return true;
            }

            // Loop until an element gets added
            while(true){
                // Traverse left if element is to be added is <= current element. Note: This tree supports duplicate values and insert them to the left of node having same value.
                if(this->node_ptr->elem >= a){
                    
                    // If nothing on left, add the element
                    if(this->node_ptr->left == NULL){
                        this->node_ptr->left = new Node<T>;
                        this->node_ptr->left->elem = a;
                        this->node_ptr->left->parent = this->node_ptr;
                        this->num_elems++;

                        this->node_ptr = this->root_ptr; // Bring back the parser pointer to root node
                        /* printf("left"); */
                        return true;
                    }
                    
                    // If there is an element on left, just move the pointer to the left
                    this->node_ptr = this->node_ptr->left;

                }

                // Traverse right if element is to be added is > current element
                else if(this->node_ptr->elem < a){
                    // If nothing on left, add the element
                    if(this->node_ptr->right == NULL){
                        this->node_ptr->right = new Node<T>;
                        this->node_ptr->right->elem = a;
                        this->node_ptr->right->parent = this->node_ptr;
                        this->num_elems++;

                        this->node_ptr = this->root_ptr; // Bring back the parser pointer to root node                        
                        /* printf("right"); */
                        return true;
                    }
                    // If there is an element on right, just move the pointer to the right

                    this->node_ptr = this->node_ptr->right;
                }
            }
        }
        // **SEARCH** the element in the binary tree
        bool search(T a){
            while(true){
                // If pointer reaches NULL, restore the node_ptr and return false
                if(this->node_ptr == NULL){
                    cout << "Element NOT found!\n";
                    this->node_ptr = this->root_ptr; // Restore point of node_ptr to root node
                    return false;
                }

                // If element is found, restore the node_ptr and return true 
                else if(this->node_ptr->elem == a){
                    cout << "Element found!\n";
                    this->node_ptr = this->root_ptr; // Restore point of node_ptr to root node
                    return true;
                }

                // Traverse left if element that is to be found is <= current element.
                else if(this->node_ptr->elem > a){
                    //Move the pointer to the left
                    this->node_ptr = this->node_ptr->left;
                }

                // Traverse right if element that is to be found is > current element.
                else if(this->node_ptr->elem < a){
                    // Move the pointer to the right
                    this->node_ptr = this->node_ptr->right;
                }
                
            }
        }

        // **REMOVE** the element from the binary tree
        bool remove(T a){
            while(true){
                // If pointer reaches NULL, restore the node_ptr and return false
                if(this->node_ptr == NULL){
                    cout << "Element NOT found to remove!\n";
                    this->node_ptr = this->root_ptr; // Restore point of node_ptr to root node
                    return false;
                }

                // If element is found, check what case of removal is it
                else if(this->node_ptr->elem == a){
                    cout << "Element found to remove!\n";
                    
                    // Found node is a leaf node
                    if(this->node_ptr->right==NULL && this->node_ptr->left==NULL){
                        cout << "Node " << this->node_ptr->elem << " removed!\n";
                        if(this->node_ptr->parent->right == this->node_ptr){
                            this->node_ptr->parent->right=NULL;
                        }
                        else this->node_ptr->parent->left=NULL;

                        /* delete this->node_ptr; */cout << "Node " << this->node_ptr->elem << " removed!\n";
                        this->node_ptr = this->root_ptr; // Restore node_ptr to root_ptr
                        return true;
                    }

                    // Found node is null at left only, next node becomes the successor
                    else if(this->node_ptr->left==NULL){
                        this->node_ptr->parent->right = this->node_ptr->right;
                        this->node_ptr->right->parent = this->node_ptr->parent;
                        cout << "Node " << this->node_ptr->elem << " removed!\n";
                        delete this->node_ptr;
                        this->node_ptr = this->root_ptr; // Restore node_ptr to root_ptr
                        return true;
                    }

                    // Found node is null at right only, next node becomes the successor
                    else if(this->node_ptr->right==NULL){
                        this->node_ptr->parent->left = this->node_ptr->left;
                        this->node_ptr->left->parent = this->node_ptr->parent;
                        cout << "Node " << this->node_ptr->elem << " removed!\n";
                        delete this->node_ptr;
                        this->node_ptr = this->root_ptr; // restore node_ptr to root_ptr
                        return true;
                    }

                    // Found node has both children
                    else{
                        cout << "Node " << this->node_ptr->elem << " removed!\n";
                        Node<T>* successor = this->node_ptr->right;
                        while(successor->left!=NULL){
                            continue;
                        }
                        // swap
                        T temp = successor->elem;
                        successor->elem = this->node_ptr->elem;
                        this->node_ptr->elem = temp;

                        // Removing the smallest node in the right subtree
                        successor->parent->right = successor->right;
                        successor->right->parent = successor->parent;
                        
                        delete successor;
                        this->node_ptr = this->root_ptr; // restore node_ptr to root_ptr
                        return true;
                    }
                    
                }

                // Continue to traverse left if element that is to be found is <= current element.
                else if(this->node_ptr->elem >= a){
                    //Move the pointer to the left
                    this->node_ptr = this->node_ptr->left;
                }

                // Continue to traverse right if element that is to be found is > current element.
                else if(this->node_ptr->elem < a){
                    // Move the pointer to the right
                    this->node_ptr = this->node_ptr->right;
                }
                
            }
        }
        
        // Tree Traversals (Using recursion)
        // Pre-Order
        void print_preorder(){
            private_pre_order(this->node_ptr);
            printf("\n");
        }
        // In-Order
        void print_in_order(){
            private_in_order(this->node_ptr);
            printf("\n");
        }
        // Post-Order
        void print_post_order(){
            private_post_order(this->node_ptr);
            printf("\n");
        }
        // Level-Order or Breadth-First-Search. Queues are used to keep track of the elements to be printed.
        void print_level_order(){
            Queue< Node<T>* > queue;

            queue.enqueue(this->root_ptr);
            while(!queue.isEmpty()){
                Node<T>* queue_head = queue.at_head();
                if(queue_head->left!=NULL) {
                    queue.enqueue(queue_head->left);
                }
                if(queue_head->right!=NULL) {
                    queue.enqueue(queue_head->right);
                }
                cout << queue_head->elem << "->";
                queue.dequeue();
                
            }
            printf("\b\b  ");
            printf("\n");
            
        }

        /* void print_node(){
            cout << "\nNode: " << this->root_ptr->right->right->right->right->elem << "\n";
        } */
        
};

int main(){
    BinarySearchTree<int> tree;
    
    tree.insert(5);

    /* Node<int>* node;
    cout << node->left->right; */
    tree.insert(6);
    tree.insert(7);
    tree.insert(10);
    tree.insert(3);
    tree.insert(11);
    tree.insert(-1);
    tree.insert(0);
    tree.insert(7);
    tree.remove(7);
    tree.print_level_order();    
}