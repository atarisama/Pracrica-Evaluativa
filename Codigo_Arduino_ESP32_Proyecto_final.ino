#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define CE 4
#define CSN 5
#define LED 2

int pin = 12;
int pingnd = 34;

int G1 = 0;
int G2 = 0;
int G3 = 0;

Adafruit_SSD1306 display (128,64, &Wire, -1);



RF24 radio(CE, CSN);

const byte direccion[6] = "00701";

int datoRecibido;

void setup() {
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  pinMode(pingnd, OUTPUT);
  pinMode(LED, OUTPUT);
  
  

  Wire.begin(27, 26); // Tus pines

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Error OLED");
    while(true);
  }

  display.clearDisplay();


  radio.begin();
  radio.openReadingPipe(0, direccion);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
}

void loop() {
  digitalWrite(pin, HIGH);
  digitalWrite(pingnd, LOW);
  

  if (radio.available()) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    radio.read(&datoRecibido, sizeof(datoRecibido));

    Serial.print("Dato recibido: ");
    Serial.println(datoRecibido);

    if (datoRecibido == 1) G1++;
    if (datoRecibido == 2) G2++;
    if (datoRecibido == 3) G3++;
  }
  int total = G1 + G2 + G3;

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.print("G1: ");
  display.println(G1);

  display.setCursor(0, 15);
  display.print("G2: ");
  display.println(G2);

  display.setCursor(0, 30);
  display.print("G3: ");
  display.println(G3);

  display.setCursor(0, 50);
  display.print("Total: ");
  display.println(total);

  display.display();
  
}
