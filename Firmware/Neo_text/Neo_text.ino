#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN A4
#define NUM_LEDS 25

boolean E[25] = {0, 1, 1, 1, 1,  0, 1, 0, 0, 0,  0, 1, 1, 1, 0,  0, 1, 0, 0, 0,  0, 1, 1, 1, 1};
boolean C[25] = {0, 0, 1, 1, 1,  0, 1, 0, 0, 0,  0, 1, 0, 0, 0,  0, 1, 0, 0, 0,  0, 0, 1, 1, 1};
boolean H[25] = {0, 1, 0, 0, 1,  0, 1, 0, 0, 1,  0, 1, 1, 1, 1,  0, 1, 0, 0, 1,  0, 1, 0, 0, 1};
boolean I[25] = {0, 1, 1, 1, 0,  0, 0, 1, 0, 0,  0, 0, 1, 0, 0,  0, 0, 1, 0, 0,  0, 1, 1, 1, 0};
boolean D[25] = {0, 1, 1, 0, 0,  0, 1, 0, 1, 0,  0, 1, 0, 0, 1,  0, 1, 0, 1, 0,  0, 1, 1, 0, 0};
boolean N[25] = {0, 1, 0, 0, 1,  0, 1, 1, 0, 1,  0, 1, 0, 1, 1,  0, 1, 0, 0, 1,  0, 1, 0, 0, 1};
boolean A[25] = {0, 0, 1, 0, 0,  0, 1, 0, 1, 0,  0, 1, 0, 0, 1,  0, 1, 1, 1, 1,  0, 1, 0, 0, 1};
int wait = 200;
int ret1 = 100;
int R;
int G;
int B;
int i = 0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  for (int j = 0; j < 10; j++) {
    pixels.begin();

    for (i = 0; i < 25; i++) {
      R = random(0, 32); G = random(0, 32); B = random(0, 32);
      pixels.setPixelColor(i, pixels.Color(R, G, B));
      pixels.show();
      delay(ret1);
    }
  }
  
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    delay(ret1);
  }

  delay(2 * wait);
  R = 8; G = 0; B = 0;
  vis_E(); delay(wait); vis_C(); delay(wait); vis_H(); delay(wait); vis_I(); delay(wait); vis_D(); delay(wait); vis_N(); delay(wait); vis_A();
  delay(wait);
  R = 0; G = 8; B = 0;
  vis_E(); delay(wait); vis_C(); delay(wait); vis_H(); delay(wait); vis_I(); delay(wait); vis_D(); delay(wait); vis_N(); delay(wait); vis_A();
  delay(wait);
  R = 0; G = 0; B = 16;
  vis_E(); delay(wait); vis_C(); delay(wait); vis_H(); delay(wait); vis_I(); delay(wait); vis_D(); delay(wait); vis_N(); delay(wait); vis_A();
  delay(wait);
}
void loop() {

  delay(2 * wait);
  R = random(0, 32); G = random(0, 32); B = random(0, 32);
  vis_E(); delay(wait); vis_C(); delay(wait); vis_H(); delay(wait); vis_I(); delay(wait); vis_D(); delay(wait); vis_N(); delay(wait); vis_A();
}


void vis_E() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * E[i], G * E[i], B * E[i])); //
    pixels.show();
  }
}
void vis_C() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * C[i], G * C[i], B * C[i])); //
    pixels.show();
  }
}
void vis_H() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * H[i], G * H[i], B * H[i])); //
    pixels.show();
  }
}

void vis_I() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * I[i], G * I[i], B * I[i])); //
    pixels.show();
  }
}
void vis_D() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * D[i], G * D[i], B * D[i])); //
    pixels.show();
  }
}

void vis_N() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * N[i], G * N[i], B * N[i])); //
    pixels.show();
  }
}

void vis_A() {
  for (i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, pixels.Color(R * A[i], G * A[i], B * A[i])); //
    pixels.show();
  }
}
