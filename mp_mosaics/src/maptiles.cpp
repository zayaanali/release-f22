/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

<<<<<<< HEAD
    LUVAPixel tilePixel= LUVAPixel();
    Point<3> tilePoint = Point<3>();
    vector<Point<3>> pointArray; // vector of each point
    map<Point<3>, TileImage*> tileMap; // maps each treepoint to tileimage
    for (auto& it : theTiles) {
        tilePoint = convertToXYZ(it.getAverageColor()); // get color from each tile, convert to point
        pointArray.push_back(tilePoint); // add each point to tile point vector
        tileMap[tilePoint] = &it; // map each tilepoint to tileimage
    }


    KDTree<3> tree(pointArray);
    for (int r=0; r<theSource.getRows(); r++) {
        for (int c=0; c<theSource.getColumns(); c++) { // each r/c of mosaic
            Point<3> color = convertToXYZ(theSource.getRegionColor(r,c)); // get color point from region of source image
            Point<3> colorMatch = tree.findNearestNeighbor(color); // find closest color point match
            if(c == 281 && r == 118){
                std::cout << color << " " << colorMatch << std::endl;
            }
            canvas->setTile(r, c, (tileMap[colorMatch])); // set the tile
        }
    }

    // return the canvas
    return canvas;
=======
    return NULL;
>>>>>>> c6cd753fb54518742940eced18033be74ae46da3
}

