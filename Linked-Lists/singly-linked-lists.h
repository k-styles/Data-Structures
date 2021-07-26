// Single Linked List
#include<stdio.h>
#include<iostream>

using namespace std;

template<typename T>
class Node{
    public:
        T elem; 
        Node<T>* next;
    
    public:
        void print(){
            if(this->next==NULL) printf("%d->\n", this->elem);
            else printf("%d->", this->elem);
        }
};

template <typename T>
class SinglyLinkedList{
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
bool SinglyLinkedList<T>::add_head_element(T a){
    if(this->head == NULL){
        Node<T>* new_node = new Node<T>;
        new_node->elem = a;
        this->head = new_node;
        this->tail = new_node;
        return true;
    }

    Node<T> *temp_node = this->head;

    Node<T> *new_node = new Node<T>;
    new_node->elem = a;

    this->head = new_node;
    new_node->next = temp_node;

    return true;

}

template <typename T>
bool SinglyLinkedList<T>::add_tail_element(T a){
    if(this->tail == NULL){
        Node<T>* new_node = new Node<T>;
        new_node->elem = a;
        this->head = new_node;
        this->tail = new_node;
        return true;
    }

    Node<T> *temp_node = this->tail;

    Node<T> *new_node = new Node<T>;
    temp_node->next = new_node;
    new_node->elem = a;

    this->tail = new_node;
    new_node->next = NULL;

    return true;

}

//////////////////////////////////////////////////////////////////////////
// Remove Methods. rm_tail_element() function would have been a linear time function, so ignoring that in ingly linked lists
template <typename T>
bool SinglyLinkedList<T>::rm_head_element(){
    Node<T> *temp_node = this->head;
    this->head = this->head->next;
    delete temp_node;
    return true;
}

//////////////////////////////////////////////////////////////////////////
int main(){
    /* Node<int> node;
    node.elem = 5;
    node.next=NULL;
    node.print(); */

    SinglyLinkedList<int> list;
    list.add_tail_element(5);
    list.add_tail_element(7);
    list.rm_head_element();
    list.print_list();
}