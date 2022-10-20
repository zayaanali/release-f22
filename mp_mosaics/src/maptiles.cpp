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
    // create new mosaic
    MosaicCanvas *canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    // traverse the entire vector tile array
    // get each pixel, convert to xyz, store each avg pixel into vectorarray
    // map each avg pixel to a tile
    LUVAPixel tilePixel= LUVAPixel();
    Point<3> tilePoint = Point<3>();
    vector<Point<3>> pointArray; // vector of each point
    map<Point<3>, TileImage> tileMap;
    for (auto it: theTiles) {
        tilePoint = convertToXYZ(it.getAverageColor());
        pointArray.push_back(tilePoint);
        tileMap[tilePoint] = it;
    }

    // build kdtree with tile points
    // for each row/col of the source image get the color of the region
    // convert each region point to xyz
    // find nearest neighbor point from tile kdtree
    // set the tile on the canvas by getting the corresponding tile 
    // from the map
    KDTree<3> tree(pointArray);
    for (int r=0; r<theSource.getRows(); r++) {
        for (int c=0; c<theSource.getColumns(); c++) {
            Point<3> color = convertToXYZ(theSource.getRegionColor(r,c));
            Point<3> colorMatch = tree.findNearestNeighbor(color);
            canvas->setTile(r, c, &tileMap[colorMatch]);
        }
    }

    // return the canvas
    return NULL;
}

