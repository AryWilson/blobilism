/**
 * a simple interractive drawing program
 * 
 * @author Awilson
 * @date 2023-01-26
 * @file blobilism.cpp
 */

#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
using namespace tinygl;


class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }
  // stores color values 
  struct ColorRGB {
    float r;
    float g;
    float b;
  };
  //stores features of a circle
  //** store features of a circle, implementation keeps track of brush strokes and buttons/
  struct Circle {
    int x;
    int y;
    float size;
    ColorRGB col;
    float alpha;
  };

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // store a circle with the current color, size, x, y
      struct Circle newCircle{x,y,brushSize,globalColor,alpha};
      circles.push_back(newCircle);

    }
  }
  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      // check if user clicked a color 
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      //checks if mouse was clicked inside any of the pallet buttons
      for(struct Circle c : pallet){
        float dist = sqrt(pow((c.x-mx),2)+pow((c.y-my),2));
        if (dist<c.size) {
          //color clicked
          globalColor = c.col;
        }
      }


    }
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
      brushSize += 1;
    } 
    else if (key == GLFW_KEY_DOWN) {
      // decrease size of circle, within domain
      if(brushSize > 0){
        brushSize -= 1;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      // decrease alpha, within domain
      if(alpha > 0){
        alpha -= .1;
      }

    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha, within domain
      if(alpha < 1){
        alpha += .1;
      }
      

    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
      circles.clear();

    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f);

    
    //display drawing, draw evey stored circle
    for (struct Circle c : circles){
      // circle(x,y,diameter);
      color(c.col.r,c.col.g,c.col.b,c.alpha);
      circle(c.x,c.y,c.size);
    }
    
    // draw pallet on top of drawing
    color(0.1f, 0.1f, 0.1f);
    square(width()/2.0f, 35, width(), 70); //ceterx, centery, width, height
    for (struct Circle c : pallet) {
      color(c.col.r,c.col.g,c.col.b);
      circle(c.x,c.y,c.size);
    }
  }
 private:

  // member variables current circle size
  float brushSize=10;
  // current transparency
  float alpha = 1;
  // current color
  struct ColorRGB globalColor{0.0f,0.0f,0.0f};
  // list of circles to draw each frame
  std::vector<struct Circle> circles;
  // color pallet, define colors and store them in an array
  struct ColorRGB b{0.0f,0.0f,0.0f}; 
  struct ColorRGB w{1.0f,1.0f,1.0f}; 
  struct ColorRGB r{1.0f,0.1f,0.2f}; 
  struct ColorRGB g{0.2f,0.9f,0.2f}; 
  struct ColorRGB bl{0.2f,0.2f,1.0f}; 

  struct Circle black{1*width()/6,35,55,b,1.0f};
  struct Circle white{2*width()/6,35,55,w,1.0f};
  struct Circle red{3*width()/6,35,55,r,1.0f};
  struct Circle yellow{4*width()/6,35,55,g,1.0f};
  struct Circle blue{5*width()/6,35,55,bl,1.0f};


  struct Circle pallet[5] = {black,white,red,yellow,blue};


};

int main() {
  MyWindow window(500, 500);
  window.run();
}
