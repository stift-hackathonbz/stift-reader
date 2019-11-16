
 /*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */



#include <SPI.h>
#include "MFRC522.h"


#define DEBUG false

//RFID
constexpr uint8_t RST_PIN = 9;          // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
int oldcount=0;


void setup() {
  
  Serial.begin(115200);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus


  //RFID
  mfrc522.PCD_Init();   // Init MFRC522
  if(DEBUG)
    mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
       
}



void loop() {
  byte bufferATQA[5];
  byte bufferSize = 5;
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Select one of the cards
    if (mfrc522.PICC_ReadCardSerial()) {
      // Dump debug info about the card; PICC_HaltA() is automatically called
      if(DEBUG)
        mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
        mfrc522.PICC_HaltA();
        mfrc522.PICC_saveUID(&(mfrc522.uid));
    }
    
  }

  if(mfrc522.myuid_count != oldcount){
    for(int i=0; i<mfrc522.myuid_count; i++){
      mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.myuid[i]));
      Serial.println("");
    }
    oldcount = mfrc522.myuid_count;
  }

  for(int i=0; i<mfrc522.myuid_count; i++){
      mfrc522.PICC_WakeupA(bufferATQA, &bufferSize);
      if(mfrc522.PICC_Select(&(mfrc522.myuid[i]))==3){
        mfrc522.PICC_deleteUID(&(mfrc522.myuid[i]));
        //Serial.println("Delete");
      }
  }
}





