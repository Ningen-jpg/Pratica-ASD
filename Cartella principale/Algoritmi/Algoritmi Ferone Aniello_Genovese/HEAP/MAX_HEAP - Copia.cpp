#include <iostream>
#include <fstream>
#include <vector>

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
    T heapsize;

    void max_heapify(int i){
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int max = i;
        if(l < heapsize && data[l]->k > data[max]->k){
            l = max;
        }
        if(r < heapsize && data[r]->k > data[max]->k){
            r = max;
        }
        if(max != i){
            swap(data[i], data[max]);
            max_heapify(max);
        }
    }

    void build_max_heap(){
        for(int i = heapsize / 2; i >= 0; i--){
            max_heapify(i);
        }
    }

    public: 

    Heap(vector<Node<T>*> &value) : data(value), heapsize(value.size()){
        build_max_heap();
    }

    T getMax() const{
        return data[0]->k;
    }
    
    vector<Node<T>*> getNodes(){
        return this->data;
    }

    void heapsort(){
        build_max_heap();
        for(int j = heapsize - 1; j >= 1; j--){
            swap(data[0], data[j]);
            heapsize--;
            max_heapify(0);
        }
    }

    void increase(T val, int i){
        if(i < 0 || i> data.size()){
            cerr<<"ERROR INDICE"<<endl;
            exit(-1);
        }
        if(val < data[i]->k){
            cerr<<"ERROR VALORE"<<endl;
            exit(-2);
        }
        data[i]->k = val;
        while(i > 0 && data[(i -1)/2]->k < data[i]->k){
            swap(data[i], data[(i-1)/2]);
            i = (i- 1)/ 2;
        }
    }

    void insert(T key){
        heapsize++;
        data.push_back(new Node<T>(key));
        int i = heapsize-1;
        while(i >= 0 && data[(i - 1)/ 2]->k < data[i]->k){
            swap(data[i], data[(i-1) / 2]);
            i = (i - 1)/2;
        }
    }

    //MANCA L'INCREASE/DECREASE, STA IN UN ALTRO FILE
};

int main() {
    ifstream in("input.txt");
    ofstream out("output4.txt");

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
    out<<" "<<endl;
    out<<"INCREASE"<<endl;
    H.increase(69, 3);
    for(auto h:H.getNodes()){
        out<<"Increase fatto: "<<h->k<<endl;
    }
    out<<" "<<endl;
    out<<"INSERT";
    int kk = 77;
    H.insert(kk);
    for(auto h: H.getNodes()){
        out<<"Insert fatto: "<<h->k<<endl;
    }
    out<<" "<<endl;
    out<<"HEAPSORT: "<<endl;
    H.heapsort();
    for(auto h: H.getNodes()){
        out<<"Heapsort fatto: "<<h->k<<endl;
    }
    out<<endl;
    in.close();
    out.close();
    return 0;
}
