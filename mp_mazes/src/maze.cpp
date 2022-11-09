#include "maze.h"
#include "cs225/PNG.h"
#include <queue>
#include <algorithm>
#include <iterator>
#include <assert.h>
#include <sys/time.h>

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
    
    right_.resize(height);
    down_.resize(height);
    for (int i=0; i<height; ++i) {
        right_[i].resize(width);
        down_[i].resize(width);
    }

    // init each square of maze to true
    for (int w=0; w<width; w++) {
        for (int h=0; h<height; h++) {
            right_[w][h] = true;
            down_[w][h] = true;
        }
    }
    // struct timeval tv;
    // gettimeofday(&tv,NULL);
    // srand(tv.tv_usec);
    
    int rWidth, rHeight, rDir, rSquare;
    // until has been merged into one set
    while (dset_.size(0)<(width*height)) {
        //cout << "here" << endl;
        // generate random dir/height/width
        rDir = rand() % 2; // down or right
        rWidth = rand() % width_;
        rHeight = rand() % height_;
        rSquare = (rHeight*width)+rWidth; // 1D index of rand square
    
        if (rDir == 0) { // RIGHT
        // set union right if not at perimeter/not already in same set    
            if (rWidth != (width-1)) { // not at right perimeter
                if (dset_.find(rSquare)!=dset_.find(rSquare+1)) { // not part of same set
                    setWall(rWidth, rHeight, 0, false);
                    dset_.setunion(rSquare, rSquare+1); 
                }
            }
        } 
        else if (rDir==1) { // DOWN
        // set union down if not at perimeter/not already in same set    
            if (rHeight!=(height-1)) {
                if (dset_.find(rSquare)!=dset_.find(rSquare+width)) {
                    setWall(rWidth, rHeight, 1, false);
                    dset_.setunion(rSquare, rSquare+width);
                }
            }
        }
    }
    //cout << "DSET SIZE: " << dset_.size(0) << " size: " << width*height;   
}



bool SquareMaze::canTravel(int x, int y , int dir) const {
    // // initial check that given coordinate within bounds
    // if (x>=width_ || y>=height_ || x<0 || y<0) return false;
    // //assert(x>-1 && y>-1);
    // // RIGHT
    // if (dir==0) {
    //     if (x+1 >= width_) return false;
    //     return !(right_[x][y]);
    // } 
    // // DOWN
    // else if (dir==1) {
    //     if (y+1>=height_) return false;
    //     return !(right_[x][y]);
    // } 
    // //LEFT
    // else if (dir==2) {
    //     if (x-1<0) return false;
    //     return !(right_[x-1][y]);

    // } 
    // // UP
    // else if (dir==3) {
    //     if (y-1<0) return false;
    //     return !(right_[x][y-1]);
    // }
    // else return false;
     // initial check that given coordinate within bounds
    if (x>=width_ || y>=height_ || x<0 || y<0) return false;
    
    // RIGHT
    if (dir==0) {
        if (x+1 >= width_ || right_[x][y]==true) return false; // if out of bounds or wall exists
        else return true;
    } 
    // DOWN
    else if (dir==1) {
        if (y+1>=height_ || down_[x][y]==true) return false;
        else return true;
    } 
    //LEFT
    else if (dir==2) {
        if (x-1<0 || right_[x-1][y]==true) return false;
        else return true;

    } 
    // UP
    else if (dir==3) {
        if (y-1<0 || down_[x][y-1]==true) return false;
        else return true;
    }
    // dir is something else
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    // RIGHT
    if (dir==0) {
        //right_[y][x]=exists;
        right_[x][y]=exists;
    }
    // DOWN
    else if (dir==1) {
        //down_[y][x]=exists;
        down_[x][y]=exists;
    }


}

vector<int> SquareMaze::solveMaze() {
    queue<int> q;
    vector<int> length(width_*height_, -1);
    vector<int> path(width_*height_, -1);
    // vector<vector<int>> length(height_, vector<int> (width_, -1));
    // vector<vector<int>> path(height_, vector<int> (width_, -1));
    //vector<bool> visited(width_*height_, false);
    vector<int> previous(width_*height_, -1);
    q.push(0);

    while (!q.empty()) {
        // current index being checked
        int currentIdx = q.front();
        //q.pop();
        int x = currentIdx%width_;
        int y = currentIdx/width_;

        // TRY RIGHT
        if (canTravel(x,y,0) && length[currentIdx+1]==-1) {
            //assert(currentIdx<width_*height_);
            length[currentIdx+1] = length[currentIdx]+1;
            path[currentIdx+1]=0;
            previous[currentIdx+1] = currentIdx;
            //visited[currentIdx+1]=true;
            q.push(currentIdx+1);
        }
        // TRY DOWN
        if (canTravel(x,y,1) && length[currentIdx+width_]==-1) {
            //assert(currentIdx<width_*height_);
            length[currentIdx+width_] = length[currentIdx]+1;
            path[currentIdx+width_]=1;
            previous[currentIdx+width_]=currentIdx;
            //visited[currentIdx+width_]=true;
            q.push(currentIdx+width_);
        }
        // TRY LEFT
        if (canTravel(x,y,2) && length[currentIdx-1]==-1) {
            //assert(currentIdx<width_*height_);
            length[currentIdx-1] = length[currentIdx]+1;
            path[currentIdx-1]=2;
            previous[currentIdx-1]=currentIdx;
            //visited[currentIdx-1]=true;
            q.push(currentIdx-1);
        }
        // TRY UP
        if (canTravel(x,y,3) && length[currentIdx-width_]==-1) {
            //assert(currentIdx<width_*height_);
            length[currentIdx-width_] = length[currentIdx]+1;
            path[currentIdx-width_]=3;
            previous[currentIdx-width_]=currentIdx;
            //visited[currentIdx-width_]=true;
            q.push(currentIdx-width_);
        }
        q.pop();
    }
    //for (auto it: path) cout << it << " ";
    // last row heights
    int startIdx = ((height_-1)*width_);
    //cout << "HEIGHT: " << height_ << " WIDTH: " << width_ << " IDX: " << startIdx;
    int curMax=0;
    int curMaxIdx=0;
    // get the maximum length on the bottom row, plus index of the element
    for (int i=startIdx; i<width_*height_; i++) {
        //cout << "length " << length[i];
        if (length[i]>curMax) {
            //cout << "length: " << length[i];
            curMax=length[i];
            curMaxIdx=i;
        }
    }
    // cout << "CURMAX " << curMax;
    // cout << "CURMAXIDX: " << curMaxIdx;
    solX_ = curMaxIdx%width_;
    solY_ = curMaxIdx/width_;


    vector<int> longestPath;
    int pathIdx = curMaxIdx;
    //cout << "CURMAXIDX: " << pathIdx;
    // until reaches the beginning
    while (pathIdx!=0) {
        //assert(pathIdx<2000);

        longestPath.push_back(path[pathIdx]);
        pathIdx = previous[pathIdx];
        //std::cout << pathIdx << std::endl;
    }
    
    reverse(longestPath.begin(), longestPath.end());
    return(longestPath);
    
}

PNG* SquareMaze::drawMaze() {
    // create new PNG
    int mazeWidth = (width_*10)+1;
    int mazeHeight = (height_*10)+1;
    PNG *maze = new PNG(mazeWidth, mazeHeight);

    // Blacken top row, leftmost column of pixels (not 1,0 through 9,0)
    for (int x=10; x<mazeWidth; x++)
        maze->getPixel(x,0).l = 0;

    for (int y=0; y<mazeHeight; y++)
        maze->getPixel(0,y).l = 0;

    // for each square in the maze, call its maze coordinates
    for (int x=0; x<width_; x++) {
        for (int y=0; y<height_; y++) {
            // RIGHT
            if (right_[x][y]) {
                for (int k=0; k<11; k++)
                    maze->getPixel((x+1)*10, (y*10)+k).l = 0;
            }
            // DOWN
            if (down_[x][y]) {
                for (int k=0; k<11; k++)
                    maze->getPixel((x*10)+k, (y+1)*10).l = 0;
            }
        }
    }
    return maze;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG *maze = drawMaze();
    vector<int> sol = solveMaze();
    int x=5;
    int y=5;

    for (auto it: sol) {
        // RIGHT
        if (it==0) {
            for (int i=0; i<11; i++) {
                HSLAPixel &p = maze->getPixel(x+i,y);
                p.h=0;
                p.s=1;
                p.l=0.5;
                p.a=1;
            }
            x+=10;
            //break;
        }
        
        // DOWN
        else if (it==1) {
            for (int i=0; i<11; i++) {
                HSLAPixel &p = maze->getPixel(x,y+i);
                p.h=0;
                p.s=1;
                p.l=0.5;
                p.a=1;
            }
            y+=10;
            //break;
        }
        // LEFT
        else if (it==2) {
            for (int i=0; i<11; i++) {
                HSLAPixel &p = maze->getPixel(x-i,y);
                p.h=0;
                p.s=1;
                p.l=0.5;
                p.a=1;
                //x--;
            }
            x-=10;
            //break;
        }
        // UP
        else if (it==3) {
            for (int i=0; i<11; i++) {
                HSLAPixel &p = maze->getPixel(x,y-i);
                p.h=0;
                p.s=1;
                p.l=0.5;
                p.a=1;
                //y++;
            }
            y-=10;
            //break;
        }
    }
    
    // SET EXIT
    for (int m=1; m<10; m++)
        maze->getPixel((solX_*10)+m, (solY_+1)*10).l = 1;
    
    return maze;

}


