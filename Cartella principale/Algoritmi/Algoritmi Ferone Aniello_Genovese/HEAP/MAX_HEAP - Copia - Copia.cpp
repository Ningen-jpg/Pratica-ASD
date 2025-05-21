#include <iostream>
#include <fstream>
#include <vector>
//IN GENERE METTE QUESTA PROVA MA COL MIN
using namespace std;

template<typename T>
class Node{
    public: 
    T k;
    Node(T k) : k(k){}
};

template<typename T>
class Heap{
    private:
    vector<Node<T>*> data;
    int heapsize;

 

    void max_heap(int i){
        int l = (i * 2)+ 1;
        int r = (i * 2) + 2;
        int max = i;
        if(l < heapsize && data[l]->k > data[max]->k){
            max = l;
        }
        if(r < heapsize && data[r]->k > data[max]->k){
            max = r;
        }
        if(max != i){
            cout<<"SCAMBIO "<<data[i]<<", "<<data[max]<<endl;
            swap(data[i], data[max]);
            max_heap(max);
        }
    }

    void build(){
        for(int i = heapsize/2 - 1; i >= 0; i --){
            max_heap(i);
        }
    }

    public:
    Heap(vector<Node<T>*> &value) : data(value), heapsize(value.size()) {
        build();
    }

    T getMax() const {
        return data[0]->k;
    }

    vector<Node<T>*> getNodes(){
        return this->data;
    }
      void increase(T val, int i){
        build();
        if(i < 0 || i> data.size()){
            cerr<<"ERROR INDICE"<<endl;
            exit(-1);
        }
        if(val<data[i]->k){
            cerr<<"ERROR VALUE"<<endl;
            exit(-2);
        }
        data[i]->k=val;
        while(i >= 0 && data[(i-1)/2]->k < data[i]->k){
            swap(data[i], data[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void heapsort(){
        build();
        for(int j = heapsize - 1; j >= 0; j--){
            swap(data[0], data[j]);
            heapsize--;
            max_heap(0);
        }
    }


};

int main() {
    ifstream in("input.txt");
    ofstream out("output099.txt");

    int val;
    vector<Node<int>*> nodes;
    while(in>>val){
        Node<int>* nodo = new Node<int>(val);
        nodes.push_back(nodo);
    }

    Heap<int> H(nodes);
    for(auto h:H.getNodes()){
        out<<"Heap fatto: "<<h->k<<endl;
    }
    out<<"HEAPSORT"<<endl;
    H.heapsort();
    for(auto h:H.getNodes()){
        out<<h->k<<endl;
    }

    out<<"INCREASE"<<endl;
    H.increase(220000, 5);
    for(auto h:H.getNodes()){
        out<<h->k<<endl;
    }
    in.close();
    out.close();
    return 0;
}

