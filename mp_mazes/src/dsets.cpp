

#include "dsets.h"
using namespace std;

void DisjointSets::addelements(int num) {
    int newsize = _elems.size() + num;
    _elems.resize(newsize, -1);
}

int DisjointSets::find(int elem) {
    if (_elems[elem]<0) {
        return elem;
    } else {
        int rootElem = find(_elems[elem]);
        _elems[elem] = rootElem;
        return rootElem;
    }
}

void DisjointSets::setunion(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    int newSize= _elems[rootA]+_elems[rootB];

    if (_elems[rootA]<_elems[rootB]) { // rootB is larger
        _elems[rootB] = rootA; // point rootB to rootA
        _elems[rootA] = newSize;
    } else { // rootA is larger (or same size)
        _elems[rootA]=rootB; // point rootA to rootB
        _elems[rootB]=newSize;
    }   
}

int DisjointSets::size(int elem) {
    int root=find(elem);
    return _elems[root]*-1;

}