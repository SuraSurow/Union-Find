#include <iostream>
#include <fstream>
#include "dynamicArray.h"
const int ERROR_FLAG = -1;

class GraphNode
{
public:
    double x , y;
    GraphNode():x(0.0),y(0.0){};
    GraphNode( double x,double y):x(x),y(y){};
};

class GraphEdge
{
public:
    int source,destination;
    double cost;
    GraphEdge():source(0),destination(0),cost(0.0){};
    GraphEdge(int source , int destination, double cost): source(source), destination(destination), cost(cost){};\
};

class Graph
{
public:
    int vertices;
    Dynamic_Array<GraphEdge>edge;
    Dynamic_Array<GraphNode>node;
    explicit Graph(int vertives) :vertices(vertives), edge(), node() {}
    void quickSortEdges() {
        quickSortEdges(0, edge.currentSize - 1);
    }
    void addEdge(int source, int destination, double cost) {
        GraphEdge newEdge(source, destination, cost);
        edge.addObj(&newEdge);
    }

private:
    void quickSortEdges(int low, int high) {
        if (low < high) {
            int pivotIndex = partitionEdges(low, high);
            if (pivotIndex == ERROR_FLAG) {
                std::cerr << "\nError\nquickSortEdges call -> current size = 0\n";
                return;
            }
            quickSortEdges(low, pivotIndex - 1);
            quickSortEdges(pivotIndex + 1, high);
        }
    }

    int partitionEdges(int low, int high) {
        if (edge.currentSize <= 0) {
            return ERROR_FLAG;
        }
        GraphEdge pivot = *edge.getObj(high);
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (edge.getObj(j)->cost <= pivot.cost) {
                i++;
                edge.switchObj(i, j);
            }
        }

        edge.switchObj(i + 1, high);
        return i + 1;
    }
};

class UnionFind
{
    Dynamic_Array<int>parent;
    Dynamic_Array<int>rank;
public:
    UnionFind(int numOfNodes) : parent(numOfNodes), rank(numOfNodes)
    {
        rank.fillOutZeros();
        for (int i = 0; i < numOfNodes; ++i)
        {
            *parent.getObj(i) = i;
        }
    }
    void UnionByRank(int firstNode, int secondNode)
    {
        int root_first = Find(firstNode);
        int root_second = Find(secondNode);
        if ( root_first == ERROR_FLAG )
        {
            std::cerr<<"\nError\nUnion function call -> root_first out of scope\n";
            return;
        }
        if ( root_second  == ERROR_FLAG )
        {
            std::cerr<<"\nError\nUnion function call -> root_second out of scope\n";
            return;
        }
        if ( root_second == root_first)
        {
            return;
        }
        if (*rank.getObj(root_first) < *rank.getObj(root_second))
        {
            *parent.getObj(root_first) = root_second;
        }
        else if ( *rank.getObj(root_first) > *rank.getObj(root_second))
        {
            *parent.getObj(root_second) = root_first;
        }
        else
        {
            *parent.getObj(root_second) = root_first;
            (*rank.getObj(root_first))++;
        }
    }
    void Union(int firstNode, int secondNode) {
        int root_first = Find(firstNode);
        int root_second = Find(secondNode);
        if (root_first == ERROR_FLAG || root_second == ERROR_FLAG) {
            std::cerr << "\nError\nUnion function call -> root_first or root_second out of scope\n";
            return;
        }
        if (root_second != root_first) {
            *parent.getObj(root_first) = root_second;
        }
    }
    int Find(int indexNode)
    {
        if(indexNode> parent.currentSize || indexNode < 0 ){
            std::cerr<<"\nError\nFind function call -> Index out of scope!!!\n";
            return ERROR_FLAG;
        }
        if(*parent.getObj(indexNode ) != indexNode)
        {
            *parent.getObj(indexNode )= Find(*parent.getObj(indexNode));
        }
        return *parent.getObj(indexNode);
    }
};
static Graph kruskal(Graph graf)
{
    graf.quickSortEdges();
    UnionFind unionFind(graf.vertices);
    Graph minSpanningTree(graf.vertices);
    for (int i = 0; i < graf.edge.currentSize; ++i)
    {
        int sourceRoot = unionFind.Find(graf.edge.getObj(i)->source);
        int destRoot = unionFind.Find(graf.edge.getObj(i)->destination);
        if (sourceRoot != destRoot)
        {
            minSpanningTree.edge.addObj(graf.edge.getObj(i));
            unionFind.UnionByRank(sourceRoot, destRoot);
        }
    }
    return minSpanningTree;
}


Graph read(const std::string &name)
{
    std::ifstream file(name);
    if( file.bad()){
        std::cerr<<"\nERROR\nFILE = '"<<&name<<"' are bad!!!\n";
    }
    else if ( file.eof()){
        std::cerr<<"\nERROR\nFILE = '"<<&name<<"' are eof!!!\n";
    }
    else if ( file.fail()){
        std::cerr<<"\nERROR\nFILE = '"<<&name<<" 'are fail!!!\n";
    }
    else
    {
        int node , edge;
    }
}
;


int main (void)
{

    std::string file = "C:\\Users\\admin\\CLionProjects\\Union-Find\\Pklesk_kruskal_union_find\\excercises\\g1.txt";
}