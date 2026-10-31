#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#define CE_PIN 7
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6][6] = {"00001","00002","00003","00004","00005","00006"};
uint8_t selectedAddress = 0;


/*
PUESDO CODE:

Initial Communication:
  1. Connect with the controller
  2. Recieve Channel
  3. Switch Channel
  4. Confirm reconncetion





*/

void setChannel(){
  bool selectedChannel = false;
  while(!selectedChannel){
    char buffer[50];
    sprintf(buffer,"Current Address: %d", selectedAddress);
    Serial.println(buffer);
    if(radio.available())
    {
      radio.read(&selectedAddress,sizeof(selectedAddress));
      sprintf(buffer,"Current Address: %d", selectedAddress);
      Serial.println(buffer);
      if(selectedAddress < 6)
      {
        radio.openReadingPipe(1, address[selectedAddress]);
        selectedChannel = true;
      }
    }
  }

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!radio.begin()){
    Serial.print("Radio not responding");
    while(true) {}
  }
  radio.openReadingPipe(1, address[selectedAddress]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  setChannel();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available())
  {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
