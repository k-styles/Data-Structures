//Name: Kartik Anand
//Roll no: 1903123
#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <math.h>
#include <stack>
#include <queue>
using namespace std;

class UndirectedGraph{
    public:
        vector<vector<int>> adjacency_mat;
        vector<int> vertices;
        size_t N;
        size_t size;

        vector<int> distance_vector;
        vector<int> neighbours;

        map<int, bool> visited;

    public:


        UndirectedGraph(size_t N, int populate_adj_mat=0){

            this->N = N;
            this->size = N*N;
            
            this->vertices = vector<int> (this->N,0);
            this->adjacency_mat = vector<vector<int>> (this->N,vector<int> (this->N,populate_adj_mat));

            for(int i=0; i<this->N; i++){
                this->visited.insert({vertices[i], false});
            }
        }

        void print_visited(){
            cout<<"\n--What points are reachable--\n";
            cout << "Points" << '\t' << "Visited" << '\n';
            for (auto itr = visited.begin(); itr != visited.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\n';
            }
        }



//////////////////////////////////// Adjacent Matrix ///////////////////////////////////////////////
        /* void input_adj_mat(){
            printf("\nInput Adjacent Matrix:\n");
            for(int i = 0; i < this->N; i++){
                for(int j = 0; j < this->N; j++){
                        cin  >> this->adjacency_mat[i][j];
                    }
            }
        } */
        
        void print_adj_mat(){
            cout<<"\n--Adjacency Matrix--\n";
            cout << "   _";
            for(int i=0; i<this->N; i++){
                cout << i << "_";
            }
            cout<<"\n";
            for(int i = 0; i < this->N; i++){
                cout << i << " | ";
                for(int j = 0; j < this->N; j++){
                    cout << this->adjacency_mat[i][j] << " ";
                }
                cout << "\n";
            }
        }

        void enter_edge(){
            int v, u;
            cout<<"Enter the Edge: ";
            
            cin>>v>>u;
            
            
            adjacency_mat[v][u]=1; adjacency_mat[u][v]=1;
            printf("\nEdge (%d, %d) added.\n", v, u);
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////
        // Initialises vertix vector and visited nodes
        void input_vertices(){
            for(int i=0; i<N; i++){
                this->vertices[i] = i;
            }

          
            // Updating Visited map
            for(int i=0; i<this->N; i++){
                this->visited.insert({vertices[i], false});
            }
        }


        // DFS Algorithm

        void DFS(int v){    
            cout << "\n///////////// Implementing Depth First Search /////////////\n";
            cout << "Source Node: " << v <<'\n';
            stack<int> stack;
            stack.push(v);

            while(!stack.empty()){
                v = stack.top();
                stack.pop();

                if(!this->visited[v]){
                    visited[v]=true;
                    cout << "Visiting: " << v << '\n';
                    // Looping for all other vertices
                    for(int u=0; u < this->N; u++){
                        // If the vertex is connected and has not been visited 
                        if((this->adjacency_mat[v][u]==1) && (!this->visited[u])){
                            stack.push(u);
                        }
                    }
                }
            }
            
            
        }


        // BFS Algorithm
        void BFS(int v){    
            cout << "\n///////////// Implementing Breadth First Search /////////////\n";
            cout << "Source Node: " << v <<'\n';
            queue<int> queue;
            queue.push(v);

            this->distance_vector = vector<int> (this->N,-1);
            this->distance_vector[v] = 0;

            int distance=0;

            while(!queue.empty()){
                v = queue.front();
                queue.pop();

                if(!this->visited[v]){
                    visited[v]=true;
                    cout << "Visiting: " << v << '\n';
                    // Looping for all other vertices
                    
                    for(int u=0; u < this->N; u++){
                        distance = this->distance_vector[v] + 1;
                        // If the vertex is connected and has not been visited 
                        if((this->adjacency_mat[v][u]==1) && (!this->visited[u])){
                            queue.push(u);
                            
                            /* this->neighbours.push_back(u); */
                            if(this->distance_vector[u]==0 || this->distance_vector[u]==-1){
                                this->distance_vector[u] = distance;
                            }
                        }
                    }
                }
            } 
        }

        void print_distance(){
            cout<<'\n';
            cout << "--Distance from the source node--\n";
            cout << "Points" << "\t" << "Distance\n";
            for(int i  = 0; i < this->N; i++){
                cout << i << "\t" << this->distance_vector[i] << '\n';
            }
            cout<<'\n';
        }
};

int main(){
    size_t vertices;
    char want_more;

    cout<<"Enter the number of vertices in your graph: ";
    cin >> vertices;

    UndirectedGraph G(vertices, 0);

    G.input_vertices();

    while (true){
        cout<<"Do you want to enter more edges? (y/n): ";
        cin>>want_more;
        if(want_more=='y'){
            G.enter_edge();
        }
        else{
            break;
        }
    }



    G.print_adj_mat();

    
    G.BFS(1);

    G.print_visited();

    G.print_distance();
}