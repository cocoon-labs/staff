uint16_t getPixelNum(uint8_t x, uint8_t y) {
  int pixel;
  if (x % 2 == 0) pixel = (x * 7) + y;
  else            pixel = ((x + 1) * 7 - (y + 1));
  return pixel;
}

void shift(uint8_t dir, uint32_t color) {
  switch (dir) {
    case UP:
      shiftUp(color);
      break;
    case DOWN:
      shiftDown(color);
      break;
    case LEFT:
      shiftLeft();
      break;
    case RIGHT:
      shiftRight();
      break;
  }
}

/* Given a color, this function shifts the colors down one row,
 * and sets the color of the top row to the input color. */
void shiftDown(uint32_t Color) {
  uint8_t x, y; // Variables for looping
  // Shift colors down row by row, starting from the bottom.
  for (y=ROWS-1 ; y>0 ; y--){
    // Set the current pixel's color to that of the above pixel in its column.
    for (x=0 ; x<COLS ; x++){
      uint16_t i = getPixelNum(x, y);
      uint16_t j = getPixelNum(x, y-1);
      strip.setPixelColor(i, strip.getPixelColor(j));
    }
  }
  // Set the top row to the input color.
  for (x=0 ; x<COLS ; x++){
    uint8_t i = getPixelNum(x, 0);
    strip.setPixelColor(i, Color);
  }
}

/* Given a color, this function shifts the colors up one row,
 * and sets the color of the bottom row to the input color. */
void shiftUp(uint32_t Color) {
  uint8_t x, y; // Variables for looping
  
  // Shift colors up row by row, starting from the top.
  for (y=0 ; y<ROWS-1 ; y++){
    // Set the current pixel's color to that of the below pixel in its column.
    for (x=0 ; x<COLS ; x++){
      uint16_t i = getPixelNum(x, y);
      uint16_t j = getPixelNum(x, y+1);
      strip.setPixelColor(i, strip.getPixelColor(j));
    }
  }
  // Set the bottom row to the input color.
  for (x=0 ; x<COLS ; x++){
    uint8_t i = getPixelNum(x, ROWS-1);
    strip.setPixelColor(i, Color);
  }
}

/* Given a color, this function shifts the colors left one column. */
void shiftLeft() {
  uint8_t x, y; // Variables for looping
  
  // Shift colors left column by column.
  for (x=COLS+COLS-1 ; x>COLS-1 ; x--){
    // Set the current pixel's color to that of the pixel in its row to its right.
    for (y=0 ; y<ROWS ; y++){
      uint16_t i = getPixelNum(x%COLS, y);
      uint16_t j = getPixelNum((x-1)%COLS, y);
      strip.setPixelColor(i, strip.getPixelColor(j));
    }
  }
}

/* Given a color, this function shifts the colors right one column. */
void shiftRight() {
  uint8_t x, y; // Variables for looping
  
  // Shift colors right column by column.
  for (x=0 ; x<COLS ; x++){
    // Set the current pixel's color to that of the pixel in its row to its left.
    for (y=0 ; y<ROWS ; y++){
      uint16_t i = getPixelNum(x, y);
      uint16_t j = getPixelNum((x+1)%COLS, y);
      strip.setPixelColor(i, strip.getPixelColor(j));
    }
  }
}

// Input a value 0 to 255 to get a color value.
uint32_t Wheel(byte WheelPos) {
  // Use selected color scheme.
  switch (scheme) {
    case S_RAINBOW: // Rainbow
      return rainbowWheel(WheelPos);
    case S_CRISPY: //
      return generalWheel(WheelPos, strip.Color(2,255,222), strip.Color(229,149,217), strip.Color(210,255,0));
    case S_SNOWSKIRT: //
      return generalWheel(WheelPos, strip.Color(229,255,46), strip.Color(240,23,0), strip.Color(147,0,131));
    case S_ROYAL: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(128,0,255), strip.Color(128,0,128));
    case S_GLEAM: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(23,7,0), strip.Color(85,60,0));
    case S_FIRE: //
      return generalWheel(WheelPos, strip.Color(255,0,0), strip.Color(255,100,0), strip.Color(232,120,0));
    case S_SPORKLE: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(80,0,230), strip.Color(0,0,0));
    case S_DORK: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(196,0,255), strip.Color(209,209,209));
    case S_KELPY: //
      return generalWheel(WheelPos, strip.Color(0,0,133), strip.Color(0,196,255), strip.Color(0,240,44));
    case S_JUNGLE: //
      return generalWheel(WheelPos, strip.Color(214,185,0), strip.Color(0,255,17), strip.Color(60,138,80));
    case S_AMERICA: //
      return generalWheel(WheelPos, strip.Color(255,0,0), strip.Color(209,209,209), strip.Color(0,0,255));
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t rainbowWheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

uint32_t generalWheel(byte WheelPos, uint32_t C0, uint32_t C1, uint32_t C2) {
  uint8_t r0 = C0 >> 16;
  uint8_t g0 = (C0 >> 8) & 255;
  uint8_t b0 = C0 & 255;
  uint8_t r1 = C1 >> 16;
  uint8_t g1 = (C1 >> 8) & 255;
  uint8_t b1 = C1 & 255;
  uint8_t r2 = C2 >> 16;
  uint8_t g2 = (C2 >> 8) & 255;
  uint8_t b2 = C2 & 255;
  
  if(WheelPos < 85) {
   return strip.Color(r0 + (WheelPos * (r1 - r0) / 85), g0 + (WheelPos * (g1 - g0) / 85), b0 + (WheelPos * (b1 - b0) / 85));
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(r1 + (WheelPos * (r2 - r1) / 85), g1 + (WheelPos * (g2 - g1) / 85), b1 + (WheelPos * (b2 - b1) / 85));
  } else {
   WheelPos -= 170;
   return strip.Color(r2 + (WheelPos * (r0 - r2) / 85), g2 + (WheelPos * (g0 - g2) / 85), b2 + (WheelPos * (b0 - b2) / 85));
  }
}

void shiftGradDown() {
  uint8_t x, y; // Variables for looping
  
  // Shift colors down row by row, starting from the bottom.
  for (y=ROWS-1 ; y>0 ; y--){
    // Set the current pixel's color to that of the above pixel in its column.
    for (x=0 ; x<COLS ; x++){
      uint16_t i = getPixelNum(x, y);
      uint16_t j = getPixelNum(x, y-1);
      strip.setPixelColor(i, strip.getPixelColor(j));
    }
  }
  // Set the top row to the input color.
  uint16_t wpTemp = wheelPos;
  for (x=0 ; x<COLS ; x++){
    uint8_t i = getPixelNum(x, 0);
    
    strip.setPixelColor(i, Wheel((wpTemp + (x * 256 / COLS)) % 256));
  }
}

void shiftGradUp() {
  uint8_t x, y; // Variables for looping
  
  // Shift colors up row by row, starting from the top.
  for (y=0 ; y<ROWS-1 ; y++){
    // Set the current pixel's color to that of the below pixel in its column.
    for (x=0 ; x<COLS ; x++){
      uint16_t i = getPixelNum(x, y);
      uint16_t j = getPixelNum(x, y+1);
      strip.setPixelColor(i, strip.getPixelColor(j));
    }
  }
  // Set the bottom row to the input color.
  uint16_t wpTemp = wheelPos;
  for (x=0 ; x<COLS ; x++){
    uint8_t i = getPixelNum(x, ROWS-1);
    
    strip.setPixelColor(i, Wheel((wpTemp + (x * 256 / COLS)) % 256));
  }
}

void pushOne (uint8_t vertDir, uint32_t color, uint8_t x) {
  uint16_t i;
  shift(vertDir, BLACK);
  if (vertDir == UP) i = getPixelNum(x, ROWS-1);
  else                i = getPixelNum(x, 0);
  strip.setPixelColor(i, color);
}

void randomize () {
  if (!random(chance)) {
    if (vertDir == UP) vertDir = DOWN;
    else vertDir = UP;
  }
  if (!random(chance)) {
    if (horiDir == LEFT) horiDir = RIGHT;
    else horiDir = LEFT;
  }
  if (!random(chance)) {
    shiftBy = random(50);
  }
  if (!random(chance)) {
    updateInterval = 20 + random(200);
  }
  if (!random(chance)) {
    fadeFactor = 2 + random(10);
  }
}

uint32_t fadeFactory(uint32_t color) {
  uint32_t r = (color >> 16) * 2 / fadeFactor;
  uint32_t g = ((color >> 8) & 255) * 2 / fadeFactor;
  uint32_t b = (color & 255) * 2 / fadeFactor;
  return (r << 16) | (g << 8) | b;
}  

void fadeAll( ) {
  uint8_t col, row;
  uint16_t idx;
  uint32_t color;
  
  for (row = 0; row < ROWS; row++) {
    for (col = 0; col < COLS; col++) {
      idx = getPixelNum(col, row);
      color = strip.getPixelColor(idx);
      color = fadeFactory(color);
      strip.setPixelColor(idx, color);
    }
  }
}
