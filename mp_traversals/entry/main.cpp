
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG png;
  png.readFromFile("/workspaces/CS 225 MPs/release-f22/mp_traversals/entry/lantern.png");
  FloodFilledImage image(png);

  DFS dfs(png, Point(1,1), 0.2);
  BFS bfs(png, Point(1,1), 0.2);

  MyColorPicker my(0.3);
  image.addFloodFill(dfs, my);
  image.addFloodFill(bfs, my);
  
  Animation animation = image.animate(5000);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
