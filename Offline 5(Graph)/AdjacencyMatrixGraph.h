#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"
#include "queue.h"

class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    int **matrix;
    int sz;
    
    void resizeMatrix(int v)
    {
        //TODO: you need to resize your matrix when you will less data or more data
        int **matrix2 = new int*[v+1];
        for(int i=0;i<=v;i++){
            matrix2[i] = new int[v+1]();
        }
        for(int i=1;i<=sz;i++){
            for(int j=1;j<=sz;j++){
                matrix2[i][j] = matrix[i][j]; 
            }
        }
        for(int i=0;i<=sz;i++) delete[] matrix[i];
        delete[] matrix;
        matrix = matrix2;
        sz = v;
    }

    bool dfsCheckPath(int u, int v, bool visited[]) const {
        if(u==v) return true;
        visited[u] = true;
        for(int i=1;i<=sz;i++){
            if(matrix[u][i] && !visited[i]){
                if(dfsCheckPath(i,v,visited)) return true;
            }
        }
        return false;
    }

public:
    AdjacencyMatrixGraph(){
        matrix = new int*[2];
        matrix[0] = new int[2]();
        matrix[1] = new int[2]();
        sz = 1;
    }

    ~AdjacencyMatrixGraph() {
        for(int i=0; i<=sz; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void AddNode(int v) override
    {
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if(v>sz){
            resizeMatrix(v);
        }
    }

    void AddEdge(int u, int v) override
    {
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);
        matrix[u][v] = 1;
        matrix[v][u] = 1;
    }

    bool CheckEdge(int u, int v) const override
    {
        //TODO: Check whether there is an edge between two nodes u and v
        if(matrix[u][v] || matrix[v][u]) return true;
        return false; 
    }

    void RemoveNode(int v) override
    {
        //TODO: Remove a node.
        if(v<=sz){
            for(int i=1;i<=sz;i++){
                if(matrix[v][i]){
                    matrix[v][i] = matrix[i][v] = 0;
                } 
            }
        } 
    }

    void RemoveEdge(int u, int v) override
    {
        //TODO: remove an edge
        if(u<=sz && v<=sz) matrix[u][v] = matrix[v][u] = 0;
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        bool visited[sz+1];
        for(int i=0;i<=sz;i++) visited[i] = false;
        return dfsCheckPath(u, v, visited);
    }

    void FindShortestPath(int u, int v) const override
    {
        //TODO: Find the shortest path between the nodes u and v and print it.
        if(u==v) {
            cout << "Shortest path from " << u << " to " << v << ": " << u << endl;
            return;
        }
        ListQueue q;
        q.enqueue(u);
        bool visited[sz+1];
        int parent[sz+1];
        for(int i=0;i<=sz;i++){ 
            visited[i] = false;
            parent[i] = -1;
        }
        visited[u] = true;
        bool found = false;
        while(!q.empty()){
            int nd = q.front();
            q.dequeue();
            for(int i=1;i<=sz;i++){
                if(!visited[i] && matrix[nd][i]){  
                    visited[i] = true;
                    q.enqueue(i);
                    parent[i] = nd;
                    if(i== v) {
                        found = true;
                        break;
                    }
                }
            }
        }
        if(found){
            int path[sz+1],pathlen = 0;
            int curr = v;
            while(curr!=-1){
                path[pathlen++] = curr;
                curr = parent[curr];
            }
            for(int i=pathlen-1;i>=0;i--) cout << path[i] << " ";
            cout << endl;
        }else{
            cout << "No path exists between " << u << " and " << v << endl;
        }
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        if(u > sz || v > sz) return -1; 
        if(u == v) return 0; 
        ListQueue q;
        q.enqueue(u);
        bool visited[sz+1];
        int distance[sz+1];
        for(int i=0;i<=sz;i++){ 
            visited[i] = false;
            distance[i] = -1;
        }
        visited[u] = true;
        distance[u] = 0;
        
        while(!q.empty()){
            int nd = q.front();
            q.dequeue();
            for(int i=1;i<=sz;i++){
                if(!visited[i] && matrix[nd][i]){  
                    visited[i] = true;
                    q.enqueue(i);
                    distance[i] = distance[nd]+1;
                    if(i== v) {
                        return distance[i];
                    }
                }
            }
        }
        return -1;
    }

    linkedList GetNeighbors(int u) const override
    {
        //TODO return a list of neighbors of node u
        linkedList list;
        init(&list);
        for(int i= 1;i<=sz;i++){
            if(matrix[u][i]) append(i,&list);
        }
        return list;
    }
};

#endif // ADJACENCY_MATRIX_GRAPH_H
