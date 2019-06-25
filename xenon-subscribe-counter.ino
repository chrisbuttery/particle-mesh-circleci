/// This #include statement was automatically added by the Particle IDE.
#include "adafruit-led-backpack.h"

Adafruit_7segment matrix = Adafruit_7segment();
int count = 0;

void logToDisplay(const char *event, const char *data) {
  digitalWrite(D7, HIGH);
  delay(1000);
  digitalWrite(D7, LOW);
  count++;
  matrix.print(count);
  matrix.writeDisplay();
}

void setup() {
  Mesh.subscribe("matrix_display_message", logToDisplay);
  matrix.begin(0x70);
  matrix.print(count);
  matrix.writeDisplay();
}

void loop() {}