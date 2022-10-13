#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */


/*
* declare queue and insert starting vertex. 
* Init visited array and mark starting point as visited
* Remove first queue member and mark as visited. Insert all unvisited neighbors into queue
*/
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */

  // initialize private vars
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  height_ = png_.height();
  width_ = png.width();
  // resize visited to size of the entire png, init all to false
  visited_.resize(width_, vector<bool>(height_, false));

  // go to first element and set as visited
  queue_.push(start);
  visited_[start.x][start.y] = true;

}





/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */

  //BFS *bfs = new BFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(png_, this, start_, tolerance_);

}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(); // return -1,-1
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  queue_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if (queue_.empty()) 
    { return Point(-1,-1); }
  else 
    { Point ret = queue_.front(); queue_.pop(); return ret; }
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if (queue_.empty())
    { return Point(-1,-1); }
  else 
    { return queue_.front(); }
 
}
bool BFS::getVisited(unsigned x, unsigned y) {
    return visited_[x][y];
}
void BFS::setVisited(unsigned x, unsigned y) {
    visited_[x][y] = true;
}


/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if (queue_.empty()) return true;
  else return false;
}
