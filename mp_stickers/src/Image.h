/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

 // image class declaration

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#pragma once
using namespace cs225;

// subclass of PNG class
class Image : public PNG {
    public:
        void lighten();
        void lighten(double amount);
        void darken();
        void darken(double amount);
        void saturate();
        void saturate(double amount);
        void desaturate();
        void desaturate(double amount);
        void grayscale();
        void rotateColor(double degrees);
        void illinify();
        void scale(double factor);
        void scale(unsigned w, unsigned h);

};
