#include<iostream>
#include<fstream>
#include<vector>

//L'HASH E' UNA CATEGORIA CHE RIMANE INTATTA OGNI VOLTA CHE ESCE
//PUO' CHIAMARE IL FILE DI INPUT CHE POTREBBE DARE FERONE
//VI CONSIGLIO DI ESERCITARVI ANCHE CON CARATTERI, INTERI E STRINGHE
using namespace std;

template<typename T, typename S>
class item{
    public:
    T key;
    S val;

    item(T key, S val) : key(key), val(val){}
};

template<typename T, typename S>
class hashtable{
    public:
    vector<item<T, S>*> table;
    int m;

    hashtable(int m) : m(m)  {
        table.resize(m, nullptr);
    }

    int hash(T key, int i){
        return(key+i)%m;
    }

    void insert(item<T,S>* item){
        int i = 0;
        while(i < m){
            int j = hash(item->key, i);
            if(table[j] == nullptr){
                table[j] = item;
                return;
            } else {
                i++;
            }
        }
        cout<<"ERROR"<<endl;
    }

    item<T,S>* find(T key){
        int i = 0;
        int j = hash(key, i);
        while(table[j] != nullptr && i != m){
            if(table[j]->key == key){
                return table[j];
            }
            i++;
            j = hash(key, i);
        }
        return nullptr;
    }

    void remove(T key){
        int i = 0;
        int j = hash(key, i);
        while(table[j] != nullptr && i != m){
            if(table[j]->key == key){
                delete table[j];
                table[j] = nullptr;
                return;
            }
            i++;
            j = hash(key, i);
        }
    }

    void print(ofstream &out){
        for(int i = 0; i < table.size(); i++){
            if(table[i] != nullptr){
                out<<"CHIAVE: "<<table[i]->key<<" VALORE: "<<table[i]->val<<endl;
            }
        }
    }
};

int main(){
    ifstream in("hashstringa.txt");
    //FILE INPUT SENZA <,>
   /* int hashsize;
    in>>hashsize;
    hashtable<int, char> H(hashsize);
    for(int i = 0; i < hashsize; i++){
        int key;
        char val;
        in>>key>>val;
        item<int, char>* itemx = new item<int, char>(key, val);
        H.insert(itemx);
    } */
   //FILE INPUT CON <,>

    hashtable<int, string> H(999);
    char appoggio;
    int key;
    string val;
    while(in>>appoggio>>key>>appoggio>>val){
        val.resize(val.size()-1);
        item<int, string>* itemx = new item<int, string>(key, val);
        H.insert(itemx);
    }   
    in.close();
    //PER RICERCARE PUOI USARE IL METODO CHE VUOI, PER CONVEZIONE HO 
    //USATO QUESTO
    item<int, string>*result = H.find(1); // oppure item<int, char> nel caso di una ricerca col char
    ofstream out("output.txt");
    if(result != nullptr){
        out<<"L'elemento richiesto ha come chiave: "<<result->key<<" ed il valore: "<<result->val<<endl;
    } else {
        out<<"L'elemento non esiste"<<endl;
    }
    H.remove(2);
    H.print(out);
    out.close();
    return 0;
}

