#include <string.h>

#include "classificacao.h"

const int BTN = 2;
const int POT = A0;
const int LED_ALARME = 8;

unsigned long amostra = 0;

void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED_ALARME, OUTPUT);
  digitalWrite(LED_ALARME, LOW);

  Serial.begin(9600);
  Serial.println("amostra,botao,bruto,pct,tempC,estado");
}

void loop() {
  const bool botao = digitalRead(BTN) == LOW;
  const int bruto = analogRead(POT);
  const float pct = 100.0f * bruto / 1023.0f;
  const float tempC = pct;  // Grandeza simulada pelo potenciometro: 0 a 100 °C.
  const char* estado = classificar(pct);

  // O LED indica exclusivamente o estado PERIGO; o botao apenas e registrado.
  digitalWrite(LED_ALARME,
               strcmp(estado, "PERIGO") == 0 ? HIGH : LOW);

  Serial.print(amostra++);
  Serial.print(',');
  Serial.print(botao);
  Serial.print(',');
  Serial.print(bruto);
  Serial.print(',');
  Serial.print(pct, 2);
  Serial.print(',');
  Serial.print(tempC, 2);
  Serial.print(',');
  Serial.println(estado);

  delay(500);
}
