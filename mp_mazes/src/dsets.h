#pragma once
#include<vector>
using std::vector;

class DisjointSets {
    public:
        void addelements (int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
    
    private:
        vector<int> _elems;

};