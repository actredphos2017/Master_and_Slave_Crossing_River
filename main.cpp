#include "Search_Status.h"

int Search_Tree::count = 0;

using namespace std;

int main(){
    int s, m, k;
    cin >> s >> m >> k;
    Status _s(s,m,k);
    Search_Tree* res = _s.search();
    if(res != nullptr){
        cout << "Found out!" << endl;
        Search_Tree* p = res;
        list<Search_Tree*> l;
        while(p != nullptr){
            l.push_front(p);
            p = p->father;
        }
        for(auto it : l)
            cout << it->S << " " << it->M << " " << (it->B ? "Here" : "There") << endl;
        cout << "Nodes count: " << Search_Tree::count << endl;
    }else{
        cout << "No result!" << endl;
    }
}