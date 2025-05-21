#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template <typename T>
class Node {
public:
    T k;

    Node(T k) : k(k) {}
};

template <typename T>
class Heap {
private:
    vector<Node<T>*> data;
    int heapsize;

    void min_heapify(int i) {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int min = i;
        if (l < heapsize && data[l]->k < data[min]->k) {
            min = l;
        }
        if (r < heapsize && data[r]->k < data[min]->k) {
            min = r;
        }
        if (min != i) {
            swap(data[i], data[min]);
            min_heapify(min);
        }
    }

    void build_min_heap() {
        for (int i = heapsize / 2; i >= 0; i--) {
            min_heapify(i);
        }
    }

public:
    Heap(vector<Node<T>*> &values) : data(values), heapsize(values.size()) { build_min_heap(); }

    T getmin() const {
        return data[0]->k;
    }

    vector<Node<T>*> getNodes() {
        return this->data;
    }

    T extractmin() {
        if (heapsize == 0) {
            throw out_of_range("heap is empty");
        }
        T min = getmin();
        data[0] = data[heapsize - 1];
        heapsize--;
        data.pop_back();
        min_heapify(0);
        return min;
    }

    void insert(T key) {
        heapsize++;
        data.push_back(new Node<T>(key));
        int i = heapsize - 1;
        while (i > 0 && data[(i - 1) / 2]->k > data[i]->k) {
            swap(data[i], data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapsort() {
        build_min_heap();
        for (int j = heapsize - 1; j >= 1; j--) {
            swap(data[0], data[j]);
            heapsize--;
            min_heapify(0);
        }
    }

};

int main() {
    ifstream input("input.txt");
    // Controlliamo apertura
    if (!input.is_open()) {
        cerr << "Errore nell'apertura del file di input" << endl;
        return 1;
    }

    ofstream output("output.txt");
    if (!output.is_open()) {
        cerr << "Errore nell'apertura del file di output" << endl;
        return 1;
    }

    int val;
    vector<Node<int>*> nodes;
    while (input >> val) {
        Node<int>* nodo = new Node<int>(val);
        nodes.push_back(nodo);
    }

    Heap<int> H(nodes);
    for (auto h : H.getNodes()) {
        output << h->k << endl;
    }
    output << endl;

    output << "Inseriamo 77" << endl;
    int k = 77;
    H.insert(k);
    for (auto h : H.getNodes()) {
        output << h->k << endl;
    }
    output << endl;

    output << "Inseriamo 9" << endl;
    int kk = 9;
    H.insert(kk);
    for (auto h : H.getNodes()) {
        output << h->k << endl;
    }
    output << endl;

    output << "Estraiamo il minimo: " << H.extractmin() << endl;
    for (auto h : H.getNodes()) {
        output << h->k << endl;
    }
    output << endl;

    output << "Facciamo l'heapsort:" << endl;
    H.heapsort();
    for (auto h : H.getNodes()) {
        output << h->k << endl;
    }

    input.close();
    output.close();

    return 0;
}


