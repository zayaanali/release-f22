/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim]==second[curDim])
      return first<second;
    else 
      return first[curDim]<second[curDim];
    
}

template <int Dim>
int KDTree<Dim>::getDistance(const Point<Dim>& p1, const Point<Dim>& p2) const {
    int tot=0;
    int temp;
    for (int i=0; i<Dim; i++) { 
      temp = p1[i]-p2[i];
      temp=temp*temp;
      tot = temp+tot;
    }
    return sqrt(tot);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int d1 = getDistance(target, currentBest);
    int d2 = getDistance(target, potential);
    if (d1==d2) 
      return potential<currentBest;
    else 
      return (d2<d1);
}


template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, int dimension) {
  Point<Dim> pivotValue = list[pivotIndex];
  swap(list[pivotIndex], list[right]);
  int storeIndex = left;

  for (int i=0; i<right-1; i++) {
    if (smallerDimVal(list[i], pivotValue, dimension)) {
      swap(list[storeIndex], list[i]);
      storeIndex++;
    }
  }
  swap(list[right], list[storeIndex]);
  return storeIndex;
}

// find kth smallest element
template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, int k, int dimension) {
  if (left==right) return list[left];

  int pivotIndex = k; //middle
  pivotIndex = partition(list, left, right, pivotIndex, dimension);

  if (k==pivotIndex) 
    return list[k];
  else if (k<pivotIndex)
    return select(list, left, pivotIndex-1, k, dimension);
  else
    return select(list, pivotIndex+1, right, k, dimension);


}

template <int Dim>
void KDTree<Dim>::buildTree(vector<Point<Dim>> &points, int dimension, int left, int right, KDTreeNode *&curRoot) {
  if (left<=right) return;
    
  int middle=(left+right)/2;
  curRoot = new KDTreeNode(select(points, left, right, middle, dimension));
  size++;

  buildTree(points, (dimension+1)%Dim, left, middle-1, curRoot->left);
  buildTree(points, (dimension+1)%Dim, middle+1, right, curRoot->right);

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size=0;
    vector<Point<Dim>> p = newPoints;
    buildTree(p, 0, 0, p.size()-1, root);
    


}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

