void wander() {
  randomize();
  
  uint32_t color = Wheel(wheelPos & 255);
  
  fadeAll();
  
  uint16_t i = getPixelNum(xPos, yPos);
  strip.setPixelColor(i, color);
  
  if (vertDir == UP) {
    if (yPos < ROWS - 1) { // not at top, move up
      yPos++;
    } else { // at top, bounce down
      vertDir = DOWN;
      yPos--;
    }
  } else { // vertDir == DOWN
    if (yPos > 0) { // not at bottom, move down
     yPos--;
    } else { // at bottom, bounce up
      vertDir = UP;
      yPos++;
    }
  }
  
  if (horiDir == RIGHT) {
    xPos = (xPos + COLS - 1) % COLS;
  } else { // horiDir == LEFT
    xPos = (xPos + 1) % COLS;
  }
  
  wheelPos += shiftBy;
  strip.show();
  delay(updateInterval);
}
