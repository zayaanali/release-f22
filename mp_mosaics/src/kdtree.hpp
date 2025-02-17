/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
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
double KDTree<Dim>::getDistance(const Point<Dim>& p1, const Point<Dim>& p2) const {
    double tot=0;
    double temp;
    for (int i=0; i<Dim; i++) { 
      temp = p1[i]-p2[i];
      temp=temp*temp;
      tot = temp+tot;
    }
    return tot;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double d1 = getDistance(target, currentBest);
    double d2 = getDistance(target, potential);
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

  for (int i=left; i<right; i++) {
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
  if (left>right) return;
    
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
    root = NULL;
    vector<Point<Dim>> p = newPoints;
    buildTree(p, 0, 0, p.size()-1, root);
    


}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(this->root, other->root);
  size=other.size;

}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode *&newRoot, const KDTree<Dim> *&other) {
  if (other==NULL) return;

  newRoot = new KDTreeNode(other->point);
  copy(newRoot->left, other->left);
  copy(newRoot->right, other->right);
}

template <int Dim>
void KDTree<Dim>::deleteTree(KDTreeNode *&root) {
  // delete root;
  if (root==NULL) return;
  delete(root->left);
  delete(root->right);
  delete root;
}


template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  delete(root);
  copy(root, rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  deleteTree(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    if (root==NULL) return NULL;
    Point<Dim> curBest = root->point;
    Point<Dim> q = query;
    return findNeighbor(q, 0, root);
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNeighbor(Point<Dim>& query, int dim, KDTreeNode *curRoot) const
{
<<<<<<< HEAD
    if (curRoot->right==NULL && curRoot->left==NULL) return curRoot->point;
    // go to either the left or right side
    Point<Dim> curBest = curRoot->point;
    Point<Dim> nearest = curRoot->point;
=======
    if (root==NULL) return NULL;
    // go to either the left or right side
    KDTreeNode curBest = Point<Dim>();
    Point<Dim> nearest = Point<Dim>();
    bool dir = smallerDimVal(curRoot->left->point, query, dim);
>>>>>>> c6cd753fb54518742940eced18033be74ae46da3

    // make sure that not accessing null values
    bool dir = smallerDimVal(query, curRoot->point, dim);

    if (dir) { // go left
      if (curRoot->left != NULL)
        nearest = findNeighbor(query,(dim+1)%Dim, curRoot->left);
    } else { // go right
      if (curRoot->right != NULL)
        nearest = findNeighbor(query,(dim+1)%Dim, curRoot->right);
    }

    if (shouldReplace(query, curBest, nearest))
      curBest = nearest;

    double radius = getDistance(query, nearest);
    double splitDist = pow(curRoot->point[dim]-query[dim], 2);
    Point<Dim> tempNearest=curRoot->point;
  
    if (radius>=splitDist) {
      if (dir) { // if had previously recursed left first
        if (curRoot->right != NULL)
          tempNearest = findNeighbor(query,(dim+1)%Dim, curRoot->right);
      } else {
        if (curRoot->left != NULL)
          tempNearest = findNeighbor(query,(dim+1)%Dim, curRoot->left);
      }

      if (shouldReplace(query, curBest, tempNearest))
        curBest = tempNearest;
    }
  return curBest;

}