#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


uint8_t button1 = 10;
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
  pinMode(joyStickButton, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.setTextColor(WHITE);
  display.clearDisplay();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  display.setTextSize(1);
  display.setCursor(0, 0); // col, row
  sprintf(buffer, "1: %d 2: %d 3: %d 4: %d\n", digitalRead(button1),digitalRead(button2),digitalRead(button3),digitalRead(button4));
  display.println(buffer);
  sprintf(buffer, "X: %d, Y: %d, B: %d\n ", analogRead(joyStickX),analogRead(joyStickY),digitalRead(joyStickButton));
  display.println(buffer);
  display.display();
  delay(500);
  display.clearDisplay();
}
