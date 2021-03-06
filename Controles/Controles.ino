//Librerias que se utilizarán para el manejo de hardware y software
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

//Variables que serán utilizadas a lo largo del código
int boton_jugador1_arriba = 12; 
int boton_jugador1_abajo = 13;
int boton_jugador2_arriba = 10;
int boton_jugador2_abajo = 11;
int boton_pausa = A0;
int boton_volumen = A1;
int boton_color = A2;
int punto;
int p1;
int p2;

uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};


void setup() {
  
  //Inicializa la comunicacion serial
  Serial.begin(9600);

  //Tipo de señal en cada respectivo pin
  pinMode(boton_jugador1_arriba, INPUT_PULLUP);
  pinMode(boton_jugador1_abajo, INPUT_PULLUP);
  pinMode(boton_jugador2_arriba, INPUT_PULLUP);
  pinMode(boton_jugador2_abajo, INPUT_PULLUP);
  pinMode(boton_pausa, INPUT_PULLUP);
  pinMode(boton_volumen, INPUT_PULLUP);
  pinMode(boton_color, INPUT_PULLUP);
  
  //Etapa de inicialización del LCD Display
  lcd.begin();
  lcd.clear();
  lcd.print("     ");
  lcd.print("!PONG!");
  lcd.setCursor(0, 1);
  lcd.print("Elije un modo!!!");
  }

void loop() {
  
  //Se crean las variables tipo Sting necesarias para retornar en el monitor Serial de Arduino
  String w = "w";
  String s = "s";
  String u = "u";
  String down = "down";
  String pausa = "p";
  String volumen = "v";
  String color = "c";

  //Se definen variables de tipo booleanos dependiendo del botón que se presione y po medio del comando digitalRead
  int estado_w = digitalRead(boton_jugador1_arriba);
  int estado_s = digitalRead(boton_jugador1_abajo);
  int estado_up = digitalRead(boton_jugador2_arriba);
  int estado_down = digitalRead(boton_jugador2_abajo);
  int estado_p = digitalRead(boton_pausa);
  int estado_v = digitalRead(boton_volumen);
  int estado_c = digitalRead(boton_color);

  //variable que lee el monitor serial en busca de puntajes
  punto = Serial.read();

  //E: Valores booleanos de los digitalRead anteriores
  //S: Datos en el monitor serial de Arduino
  //R: Ninguna

  //Casos para el control 1
  if (estado_w == 1){
    Serial.println(w);
    delay(45);
  }
  if (estado_s == 1){
    Serial.println(s);
    delay(45);
  }

  //Casos para el control 2
  if (estado_up == 1){
    Serial.println(u);
    delay(50);
  }
  if (estado_down == 1){
    Serial.println(down);
    delay(50);
  }

  //Casos para la consola, pausa, volumen y color respectivamente
  if (estado_p == 0){
    Serial.println(pausa);
    delay(300);
  }
  if (estado_v == 0){
    Serial.println(volumen);
    delay(300);
  }
  if (estado_c == 0){
    Serial.println(color);
    delay(300);
  }

  //Casos para los puntajes a ser mostrados en el LCD Display

  //Caso de ganador
  if (punto == 90){
    lcd.clear();
    lcd.print("!!Felicidades!!");
    }

  //Caso en el que el marcador empieza en cero
  if (punto == 48){
    lcd.clear();
    lcd.print("Jugador 1: 0");
    lcd.setCursor(0, 1);
    lcd.print("Jugador 2: 0");
    p1 = 0;
    p2 = 0;
  }

  //Caso en el que el jugador 1 anota un punto
  if ((punto == 33) || (punto == 49) || (punto == 50) || (punto == 51) || (punto == 52) || (punto == 53) || (punto == 54) || (punto == 55) || (punto == 56) || (punto == 57)){
    p1 += 1;
    lcd.clear();
    lcd.print("Jugador 1: " + String(p1));
    lcd.setCursor(0, 1);
    lcd.print("Jugador 2: " + String(p2));
  }

  //Caso en el que el jugador 2 anota un punto
  if ((punto == 65) || (punto == 66) || (punto == 67) || (punto == 68) || (punto == 69) || (punto == 70) || (punto == 71) || (punto == 72) || (punto == 73) || (punto == 74)){
    p2 += 1;
    lcd.clear();
    lcd.print("Jugador 1: " + String(p1));
    lcd.setCursor(0, 1);
    lcd.print("Jugador 2: " + String(p2));
  }
}
