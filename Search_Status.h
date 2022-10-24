//
// Created by actre on 2022/10/23.
//

#ifndef UNTITLED_SEARCH_STATUS_H
#define UNTITLED_SEARCH_STATUS_H

#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Search_Tree{
    Search_Tree* father;
    int S, M;
    bool B;
    static int count;
    Search_Tree(Search_Tree* f = nullptr):father(f){}
};

struct task{
    int price;
    int S, M, K;
    bool B;
    Search_Tree* node;
};

struct st{
    int _s, _m;
};

struct sstatus{
    int s, m;
    bool b;
    bool operator==(sstatus& ss) const;
};

class Status{
private:
    int S, M, K;
    list<task> tasks;
    vector<sstatus> hash_map;
    Search_Tree* stree = nullptr;
public:
    Status(int s, int m, int k):S(s), M(m), K(k){}
    void add_task(task, int);
    bool inRule(st) const;
    vector<st> stasks(task) const;
    Search_Tree* search();
};

#endif //UNTITLED_SEARCH_STATUS_H
