#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

const int ERROR_FLAG = -1;
int licznikFind = 0;


//-----------
template<typename Data_type>
class Dynamic_Array {

public:
    Data_type* array;
    unsigned int currentSize;
    unsigned int maxSize;
    float growthRate;

    Dynamic_Array() : currentSize(0), maxSize(1), growthRate(2.0) {
        array = new Data_type[maxSize];
    }
    Dynamic_Array(unsigned int max) : currentSize(0), maxSize(max), growthRate(2.0) {
        array = new Data_type[maxSize];
    }
    Dynamic_Array(const Dynamic_Array<Data_type> &otherDynamic) {
        maxSize = otherDynamic.maxSize;
        currentSize = otherDynamic.currentSize;
        growthRate = otherDynamic.growthRate;
        array = new Data_type[maxSize];
        for (unsigned int i = 0; i < currentSize; i++) {
            array[i] = otherDynamic.array[i];
        }
    }

    ~Dynamic_Array() {
        delete[] array;
    }

    Data_type * getObj(unsigned int indeks) const {
        if (indeks >= currentSize) {
            std::cerr << "\n'getObj(" << indeks << ") indeks większy lub równy od rozmiaru tablicy!!\n";
            return nullptr;
        }
        return &array[indeks];
    }

    bool objExist( Data_type& value) const {
        for (unsigned int i = 0; i < currentSize; ++i) {
            if (*getObj(i) == value) {
                return true;
            }
        }
        return false;
    }

    void addObj(Data_type *obj) {
        if (currentSize == maxSize) {
            maxSize *= growthRate;
            Data_type *newArray = new Data_type[maxSize];
            for (unsigned int i = 0; i < currentSize; i++) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        array[currentSize] = *obj;
        currentSize++;
    }

    void switchObj(unsigned int indexOne, unsigned int indexTwo) {
        if (indexOne < currentSize && indexTwo < currentSize) {
            Data_type temp = array[indexOne];
            array[indexOne] = array[indexTwo];
            array[indexTwo] = temp;
        } else {
            std::cerr << "Nieprawidłowy indeks." << std::endl;
        }
    }
};
//-----------

class GraphNode
{
public:
    double x , y;
    GraphNode():x(0.0),y(0.0){};
    GraphNode( double x,double y):x(x),y(y){};

    bool operator==(const GraphNode& other) const {
        return (x == other.x) && (y == other.y);
    }
};

class GraphEdge
{
public:
    int source,destination;
    double cost;
    GraphEdge():source(0),destination(0),cost(0.0){};
    GraphEdge(int source , int destination, double cost): source(source), destination(destination), cost(cost){};
};

class Graph
{
public:
    int vertices;
    Dynamic_Array<GraphEdge>edge;
    Dynamic_Array<GraphNode>node;
     Graph(int vertives) :vertices(vertives), edge(), node() {}

    void addEdge(int source, int destination, double cost) {
        if (source < vertices && destination < vertices) {
            GraphEdge newEdge(source, destination, cost);
            edge.addObj(&newEdge);
        } else {
            std::cerr << "Błąd dodawania krawędzi: Wierzchołki nie istnieją!" << std::endl;
        }
    }

    void addNode(double x, double y) {
        GraphNode newNode(x, y);

        if (!node.objExist(newNode)) {
            node.addObj(&newNode);
        } else {
            std::cerr << "Błąd dodawania węzła: Węzeł już istnieje!" << std::endl;
        }
    }
    void quickSortEdges() {
        quickSortEdges(0, edge.currentSize - 1);
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
        for (int i = 0; i < numOfNodes; ++i)
        {
            int *addParent = new int(i);
            int *addRank = new int (0);
            parent.addObj(addParent);
            rank.addObj(addRank);
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
        licznikFind++;
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


Graph read(const std::string &name) {
    std::ifstream file(name);
    if (!file.is_open()) {
        std::cerr << "\nERROR\nCould not open file: " << name << "\n";
        return Graph(0);  // Zwróć pusty graf w przypadku problemu z otwarciem pliku
    }

    int numNodes = 0;
    int numEdges = 0;
    file >> numNodes;

    Graph output(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        double x = 0;
        double y = 0;
        if (!(file >> x >> y)) {
            std::cerr << "\nERROR\nFailed to read coordinates for node " << i << "\n";
            return Graph(0);
        }
        output.addNode(x, y);
    }

    file >> numEdges;
    for (int i = 0; i < numEdges; i++) {
        int source, destination;
        double cost;
        if (!(file >> source >> destination >> cost)) {
            std::cerr << "\nERROR\nFailed to read edge information for edge " << i << "\n";
            return Graph(0);
        }
        output.addEdge(source, destination, cost);
    }

    file.close();
    return output;
}


int main(void) {
    for (int i = 1; i <= 3; ++i) {
        std::string filename = "C:\\Users\\admin\\CLionProjects\\Union-Find\\Pklesk_kruskal_union_find\\excercises\\g" + std::to_string(i) + ".txt";
        Graph graf = read(filename);

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        Graph mts = kruskal(graf);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> duration = end - start;

        std::cout << "\nFile:\tg" << i <<".txt"<< std::endl;
        std::cout << "Edge:\t" << mts.edge.currentSize << std::endl;
        std::cout << "Find():\t"<<licznikFind<<std::endl;
        licznikFind=0;

        double Cost = 0.0;
        for (int i = 0; i < mts.edge.currentSize; ++i) {
            Cost += mts.edge.getObj(i)->cost;
        }
        std::cout << "Weight\t: " << Cost << std::endl;
        std::cout << "Time\t: " << std::fixed << std::setprecision(5) << duration.count() << " sekundy." << std::endl;

        std::cout << std::endl;
    }

    return 0;
}

