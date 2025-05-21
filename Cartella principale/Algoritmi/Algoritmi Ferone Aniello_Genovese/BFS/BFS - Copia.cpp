#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>

using namespace std;

const int WHITE = 0;
const int GREY = 1;
const int BLACK = 2;
const int infinity = 99999;

template<typename T>
class Node{
    public: 
    T key, val;
    Node<T>* parent;
    T distance;
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
    vector<Node<T>*> nodes;
    vector<Edge<T>*> edges;
    unordered_map<T, vector<pair<T,T>>> adj;

    void addNode(Node<T>* node){
        nodes.push_back(node);
    }
    
    void addEdge(T weight, Node<T>* source, Node<T>* destination){
        Edge<T>* edge = new Edge<int>(weight, source, destination);
        edges.push_back(edge);
        //In questo caso il grafo è orientato, per renderlo non orientato
        //bisogna togliere il secondo adj ed inserire solo il primo
        adj[source->val].push_back(make_pair(destination->val, weight));
        adj[destination->val].push_back(make_pair(source->val, weight));
    }
    //Lo pseudocodice è molto simile, vi consiglio di leggere quello

    void BFS(Node<T>* snode){
        for(Node<T>* node: nodes){
            node->color = WHITE;
            node->parent = nullptr;
            node->distance = infinity;
        }
        snode->color = GREY;
        snode->parent = nullptr;
        snode->distance = 0;
        queue<Node<T>*> q;
        q.push(snode);
        while(!q.empty()){
            Node<T>* u = q.front();
            q.pop();
            for(auto v: adj[u->val]){
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
                    node->color = GREY;
                    node->parent = u;
                    node->distance = u->distance + v.first;
                    q.push(node);
                }
            }
            u->color = BLACK;
        }
    }


};
int main(){
    //Ho usato la lettura e scrittura su file, in genere Ferone lo chiede
    //ma leggete bene la traccia che potrebbe chiedere su video.
    ifstream in("input.txt");
    int numnodes, numedges;
    in>>numnodes>>numedges;
    unordered_map<int, Node<int>*> nodesmap;
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
    Node<int>* snode = g.nodes[0];
    ofstream out("output.txt");
    g.BFS(snode);
    out<<"DISTANZE DAL NODO "<<snode->val<<":\n"<<endl;
    for(Node<int>* node : g.nodes){
        out<<"DISTANZA DAL NODO "<<node->val<<": "<<node->distance<<endl;
    }
    out.close();
    cout<<"File creato"<<endl;
    return 0;
}
