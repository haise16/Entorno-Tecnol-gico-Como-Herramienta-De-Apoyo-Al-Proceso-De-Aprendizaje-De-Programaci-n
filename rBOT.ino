#include <BluetoothSerial.h>

BluetoothSerial SerialBT; // Objeto para manejar la comunicación Bluetooth

//Motor A
const int ENA = 15;
const int INA1 = 14;
const int INA2 = 5;

//Motor B
const int ENB = 13;
const int INB1 = 4;
const int INB2 = 26;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32 rBoT"); // Inicializar el Bluetooth y asignar un nombre
  //Serial.println(F("Prueba DHT11!"));

  //dht.begin();
  
  pinMode(ENA, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);

  digitalWrite(ENA, LOW);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
}

void loop() {
  if (SerialBT.available()) { // Verificar si hay datos disponibles para leer
    char data = SerialBT.read();
    if (data != 'S'){
      switch (data) {
        case 'A':
          adelante();
          Serial.println("Adelante");
          break;

        case 'B':
          antihorario();
          Serial.println("Izquierda");
          break;

        case 'C':
          horario();
          Serial.println("Derecha");
          break;
        case 'D':
          atras();
          Serial.println("Atrás");
          break;

        case 'X':
          stop();
          Serial.println("Detener");
          break;
        }
    }else{

      char receivedData[8];

      for (int i = 0; i < 7; i++) {
      receivedData[i] = SerialBT.read(); // Leer el carácter recibido
    }
    receivedData[7] = '\0';  // Añadir el terminador nulo al final del array

    for (int i = 0; i < 7; i++) {
      //String enviar = 
        if (receivedData[i] == 'A') {
          adelante();
          Serial.println("Adelante");
          SerialBT.print("Adelante|");
        }
        if (receivedData[i] == 'B') {
          antihorario();
          Serial.println("Izquierda");
          SerialBT.print("Izquierda|");
        }
        if (receivedData[i] == 'C') {
          horario();
          Serial.println("Derecha");
          SerialBT.print("Derecha|");
        }
        if (receivedData[i] == 'D') {
          atras();
          Serial.println("Atrás");
          SerialBT.print("Atras|");
        }
        if (receivedData[i] == 'X') {
          stop();
          Serial.println("Detener");
          SerialBT.print("Detener|");
        }
        delay(200);
      }

    }
    
  }
}

void adelante(){
  digitalWrite(ENA, HIGH);
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  digitalWrite(ENB, HIGH);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);
}
void atras(){
  digitalWrite(ENA, HIGH);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);
}
void horario(){
  digitalWrite(ENA, HIGH);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);
}
void antihorario(){
  digitalWrite(ENA, HIGH);
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  digitalWrite(ENB, HIGH);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);
}
void stop(){
  digitalWrite(ENA, LOW);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
}
