//Name: Kartik Anand
//Roll no: 1903123
#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <math.h>
#include <stack>
#include <queue>
#include <list>

int temp=0;
int temp2=0;
using namespace std;

class DirectedGraph{
    public:
        vector<list<int>> adjacency_list;
        vector<int> vertices;
        size_t N;
        size_t size;

        int clock=0;
        int flag = 0;

        vector<int> distance_vector;
        vector<int> neighbours;

        vector<int> ancestors;

        map<int, int> visited;      // Actual dictionary of visited list. 1 implies node is reachable.
        map<int, int> temp_visited; // Only to maintain track of nodes to identify cycle. 1 implies nodes is still in the recursive stack. 2 implies, it will never be visited again.

        stack<int> vertex_holder;   //No use as such.

        map<int, int> pre;
        map<int, int> post;

        list<int> path;

    public:


        DirectedGraph(size_t N, int populate_adj_mat=0){

            this->N = N;
            this->size = N*N;
            
            this->vertices = vector<int> (this->N,0);
            this->adjacency_list = vector<list<int>> (this->N,list<int> (0,populate_adj_mat));

            for(int i=0; i<this->N; i++){
                this->visited.insert({vertices[i], false});
            }
            this->temp_visited = this->visited;
        }

        void print_visited(){
            cout<<"\n--What Points are reachable--\n";
            cout << "Points" << '\t' << "Visited" << '\n';
            for (auto itr = visited.begin(); itr != visited.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\n';
            }
        }



//////////////////////////////////// Adjacent Matrix ///////////////////////////////////////////////
        /* void input_adj_mat(){
            int added;
            printf("\nInput Adjacent Matrix:\n");
            for(int i = 0; i < this->N; i++){
                for(int j = 0; j < this->N; j++){
                        cin  >> this->adjacency_mat[i][j];
                    }
            }
        } */
        
        void print_adj_list(){
            cout<<"\n--Graph Representation--\n";
            for(int i = 0; i < this->N; i++){
                cout << i << "->";
                for(list<int>::iterator j = adjacency_list[i].begin(); j != adjacency_list[i].end(); j++){
                    cout << *j << " ";
                }
                cout << "\n";
            }
        }

        void enter_edge(){
            int v, u;
            cout<<"Enter the Edge: ";
            
            cin>>v>>u;
            
            
            adjacency_list[v].push_back(u);
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
            this->temp_visited = this->visited;
        }


        // DFS Algorithm
        void DFS(int v){
            if(temp==0){
                cout<<"\n--Implementing DFS Algorithm--\n";
                temp++;
            }
            
            visited[v] = true;
            cout << "Visiting: " << v << "\n";
            for(list<int>::iterator i = adjacency_list[v].begin(); i != adjacency_list[v].end(); ++i){
                if(!visited[*i]){
                    DFS(*i);
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
                    
                    for(list<int>::iterator i = adjacency_list[v].begin(); i != adjacency_list[v].end(); ++i){
                        distance = this->distance_vector[v] + 1;
                        // If the vertex is connected and has not been visited 
                        if(!this->visited[*i]){
                            queue.push(*i);
                            
                            this->neighbours.push_back(*i);
                            if(this->distance_vector[*i]==0 || this->distance_vector[*i]==-1){
                                this->distance_vector[*i] = distance;
                            }
                        }
                    }
                }
            } 
        }

        // Linearisation
        void previsit(int v){
            pre.insert({v, clock});
            clock = clock + 1;
        }

        void postvisit(int v){
            post.insert({v, clock});
            if(temp_visited[v] == 1){
                path.push_front(v);
            }
            clock = clock + 1;
            this->temp_visited[v] = 2;
        }

        void linearisation_algo(int v){
            visited[v] = 1;
            temp_visited[v] = 1;
            
            if(temp2==0){
                cout<<"\n--Implementing DFS Algorithm--\n";
                temp2++;
            }
            previsit(v);          
            cout << "Visiting: " << v << "\n";
            for(list<int>::iterator i = adjacency_list[v].begin(); i != adjacency_list[v].end(); ++i){
                if(temp_visited[*i] == 0){
                    linearisation_algo(*i);
                }
                else if(temp_visited[*i] == 1){
                    flag = 1;
                }
            }
            postvisit(v);
        }

        void linearisation(int v){
            linearisation_algo(v);
            if(flag==0){
                cout<<"\nLinearisation of Graph:\n";
                while(!path.empty()){
                    cout << path.front() << ' ';
                    path.pop_front();
                }
                
                cout<<'\n';
            }

            else if(flag==1){
                cout<<"\nThe graph G is not a DAG.\n";
            }
        }

        void print_pre_map(){
            cout << "\n*Pre Visit Clock*\n";
            for (auto itr = pre.begin(); itr != pre.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\n';
            }
        }

        void print_post_map(){
            cout << "\n*Post Visit Clock*\n";
            for (auto itr = post.begin(); itr != post.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\n';
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

        void print_temp_visited(){
            cout << "\n*Temp Visited*\n";
            for (auto itr = this->temp_visited.begin(); itr != this->temp_visited.end(); ++itr) {
                cout << itr->first << '\t' << itr->second << '\n';
            }
        }

        void print_vector(vector<int> vec){
            for(int i=0; i<vec.size(); i++){
                cout<<vec[i]<<' ';
            }
        }
};

int main(){
    size_t vertices;
    char want_more;

    cout<<"Enter the number of vertices in your graph: ";
    cin >> vertices;

    DirectedGraph G(vertices, 0);

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



    G.print_adj_list();

    
    G.linearisation(1);

    G.print_visited();

    printf("\n");

    /* G.print_temp_visited(); */

    /* G.print_post_map(); */

    /* G.print_distance(); */
}