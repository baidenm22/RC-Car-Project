//This is the radio library
#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#define CE_PIN 7
#define CSN_PIN 10
RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001";
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

char buffer[50];

void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(joyStickButton, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  delay(1000);
  display.setTextColor(WHITE);
  display.clearDisplay();
  radio.begin();
  delay(1000);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  display.setTextSize(1);
  display.setCursor(0, 0); // col, row
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
