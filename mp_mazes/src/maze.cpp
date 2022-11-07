#include "maze.h"
#include "cs225/PNG.h"
#include <queue>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze() {
    width_=0;
    height_=0;
}

void SquareMaze::makeMaze(int width, int height) {
    // set vars
    width_ = width;
    height_ = height;
    
    // add all maze squares to disjoint set
    dset_.addelements(width_*height_);

    // init each square of maze to true
    for (int w=0; w<width; w++) {
        for (int h=0; h<height; h++) {
            right_[w][h] = true;
            down_[w][h] = true;
        }
    }
    
    // until has been merged into one set
    while ((width*height)!=dset_.size(0)) {
        
        // generate random dir/height/width
        int rDir = rand() % 2; // down or right
        int rWidth = rand() % width;
        int rHeight = rand() % height;
        int rSquare = (rHeight*width)+rWidth; // 1D index of rand square
    
        if (rDir == 0) { // RIGHT
        // set union right if not at perimeter/not already in same set    
            if (rWidth != (width-1)) { // not at right perimeter
                if (dset_.find(rSquare)!=dset_.find(rSquare+1)) { // not part of same set
                    right_[rWidth][rHeight]=false;
                    dset_.setunion(rSquare, rSquare+1); 
                }
            }
        } 
        else if (rDir==1) { // DOWN
        // set union down if not at perimeter/not already in same set    
            if (rHeight!=(height-1)) {
                if (dset_.find(rSquare)!=dset_.find(rSquare+width)) {
                    down_[rWidth][rHeight] = false;
                    dset_.setunion(rSquare, rSquare+width);
                }
            }
        }
    }    
}

bool SquareMaze::canTravel(int x, int y , int dir) const {
    // initial check that given coordinate within bounds
    if (x>=width_ || y>=height_ || x<0 || y<0) return false;

    // RIGHT
    if (dir==0) {
        if (x+1 >= width_) return false;
        return !(right_[x][y]);
    } 
    // DOWN
    else if (dir==1) {
        if (y-1 < 0) return false;
        return !(right_[x][y]);
    } 
    //LEFT
    else if (dir==2) {
        if (x-1 < 0) return false;
        return !(right_[x-1][y]);

    } 
    // UP
    else if (dir==3) {
        if (y+1 >= height_) return false;
        return !(right_[x][y-1]);
    }
    else return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    // RIGHT
    if (dir==0) {
        right_[x][y]=exists;
    }
    // DOWN
    else if (dir==1) {
        down_[x][y]=exists;
    }


}

vector<int> SquareMaze::solveMaze() {
    queue<int> q;
    vector<int> length(width_*height_, -1);
    vector<int> path(width_*height_, -1);
    // vector<vector<int>> length(height_, vector<int> (width_, -1));
    // vector<vector<int>> path(height_, vector<int> (width_, -1));
    vector<int> previous(width_*height_, -1);
    q.push(0);

    while (!q.empty()) {
        // current index being checked
        int currentIdx = q.front();
        q.pop();
        int x = currentIdx%width_;
        int y = currentIdx/width_;

        // TRY RIGHT
        if (canTravel(x,y,0) && length[currentIdx+1]==-1) {
            length[currentIdx+1] = length[currentIdx]+1;
            path[currentIdx+1]=0;
            previous[currentIdx+1] = currentIdx;
            q.push(currentIdx+1);
        }
        // TRY DOWN
        if (canTravel(x,y,1) && length[currentIdx+width_]==-1) {
            length[currentIdx+width_] = length[currentIdx]+1;
            path[currentIdx+width_]=1;
            previous[currentIdx+width_]=currentIdx;
            q.push(currentIdx+width_);
        }
        // TRY LEFT
        if (canTravel(x,y,2) && length[currentIdx-1]==-1) {
            length[currentIdx-1] = length[currentIdx]+1;
            path[currentIdx-1]=2;
            previous[currentIdx-1]=currentIdx;
            q.push(currentIdx-1);
        }
        // TRY UP
        if (canTravel(x,y,3) && length[currentIdx-width_]==-1) {
            length[currentIdx-width_] = length[currentIdx]+1;
            path[currentIdx-width_]=3;
            previous[currentIdx-width_]=currentIdx;
            q.push(currentIdx-width_);
        }

        // last row heights
        int startIdx = ((height_-1)*width_);
        int curMax=0;
        int curMaxIdx;
        // get the maximum length on the bottom row, plus index of the element
        for (int i=startIdx; i<width_*height_; i++) {
            if (length[i]>curMax) {
                curMax=length[i];
                curMaxIdx=i;
            }
        }

        vector<int> longestPath;
        int pathIdx;
        while (pathIdx != -1) {
            
        }


    }

return vector<int>();
}

PNG* SquareMaze::drawMaze() {
    PNG *temp = new PNG();
return temp;
}

PNG* SquareMaze::drawMazeWithSolution() {
PNG *temp = new PNG();
return temp;
}


