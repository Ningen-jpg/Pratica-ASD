#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <functional>
//UGUALE AL DFS SOLO CHE UTILIZZIAMO LO STACK
using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;

template<typename T>
class Node{
    public:
    T key, val;
    T discovery = 0;
    T finish = 0;
    Node<T>* parent;
    int color = WHITE;

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
    unordered_map<T, vector<pair<T,T>>> ver;

    void addNode(Node<T>* node){
        nodes.push_back(node);
    }

    void addEdge(T weight, Node<T>* source, Node<T>* destination){
        Edge<T>* edge = new Edge<T>(weight, source, destination);
        edges.push_back(edge);
        //ORIENTATO
        ver[source->val].push_back(make_pair(destination->val, weight));
        ver[destination->val].push_back(make_pair(source->val, weight));
    }

    //PER CONVENZIONE MI SONO DICHIARATO L'OFSTREAM QUI

    void DFS(ofstream &out){
        stack<Node<T>*> topostack;
        for(auto u: nodes){
            u->color = WHITE;
            u->parent = nullptr;
        }
        for(auto u: nodes){
            if(u->color == WHITE){
                DFS_VISIT(u, topostack);
            }
        }

        while(!topostack.empty()){
            Node<T>* node = topostack.top();
            out<<"Nodo in ordine topologico: "<<node->val<<endl;
            topostack.pop();
        }
    }

    void DFS_VISIT(Node<T>* u, stack<Node<T>*> &topostack){
        u->color = GREY;
        u->discovery = ++time;
        for(auto v: ver[u->val]){
            Node<T>* node = nullptr;
            for(auto n: nodes){
                if(n->val == v.first){
                    node = n;
                    break;
                }
            }
            if(node == nullptr){
                continue;
            }
            if(node->val == WHITE){
                node->parent = u;
                DFS_VISIT(node, topostack);
            }
        }
        u->color = BLACK;
        u->finish = ++time;
        topostack.push(u);
    }
};

int main() {
    ifstream in("input.txt");
    int numnodes, numedges;
    in>>numnodes>>numedges;
    unordered_map<int,Node<int>*> nodesmap;
    Graph<int> g;

    for(int i = 0; i < numedges; i++){
        int weight, sourceval, desteval;
        in>>weight>>sourceval>>desteval;

        Node<int>* sourcen = nullptr;
        auto itsource = nodesmap.find(sourceval);
        if(itsource == nodesmap.end()){
            sourcen = new Node<int>(sourceval);
            nodesmap[sourceval] = sourcen;
            g.addNode(sourcen);
        } else {
            sourcen = itsource->second;
        }

        Node<int>* desten = nullptr;
        auto itdeste = nodesmap.find(desteval);
        if(itdeste == nodesmap.end()){
            desten = new Node<int>(desteval);
            nodesmap[desteval] = desten;
            g.addNode(desten);
        } else {
            desten = itdeste->second;
        }
        g.addEdge(weight, sourcen, desten);
    }

    in.close();
    ofstream out("outputtop.txt");
    g.DFS(out);
    out.close();
    cout << "File creato" << endl;
    return 0;
}
