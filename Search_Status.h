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

struct singleTask{
    int price;
    int S, M, K;
    bool B;
    Search_Tree* node;
};

struct smallTask{
    int s, m;
};

struct smallStatus{
    int s, m;
    bool b;
    bool operator==(smallStatus& ss) const;
};

class Status{
private:
    int S, M, K;
    list<singleTask> tasks;
    vector<smallStatus> hash_map;
    Search_Tree* stree = nullptr;
public:
    Status(int s, int m, int k):S(s), M(m), K(k){}
    void add_task(singleTask, int);
    bool inRule(smallTask) const;
    vector<smallTask> buildSmallTasks(singleTask t) const;
    Search_Tree* search();
};

#endif //UNTITLED_SEARCH_STATUS_H
