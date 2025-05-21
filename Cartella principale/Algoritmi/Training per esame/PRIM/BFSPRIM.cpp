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
    bool inMST ;

    Node(int key ): key(key){
        parent = nullptr;
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
    unordered_map<int,int> mst;

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

    int minKey(vector<Node*> v)
    {
            int min = INT_MAX;
            int min_index;

            for(int i = 0; i<v.size(); i++)
            {
                if(v[i]->inMST == false && v[i]->val < min){
                    min = v[i]->key;
                    min_index = i; 
                }
        
            }
            return min_index;

    }
    void prim(Node * r)
    {

        for(Node * n : nodes)
        {
            n->val = inf;
            n->parent = nullptr;
            n->inMST = false;
        }

        r->val = 0;
        r->inMST = true;
        vector <Node *> q;
        for(Node * qNode : nodes)
        {
            q.push_back(qNode);
        }

        while(!q.empty())
        {
            //tramite minkey
            int min_index = minKey(q);
            Node * u = q[min_index];
            q.erase(q.begin()+min_index);//fatto la pop

            for(auto v: adjList[u->key]){
                Node * temp = nullptr;
                for(Node * nx : nodes){
                    if(nx->key == v.first)
                    {
                        temp = nx;
                        break;
                    }
                }

                if(temp != nullptr && temp->inMST == false && temp->val > v.second)
                {
                    temp->val = v.second;
                    temp->parent = u;
                    //temp->inMST = true;                 
                }
            }

            //adesso mettiamo quello con arco minimo nel nostro MST
            int min_val = INT_MAX;
            int min_key;
            for(auto v: adjList[u->key]){
                Node * tempx = nullptr;
                for(Node * nx : nodes){
                    if(nx->key == v.first)
                    {
                        tempx = nx;
                        break;
                    }
                }
                if(tempx->val < min_val)
                {
                    min_val = tempx->val;
                    min_key = tempx->key;
                }
            }

            //aggiungiamo finalmente all'MST
            mst[u->key]=min_key;

            for (Node * x :nodes)
            {
                if (x->key == min_key)
                {
                    x->inMST = true;
                }
            }
        }
    }
    void printMST()
    {
        ofstream out ("PRIM.txt");
        for (auto x : mst)
        {    
                Node * source= nullptr;
                for(Node * nodo  : nodes)
                {
                    if (nodo->key ==x.first)
                    {
                        source = nodo;
                        break;
                    }
                }

           out<< "Nodo : "<<x.first<< "collegato a: "<<x.second<<"con peso: : "<<source->val<< endl;
        }
        out.close();
        cout<<"file MST creato"<<endl;
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

    Node * rNode = g.nodes[0];
    g.prim(rNode);
    g.printMST();

    return 0;
}