#include <Colorduino.h>

const boolean tree[8] = { 0x18, 0x3c, 0x7e, 0x3c, 0x7e, 0x3c, 0x7e, 0xff };
unsigned const char numOfLights = 5;
unsigned char xR[numOfLights], yR[numOfLights];
unsigned char rR[numOfLights], gR[numOfLights],bR[numOfLights];
const long colors[numOfLights] = { 0xff0000, 0xffff00, 0xffff00, 0xff0000, 0x0000ff};
unsigned char r,g,b;

void randomLightsOn() {
  unsigned n = 0;

  do {
      xR[n] = random(ColorduinoScreenHeight - 1);
      yR[n] = random(ColorduinoScreenWidth - 1);
      if (tree[xR[n]] & (1<<yR[n])) {
        rR[n] = (colors[n] & (0xff0000)) >> 16;
        gR[n] = (colors[n] & (0x00ff00)) >> 8;
        bR[n] = (colors[n] & (0x0000ff));
        n++;
      }
  } while(n < numOfLights);
}

void lightsOff() {
  for (unsigned char i;i<numOfLights;i++) {
    xR[i] = 4;
    yR[i] = 4;
    rR[i] = bR[i] = 0;
    gR[i] = 255;
  }
}

void drawTree(boolean lightsOn) {
  
  if (lightsOn) {
    randomLightsOn();
  } else {
     lightsOff();
  }
  
  for (unsigned char y=0;y<ColorduinoScreenWidth;y++) {
     for(unsigned char x=0;x<ColorduinoScreenHeight;x++) {
       for(unsigned char l=0;l<numOfLights;l++){
          if (x == xR[l] && y == yR[l]) {
            r = rR[l];
            g = gR[l];
            b = bR[l];
            l = numOfLights - 1;
          } else if ((tree[x] & (1<<y))) {
            r = b = 0;
            g = 255;
          } else {
            r = g = b = 0;
          }     
          Colorduino.SetPixel(x, y, r, g, b);
      }
     }
  }

 Colorduino.FlipPage();
  
}

void setup()
{
  Colorduino.Init(); // initialize the board
   unsigned char whiteBalVal[3] = {36,63,63}; // for LEDSEE 6x6cm round matrix
  Colorduino.SetWhiteBal(whiteBalVal);
  randomSeed(analogRead(0));
}

void loop()
{
  drawTree(false);
  delay(500);
  drawTree(true);
  delay(500); 
}
