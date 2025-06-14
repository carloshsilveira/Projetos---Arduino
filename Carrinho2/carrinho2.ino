#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class DCMotor {
  int spd = 255, pin1, pin2;

public:
  void Pinout(int in1, int in2) {
    pin1 = in1;
    pin2 = in2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void Speed(int vel) {
    spd = vel;
  }

  void Forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  void Backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  void Stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

DCMotor Motor1;
DCMotor Motor2;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int potPin = A0;

int tempoSegundos = 1;
int tempoAnterior = -1;

unsigned long tempoUltimaMudanca = 0;
const unsigned long tempoConfirmacao = 5000; // 3 segundos de estabilidade

bool cicloExecutado = false;

void setup() {
  lcd.init();
  lcd.backlight();

  Motor1.Pinout(5, 6);
  Motor2.Pinout(8, 7);
  Motor1.Speed(255);
  Motor2.Speed(255);

  lcd.setCursor(0, 0);
  lcd.print("Ajuste o tempo:");
}

void loop() {
  int leitura = analogRead(potPin);
  int tempoAtual = map(leitura, 0, 1023, 1, 30); // segundos inteiros

  if (tempoAtual != tempoAnterior) {
    tempoAnterior = tempoAtual;
    tempoUltimaMudanca = millis();
    cicloExecutado = false;

    lcd.setCursor(0, 1);
    lcd.print("Tempo: ");
    lcd.print(tempoAtual);
    lcd.print(" s   ");
  }

  // Se o tempo ficou estável por 3s e ainda não executou o ciclo
  if (!cicloExecutado && millis() - tempoUltimaMudanca >= tempoConfirmacao) {
    tempoSegundos = tempoAtual;
    cicloExecutado = true;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Executando por:");
    lcd.setCursor(0, 1);
    lcd.print(tempoSegundos);
    lcd.print(" segundos");

    Motor1.Backward();
    Motor2.Backward();
    delay(tempoSegundos * 1000);
    Motor1.Stop();
    Motor2.Stop();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ciclo concluido!");
    lcd.setCursor(0, 1);
    lcd.print("Novo ajuste...");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ajuste o tempo:");
  }

  delay(100);
}