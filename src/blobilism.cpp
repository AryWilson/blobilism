/**
 * A01
 * 
 * @author Awilson
 * @date 2023-01-26
 * @file blobilism.cpp
 */

#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
using namespace tinygl;


// struct Circle {
//   int x;
//   int y;
//   float size;
//   float col[3];
// };

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  struct Circle {
    int x;
    int y;
    float size;
    float col[3];
  };

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // todo: store a circle with the current color, size, x, y
      struct Circle newCircle{x,y,brushSize,globalColor};
      circles.push_back(newCircle);

    }
  }
  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      // todo: check if user clicked a color 
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      for(Color col : pallet){
        float d = sqrt(pow((col.x-mx),2)+pow((col.y-my),2));
        if (d<col.size) {
          //color clicked
          globalColor = col.color;
        }
      }


    }
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
      brushSize += .1;
    } 
    else if (key == GLFW_KEY_DOWN) {
      // decrease size of circle
      if(brushSize > 0){
        brushSize -= .1;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      // decrease alpha
      if(alpha > 0){
        alpha -= .1;
      }

    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha
      alpha += .1;

    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
      circles.clear();

    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    // color(1.0f, 0.5f, 0.5f);
    // circle(width() * 0.5f, height() * 0.5, 300);

    // todo : draw pallet
    color(0.1f, 0.1f, 0.1f);
    square(width()/2.0f, 35, width(), 70); //ceterx, centery, width, height
    for (Color col : pallet) {
      color(col.color[0],col.color[1],col.color[2]);
      circle(col.x,col.y,col.size);
    }
    //draw background
    for (struct Circle c : circles){
      // circle(x,y,diameter);
      color(c.col[0],c.col[1],c.col[2]);
      circle(c.x,c.y,c.size);
    }
  }
 private:

  // todo: create member variables for 
  // current circle size
  float brushSize=1;
  // current transparency
  float alpha = 1;
  // current color
  float globalColor[3] = {1.0f,0.1f,0.5f};

  // list of circles to draw each frame
  std::vector<struct Circle> circles;
  // color pallet
  //5 rows (colors:black,white,red,yellow,blue) 3 columns (values:r,g,b)
  struct Color black{1*width()/6,10,10,{0.0f,0.0f,0.0f}};
  struct Color white{2*width()/6,10,10,{0.0f,0.0f,0.0f}};
  struct Color red{3*width()/6,10,10,{0.0f,0.0f,0.0f}};
  struct Color yellow{4*width()/6,10,10,{0.0f,0.0f,0.0f}};
  struct Color blue{5*width()/6,10,10,{0.0f,0.0f,0.0f}};


  float pallet[5] = {black,white,red,yellow,blue};


};

int main() {
  MyWindow window(500, 500);
  window.run();
}
