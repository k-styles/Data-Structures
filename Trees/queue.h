#include<stdio.h>
#include<iostream>

using namespace std;

template<typename T>
class Queue_node{
    public:
        T elem; 
        Queue_node<T>* next = NULL;
    
    public:
        void print(){
            if(this->next==NULL) printf("%d\n", this->elem);
            else printf("%d->", this->elem);
        }
};

template <typename T>
class Queue{
    private:
        Queue_node<T> *head = NULL;
        Queue_node<T> *tail = NULL;
        int num=0;

    public:
        bool enqueue(T a);
        bool dequeue();
        bool isEmpty(){
            if (this->head==NULL) return true;
            else return false;
        }

        void extreme_elements(){
            cout << "Head at: " << this->head->elem << "Tail at: " << this->tail->elem;
            cout << "\n";
        }

        T at_head(){
            return this->head->elem;
        }

        int size(){
            return this->num;
        }

        void print_queue(){
            Queue_node<T> *print_this = this->head;
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

template <typename T>
bool Queue<T>::enqueue(T a){
    if(this->tail == NULL){
        Queue_node<T>* new_Queue_node = new Queue_node<T>;
        new_Queue_node->elem = a;
        this->head = new_Queue_node;
        this->tail = new_Queue_node;
        this->num++;
        return true;
    }

    Queue_node<T> *new_Queue_node = new Queue_node<T>;
    new_Queue_node->elem = a;

    Queue_node<T>* temp_tail_ptr = this->tail;
    this->tail = new_Queue_node;
    temp_tail_ptr->next = new_Queue_node;
    this->num++;

    return true;

}

// Dequeuing
template <typename T>
bool Queue<T>::dequeue(){
    if(this->isEmpty()){
        cout << "Queue is empty!";
        throw 505;
        return false;
    }

    Queue_node<T> *temp_Queue_node = this->head;
    this->head = this->head->next;
    delete temp_Queue_node;
    this->num--;
    return true;
}
/*
int main(){
    Queue<int> queue;
    queue.enqueue(5);
    queue.enqueue(6);
    queue.print_queue();
    queue.dequeue();
    queue.print_queue();
    queue.enqueue(10);
    queue.enqueue(11);
    queue.print_queue();
    queue.dequeue();
    queue.print_queue();
}
*/
