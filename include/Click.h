#ifndef CLICK_H
#define CLICK_H

// Storage class; just retains X and Y
// of a mouse Click
class Click {
public:
  bool targetX = false;
  bool targetY = false;
  int x, y;
  Click();
  Click(int, int);
};

#endif