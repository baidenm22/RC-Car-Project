//This is the radio library
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#define CE_PIN 7
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6][6] = {"00001","00002","00003","00004","00005","00006"};
uint8_t selectedAddress = 0;

//This is the OLED library
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


uint8_t button1 = 8;
uint8_t button2 = 9;
uint8_t button3 = 3;
uint8_t button4 = 2;
uint8_t joyStickButton = 6;
uint8_t joyStickX = 2;
uint8_t joyStickY = 1;

char buffer[32];

/*
PUESDO CODE:

Initial Communication:
  1. Connect with the car
  2. Select Channel (Show Channel and All)
  3. Send Channel
  4. Switch Channel
  5. Confirm reconnection





*/
struct packet {
  uint16_t joystickX; //2 bytes
  uint16_t joystickY; //2 bytes
  uint8_t joystickButton; //1 byte
  uint8_t button1; //1 byte
  uint8_t button2; //1 byte
  uint8_t button3; //1 byte
  uint8_t button4; // 1 byte
  //1 byte padding
  //total: 10 bytes, so 22 bytes avliable to send
} data;




void setPins() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(joyStickButton, INPUT_PULLUP);
}

void setChannel() {
  bool selectedChannel = false;
  sprintf(buffer, "Current Channel: %d", selectedAddress);
  display.print(buffer);
  display.display();
  while(!selectedChannel){
    if(digitalRead(button1)) {
      delay(500);
      selectedAddress = (selectedAddress + 1) % 6;
      sprintf(buffer, "Current Channel: %d", selectedAddress);
      display.setCursor(0,0);
      display.clearDisplay();
      display.print(buffer);
      display.display();
    }
    if(digitalRead(button2)) {
      delay(500);
      selectedAddress = (selectedAddress + 5) % 6;
      sprintf(buffer, "Current Channel: %d", selectedAddress);
      display.setCursor(0,0);
      display.clearDisplay();
      display.print(buffer);
      display.display();
    }
    if(digitalRead(button3)) {
      delay(500);
      if(radio.write(&selectedAddress, sizeof(selectedAddress))){
        radio.openWritingPipe(address[selectedAddress]);
        selectedChannel = true;
      } else {
        display.setCursor(0,0);
        display.clearDisplay();
        display.print("Failed to connect: Retry");
        display.display();
        delay(2000);
      }
    }
  }
}


void setup() {
  //Set the Pins
  setPins();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  delay(1000);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);

  if(!radio.begin())
  {
    display.print("Failed to start Radio");
  }
  delay(1000);
  radio.openWritingPipe(address[selectedAddress]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  setChannel();

}

void loop() {
  // put your main code here, to run repeatedly:
  display.setCursor(0,0);
  sprintf(buffer, "1: %d 2: %d 3: %d 4: %d\n", digitalRead(button1),digitalRead(button2),digitalRead(button3),digitalRead(button4));
  display.println(buffer);
  radio.writeFast(&buffer, sizeof(buffer));
  sprintf(buffer, "X: %d, Y: %d, B: %d\n ", analogRead(joyStickX),analogRead(joyStickY),digitalRead(joyStickButton));
  display.println(buffer);
  display.display();
  delay(250);
  radio.writeFast(&buffer, sizeof(buffer));
  display.clearDisplay();
}
