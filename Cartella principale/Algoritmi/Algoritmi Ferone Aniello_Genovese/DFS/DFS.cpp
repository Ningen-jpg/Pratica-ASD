#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;

template<typename T>
class Node{
    public:
    T val, key;
    T discovery = 0;
    T finish = 0;
    int color = WHITE;
    Node<T>* parent;


    Node(T val) : val(val){}
};

template<typename T>
class Edge{
    public:
    T weight;
    Node<T>* source;
    Node<T>* destination;

    Edge(T weight, Node<T>* source, Node<T>* destination) : weight(weight), source(source), destination(destination){}
};

template<typename T>
class Graph{
    public:
    T time = 0;
    vector<Node<T>*> nodes;
    vector<Edge<T>*> edges;
    map<T, vector<pair<T,T>>> ver;

    void addNode(Node<T>* node){
        nodes.push_back(node);
    }

    void addEdge(T weight, Node<T>* source, Node<T>* destination){
        Edge<T>* edge = new Edge<T>(weight, source, destination);
        edges.push_back(edge);
        //GRAFO NON ORIENTATO
        ver[source->val].push_back(make_pair(destination->val, weight));
       
    }

    void DFS(){
        for(auto u: nodes){
            u->color = WHITE;
            u->parent = nullptr;
        }
        for(auto u: nodes){
            if(u->color == WHITE){
                DFS_VISIT(u);
            }
        }
    }

    void DFS_VISIT(Node<T>* u){
        u->color = GREY;
        u->discovery = ++time;
        for(auto v : ver[u->val]){
            Node<T>* node = nullptr;
            for(Node<T>* n: nodes){
                if(n->val == v.first){
                    node = n;
                    break;
                }
            }
            if(node == nullptr){
                continue;
            }
            if(node->color == WHITE){
                node->parent = u;
                DFS_VISIT(node);
            }
        }
        u->color = BLACK;
        u->finish = ++time;
    }

};

int main() {
    ifstream in("input.txt");
    int numNode, numEdge;
    in >> numNode >> numEdge;
    unordered_map<int, Node<int>*> nodesMap;
    Graph<int> g;

    for (int i = 0; i < numEdge; i++) {
        int weight, sourceVal, destinationVal;
        in >> sourceVal >> destinationVal >> weight;
        Node<int>* sourceNode = nullptr;
        auto itSource = nodesMap.find(sourceVal);
        if (itSource == nodesMap.end()) {
            sourceNode = new Node<int>(sourceVal);
            nodesMap[sourceVal] = sourceNode;
            g.addNode(sourceNode);
        } else {
            sourceNode = itSource->second;
        }

        Node<int>* destinationNode = nullptr;
        auto itDestination = nodesMap.find(destinationVal);
        if (itDestination == nodesMap.end()) {
            destinationNode = new Node<int>(destinationVal);
            nodesMap[destinationVal] = destinationNode;
            g.addNode(destinationNode);
        } else {
            destinationNode = itDestination->second;
        }
        g.addEdge(weight, sourceNode, destinationNode);
    }
    in.close();
    g.DFS();
    ofstream out("output.txt");
    for(Node<int>* node: g.nodes){
          out << "Nodo: " << node->val << ", tempo di scoperta: " << node->discovery << ", tempo di completamento: " << node->finish<< endl;
    }
    out.close();
    //cout << "File creato" << endl;
    return 0;
}
