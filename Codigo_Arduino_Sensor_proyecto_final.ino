#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE 9
#define CSN 10
#define entrada 5
#define btn1 4
#define btn2 3

RF24 radio(CE, CSN);

const byte direccion[6] = "00701";

int dato;
int dato2;
int dato3;

int val1 = 1;
int val2 = 2;
int val3 = 3;

void setup() {

  pinMode(entrada, INPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);

  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(direccion);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();

  Serial.println("Transmisor listo");
}

void loop() {

  dato = digitalRead(entrada);   // leer sensor FC-51
  dato2 = digitalRead(btn1);
  dato3 = digitalRead(btn2);

  

  Serial.print("Valor enviado: ");
  Serial.println(dato);
  Serial.print("Valor enviado 2: ");
  Serial.println(dato2);
  Serial.print("Valor enviado 3: ");
  Serial.println(dato3);

  
  if (dato == 0) radio.write(&val3, sizeof(val3));
  if (dato2 == 1) radio.write(&val2, sizeof(val2));
  if (dato3 == 1) radio.write(&val1, sizeof(val1));

  dato = 0;
  dato2 = 0;
  dato3 = 0;

  delay(1000);

}