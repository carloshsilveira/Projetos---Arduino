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
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long tempoMotorMs = 4000; // Tempo que o motor ficará ligado (em milissegundos)

void setup() {
  lcd.init();
  lcd.backlight();

  // Mensagem inicial e delay de 5 segundos
  lcd.setCursor(2, 0);
  lcd.print("Iniciando... ");
  lcd.setCursor(0, 1);
  lcd.print("Intervalo: ");
  lcd.print(tempoMotorMs / 1000);
  lcd.print("s");
  delay(5000); // Caso queira mudar o tempo de delay para iniciar basta mudar nessa linha

  // Mensagem de tempo de funcionamento
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Intervalo: ");
  lcd.print(tempoMotorMs / 1000);
  lcd.print("s");

  // Controle do motor
  Motor1.Pinout(5, 6);
  Motor1.Speed(255);
  Motor1.Backward();
  delay(tempoMotorMs);
  Motor1.Stop();

  // Mensagem de conclusão
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Concluido...");
  lcd.setCursor(0, 1);
  lcd.print("Intervalo: ");
  lcd.print(tempoMotorMs / 1000);
  lcd.print("s");
}

void loop() {
}

