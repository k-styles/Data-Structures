// Single Linked List
#include<stdio.h>
#include<iostream>

using namespace std;

template<typename T>
class Node{
    public:
        T elem; 
        Node<T>* next = NULL;
        Node<T>* prev = NULL;
    
    public:
        void print(){
            if(this->next==NULL) printf("%d->\n", this->elem);
            else printf("%d->", this->elem);
        }
};

template <typename T>
class DoublyLinkedList{
    private:
        Node<T> *head = NULL;
        Node<T> *tail = NULL;

    public:
        bool add_head_element(T a);
        bool add_tail_element(T a);
        bool rm_head_element();
        bool isEmpty(){
            if (this->head==NULL) return true;
            else return false;
        }

        void make_list_user();

        void extreme_elements(){
            cout << "Head at: " << this->head->elem << "Tail at: " << this->tail->elem;
            cout << "\n";
        }

        void print_list(){
            Node<T> *print_this = this->head;
            
            while(print_this!=NULL){
                if(print_this->next==NULL){
                    cout << print_this->elem << "->\n";
                    print_this = print_this->next;
                }
                else{
                    cout << print_this->elem << "->";
                    print_this = print_this->next;
                }
            }
            
        }
};

//////////////////////////////////////////////////////////////////////////
// Adding elements methods
template <typename T>
bool DoublyLinkedList<T>::add_head_element(T a){
    if(this->head == NULL){
        Node<T>* new_node = new Node<T>;
        new_node->elem = a;
        this->head = new_node;
        this->tail = new_node;
        return true;
    }

    Node<T> *new_node = new Node<T>;
    Node<T> *temp_node = this->head;

    // Shift head to new node 
    this->head = new_node;

    // Exchange pointers
    temp_node->prev = this->tail;
    this->head->next = temp_node;
    this->head->elem = a;


    return true;

}

template <typename T>
bool DoublyLinkedList<T>::add_tail_element(T a){
    if(this->tail == NULL){
        Node<T>* new_node = new Node<T>;
        new_node->elem = a;
        this->head = new_node;
        this->tail = new_node;
        return true;
    }

    Node<T> *new_node = new Node<T>;
    Node<T> *temp_node = this->tail;

    // Shift tail to new node 
    this->tail = new_node;

    // Exchange pointers and add value to new node
    temp_node->next = this->tail;
    this->tail->prev = temp_node;
    this->tail->elem = a;

    return true;

}

//////////////////////////////////////////////////////////////////////////
// Remove Methods. rm_tail_element() function would have been a linear time function, so ignoring that in singly linked lists
template <typename T>
bool DoublyLinkedList<T>::rm_head_element(){
    Node<T> *temp_node = this->head;

    // Shift head pointer to right
    this->head = this->head->next;

    // handle pointers
    delete temp_node;
    
    return true;
}

//////////////////////////////////////////////////////////////////////////
/*int main(){
    /* Node<int> node;
    node.elem = 5;
    node.next=NULL;
    node.print(); */

  /*  DoublyLinkedList<int> list;
    list.add_head_element(5);
    list.add_head_element(6);
    list.print_list();
}*/
