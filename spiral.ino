void spiral() {
  randomize();
  
  uint32_t color = Wheel(wheelPos & 255);
  
  shift(vertDir, color);
  shift(horiDir, BLACK);
  
  wheelPos += shiftBy;
  strip.show();
  delay(updateInterval);
}

void swirl() {
  randomize();
  
  uint32_t color = Wheel(wheelPos & 255);
  
  shift(horiDir, BLACK);
  pushOne(vertDir, color, xPos);
  
  if (horiDir == LEFT) xPos = (COLS + xPos - 1) % COLS;
  else                 xPos = (xPos + 1) % COLS;
  
  wheelPos += shiftBy;
  strip.show();
  delay(updateInterval);
}
