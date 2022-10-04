/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>

using namespace cs225;
class StickerSheet {
    public: 
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet &operator= (const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x,  unsigned y);
        void removeSticker(unsigned index);
        Image *getSticker(unsigned index);
        Image render() const;
    private:
        struct Sticker {
            Image stickerImage_;
            int x_;
            int y_;
            Sticker(Image &stickerImage, int x, int y) {
                stickerImage_ = stickerImage;
                x_ = x;
                y_ = y;
            }
        };
        std::vector<Sticker*> imageArray;
        Image baseImage;
        unsigned int max_;
};  