void torch() {
  uint8_t col;
  uint32_t color;

  //randomize();
  uint8_t updateInterval = 75;
  
  for(col = 0; col < COLS; col++) {
    if (random(2)) {
      fadeCol(col);
    } else {
      color = Wheel(wheelPos & 255);
      colFlame(col, color);
    }
  }
  wheelPos += shiftBy;
  strip.show();
  delay(updateInterval);
}

void colFlame(uint8_t col, uint32_t color) {
  uint8_t height = 2 + random(ROWS-1);
  uint8_t row;
  uint16_t idx;
    
  for(row = 0; row < height; row++) {
    idx = getPixelNum(col, row);
    strip.setPixelColor(idx, color);
    color = fadeFactory(color);
  }
  for (row = height; row < ROWS; row++) {
    idx = getPixelNum(col, row);
    strip.setPixelColor(idx, BLACK);
  }
}

void fadeCol(uint8_t col) {
  uint8_t row;
  uint16_t idx;
  uint32_t color;
  for (row = 0; row < ROWS; row++) {
    idx = getPixelNum(col, row);
    color = strip.getPixelColor(idx);
    color = fadeFactory(color);
    strip.setPixelColor(idx, color);
  }
}

