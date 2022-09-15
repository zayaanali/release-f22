#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image base, sticker1, sticker2, sticker3, output;
  base.readFromFile("../alma.png");
  sticker1.readFromFile("../i.png");
  sticker2.readFromFile("../i.png");
  sticker3.readFromFile("../i.png");

  StickerSheet sheet(base, 3);
  sheet.addSticker(sticker1, 20, 200);
  sheet.addSticker(sticker1, 40, 200);
  sheet.addSticker(sticker1, 80, 200);

  output = sheet.render();
  output.writeToFile("myImage.png");
  
  return 0;
}
