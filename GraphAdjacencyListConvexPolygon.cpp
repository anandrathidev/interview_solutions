#include <iostream>
#include <vector>
#include <map>
#include <array>

using Vertex = int;
using Wight = int;
using Neigours =  std::map<Vertex, Wight> ;

struct Node
{
    Node()= default;
    Node(const Node&)= default;
    Node& operator=(const Node&)= default;
    Node(Node&&)= default;
    Node& operator(Node&&)= default;
    ~Node()= default;
    
    Node(int v):vertex(v){}
    Vertex vertex;
    Neigours mNeigours;
};

using Graph = std::map<Vertex, Node> ;
using Graph100 = std::vector<Vertex> ;


// Simply add a vertex with no connection
void GraphAddNode(Graph& graph, const Node& n)
{
    auto it = graph.find(n.vertex);
    if(it == graph.end())    
    graph[n.vertex] = n;
}


void FormEdge(Graph& graph, const Node& a, const Node& b, int weight)
{
    auto it = graph.begin();
    auto ait = graph.find(a.vertex);
    auto bit = graph.find(b.vertex);
    if(ait!=graph.end() && bit!=graph.end() )
    {
        auto isBit = ait->second.mNeigours.find(b.vertex);
        if(isBit==ait->second.mNeigours.end())
        {
            ait->second.mNeigours[b.vertex] = weight;
        }
        auto isAit = bit->second.mNeigours.find(a.vertex);
        if(isAit==bit->second.mNeigours.end())
        {
            bit->second.mNeigours[a.vertex] = weight;
        }
    }
}

void printGraph(const Graph& graph)
{
    std::cout << std::endl;
    for(auto& v : graph )
    {
        std::cout << "Node:" << v.first << " : ";
        for(auto& n : v.second.mNeigours)
        {
            std::cout << n.first << " : " << n.second << " ,  ";
        }
        std::cout << std::endl;
    }
}

struct Point 
{
    int x;
    int y;
};

struct ConvexPolygon
{
  std::vector<Point> mPoints;
  bool isInside(Point& p)
  {
      
  }

};

int main()
{
    Graph graph;
    GraphAddNode(graph, Node(1));
    GraphAddNode(graph, Node(2));
    GraphAddNode(graph, Node(3));
    GraphAddNode(graph, Node(4));
    FormEdge(graph, Node(1),  Node(2), 12);
    FormEdge(graph, Node(2),  Node(3), 10);
    FormEdge(graph, Node(1),  Node(3), 20);
    FormEdge(graph, Node(1),  Node(4), 70);
    FormEdge(graph, Node(3),  Node(4), 100);
 
    Graph100 g100(100);   // rvalues , capa 100 // pre optmial for 100
    printGraph(graph);
    return 0;
}
