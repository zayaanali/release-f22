#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <iostream>

using namespace cs225;

// initialize stickersheet with base picture and max stickers
StickerSheet::StickerSheet(const Image &picture, unsigned max) {
    // set base image
    baseImage = picture;
    // set max size of the vector array
    max_ = max; 
}


StickerSheet::~StickerSheet() {
    // no dynamically allocated files
    for (unsigned int i=0; i<imageArray.size(); i++) {
        delete imageArray.at(i);
    }
}
StickerSheet::StickerSheet(const StickerSheet &other) {
    // how distinct of a copy does this need to be
    baseImage = other.baseImage;
    unsigned int i;
    for (i=0; i<other.imageArray.size(); i++) {
        Sticker *tempSticker = new Sticker(other.imageArray.at(i)->stickerImage_, other.imageArray.at(i)->x_, other.imageArray.at(i)->y_);
        imageArray.push_back(tempSticker);
    }
    max_ = other.max_;
}

const StickerSheet &StickerSheet::operator= (const StickerSheet &other) {
    // remove everything from the vector array
    for (unsigned int i=0; i<imageArray.size(); i++) {
        delete imageArray.at(i);
    }
    // re add the objects back to constructor array
    unsigned int i;
    for (i=0; i<other.imageArray.size(); i++) {
        Sticker *tempSticker = new Sticker(other.imageArray.at(i)->stickerImage_, other.imageArray.at(i)->x_, other.imageArray.at(i)->y_);
        imageArray.push_back(tempSticker);
    }
    // reassign other variables
    baseImage = other.baseImage;
    max_ = other.max_;
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    //imageArray.resize(max);
    max_ = max;
    // if array has more than maximum elements resize
    if (imageArray.size() > max_) {
        for (unsigned int i=max_; i<imageArray.size(); i++) {
            delete imageArray.at(i);
        }
        imageArray.resize(max_);
    }
    
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
    // if the sticker array is at max capacity then cannot store more stickers. return -1
    if (imageArray.size() == max_) return -1;
    // add the sticker to end of the array
    Sticker *tempSticker = new Sticker(sticker, x, y);
    imageArray.push_back(tempSticker);
    if (imageArray.size()>max_) {std::cerr << "max stickers reached"; exit(1);}
    // returns the index of the added sticker
    return imageArray.size(); 
}
bool StickerSheet::translate(unsigned index, unsigned x,  unsigned y) {
    // if index is greater than num of stickers then return false
    if (imageArray.size() < index) return false;
    // modify x and y values at index
    imageArray.at(index)->x_ = x;
    imageArray.at(index)->y_ = y;
    return true;
}
void StickerSheet::removeSticker(unsigned index) {
    delete imageArray.at(index);
    imageArray.erase(imageArray.begin()+index);

}
Image* StickerSheet::getSticker(unsigned index) {
    if (index>=imageArray.size()) return NULL;
    return &(imageArray.at(index)->stickerImage_);
}

// write a given image onto PNG
void writeImage(Image &baseImage, Image &newImage, int xcoor, int ycoor) {
    unsigned int startWidth, endWidth, startHeight, endHeight, widthCounter, heightCounter;
    /*
    //set start width and end width
    startWidth = xcoor;
    if (startWidth+newImage.width()>baseImage.width()) {endWidth=baseImage.width();}
    else{endWidth=startWidth+newImage.width();}
    
    //set start height and end height
    startHeight = ycoor;
    if (startHeight+newImage.height()>baseImage.height()) {endHeight=baseImage.height();}
    else{endHeight=startHeight+newImage.height();}
    */

    //set start width and end width
    startWidth = xcoor;
    endWidth = startWidth+newImage.width();
    if (startWidth+newImage.width()>baseImage.width()) {baseImage.resize(startWidth+newImage.width(), baseImage.height());} 

    
    //set start height and end height
    startHeight = ycoor;
    endHeight = startHeight+newImage.height();
    if (startHeight+newImage.height()>baseImage.height()) {baseImage.resize(baseImage.width(), startHeight+newImage.height());} 


    // loop runs through the given width/height bounds
    widthCounter=0;
    heightCounter=0;
    for (unsigned int w=startWidth; w<endWidth; w++) {
        for (unsigned int h=startHeight; h<endHeight; h++) {
            if (newImage.getPixel(widthCounter,heightCounter).a != 0) {
                baseImage.getPixel(w,h) = newImage.getPixel(widthCounter,heightCounter);
                heightCounter++;
            } else {
                heightCounter++;
            }
        }
    heightCounter=0;
    widthCounter++;
    }
}

Image StickerSheet::render() const {
    // local copy of base image to put stickers on top of
    Image imageCopy(baseImage);
     // goes through each element of the vector array and adds each sticker onto base image copy
    for (unsigned int i=0; i<imageArray.size(); i++) {
        writeImage(imageCopy, imageArray.at(i)->stickerImage_, imageArray.at(i)->x_, imageArray.at(i)->y_);
    }
    return imageCopy;
}