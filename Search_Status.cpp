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
        vector<smallTask> _st = this->buildSmallTasks(running_task);
        boat_loc = !running_task.B;
        for(auto it : _st){
            smallStatus ss{it.s, it.m, boat_loc};
            bool existed = false;
            for(auto item : this->hash_map)
                if(item == ss) {
                    existed = true;
                    break;
                }
            if(!existed){
//                cout << "Add singleTask: " << it.s << " " << it.m << " " << (boat_loc ? "Here" : "There") << endl;
                Search_Tree::count ++;
                auto* sonNode = new Search_Tree(running_task.node);
                sonNode->S = it.s;
                sonNode->M = it.m;
                sonNode->B = boat_loc;
                singleTask new_task{-1, it.s, it.m, this->K, boat_loc, sonNode};
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
    return ((t.m <= t.s || (t.m == 0 || t.s == 0)) && (this->M - t.m <= this->S - t.s || (this->M - t.m == 0 || this->S - t.s == 0)));
}

vector<smallTask> Status::buildSmallTasks(singleTask t) const{
    vector<smallTask> res;
    int s = t.S,
            m = t.M;
    smallTask _t = smallTask{0, 0};
    while(_t.s <= this->S){
        while(_t.m <= this->M){
            if(t.B) {
                if (m >= _t.m && s >= _t.s && (m - _t.m) + (s - _t.s) <= this->K && (m - _t.m) + (s - _t.s) != 0 && this->inRule(_t))
                    res.push_back(_t);
            }else{
                if (m <= _t.m && s <= _t.s && (_t.m - m) + (_t.s - s) <= this->K && (_t.m - m) + (_t.s - s) != 0 && this->inRule(_t))
                    res.push_back(_t);
            }
            _t.m ++;
        }
        _t.m = 0;
        _t.s ++;
    }
//    for(auto it : res)
//        cout << "smallTask: " << it.s << " " << it.m << endl;
    return res;
}
