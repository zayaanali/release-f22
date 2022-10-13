#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


  // recursive fn takes index of node, and visited array
  // mark node as visited, print node
  // traverse all adjacent and unmarked nodes
  // call recursive function with index of adjacent node

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */

/*
* create recursive function takes index of node and visited array
* mark current node as visited and print node
* traverse all adjacent and unmarked nodes, call recursive function with index of adjacent node
*/
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  // set vars
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  
  height_ = png.height();
  width_ = png.width();
  visited_.resize(width_, vector<bool>(height_, false)); // set all values to false

  // go to first element and set as visited
  stack_.push(start); // push 
  visited_[start.x][start.y] = true;

}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  // create and return iterator
  //DFS *dfs = new DFS(png_, start_, tolerance_);
  ImageTraversal::Iterator it(png_, this, start_, tolerance_);
  return it;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  stack_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  if (stack_.empty()) 
    { return Point(-1,-1); }
  else 
    { Point ret= stack_.top(); stack_.pop(); return ret; }
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  if (stack_.empty()) 
    { return Point(-1,-1); }
  else 
    { Point ret= stack_.top(); return ret; }
}

bool DFS::getVisited(unsigned x, unsigned y) {
    return visited_[x][y];
}
void DFS::setVisited(unsigned x, unsigned y) {
    visited_[x][y] = true;
}
/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if (stack_.empty()) return true;
  else return false;
}
