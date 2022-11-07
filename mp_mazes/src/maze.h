/* Your code here! */
#pragma once
#include "lib/cs225/PNG.h"
#include "dsets.h"
#include <vector>

using namespace std;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG* drawMaze();
        PNG* drawMazeWithSolution();
    private:
        DisjointSets dset_;
        int width_;
        int height_;
        vector<vector<int>> maze_;
        vector<vector<bool>> right_;
        vector<vector<bool>> down_;

};
