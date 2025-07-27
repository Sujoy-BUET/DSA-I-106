#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include "queue.h"

class AdjacencyListGraph : public GraphADT{
private:
    // TODO: Take necessary private members
    linkedList *arr;  
    int size;      
    int capacity;  
    
    void resize(int nw_capa){
        linkedList *arr2 = new linkedList[nw_capa+1];
        for(int i=0;i<=nw_capa;i++){
            init(&arr2[i]);
        }
        for(int i=1;i<=size;i++){
            node *nd = arr[i].head;
            while(nd!=NULL){
                append(nd->element,&arr2[i]);
                nd = nd->next;
            }
            free_list(&arr[i]);
        }
        delete[] arr;
        arr = arr2;
        capacity = nw_capa;
    }

    bool dfs_search(int u,int v,bool visited[])const{
        if(u==v) return true;
        visited[u] = true;
        node *curr = arr[u].head;
        while(curr!=NULL){
            int x = curr->element;
            if(!visited[x] && dfs_search(x,v,visited)) return true;
            curr = curr->next;
        }
        return false;
    }
public:
    AdjacencyListGraph(){
        size = 0;
        capacity = 1;
        arr = new linkedList[capacity+1];
        for(int i=0;i<=capacity;i++){
            init(&arr[i]);
        }
    }
    ~AdjacencyListGraph() {
        for(int i = 0; i <= capacity; i++) {
            free_list(&arr[i]);
        }
        delete[] arr;
    }
    void AddNode(int v) override{
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
        if(v > capacity) resize(v);
        if(v > size) size = v;
    }

    void AddEdge(int u, int v) override{
        //TODO: Add a new edge between the nodes u and v
        AddNode(u);
        AddNode(v);
        if (!is_present(v, &arr[u])) {
            append(v, &arr[u]);
        }
        if (!is_present(u, &arr[v])) {
            append(u, &arr[v]);
        }
    }

    bool CheckEdge(int u, int v) const override{
        //TODO: Check whether there is an edge between two nodes u and v
        if(u > size || v > size || u <= 0 || v <= 0) return false;
        if(is_present(v,&arr[u])) return true;
        return false;
    }

    void RemoveNode(int v) override{
        //TODO: Remove a node.
        node *curr = arr[v].head;
        while(curr!=NULL){
            int neighbor = curr->element;
            delete_item(v,&arr[neighbor]);
            curr = curr->next;
        }
        free_list(&arr[v]);
        init(&arr[v]);
    }

    void RemoveEdge(int u, int v) override{
        //TODO: remove an edge
         if(u > size || v > size || u <= 0 || v <= 0) return;
        delete_item(u,&arr[v]);
        delete_item(v,&arr[u]);
    }

    bool CheckPath(int u, int v) const override{
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        bool visited[size+1];
        for(int i=0;i<=size;i++) visited[i] = false;
        return dfs_search(u,v,visited);
    }

    void FindShortestPath(int u, int v) const override{
        //TODO: Find the shortest path between the nodes u and v and print it.
        if(u==v){
            printf("Shortest path from %d to %d: %d\n",u,v,u);
            return;
        }
        ListQueue queue;
        queue.enqueue(u);
        bool visited[size+1];
        int parent[size+1];
        for(int i=0;i<=size;i++){
            visited[i] = false;
            parent[i] = -1;
        }
        visited[u] = true;
        bool found = false;
        while(!queue.empty()){  
            int x = queue.dequeue();
            node *curr = arr[x].head;
            while(curr!=NULL){
                int neighbor = curr->element;
                if(!visited[neighbor]){
                    queue.enqueue(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = x;
                    if(neighbor == v){
                        found = true;
                        break;
                    }
                }
                curr = curr->next;
            }
        }
        if(!found){
            printf("No path exists between %d and %d\n", u, v);
            return;
        }
        int curr = v;
        int path[size+1];
        int path_length = 0;
        while(curr != -1){
            path[path_length++] = curr;
            curr = parent[curr];
        }
        for(int i=path_length-1;i>=0;i--){
            printf("%d ", path[i]);
        }
        printf("\n");
    }

    int FindShortestPathLength(int u, int v) const override
    {
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
        int distance[size+1];
        for(int i=0;i<=size;i++) distance[i] = -1;
        distance[u] = 0;
        ListQueue queue;
        queue.enqueue(u);
        while(!queue.empty()){
            int x = queue.dequeue();
            node *curr = arr[x].head;
            while(curr!=NULL){
                int neighbor = curr->element;
                if(distance[neighbor] == -1){
                    distance[neighbor] = distance[x] + 1;
                    queue.enqueue(neighbor);
                    if(neighbor == v) return distance[v];
                }
                curr = curr->next;
            }
        }
        return -1; 
    }

    linkedList GetNeighbors(int u) const override
    {
        //TODO: Return the list of neighbors.
        return arr[u];
    }

    bool isBFSCycle(){
        //TODO: Find the shortest path between the nodes u and v and print it.
        ListQueue queue;
        queue.enqueue(arr[1].head->element);
        bool visited[size+1];
        int parent[size+1];
        for(int i=0;i<=size;i++){
            visited[i] = false;
            parent[i] = -1;
        }
        visited[arr[1].head->element] = true;
        bool found = false;
        while(!queue.empty()){  
            int x = queue.dequeue();
            node *curr = arr[x].head;
            while(curr!=NULL){
                int neighbor = curr->element;
                if(!visited[neighbor]){
                    queue.enqueue(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = x;
                }else{
                    if(parent[x]!=neighbor) return true;
                }
                curr = curr->next;
            }
        }
        return false;
    }

    bool isDFSCycleUtil(int u,int par,bool visited[]){
        visited[u] = true;
        node *curr = arr[u].head;
        while(curr!=NULL){
            int x = curr->element; 
            if(!visited[x]){ 
                if(isDFSCycleUtil(x,u,visited))
                    return true;
            }else if(x!=par){
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool isDFSCycle(){
        bool visited[size+1]={0};
        for(int i=1;i<=size;i++){
            if(!visited[i]){
                if(isDFSCycleUtil(arr[1].head->element,-1,visited)) return true;
            }
        }  
        return false;
    }
};
#endif  //ADJACENCY_LIST_GRAPH_H





// #ifndef ADJACENCY_LIST_GRAPH_H
// #define ADJACENCY_LIST_GRAPH_H

// #include "GraphADT.h"
// #include "queue.h"
// class AdjacencyListGraph : public GraphADT
// {
// private:
//     linkedList* graph = NULL;
//     int row=0;

//     node* findNode(int v) const
//     {
//         if (graph == NULL)
//         {
//             return NULL;
//         }
//         node* temp = graph->head;
//         while (temp != NULL){
//             if (temp->element == v)
//             {
//                 return temp;
//             }
//             temp = temp->next;
//         }
//         return NULL;
//     }
    
//     int BFS(int u, int v,int *&path) const
//     {
//         if (u == v){
//             path = new int[1]; 
//             path[0] = u;
//             return 0;
//         }
//         if (graph == NULL || findNode(u) == NULL || findNode(v) == NULL){
//             return -1;
//         }

//         ListQueue queue;

//         int visited[row + 1];
//         int distance[row + 1];
//         int parent[row + 1];

//         for(int i = 0; i <= row; i++)
//         {
//             visited[i] = 0;
//             distance[i] = -1;
//             parent[i] = -1;
//         }

//         visited[u] = 1;
//         distance[u] = 0;
//         queue.enqueue(u);

//         while(!queue.empty()){
//             int current = queue.dequeue();
//             node* currentNode = findNode(current);
//             if (currentNode != NULL && currentNode->adjacencyList != NULL){
//                 node* adj = currentNode->adjacencyList->head;
//                 while(adj != NULL)
//                 {
//                     int neighbor = adj->element;
//                     if(!visited[neighbor])
//                     {
//                         visited[neighbor] = 1;
//                         distance[neighbor] = distance[current] + 1;
//                         parent[neighbor] = current;
//                         queue.enqueue(neighbor);
//                         if(neighbor == v){
//                             int path_length = distance[v];
//                             path = new int[path_length + 1];
//                             int curr = v;
//                             for(int i = path_length; i >= 0; i--) {
//                                 path[i] = curr;
//                                 curr = parent[curr];
//                             }
//                             return path_length;
//                         }
//                     }
//                     adj = adj->next;
//                 }
//             }
//         }
//         return -1;
//     }

// public:
//     AdjacencyListGraph(){
//         row = 0;
//         graph = new linkedList;
//         init(graph);
//     }
//     ~AdjacencyListGraph(){
//         if (graph != NULL) {
//             node* temp = graph->head;
//             while(temp != NULL) {
//                 if (temp->adjacencyList != NULL) {
//                     free_list(temp->adjacencyList);
//                     delete temp->adjacencyList;
//                 }
//                 temp = temp->next;
//             }
//             free_list(graph);
//             delete graph;
//         }
//     }
//     void AddNode(int v) override{
//         // if (graph == NULL){
//         //     graph = new linkedList;
//         //     init(graph);
//         // }
//         if (findNode(v) != NULL) return;
//         append(v, graph);
//         node* newNode = graph->tail; 
//         if (newNode != NULL){
//             newNode->adjacencyList = new linkedList;
//             init(newNode->adjacencyList);
//         }
//         if (v > row) row = v;
//     }

//     void AddEdge(int u, int v) override
//     {
//         if (u < 0 || v < 0){
//             std::cout << "Invalid node values." << std::endl;
//             return;
//         }
//         if (graph == NULL){
//             graph = new linkedList;
//             init(graph);
//         }
//         if (findNode(u) == NULL) AddNode(u);
//         if (findNode(v) == NULL) AddNode(v);
    
//         node* ndU = findNode(u);
//         node* ndV = findNode(v);

//         if (ndU != NULL && ndV != NULL){
//             if (!is_present(v, ndU->adjacencyList)) append(v, ndU->adjacencyList);
//             if (!is_present(u, ndV->adjacencyList)) append(u, ndV->adjacencyList);
//         }
//     }

//     bool CheckEdge(int u, int v) const override
//     {
//         if (graph == NULL){
//             return false;
//         }
//         bool flag1 = false;
//         bool flag2 = false;
//         node* temp = graph->head;
//         while(temp != NULL){
//             if(temp->element == u && is_present(v, temp->adjacencyList)){
//                 flag1 = true;
//             }
//             else if(temp->element == v && is_present(u, temp->adjacencyList)){
//                 flag2 = true;
//             }
//             temp = temp->next;
//         }
//         return flag1 && flag2;
//     }

//     void RemoveNode(int v) override{
//         if (graph == NULL){
//             std::cout << "Graph is empty." << std::endl;
//             return;
//         }

//         node* temp = graph->head;
//         while(temp != NULL)
//         {
//             if(is_present(v, temp->adjacencyList)){
//                 delete_item(v, temp->adjacencyList);
//             }
//             temp = temp->next;
//         }
//         delete_item(v, graph);
//     }

//     void RemoveEdge(int u, int v) override
//     {
//         if (graph == NULL){
//             std::cout << "Graph is empty." << std::endl;
//             return;
//         }
//         node* temp = graph->head;
//         while(temp != NULL)
//         {
//             if(temp->element == u) delete_item(v, temp->adjacencyList);
//             else if(temp->element == v) delete_item(u, temp->adjacencyList);
//             temp = temp->next;
//         }
//     }

//     bool CheckPath(int u, int v) const override
//     {
//         if (graph == NULL || findNode(u) == NULL || findNode(v) == NULL){
//             return false;
//         }
//         int *shortest_path = NULL;
//         return BFS(u, v, shortest_path) != -1;
//     }

//     void FindShortestPath(int u, int v) const override
//     {
//         int *shortest_path = NULL;
//         int len = BFS(u, v, shortest_path);
//         if (len != -1) {
//             for(int i = 0; i <= len; i++) {
//                 std::cout << shortest_path[i] << " ";
//             }
//             std::cout << std::endl;
//             delete[] shortest_path;
//         } 
//         else {
//             std::cout << "No path found." << std::endl;
//         }
//     }

//     int FindShortestPathLength(int u, int v) const override
//     {
//         if(graph == NULL || findNode(u) == NULL || findNode(v) == NULL){
//             return -1;
//         }
//         int *shortest_path = NULL;
//         int pathLength = BFS(u, v, shortest_path);
//         return pathLength;
//     }

//     linkedList GetNeighbors(int u) const override
//     {
//         node* NodeU = findNode(u);
//         linkedList Neighbor;
//         init(&Neighbor);
//         if (NodeU == NULL){
//             std::cout << "Node not found" << std::endl;
//             return Neighbor;
//         }
//         if(NodeU->adjacencyList == NULL || size(NodeU->adjacencyList) == 0)
//         {
//             std::cout << "No Neighbor found for node " << u << std::endl;
//             return Neighbor;
//         }
//         NodeU = NodeU->adjacencyList->head;

//         while(NodeU != NULL){
//             append(NodeU->element, &Neighbor);
//             NodeU = NodeU->next;
//         }
//         return Neighbor;
//     }
// };

// #endif // ADJACENCY_LIST_GRAPH_H



