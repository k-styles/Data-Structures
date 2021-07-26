// Single Linked List
#include<stdio.h>
#include<iostream>

using namespace std;

template<typename T>
class Node{
    public:
        T elem; 
        Node<T>* next = NULL;
    
    public:
        void print(){
            if(this->next==NULL) printf("%d\n", this->elem);
            else printf("%d->", this->elem);
        }
};

template<typename T>
class Stack{
    private:
        Node<T> *head = NULL;
        int num = 0;

    public:
        bool push(T a);
        bool pop();
        bool search(T a);
        int size();
        bool isEmpty();
        T peek(); 
        void print_stack(){
            Node<T> *print_this = this->head;
            while(print_this!=NULL){
                if(print_this->next==NULL){
                    cout << print_this->elem << "\n";
                    print_this = print_this->next;
                }
                else{
                    cout << print_this->elem << "->";
                    print_this = print_this->next;
                }
            }
            
        }
};

// Push an element at the head of stack. Takes O(1)
template<typename T>
bool Stack<T>::push(T a){
    Node<T>* new_node = new Node<T>;
    new_node->elem = a;
    if(this->head==NULL){
        this->head = new_node;
        this->num++;
        return true;
    }
    Node<T>* temp_head_ptr = this->head;
    this->head = new_node;
    this->head->next = temp_head_ptr;
    this->num++;
    return true;
}

// Pop an element from the head of stack. Takes O(1)
template<typename T>
bool Stack<T>::pop(){
    Node<T>* temp_head_ptr = this->head;
    this->head = this->head->next;
    delete temp_head_ptr;
    this->num--;
    return true;
}

// Search an elemnt in the stack. Takes O(n)
template<typename T>
bool Stack<T>::search(T a){
    Node<T>* stack_parser = this->head;
    while(stack_parser!=NULL){
        if(stack_parser->elem == a) return true;
        stack_parser = stack_parser->next;
    }
    return false;
}

// Returns size of the stack. Takes O(1)
template<typename T>
int Stack<T>::size(){
    return this->num;      
}

// Checks if stack is empty.
template<typename T>
bool Stack<T>::isEmpty(){
    if(this->head==NULL) return true;
}

// Peeks at the top elemnt in stack
template<typename T>
T Stack<T>::peek(){
    if(this->isEmpty()) throw 505;
    else return this->head;
}

int main(){
    Stack<int> stack;
    stack.push(4);
    stack.push(5);
    stack.push(7);
    stack.push(8);
    stack.print_stack();
    stack.pop();
    stack.print_stack();
    stack.pop();
    stack.print_stack();
}