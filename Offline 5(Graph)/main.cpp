#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GraphADT.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
using namespace std;

int main(){
    AdjacencyListGraph *g = new AdjacencyListGraph();
    g->AddEdge(1,2);
    g->AddEdge(2,3);
    g->AddEdge(3,4);
    cout << g->isDFSCycle() << '\n';
}