#include <iostream>
#include <stdio.h>
using namespace std;
template<typename T>
class MinHeap{
    public:
        int size = 1;
        T* arr = new T[this->size];
        
    public:
        // Constructor
        MinHeap(T* arr, int size){
            this->size = size;
            this->arr = arr;

            T* heap = new T[this->size];

            heap[0] = this->arr[0];
            for(int i = 2; i<=this->size; i++){
                heap[i-1] = this->arr[i-1];
                int j = i;
                while(heap[j/2 - 1]>heap[j-1]){
                    T temp = heap[j/2 - 1];
                    heap[j/2 - 1] = heap[j-1];
                    heap[j-1] = temp;
                    j = j/2;
                    if((j/2 -1) <0) break;
                }
            }
            this->arr = heap;
        }
        // Prints heap
        void print_heap(){
            int i = 0;
            while(i < this->size){
                if(i==this->size-1) cout << this->arr[i];
                else cout << this->arr[i] << ",";
                i++;
            }
            cout << "\n";
        }

        // Returns parent index (naive in nature)
        int parent_index(int i){
            int j = i + 1;
            return j/2 - 1;
        }
        // Returns left child index (naive in nature)
        int left_child_index(int i){
            int j = i + 1;
            return 2*j - 1;
        }
        // Returns right child index (naive in nature)
        int right_child_index(int i){
            int j = i + 1;
            return 2*j;
        }
        // Returns index of the minimum child
        int min_child_index(int i){
            int left_child = left_child_index(i);
            int right_child = right_child_index(i);
            if (left_child>=this->size) throw "Index: has no left child.\n";
            if (right_child>=this->size) throw "Index: has no right child.\n";
            if (arr[left_child] <= arr[right_child]) return left_child;
            if (arr[left_child] > arr[right_child]) return right_child;
            return false;
        }
        // Insert a new element to the heap while still satifying the heap property
        bool add_element(T a){
            this->size++;
            int new_elem_index = this->size-1;
            this->arr[new_elem_index] = a;

            bubble_up(new_elem_index);
            return true;
        }

        // Useful functions///////////////////////////////////////
        bool bubble_up(int index){
            while(this->arr[parent_index(index)] > this->arr[index]){
                int fake_parent = parent_index(index);
                
                //swap
                T temp = this->arr[index];
                this->arr[index] = this->arr[parent_index(index)];
                this->arr[parent_index(index)] = temp;

                //assign bubbled up element's index as previous parent's index
                index = fake_parent;
                if(parent_index(index)<0) break;
            }
            return true;
        }

        // Tells if left side is unstable 
        bool left_unstable(int index){
            if (this->left_child_index(index)>=this->size)return false;
            if (this->arr[index] > this->arr[left_child_index(index)]) return true;
            return false;

        }
        // Tells if right side is unstable
        bool right_unstable(int index){
            if (this->right_child_index(index)>=this->size)return false;
            if (this->arr[index] > this->arr[right_child_index(index)]) return true;
            return false;
        }

        // Bubbles down the incorrectly placed element (if required)
        bool bubble_down(int index){
            if((this->left_child_index(index)>this->size) && (this->right_child_index(index)>this->size)){
                throw "Index:  has no child.";
            }
            // verify that node has to move down
            while(left_unstable(index) || right_unstable(index)){

                // if both sides are unstable
                if(left_unstable(index) && right_unstable(index)){
                    int fake_child_index = this->min_child_index(index);

                    //swap
                    T temp = this->arr[index];
                    this->arr[index] = this->arr[fake_child_index];
                    this->arr[fake_child_index] = temp;

                    //assign bubbled down element's index as previous child's index
                    index = fake_child_index;                    
                }

                // if only left side is unstable
                if(left_unstable(index) && !right_unstable(index)){
                    int fake_child_index = left_child_index(index);

                    //swap
                    T temp = this->arr[index];
                    this->arr[index] = this->arr[fake_child_index];
                    this->arr[fake_child_index] = temp;

                    //assign bubbled down element's index as previous child's index
                    index = fake_child_index;
                    /* if(this->left_child_index(index)>=this->size) break; */
                    /* printf("hello\n"); */
                }

                // if only right side is unstable
                if(!left_unstable(index) && right_unstable(index)){
                    int fake_child_index = right_child_index(index);

                    //swap
                    T temp = this->arr[index];
                    this->arr[index] = this->arr[fake_child_index];
                    this->arr[fake_child_index] = temp;

                    //assign bubbled down element's index as previous child's index
                    index = fake_child_index;
                }              
            }

            return true;
        }
        /////////////////////////////////////////////////////////
        ///////////////////Removing Methods//////////////////////
        // Removes head element and reorder such as to satisfy heap property
        bool poll(){
            int last_index = this->size-1;
            int head_index = 0;

            //swap head and last element
            T temp = this->arr[last_index];
            this->arr[last_index] = this->arr[head_index];
            this->arr[head_index] = temp;

            //decrease size
            this->size--;
            
            //bring down the element at the head if necessary
            this->bubble_down(head_index);

            return true;
        }

        
};

int main(){
    int arr[7] = {1, 2, 6, 0, 9, 14, 3};
    MinHeap<int> heap(arr, 7);
    heap.add_element(-1);
    heap.add_element(0);
    heap.poll();
    heap.poll();
    heap.poll();
    heap.print_heap();
}