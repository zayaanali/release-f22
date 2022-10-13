#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
// MyColorPicker::MyColorPicker(HSLAPixel color) : color(color) {}
// HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
//   /* @todo [Part 3] */
//   color.h+=1;
//   return color;
// }

MyColorPicker::MyColorPicker(double increment)
  : hue(0), increment(increment) { }

/**
 * Picks the color for pixel (x, y).
 *
 *
 * @param x The x coordinate to pick a color for.
 * @param y The y coordinate to pick a color for.
 * @return The color selected for (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(hue, 1, 0.5);
  increment +=0.5;
  hue += increment;
  if (hue >= 360) { hue -= 360; }
  return pixel;
}


