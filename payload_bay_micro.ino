// When uploading to the payload bay micro, change this to true and the other INO to false
#if false

#include "altimeter.h"
#include "Buffer.h"

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  do {
    altimeter::initialize();
  } while (altimeter::getStatus() != altimeter::ACTIVE);
}

enum Mode {
  BELOW_5K,
  WATCHING,
  PAST_APOGEE,
};

void loop() {
  static Buffer data;
  static Mode mode = BELOW_5K;

  switch (mode) {
  case BELOW_5K:
    delay(1000);
    if (altimeter::getAltitude() >= 5000.0F) {
      mode = WATCHING;
    }
    break;
  case WATCHING:
    data.addPoint(altimeter::getAltitude());
    if (data.isDecreasing()) {
      digitalWrite(8, HIGH);
      mode = PAST_APOGEE;
    }
    break;
  case PAST_APOGEE:
    // nothing to do
    break;
  }
}

#endif
