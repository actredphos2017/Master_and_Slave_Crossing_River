//
// Created by actre on 2022/10/23.
//

#include "Search_Status.h"

#include <list>
#include <vector>
#define MAX_STEP 100

using namespace std;

bool smallStatus::operator==(smallStatus &ss) const {
    return (this->s == ss.s && this->m == ss.m && this->b == ss.b);
}

Search_Tree* Status::search(){
    int step = 0;
    bool boat_loc = true;
    Search_Tree::count = 0;
    this->stree = new Search_Tree;
    stree->S = this->S;
    stree->M = this->M;
    stree->B = boat_loc;

    this->tasks.push_back(singleTask{this->S + this->M - this->K, this->S, this->M, this->K, boat_loc});
    while(step < MAX_STEP && !tasks.empty()){
        singleTask running_task = this->tasks.front();
        this->hash_map.push_back(smallStatus{this->S, this->M, boat_loc});
        this->tasks.pop_front();
        if(running_task.S == 0 && running_task.M == 0)
            return running_task.node;
//        cout << endl << "Start singleTask: " << running_task.S << " " << running_task.M << " " << (boat_loc ? "Here" : "There") << endl;
        step ++;
        vector<smallTask> _st = this->stasks(running_task);
        boat_loc = !running_task.B;
        for(auto it : _st){
            smallStatus ss{it._s, it._m, boat_loc};
            bool existed = false;
            for(auto item : this->hash_map)
                if(item == ss) {
                    existed = true;
                    break;
                }
            if(!existed){
//                cout << "Add singleTask: " << it._s << " " << it._m << " " << (boat_loc ? "Here" : "There") << endl;
                Search_Tree::count ++;
                auto* sonNode = new Search_Tree(running_task.node);
                sonNode->S = it._s;
                sonNode->M = it._m;
                sonNode->B = boat_loc;
                singleTask new_task{-1, it._s, it._m, this->K, boat_loc, sonNode};
                this->add_task(new_task, step);
                this->hash_map.push_back(ss);
            }
        }

    }
    return nullptr;
}

void Status::add_task(singleTask t, int step){
    t.price = step+t.S+t.M-t.K*(int)t.B;
    auto it = this->tasks.begin();
    while(it != this->tasks.end()){
        if(it->price > t.price)
            break;
        it ++;
    }
    this->tasks.insert(it, t);
}

bool Status::inRule(smallTask t) const{
    return ((t._m <= t._s || (t._m == 0 || t._s == 0)) && (this->M - t._m <= this->S - t._s || (this->M - t._m == 0 || this->S - t._s == 0)));
}

vector<smallTask> Status::stasks(singleTask t) const{
    vector<smallTask> res;
    int s = t.S,
            m = t.M;
    smallTask _t = smallTask{0, 0};
    while(_t._s <= this->S){
        while(_t._m <= this->M){
            if(t.B) {
                if (m >= _t._m && s >= _t._s && (m - _t._m) + (s - _t._s) <= this->K && (m - _t._m) + (s - _t._s) != 0 && this->inRule(_t))
                    res.push_back(_t);
            }else{
                if (m <= _t._m && s <= _t._s && (_t._m - m) + (_t._s - s) <= this->K && (_t._m - m) + (_t._s - s) != 0 && this->inRule(_t))
                    res.push_back(_t);
            }
            _t._m ++;
        }
        _t._m = 0;
        _t._s ++;
    }
//    for(auto it : res)
//        cout << "smallTask: " << it._s << " " << it._m << endl;
    return res;
}
