void pulse() {
  uint32_t color;
  uint8_t x, y;

  randomize();
  
  fadeAll();
  
  for (x=0 ; x<COLS ; x++) {
        uint16_t i = getPixelNum(x,yPos);
        strip.setPixelColor(i, Wheel(wheelPos & 255));
  }
  
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
  
  wheelPos += shiftBy;
  
  strip.show();
  delay(updateInterval);
}

