#include "kusrc_function.h"

MFRC522 rfid(D2, D3);
MFRC522::MIFARE_Key key;

void blink(uint8_t debugPin, unsigned long delaytime) {
  delay(delaytime);
  digitalWrite(debugPin, LOW);
  delay(delaytime);
  digitalWrite(debugPin, HIGH);
}

void startup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);

  memset(key.keyByte, 0xFF, MFRC522::MF_KEY_SIZE);
  Serial.println();
}

void readcard(void *dest) {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    digitalWrite(BUILTIN_LED, HIGH);
    return;
  }

  digitalWrite(BUILTIN_LED, LOW);
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_1K && piccType != MFRC522::PICC_TYPE_MIFARE_4K)
    return;

  if (memcmp(rfid.uid.uidByte, dest, cardBufferSize))
    memcpy(dest, rfid.uid.uidByte, cardBufferSize);
  
  printHex(rfid.uid.uidByte, cardBufferSize);

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  digitalWrite(BUILTIN_LED, HIGH);
}

void copyId(void *dest, const void *src) {
  memcpy(dest, src, cardBufferSize);
}

void resetId(void *dest) {
  bzero(dest, cardBufferSize);
}

int sameId(void *src1, const void *src2) {
  return !memcmp(src1, src2, cardBufferSize);
}

void printHex(byte *buffer, byte size) {
  for (byte i = 0; i < size; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}

