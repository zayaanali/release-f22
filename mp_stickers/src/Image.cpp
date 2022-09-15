// image class declaration
#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <cstdlib>
#include <iostream>
using namespace cs225;

// increase the luminance of each pixel by 0.1. 
void Image::lighten() {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // luminance increases by 0.1 if does not exceed 1.0. sets luminance to 1.0 of exceeds 1.0
            if (this->getPixel(i,j).l + 0.1 <= 1) this->getPixel(i,j).l += 0.1; 
            if (this->getPixel(i,j).l + 0.1 >= 1) this->getPixel(i,j).l = 1.0;
        }
    }
}

// increase luminance of each pixel by specified amount. 
void Image::lighten(double amount) {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // luminance increase by amount if does not exceed 1.0. If exceeds then set to 1.0
            if (this->getPixel(i,j).l + amount <= 1) this->getPixel(i,j).l += amount; 
            if (this->getPixel(i,j).l + amount >= 1) this->getPixel(i,j).l = 1.0; 
        }
    }
}

// darken luminance by 0.1
void Image::darken() {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // saturation decreases by 0.1 if does not go below 0. Otherwise set to 0
            if (this->getPixel(i,j).l - 0.1 <= 0.0) this->getPixel(i,j).l = 0.0; 
            if (this->getPixel(i,j).l - 0.1 >= 0.0) this->getPixel(i,j).l -= 0.1;
        }
    }
}

// darken luminance by specified amount
void Image::darken(double amount) {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // saturation decreases by 0.1 if does not go below 0. Otherwise set to 0
            if (this->getPixel(i,j).l - amount <= 0.0) this->getPixel(i,j).l = 0.0; 
            if (this->getPixel(i,j).l - amount >= 0.0) this->getPixel(i,j).l -= amount;
        }
    }
}

// increase saturation by 0.1
void Image::saturate() {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // saturation increases by 0.1 if does not exceed 1.0. sets luminance to 1.0 of exceeds 1.0
            if (this->getPixel(i,j).s + 0.1 <= 1) this->getPixel(i,j).s += 0.1; 
            if (this->getPixel(i,j).s + 0.1 >= 1) this->getPixel(i,j).s = 1.0;
        }
    }
}

// increase saturation by 0.1
void Image::saturate(double amount) {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // saturation increase by amount if does not exceed 1.0. If exceeds then set to 1.0
            if (this->getPixel(i,j).s + amount <= 1) this->getPixel(i,j).s += amount; 
            if (this->getPixel(i,j).s + amount >= 1) this->getPixel(i,j).s = 1.0; 
        }
    }
}
// decrease saturation by 0.1
void Image::desaturate() {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // saturation decreases by 0.1 if does not go below 0. Otherwise set to 0
            if (this->getPixel(i,j).s - 0.1 <= 0.0) this->getPixel(i,j).s = 0.0; 
            if (this->getPixel(i,j).s - 0.1 >= 0.0) this->getPixel(i,j).s -= 0.1;
        }
    }
}

// decrease saturation by specified amount
void Image::desaturate(double amount) {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // saturation decreases by 0.1 if does not go below 0. Otherwise set to 0
            if (this->getPixel(i,j).s - amount <= 0.0) this->getPixel(i,j).s = 0.0; 
            if (this->getPixel(i,j).s - amount >= 0.0) this->getPixel(i,j).s -= amount;
        }
    }
}

// sets saturation of all pixels to 0
void Image::grayscale() {
    // initialize variables
    unsigned int i, j;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            this->getPixel(i,j).s = 0.0; // set to 0
        }
    }
}

// change hue by specified amount
void Image::rotateColor(double degrees) {
    // initialize variables
    unsigned int i, j;
    double rotated;
    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            rotated = this->getPixel(i,j).h + degrees; // get the modified hue value
            // ensure the hue value will be within the circle
            while (rotated > 360) rotated -= 360;
            while (rotated < 0) rotated +=360;
            // set new hue value
            this->getPixel(i,j).h = rotated;
        }
    }
}

// hue of each pixel changed to either orange or blue, whichever is closer
void Image::illinify() {
    // initialize variables
    unsigned int i, j;
    int blueDist, orangeDist;

    // for loop runs through all each individual width/height
    for (i=0; i<width(); i++) {
        for (j=0;j<height(); j++) {
            // set variables used
            orangeDist = std::abs(this->getPixel(i,j).h -11); // gets the distance from orange hue
            blueDist = std::abs(this->getPixel(i,j).h -216); // gets distance from orange hue
            // set the hue to whatever distance is shorter
            if (blueDist < orangeDist) this->getPixel(i,j).h = 216;
            if (orangeDist < blueDist) this->getPixel(i,j).h = 11;
            if (orangeDist == blueDist) this->getPixel(i,j).h = 0; // this shouldn't happen i think
        }
    }
}
void Image::scale(double factor) {
    // create copy of the original image (pixelarray)
    Image imageCopy(*this);
    //this: pointer to current object
    //Copy Constructor - Image [name of copy]([Image object to copy from]);
    // create variables for new width/height
    unsigned int w = width() * factor;   
    unsigned int h = height() * factor;

    // resize the image to new height/width
    resize(w,h); 

    //fill the new image with pixels
    unsigned int w_, h_;
    for(unsigned int i=0; i<w; i++) {
        for (unsigned int j=0; j<h; j++) {
            // fill pixels from old image into new image
            w_ = (unsigned int) i/factor;
            h_ = (unsigned int) j/factor;
            this->getPixel(i,j) = imageCopy.getPixel(w_,h_);
        }
    }
   
}
void Image::scale(unsigned w, unsigned h) {
    
    // create variables for new width/height
    double wfactor = (double) w/ width();
    double hfactor = (double) h/ height();
    double factor = std::min(wfactor, hfactor);

    scale(factor);
}