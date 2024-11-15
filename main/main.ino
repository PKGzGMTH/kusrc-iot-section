#include "kusrc_function.h"
#include <SPI.h>
#include <MFRC522.h>

byte my_card[cardBufferSize];
byte new_card[cardBufferSize];
byte old_card[cardBufferSize];

void setup() {
  startup();
  resetId(my_card);
  resetId(new_card);
  resetId(old_card);

  readcard(new_card);
  copyId(my_card, new_card);

  pinMode(D8, INPUT);
  pinMode(D0, OUTPUT);

  digitalWrite(D0, HIGH);
}

void loop() {
  readcard(new_card);

  if (digitalRead(D8) == HIGH) {
    resetId(new_card);
    printf("reset id!\n");
  }

  if (sameId(old_card, new_card)) return;
  copyId(old_card, new_card);

  if (sameId(my_card, new_card)) {
    printf("Hello welcome!\n");
    digitalWrite(D0, HIGH);
  } else {
    printf("Wrong card!\n");
    digitalWrite(D0, LOW);
  }

  delay(100);
}
