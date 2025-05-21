/*
Traccia di Maggio 2023


Prossimo step da fare:
.Dotare la classe dei metodi PRIM() e PRINT_MST() per calcolare e stampare a video
il minimum spanning tree. (pt. 6)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>

using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;
const int inf = 999999;


class Node {
    public:

    int val;
    int key;
    int distance;
    int color = WHITE;
    Node * parent;

    Node(int key ): key(key){
        parent = nullptr;
    }
};
class Compare{
    bool operator() (Node * l, Node * r)
    {
        return l->val > r->val;
    }
};

class Edge{
    public:
    int weight;
    Node * source;
    Node * destination;
    Edge(int weight, Node * source, Node * destination):weight(weight),source(source),destination(destination){}
};

class Graph{
    public:
    vector <Node *> nodes;
    vector <Edge *> edges;

    unordered_map<int,vector<pair<int,int>>> adjList;

    void addNode(Node * nodo)
    {
        nodes.push_back(nodo);
    }

    void addEdge(Node * source, Node * destination,int weight)
    {
        Edge * arco = new Edge(weight,source,destination);

        //aggiornare la adjList per entrambi i versi visto che il grafo é non direzionato
        adjList[source->key].push_back(make_pair(destination->key,weight));
        adjList[destination->key].push_back(make_pair(source->key,weight));

    }

    void BFS(Node * source)

    {
        for (Node * n : nodes)
        {
            n->color = WHITE;
            n->parent = nullptr;
            n->distance = inf;
        }
        source->color = GRAY;
        source->distance = 0;
        source->parent = nullptr;

        queue<Node*> q;
        q.push(source);

        int count = 0;
        while(!q.empty()){
            cout<<"questa é la "<< count++<<" -iesima volta nell'if"<<endl;
            Node * u =  q.front();
            q.pop();
            for(auto v: adjList[u->key])
            {
                Node * n = nullptr;
                for(Node * nodo  : nodes)
                {
                    if (nodo->key ==v.first)
                    {
                        n = nodo;
                        break;
                    }
                }

                //non ho trovato un cazzo
                if(n == nullptr)
                {
                    continue;
                }
                if(n->color == WHITE)
                {
                    cout << "sono nell'if"<<endl;
                    n->color = GRAY;
                    n->parent = u;
                    n->distance =  u->distance + v.first;
                    q.push(n);
                }
            }
            u->color = BLACK;
        }
    }

    void prim(Node * r)
    {
        vector<Node*> mstNodes;  // Vettore per i nodi del MST
        for(Node * n : nodes)
        {
            n->val = inf;
            n->parent = nullptr;
        }

        r->val = 0;
        priority_queue <Node *, vector<Node *>,Compare> q;
        for(Node * qNode : nodes)
        {
            q.push(qNode);
        }

        while(!q.empty())
        {
            Node * u = q.top();
            q.pop();
            mstNodes.push_back(u);  // Aggiungiamo il nodo al MST

            for(auto v: adjList[u->key]){
                Node * temp = nullptr;
                for(Node * nx : nodes){
                    if(nx->key == v.first)
                    {
                        temp = nx;
                        break;
                    }
                }

                if(temp != nullptr && temp->val > v.second)
                {
                    temp->val = v.second;
                    temp->parent = u;
                    // Rebuild priority queue with updated values
                    priority_queue <Node *, vector<Node *>,Compare> newQ;
                    for(Node * n : nodes)
                    {
                        newQ.push(n);
                    }
                    q = newQ;
                }
            }
        }
    }

    void printMST()
    {
        cout << "\nMinimum Spanning Tree:" << endl;
        cout << "--------------------" << endl;
        
        // Stampa i nodi del MST
        cout << "Nodi nel MST:" << endl;
        for(Node * n : nodes)
        {
            if(n->parent != nullptr || n->val == 0)  // Include il nodo radice (val = 0) e tutti i nodi con un parent
            {
                cout << "Nodo " << n->key;
                if(n->val == 0)
                    cout << " (Radice)";
                cout << endl;
            }
        }
        
        // Stampa gli archi del MST
        cout << "\nArchi nel MST:" << endl;
        int totalWeight = 0;
        for(Node * n : nodes)
        {
            if(n->parent != nullptr)
            {
                cout << n->parent->key << " -- " << n->key << " (peso: " << n->val << ")" << endl;
                totalWeight += n->val;
            }
        }
        
        cout << "\nPeso totale del MST: " << totalWeight << endl;
        cout << "--------------------" << endl;
    }
};

int main(){
    
    ifstream in ("input.txt");
    int numNodi,numArchi;

    in>>numNodi>>numArchi;

    unordered_map <int, Node *> mappaNodi;
    Graph g ;

    //il file di input é il numero di archi
    for(int i = 0; i<numArchi; i++)
    {
        int weight,sourceKey,destinationKey;
        
        in>>weight>>sourceKey>>destinationKey;
        Node * sourceNode = nullptr;
        auto itsource = mappaNodi.find(sourceKey);
        //se non lo trovo e quindi non l'ho acnora messo nel grafo
        if(itsource == mappaNodi.end()){
            //creo il mio nodo
            sourceNode = new Node (sourceKey);

            //lo metto nella mappa nodi e poi lo metto all'interno del grafo
            mappaNodi[sourceKey] = sourceNode;
            g.addNode(sourceNode);
        }
        // se già esiste all'interno della mia mappa nodi
        else{
            sourceNode = itsource->second;
            cout<<"It source->second: " << itsource->second<< endl;
        }

        Node * destinNode = nullptr;
        auto itdest = mappaNodi.find(destinationKey);
        //non ho trovato un cazzo
        if(itdest == mappaNodi.end())
        {
            destinNode = new Node (destinationKey);
            mappaNodi[destinationKey] = destinNode;
            g.addNode(destinNode);
        }
        else{
            destinNode = itdest->second;
        }
        g.addEdge(sourceNode,destinNode,weight);
    }
    in.close();
    Node * sNode = g.nodes[0];
    ofstream out("fileOutPut.txt");
    
    g.BFS(sNode);
    out<<"DISTANZE DAL NODO "<<sNode->key<<":\n"<<endl;
    
    for(Node * nodo : g.nodes){
        out<<"distanza al nodo: " << nodo->key << ":  "<<nodo->distance<<endl;
    }

    out.close();
    cout<<"il file é stato creato"<<endl;

    
    return 0;
}