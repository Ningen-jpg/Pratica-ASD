#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename T, typename S>
class Node{
    public:
    Node <T,S> * right;
    Node <T,S> * left;
    Node <T,S> * parent;
    T key;
    S val;

    Node (T key, S val): key(key), val(val){
        parent = right = left = nullptr;
    }
};

template <typename T, typename S>
class ABR{
public:
    Node<T,S> * root;

    ABR(){
        root = nullptr;
    }
    //adesso bisogna fare i metodi

    //Inserire i metodi vari per poter 
    void insert (T key, S val)
    {
        Node <T,S> * currentNode = root;
        Node <T,S> * nuovoNodo = new Node (key, val);
        Node <T,S> * parent = nullptr;
        //per andarci a posizionare nella posizione corretta
        while (currentNode != nullptr)
        {
            parent = currentNode;
            if (nuovoNodo->val < currentNode->val){
                currentNode = currentNode->left;
            }
           else if(nuovoNodo->val > currentNode->val)
            {
                currentNode = currentNode->right;
            }
        }
        nuovoNodo->parent = parent;

        if(nuovoNodo->parent == nullptr)
        {
            root= nuovoNodo;
        }

        else if(nuovoNodo->val < nuovoNodo->parent->val)
        {
            parent->left = nuovoNodo;
        }
        else if(nuovoNodo->val > parent->val)
        {
            parent->right = nuovoNodo;
        }
    }

    void preOrder(Node<T,S> *node, vector<pair<T,S>> &v)
    {
        if(node){
            v.push_back({node->key,node->val});
            preOrder(node->left,v);
            preOrder(node->right,v);
        }
    }

    void print(ofstream &out){
        vector<pair<T,S>> v;
        preOrder(root,v);
        for(auto p : v){
            out << "chiave: "<< p.first<< ",  valore: "<< p.second<<endl;
        }
    }
    
};
/*
int main()
{
    ifstream in ("inputStringa.txt");
    int key;
    char val;

    ABR<int, char> * albero = new ABR<int,char> ();
    //building the tree
    while(in>>key>>val){
        albero->insert(key,val);
    }
    in.close();
    
    ofstream out ("output.txt");

    albero->print(out);

    out.close();
    cout<<"Il file é stato creato"<<endl;
    return 0;
}
    */
   
int main(){
    ifstream in("inputStringa.txt");
    int key;
    char val;
    ABR<int, char>* albero = new ABR<int, char>();
    while(in>>key>>val){
        albero->insert(key, val);
    }  
    in.close();
    ofstream out("output.txt");
    albero->print(out);
    out.close();
    cout<<"Il file è stato creato"<<endl;
    return 0;
}