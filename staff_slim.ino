#define PIN_LIGHTS 6
#define ROWS 7 // number of rows of pixels
#define COLS 8 // number of pixels in a row
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define NUM_SCHEMES 11 // number of color schemes
#define S_RAINBOW 0
#define S_CRISPY 1
#define S_SNOWSKIRT 2
#define S_ROYAL 3
#define S_GLEAM 4
#define S_FIRE 5
#define S_SPORKLE 6
#define S_DORK 7
#define S_KELPY 8
#define S_JUNGLE 9
#define S_AMERICA 10

#define NUM_MODES 5 // number of program modes
#define M_PULSE 0
#define M_SPIRAL 1
#define M_SWIRL 2
#define M_TORCH 3
#define M_WANDER 4

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(ROWS * COLS, PIN_LIGHTS, NEO_GRB + NEO_KHZ400);

uint8_t updateInterval = 100; // Milliseconds between color updates

uint8_t mode = M_TORCH;   // Program mode selected
uint8_t scheme = S_ROYAL; // Color scheme selected
uint8_t shiftBy = 20;
uint8_t wheelPos = 0;

uint8_t vertDir = UP;
uint8_t horiDir = LEFT;

uint8_t xPos = 0;
uint8_t yPos = 0;

uint8_t fadeFactor = 3;
uint8_t chance = 100;

uint32_t BLACK = 0;

void setup()
{
  //Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'.
  randomSeed(analogRead(0));
  randomize();
  delay(10);
}

void loop()
{
  if (!random(chance)) {
    mode = random(NUM_MODES);
  }
  if (!random(chance)) {
    scheme = random(NUM_SCHEMES);
  }
  switch (mode) {
    case M_PULSE:
      pulse();
      break;
    case M_SPIRAL:
      spiral();
      break;
    case M_SWIRL:
      swirl();
      break;
    case M_TORCH:
      torch();
      break;
    case M_WANDER:
      wander();
      break;
  }
}
