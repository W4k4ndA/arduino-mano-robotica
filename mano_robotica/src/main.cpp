#include <Arduino.h>
#include <Servo.h>

// Definición de los servos y sus nombres
Servo pulgar;
Servo indice;
Servo medio;
Servo anular;
Servo menique;

// Pines para los servomotores (deben ser pines PWM)
#define pinPulgar 3
#define pinIndice 5
#define pinMedio 6
#define pinAnular 9
#define pinMenique 10

// Pines para los LEDs
#define ledPulgar  2
#define ledIndice  4
#define ledMedio  7
#define ledAnular  8
#define ledMenique  11

// Ángulos a utilizar
const int angulos[] = {0, 45, 90, 180};
const int numAngulos = 4;

// Tiempo de espera entre movimientos (ms)
const int tiempoEspera = 1000;

//declaracion de funciones
//
void moverDedo(Servo &servo, int pinLed, int angulo, const char* nombreDedo);

void setup() {
  // Inicializar los servos
  pulgar.attach(pinPulgar);
  indice.attach(pinIndice);
  medio.attach(pinMedio);
  anular.attach(pinAnular);
  menique.attach(pinMenique);
  
  // Configurar pines de los LEDs como salida
  pinMode(ledPulgar, OUTPUT);
  pinMode(ledIndice, OUTPUT);
  pinMode(ledMedio, OUTPUT);
  pinMode(ledAnular, OUTPUT);
  pinMode(ledMenique, OUTPUT);
  
  // Inicializar comunicación serial (opcional, para depuración)
  Serial.begin(9600);
  Serial.println("Sistema de control de mano robotica inicializado");
}

void loop() {
  // Mover todos los dedos secuencialmente por cada ángulo
  for (int i = 0; i < numAngulos; i++) {
    int anguloActual = angulos[i];
    
    Serial.print("Moviendo todos los dedos a ");
    Serial.print(anguloActual);
    Serial.println(" grados");
    
    // Mover pulgar
    moverDedo(pulgar, ledPulgar, anguloActual, "Pulgar");
    
    // Mover índice
    moverDedo(indice, ledIndice, anguloActual, "Índice");
    
    // Mover medio
    moverDedo(medio, ledMedio, anguloActual, "Medio");
    
    // Mover anular
    moverDedo(anular, ledAnular, anguloActual, "Anular");
    
    // Mover meñique
    moverDedo(menique, ledMenique, anguloActual, "Meñique");
    
    // Esperar antes del siguiente movimiento
    delay(tiempoEspera);
  }
}

// Función para mover un dedo y controlar su LED
void moverDedo(Servo &servo, int pinLed, int angulo, const char* nombreDedo) {
  // Encender LED mientras se mueve
  digitalWrite(pinLed, HIGH);
  
  Serial.print("Moviendo ");
  Serial.print(nombreDedo);
  Serial.print(" a ");
  Serial.print(angulo);
  Serial.println(" grados");
  
  servo.write(angulo);
  delay(200); // Pequeña pausa para el movimiento
  
  // Apagar LED después del movimiento
  digitalWrite(pinLed, LOW);
}