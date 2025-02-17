#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor. Past end constructor
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  curPoint_ = Point(-1,-1);
}

// begin traversal constructer
ImageTraversal::Iterator::Iterator(PNG png, ImageTraversal *traversal, Point point, double tolerance) {
  tolerance_ = tolerance;
  traversal_ = traversal;
  curPoint_ = point;
  png_ = png;
  start_ = point;

}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  // remove top and set in var
  curPoint_ = traversal_->pop();
  traversal_->setVisited(curPoint_.x, curPoint_.y);

  Point p2(curPoint_.x+1, curPoint_.y); // right
  Point p3(curPoint_.x, curPoint_.y+1); // above
  Point p1(curPoint_.x-1, curPoint_.y); // left
  Point p4(curPoint_.x, curPoint_.y-1); // below
  double delta;
  bool b1 = ((p1.x>=0) && (p1.x < png_.width()));
  bool b2 = ((p2.x>=0) && (p2.x < png_.width()));
  bool b3 = ((p3.y>=0) && (p3.y < png_.height()));
  bool b4 = ((p4.y>=0) && (p4.y < png_.height()));
  HSLAPixel startPixel = png_.getPixel(start_.x, start_.y);
  
  if (b2) {
    delta = calculateDelta(startPixel, png_.getPixel(p2.x, p2.y) );
    if (delta < tolerance_ && !(traversal_->getVisited(p2.x, p2.y))) 
      traversal_->add(p2);
  }
  if (b3) {
    delta = calculateDelta(startPixel, png_.getPixel(p3.x, p3.y) );
    if (delta < tolerance_ && !(traversal_->getVisited(p3.x, p3.y)))
      traversal_->add(p3);
  }
  
  if (b1) {
    delta = calculateDelta(startPixel, png_.getPixel(p1.x, p1.y) );
    if (delta < tolerance_ && !(traversal_->getVisited(p1.x, p1.y))) traversal_->add(p1);
  }
  
  if (b4) {
    delta = calculateDelta(startPixel, png_.getPixel(p4.x, p4.y) ); 
    if (delta < tolerance_ && !(traversal_->getVisited(p4.x, p4.y)))
      traversal_->add(p4);
  } 


  while (!(traversal_->empty()) && traversal_->getVisited(traversal_->peek().x, traversal_->peek().y) ) {
    traversal_->pop();
  } 
  // set next
  curPoint_ = traversal_->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if(this->traversal_ == NULL || this->traversal_->empty())
  {
    return false;
  }
  return true;
  return !(this->curPoint_==other.curPoint_);
}

